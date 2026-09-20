/*
 * NodeTree.cpp - The Garnata Retrieval System
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
