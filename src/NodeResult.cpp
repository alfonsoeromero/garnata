#include "NodeResult.h"
#include <iostream>

NodeResult::NodeResult(Unit* _u, float w=0.0f) :
  u(_u), prob(w), descendant(0) { }

// ==================================================================

NodeResult::NodeResult(const NodeResult& n) : u(n.u), prob(n.prob), descendant(n.descendant) { }
  
// ==================================================================

const NodeResult& NodeResult::operator=(NodeResult& n)
{
  u = n.getUnit();
  prob = n.getProb(); 
  descendant = n.getDescendant();
  return (*this);
}

// ==================================================================

const NodeResult& NodeResult::operator+=(float p)
{
  prob += p;
  return (*this);
}

// ==================================================================

bool NodeResult::isRoot() const
{
  return (u->getPosition() == 0);
}

// ==================================================================

float NodeResult::getProb() const { return prob; }

// ==================================================================

float NodeResult::getRSV() const { return prob; }

// ==================================================================

Unit* NodeResult::getUnit() { return u; }

// ==================================================================

void NodeResult::setProb(float f) { prob = f; }

// ==================================================================

void NodeResult::setDescendant(NodeResult* nod) 
{ 
  descendant = nod; 
}

// ==================================================================

NodeResult* NodeResult::getDescendant() const { return descendant; }

// ==================================================================

void NodeResult::propagate(float prod)
{
  prob += prod;

  if (descendant!=0)
    descendant->propagate ( prod * u->getWeight() );
}

// ==================================================================

NodeResult::~NodeResult() 
{ 
 if (u!=0 && !u->isInCache()) 
   delete u;
}

// ==================================================================

