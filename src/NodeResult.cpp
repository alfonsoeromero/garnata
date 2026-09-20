/*
 * NodeResult.cpp - The Garnata Retrieval System
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

