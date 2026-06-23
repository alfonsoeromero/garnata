#include "NodeTree.h"
#include <iostream>

// ==================================================================

NodeTree::NodeTree(unsigned _id, unsigned _tagType) : 
   id(_id+1), tagType(_tagType), _depth(0), container(0), u(0) 
   { }

// ==================================================================

NodeTree::NodeTree(const NodeTree& n) : 
  id(n.id), tagType(n.tagType), container(n.container),  
  u(n.u), _depth(n._depth), contained(n.contained) 
  { }

// ==================================================================

void NodeTree::setRoot() { container = 0; _depth = 1; }

// ==================================================================

void NodeTree::setRoot(NodeTree* _root) { root = _root; }

// ==================================================================

Unit* NodeTree::getUnit() const { return u; }

// ==================================================================

void NodeTree::setUnit(Unit* _u) { u = _u; }

// ==================================================================

unsigned NodeTree::getId() const { return id - 1; }

// ==================================================================

NodeTree* NodeTree::getContainer() const { return container; }

// ==================================================================

void NodeTree::setContainer(NodeTree* mycontainer) 
  { 
    container = mycontainer;
    _depth = mycontainer->depth() + 1;
  }

// ==================================================================

vector<unsigned> NodeTree::getPathToRoot() const
{
  vector<unsigned> tmp;
  NodeTree* current = const_cast<NodeTree*>(this);
  
  do {
    tmp.push_back(current->getId());
    current = current->getContainer();
  } while (current != 0);

  return tmp;
}

// ==================================================================

vector<unsigned> NodeTree::_getContained() const
{
  unsigned sz = contained.size();
  vector<unsigned> tmp (sz);
  for (unsigned i=0; i<sz; ++i)
    tmp[i] = contained[i]->getId();

  return tmp;
}

// ==================================================================

void NodeTree::addContained(NodeTree* n)
{
  this->contained.push_back(n);
}

// ==================================================================

unsigned NodeTree::getTagType () const { return tagType; }

// ==================================================================

vector<NodeTree *> NodeTree::getContained () const { return contained; }

// ==================================================================

unsigned NodeTree::depth() const
{
  return _depth;
}

// ==================================================================

NodeTree::~NodeTree()
{
   if (u) delete u;
}

// ==================================================================
