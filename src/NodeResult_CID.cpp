/*
 * NodeResult_CID.cpp - The Garnata Retrieval System
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

#include "NodeResult_CID.h"
#include <iostream>
// ==================================================================

NodeResult_CID::NodeResult_CID(Unit* _u, float w=0.0f) :
  NodeResult_ID(_u, w) { }

// ==================================================================

void NodeResult_CID::computeUtilities()
{

  if (descendant != 0) // node is not a leaf node
  {
    float prob_desc = descendant->getProb();
    EU_plus = prob*prob_desc*v_r_plus_u_plus_u_plus + prob*(1.0f - prob_desc)*v_r_plus_u_plus_u_minus +
    	(1.0f-prob)*prob_desc*v_r_plus_u_minus_u_plus + (1.0f-prob)*(1.0f-prob_desc)*v_r_plus_u_minus_u_minus;
    EU_minus = prob*prob_desc*v_r_minus_u_plus_u_plus + prob*(1.0f - prob_desc)*v_r_minus_u_plus_u_minus +
    	(1.0f-prob)*prob_desc*v_r_minus_u_minus_u_plus + (1.0f-prob)*(1.0f-prob_desc)*v_r_minus_u_minus_u_minus;
  } else {
    EU_plus = prob*v_r_plus_u_plus_u_minus + (1.0f - prob)*v_r_plus_u_minus_u_minus;
    EU_minus = prob*v_r_minus_u_plus_u_minus + (1.0f - prob)*v_r_minus_u_minus_u_minus;
  }
  
}

// ==================================================================

float NodeResult_CID::v_r_plus_u_plus_u_plus = 0.0f;

// ==================================================================

float NodeResult_CID::v_r_plus_u_plus_u_minus = 0.0f;

// ==================================================================

float NodeResult_CID::v_r_plus_u_minus_u_plus = 0.0f;

// ==================================================================

float NodeResult_CID::v_r_plus_u_minus_u_minus = 0.0f;

// ==================================================================

float NodeResult_CID::v_r_minus_u_plus_u_plus = 0.0f;

// ==================================================================

float NodeResult_CID::v_r_minus_u_plus_u_minus = 0.0f;

// ==================================================================

float NodeResult_CID::v_r_minus_u_minus_u_plus = 0.0f;

// ==================================================================

float NodeResult_CID::v_r_minus_u_minus_u_minus = 0.0f;

// ==================================================================

void NodeResult_CID::getListOfDescendants(vector<NodeResult_CID*>& v) const
{
  NodeResult_CID* current = (NodeResult_CID*) descendant;
  while (current != 0)
  {
    v.push_back(current);
    current = (NodeResult_CID*) current->getDescendant();
  }
}

// ==================================================================



