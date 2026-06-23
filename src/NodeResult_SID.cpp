#include "NodeResult_SID.h"
#include <iostream>
// ==================================================================

NodeResult_SID::NodeResult_SID(Unit* _u, float w=0.0f) :
  NodeResult_ID(_u, w) { }

// ==================================================================

void NodeResult_SID::computeUtilities()
{
  EU_plus = prob * (v_r_plus_u_plus - v_r_plus_u_minus) + v_r_plus_u_minus;
  EU_minus = prob * (v_r_minus_u_plus - v_r_minus_u_minus) + v_r_minus_u_minus;
}

// ==================================================================

float NodeResult_SID::v_r_plus_u_plus = 0.0f;

// ==================================================================

float NodeResult_SID::v_r_plus_u_minus = 0.0f;

// ==================================================================

float NodeResult_SID::v_r_minus_u_plus = 0.0f;

// ==================================================================

float NodeResult_SID::v_r_minus_u_minus = 0.0f;

// ==================================================================

void NodeResult_SID::getListOfDescendants(vector<NodeResult_SID*>& v) const
{
  NodeResult_SID* current = (NodeResult_SID*) descendant;
  while (current != 0)
  {
    v.push_back(current);
    current = (NodeResult_SID*) current->getDescendant();
  }
}

// ==================================================================


