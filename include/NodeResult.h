/*
 * NodeResult.h - The Garnata Retrieval System
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

#ifndef __NODERESULT_H__
#define __NODERESULT_H__

#include "Unit.h"
#include <utility>
#include <vector>

class NodeTree;

class NodeResult {
  protected:
    /** Associated unit */
    Unit* u;
    
    /** Probability */
    float prob;

    /** Node's only descendant */
    NodeResult* descendant;
    
    /** Units contained by this one */
    vector<NodeTree *> contained;

    /** Pointer to the correnpondent root node */
    NodeTree* root;

    
  public:
    /** Main constructor 
    @param u unit
    @param w weight of the unit
    */
    NodeResult(Unit* _u, float w);
    
    /** Copy constructor 
    @param n node to copy
    */
    NodeResult(const NodeResult& n);
  
    /** Adds a certain value to the node's probability
    @param p value to be added
    */
    const NodeResult& operator+=(float p);

    /** Assignment operator
    */
    const NodeResult& operator=(NodeResult& o);

    /** Returns node's probability
    @return the probability of the node
    */
    float getProb() const;
    
    /** Returns node's retrieval status value
    @return the value of the node
    */
    float getRSV() const;
    
    /** Sets node's probability
    @param f new probability of the node
    */
    void setProb(float f);
    
    /** Return one Node's unit
    @return associated unit
    */
    Unit* getUnit();
    
    /** Tells if the represented unit is root or not 
    @return true if the unit is root, false if not
    */
    bool isRoot() const;

    /** Sets only node's descendant
    @param n new descendant of the node
    */
    void setDescendant(NodeResult* n);

    /** Gets only node's descendant
    @return descendant of the node, 0 if any
    */
    NodeResult* getDescendant() const;

    /** Returns the root of the unit 
    @return root of the unit */
    NodeTree* getRoot () const;
    
    /** Propagates evidence associated to this node
    @param prod evidence to propagate
    */
    void propagate(float prod);

    /** Sets the root of the unit
    @param _root root of the unit */
    void setRoot (NodeTree* _root);

    /** Destructor */
    virtual ~NodeResult();
};


#endif

// ==================================================================

