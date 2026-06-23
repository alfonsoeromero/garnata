#include "BNR-SD.h"
#include "ID.h"
#include <ctime>
#include <set>
#include <vector>
#include <queue>
#include <utility>
#include "Globals.h"
#include "UnitReader.h"
#include "NodeResult_SID.h"
#include "NodeResult_CID.h"

const bool globalIDF = true;


// ==================================================================

template<typename T>
ID<T> :: ID ( const Collection& _c, const string& _identifier, RUM_mode _mode, bool normalize ) :
 _BNR_SD<T> (_c, _identifier) 
 { 
   mode = _mode; 
   T::normalize = normalize;
 }

// ==================================================================

template<typename T>
vector< Result >  ID<T> ::makeQuery(const ProcessedQuery& pq)
{
   // lists with final units and complex units, respectively...
  map<unsigned, T*> N_final, N_complex;
  
  // if there are no terms in the query...
  if (!pq.size())
  {
    return vector < Result >();
  }  
  
  vector< NodeGroup<T> > groups;
    
  // ================= 1st step: we propagate probabilities to the final units ===================
  propagateFinalUnits(pq, N_final, groups);
  
  // =================== 2nd step: we propagate probabilities to the complex units ===================
  propagateComplexUnits(N_final, N_complex);
  
  // =================== 3rd step: we readjust probability values, and
  // =================== construct a list of nodes instead two maps  
  // RSV computation
  if (!globalIDF)
    computeNIdf(groups, *(_BNR_SD<T>::L) );
  else computeGlobalNIdf( groups, *(_BNR_SD<T>::L) );
  
  for (typename std::map<unsigned, T*>::iterator it=N_final.begin(), end=N_final.end(); it!=end; ++it)
  {
    it->second->computeUtilities();
    it->second->computeRSV(mode);
  }
  
  for (typename std::map<unsigned, T*>::iterator it=N_complex.begin(), end=N_complex.end(); it!=end; ++it)
  {
    (it->second)->computeUtilities();
    (it->second)->computeRSV(mode);
  }  
  
  // we pass the list of nodes to the vector
  vector<T*> vec;
  _BNR_SD<T>::makeListOfNodes(vec, N_final, N_complex);
  
  // we sort the vector by RSV of each unit
  partial_sort(vec.begin(), vec.begin() + std::min((unsigned)vec.size(), _BNR_SD<T>::NUMDOCS), vec.begin(), NodeResult_ID_Ptr<T>());
  
  // ================ 4th step: list is cut down, if needed =====================================
  cutDownNodeResultVector (vec);

  // ================ 6th step: building of the result =====================================
  vector<Result> res;
  buildResult(res, vec, _BNR_SD<T>::dtds->getDTDbyId(0) );
  
  // Return value
  return res;
}

// ==================================================================

