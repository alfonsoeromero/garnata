#include "NodeGroup.h"
#include "NodeResult.h"
#include "NodeResult_SID.h"
#include "NodeResult_CID.h"
#include <cmath>

// ==================================================================

template <typename T>
NodeGroup<T>::NodeGroup(unsigned u): nIdf(0.0f)
{
  l = list<unsigned>();
  l.push_back(u);
}

// ==================================================================

template <typename T>
NodeGroup<T>::NodeGroup(const list<unsigned>& _l): l(_l), nIdf(0.0f)
{ }

// ==================================================================

template <typename T>
void NodeGroup<T>::normalize(float sum)
{
  nIdf /= sum;
}

// ==================================================================

template <typename T>
void NodeGroup<T>::computeNIdf(const Lexicon& L, unsigned NUM_UNITS)
{
  nIdf = 0.0f;
  for (list<unsigned>::const_iterator it=l.begin(), end=l.end(); it!=end; ++it)
  {
    Term* t = L.getTermFromId(*it);
    nIdf += log10f ((float) NUM_UNITS / (float) t->getNumDocs() );
  }
}

// ==================================================================

template <typename T>
float NodeGroup<T>::getNIdf() const 
  {  return nIdf; }
  
// ==================================================================

template <typename T>
void NodeGroup<T>::getNodes(vector<T*>& v)
{
  v = nodes;
}

// ==================================================================

template <typename T>
NodeGroup<T>::~NodeGroup() { }

// ==================================================================

template <typename T>
void NodeGroup<T>::add(T* n)
{
  nodes.push_back(n);
}

// ==================================================================

template class NodeGroup<NodeResult_SID>;
template class NodeGroup<NodeResult_CID>;
template class NodeGroup<NodeResult>;


