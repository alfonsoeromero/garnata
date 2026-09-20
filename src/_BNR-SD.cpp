/*
 * _BNR-SD.cpp - The Garnata Retrieval System
 * Copyright (C) 2005, 2026 Alfonso E. Romero
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "_BNR-SD.h"
#include <ctime>
#include "Globals.h"
#include "UnitReader.h"
#include "UnitCache.h"
#include "NodeGroup.h"
#include "NodeResult.h"
#include "NodeResult_SID.h"
#include "NodeResult_CID.h"

// ==================================================================

template <typename T>
_BNR_SD<T> :: _BNR_SD ( const Collection& _c, const string& _identifier ) :
 RetrievalModel (_c, _identifier), minWeight(0.0f)
 { }

// ==================================================================

template <typename T>
float _BNR_SD<T>::aggregate(float w1, float w2) const { return (w1 + w2); }

// ==================================================================

template <typename T>
void _BNR_SD<T>::propagateFinalUnits (const ProcessedQuery& pq, map<unsigned, T*>& N_final,
				     vector<NodeGroup<T> >& groups)
{
  const unsigned _size = pq.size(); 

  // For every term... we process its final units
  // The first term is processed alone
  {
    NodeGroup<T> n(pq[0]);
    
    Occurrence occ =  RetrievalModel::L->getTermFromId( pq[0] )->getOccurrence();
    const unsigned __size = occ.getNum();

    for (unsigned j=0; j<__size; ++j)
    {
      Unit* u = RetrievalModel::getFinalUnit(occ[j]);
      T* nr = new T(u, occ.getIWeight(j));
      if (!nr || !u) Globals::errorAndExit("ERROR: Not enough memory for 'nr' or 'u' (_BNR-SD::makeQuery), exiting");
      n.add(nr);
      N_final.insert( pair<unsigned, T*>(occ[j], nr) );
    }
    groups.push_back(n);
  }

  // We process the others terms in the query. This time
  // we search into memory for a unit before reading it from disk
  
  for (unsigned i=1; i<_size; ++i)
  {
    NodeGroup<T> n(pq[i]);
    Occurrence occ =  RetrievalModel::L->getTermFromId( pq[i] )->getOccurrence();
    const unsigned __size = occ.getNum();
    vector<pair<unsigned, T*> > toBeInserted;

    for (unsigned j=0; j<__size; ++j)
    {
      typename map<unsigned, T*>::iterator iter = N_final.find (occ[j]);      
      if (iter != N_final.end()) // the node existed...
      {
        *(iter->second) += occ.getIWeight(j);
	n.add(iter->second);
      }
      else 
      {
	Unit* u = RetrievalModel::getFinalUnit(occ[j]);
        T* nr = new T(u, occ.getIWeight(j));
        if (!nr || !u) Globals::errorAndExit("ERROR: Not enough memory for 'nr' or 'u' (_BNR-SD::makeQuery), exiting");
        toBeInserted.push_back(pair<unsigned,T*>(occ[j], nr));
	n.add(nr);
      }
    }
        
    for (typename vector< pair<unsigned, T*> >::const_iterator it=toBeInserted.begin(), end=toBeInserted.end(); it!=end; ++it)
      N_final.insert( *it );
    
    groups.push_back(n);
  }
}

// ==================================================================

template <typename T>
void _BNR_SD<T> :: propagateComplexUnits(const map<unsigned, T*>& N_final, map<unsigned, T*>& N_complex)
{
  // For every final unit, we propagate the probability
  for (typename map<unsigned, T*>::const_iterator it=N_final.begin(), end=N_final.end(); it!=end; ++it) 
  {
    // We take the current node..
    T* current = it->second;
    float prod = current->getProb();

    bool found = false;
    // Propagation finishes if current node is a root node, or if the node is found in the list
    // and it makes propagation itself without searching...

    while (!found && !current->isRoot())
    {
      prod *= current->getUnit()->getWeight();
      unsigned desc = current->getUnit()->getContainer();
      typename map<unsigned, T*>::iterator _it = N_complex.find(desc);
        
      if (_it != N_complex.end()) // the node existed...
      {
        current->setDescendant(_it->second);
        // Propagation along the descendants
        _it->second->propagate(prod);
        found = true;
      } else { 
        // we create a new node...
        Unit* u = RetrievalModel::getComplexUnit( desc );
        T* nr = new T(u, prod);
        if (!nr || !u) Globals::errorAndExit("ERROR: Not enough memory for 'nr' or 'u' (_BNR-SD::makeQuery), exiting");
          
        N_complex.insert( pair<unsigned, T*>(desc, nr) );
        // we set it as the descendant of the current node
        
        current->setDescendant(nr);

        // the current node is now the descendant..
        current = nr;
      }
      rootNodes.push_back ( current ); // we add the root node to the vector of root nodes
    }// while
  }// for

}

// ==================================================================

template <typename T>
void _BNR_SD<T>:: makeListOfNodes (vector<T*>& vec, 
	map<unsigned, T*> N_final,
	map<unsigned, T*> N_complex)
{
  // =================== we add prior probabilites =========================================
  const float p0 = 1.0f/RetrievalModel::L->getNum();
  const float oneMinusp0 = 1.0f - p0;
  //unsigned j=0;

//  vec = vector < T* > (N_final.size() + N_complex.size());
  vec = vector <T*>();

  // ================== 4th step: clearing of the maps and filling of the vector =====================
  
  for (typename map<unsigned, T*>::const_iterator it=N_final.begin(), _end=N_final.end(); it!=_end; ++it)
  {
    if (it->second->getUnit()->isRetrievable())
    {
      it->second->setProb( p0 + oneMinusp0 * (it->second->getProb()) );
      //vec[j++] = it->second;
      vec.push_back(it->second);
    } else delete it->second;
  }

  N_final.clear();
  N_final.swap(N_final);

  for (typename map<unsigned, T*>::const_iterator it=N_complex.begin(), _end=N_complex.end(); it!=_end; ++it)
  {
    if (it->second->getUnit()->isRetrievable())
    {
      it->second->setProb( p0 + oneMinusp0 * (it->second->getProb()) );
      //vec[j++] = it->second;
      vec.push_back(it->second);
    } else delete it->second;
  }
  
  N_complex.clear();
  N_complex.swap(N_complex);
}

// ==================================================================

template <typename T>
_BNR_SD<T> :: ~_BNR_SD () { }

// ==================================================================

template <typename T>
void _BNR_SD<T>::buildResult(vector<Result>& res, vector<T*>& vec, DTD* current)
{
  vector <string> files = c.getFiles();
  
  for (typename vector<T*>::iterator it=vec.begin(), end=vec.end(); 
       it != end; ++it)
  {
    res.push_back( Result ( files[(*it)->getUnit()->getFile()], 
                            ((UnitReader*)((*it)->getUnit()))->getRoute(current), 
			    (*it)->getRSV() ) );

    if(*it!=0) delete *it;
  }
  
  vec.clear();
  vec.swap(vec);
}

// ==================================================================

template <typename T>
void _BNR_SD<T>::cutDownNodeResultVector (vector<T*>& vec)
{
  // if we were limitating the number of resulting documents to a
  // certain number, we reduce the vector
  if (vec.size() > NUMDOCS)
  {
     for (unsigned i=NUMDOCS, last=vec.size(); i!=last; ++i)
       if(vec[i]!=0) delete vec[i];

     vec = vector<T*> (vec.begin(), vec.begin() + NUMDOCS);
     vec.swap(vec);
  } 

  if (minWeight != 0.0f)
  {
    unsigned i=0;
    for (unsigned __size=vec.size() ; i<__size && vec[i]->getProb()>minWeight; ++i) 
       ;
       
    for (unsigned j=i, __size=vec.size(); j<__size; ++j)
      delete vec[j];
    vec = vector<T*> (vec.begin(), vec.begin() + i); 
    vec.swap(vec);
  }
}

// ==================================================================

template class _BNR_SD<NodeResult>;
template class _BNR_SD<NodeResult_SID>;
template class _BNR_SD<NodeResult_CID>;