template<typename T>
void ID<T>::computeGlobalNIdf(vector<NodeGroup<T> >& groups, const Lexicon& L)
{
  // 1.- NidfQs computation an normalization...
  float sum=0.0f;
  for (typename vector< NodeGroup<T> >::iterator it = groups.begin(), end=groups.end(); it!=end; ++it)
  {
    it->computeNIdf(*(_BNR_SD<T>::L), _BNR_SD<T>::NUMUNITS);
    sum += it->getNIdf();
  }

  map<unsigned, vector<bool> > groupsById;

  unsigned i=0;
  for (typename vector< NodeGroup<T> >::iterator it = groups.begin(), end=groups.end(); it!=end; ++it, ++i)
  {
    // we normalize the NIdf of the group, dividing it by the sum of nIdfs
    it->normalize(sum);

    // we retrieve the list of final Units
    vector<T*> finalUnits;
    it->getNodes(finalUnits);
    for (typename vector<T*>::const_iterator _it=finalUnits.begin(), _end=finalUnits.end(); _it!=_end; ++_it)
    {
      typename map<unsigned, vector<bool> >::iterator iter = groupsById.find ( (*_it)->getUnit()->getId() );
      if ( iter == groupsById.end() ) // the node did not exist
      {
        vector<bool> v(groups.size(), false);
        v[i] = true;
        groupsById.insert( pair<int, vector<bool> >((*_it)->getUnit()->getId(), v) );

      } else iter->second[i] = true;
    }
  }
   
  // 2.- For each root node, we compute its set of associated units AND
  //   for each unit, we compute its root unit AND
  //   for each root node, the list of groups

  for (typename vector<T*>::iterator it=_BNR_SD<T>::rootNodes.begin(), end=_BNR_SD<T>::rootNodes.end(); it!=end; ++it)
  {
    set<T*> myUnits;

    queue<T*> ascendants;
    ascendants.push(*it);

    vector<bool> v(groups.size(), false);

    do {
      T* tmp = ascendants.front();
      ascendants.pop();
      myUnits.insert(tmp);
      tmp->setRoot(*it);
      if (tmp->getUnit()->isFinal())
      {
        vector<bool> v2 = groupsById[tmp->getUnit()->getId()];
        for (unsigned i=0, n=groups.size(); i<n; ++i)
          v[i] = v[i] || v2[i];
      }

      vector<T*> v = tmp->getContained();
      for (typename vector<T*>::iterator vit=v.begin(), vend=v.end(); vit!=vend; ++vit)
        ascendants.push(*vit);

    } while (!ascendants.empty());

    double _nidf = 0.0;
    for (vector<bool>::const_iterator _it=v.begin(), _end=v.end(); _it!=_end; ++_it)
      if (*_it)  _nidf += groups[i].getNIdf();
    (*it)->addNIdf( _nidf ); // we add nidf for the root
    
    // we add it for all associated units
    for (typename set<T*>::iterator _it=myUnits.begin(), _end=myUnits.end(); _it!=_end; ++_it)
      (*_it)->addNIdf( _nidf );
  }
}


// ==================================================================

template<typename T>
void ID<T>::computeNIdf(vector<NodeGroup<T> >& groups, const Lexicon& L)
{
  // 1.- NidfQs computation an normalization...
  float sum=0.0f;
  for (typename vector< NodeGroup<T> >::iterator it = groups.begin(), end=groups.end(); it!=end; ++it)
  {
    it->computeNIdf(*(_BNR_SD<T>::L), _BNR_SD<T>::NUMUNITS);
    sum += it->getNIdf();
  }

  // 2.- NidfQs "propagation"...	
  for (typename vector<NodeGroup<T> >::iterator it = groups.begin(), end=groups.end(); it!=end; ++it)
  {
    // we normalize the NIdf of the group, dividing it by the sum of nIdfs
    it->normalize(sum);
    
    // we obtain the nIdf of the node
    float nIdf = it->getNIdf();
    
    // where we are going to retrieve the associated list of complex units
    set<T*> associatedUnits;    
    
    // we retrieve the list of final Units
    vector<T*> finalUnits;
    it->getNodes(finalUnits);
    
    // for every final unit, we add to the list of complex units its descendants
    for (typename vector<T*>::iterator _it=finalUnits.begin(), _end=finalUnits.end(); _it!=_end; ++_it)
    {
      vector<T*> descendants;
      (*_it)->getListOfDescendants(descendants);
      for (typename vector<T*>::const_iterator __it=descendants.begin(), __end=descendants.end(); __it!=__end; ++__it)
        associatedUnits.insert(*__it);
      
      // additionally, we add nIdf to corresponding final unit
      (*_it)->addNIdf( nIdf );
    }
    
    // we add nIdf to the entire list of complex units
    for (typename set<T*>::iterator _it=associatedUnits.begin(), _end=associatedUnits.end(); _it!=_end; ++_it)
      (*_it)->addNIdf( nIdf );
  }

}

// ==================================================================

template<typename T>
ID<T> :: ~ID () { }

// ==================================================================

template class ID<NodeResult_SID>;
template class ID<NodeResult_CID>;


