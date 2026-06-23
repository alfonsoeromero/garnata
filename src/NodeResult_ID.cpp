#include "NodeResult_ID.h"

// ==================================================================

NodeResult_ID::NodeResult_ID(Unit* _u, float w=0.0f) :
  NodeResult(_u, w), EU_plus(0.0f), EU_minus(0.0f), RSV(0.0f), nIdf(0.0f) { }

// ==================================================================

bool NodeResult_ID::shouldBeRetrieved() const
{  return EU_plus > EU_minus; } 

// ==================================================================

NodeResult_ID::NodeResult_ID(const NodeResult_ID& n) 
  : NodeResult(n), EU_plus(n.EU_plus), EU_minus(n.EU_minus), RSV(n.RSV) { }

// ==================================================================

void NodeResult_ID::operator*=(float f)
{
  RSV *= f;
}

// ==================================================================

const NodeResult_ID& NodeResult_ID::operator=(NodeResult_ID& n)
{
  u = n.getUnit();
  prob = n.getProb(); 
  descendant = n.getDescendant();
  EU_plus = n.EU_plus;
  EU_minus = n.EU_minus;
  RSV = n.RSV;
  return (*this);
}

// ==================================================================

void NodeResult_ID::computeRSV(RUM_mode r)
{
  switch(r)
  {
    case RUM_q:
      RSV = EU_plus / EU_minus;
      break;
    
    case RUM_d:
      RSV = EU_plus - EU_minus;
      break;
      
    case RUM_u:
    default:
      RSV = EU_plus;
  }
  
  if (normalize)
    RSV *= nIdf;
}

// ==================================================================

void  NodeResult_ID::addNIdf(float f)
{
  nIdf += f;
}

// ==================================================================

float NodeResult_ID::getRSV() const 
{ return RSV; }

// ==================================================================

bool NodeResult_ID::normalize = true;

// ==================================================================

NodeResult_ID::~NodeResult_ID() { }
