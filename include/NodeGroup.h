/*
 * NodeGroup.h - The Garnata Retrieval System
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

#ifndef __NODE_GROUP__
#define __NODE_GROUP__

#include <list>
#include "Lexicon.h"

template <typename T>
class NodeGroup 
{
  private:
    /**  List of identifiers of the group */
    list<unsigned> l;
    
    /** Associated final units */
    vector<T*> nodes;
    
    /**  nIdf of this group */
    float nIdf;
    
  public:
    /** Creates a node with a single 
    term identifier */
    NodeGroup(unsigned u);
  
    /** Creates a node with a list of  
    term identifiers */
    NodeGroup(const list<unsigned>& _l);
    
    /** Return node's idf
    @return one node's idf 
    */
    float getNIdf() const;
    
    /** Adds a final unit to the list of associated final units
    @param n final unit to add
    */
    void add(T* n);
    
    /** Return associated list of NodeResults
    @param v list to return
    */
    void getNodes(vector<T*>& v);
    
    /** Compute one node's idf
    @param L lexicon of the system
    */
    void computeNIdf(const Lexicon& L, unsigned NUM_UNITS);
    
    /** Normalize NIdf, dividing it by a certain value
    @param f parameter to divide the nidf by
    */
    void normalize(float f);
    
    /** Destructor */
    ~NodeGroup();
};

#endif


