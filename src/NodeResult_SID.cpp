/*
 * NodeResult_SID.cpp - The Garnata Retrieval System
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


