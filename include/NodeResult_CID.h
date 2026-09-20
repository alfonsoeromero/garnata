/*
 * NodeResult_CID.h - The Garnata Retrieval System
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

#ifndef __NODERESULT_CID_H__
#define __NODERESULT_CID_H__

#include "Unit.h"
#include "NodeResult.h"
#include "NodeResult_ID.h"
#include <utility>

class NodeResult_CID : public NodeResult_ID {
  public:
     /** Main constructor 
    @param u unit
    @param w weight of the unit
    */
    NodeResult_CID(Unit* _u, float w);
 
    /** Return one node's list of descendants
    @param v list to return
    */
    void getListOfDescendants(vector<NodeResult_CID*>& v) const;

    /** Compute the two utilities of the node */
    void computeUtilities();
    
    /** Utility of retrieving a unit being relevant itself
    and being relevant its descendant */
    static float v_r_plus_u_plus_u_plus;
    
    /** Utility of retrieving a unit being relevant itself
    and not being relevant its descendant */
    static float v_r_plus_u_plus_u_minus;
    
    /** Utility of retrieving a unit not being relevant 
    and being relevant its descendant */
    static float v_r_plus_u_minus_u_plus;
    
    /** Utility of retrieving a unit not being relevant 
    and not being relevant its descendant */
    static float v_r_plus_u_minus_u_minus;
    
    /** Utility of not retrieving a unit being relevant
    and being relevant its descendant */
    static float v_r_minus_u_plus_u_plus;
    
    /** Utility of not retrieving a unit being relevant
    and not being relevant its descendant */
    static float v_r_minus_u_plus_u_minus;
    
    /** Utility of not retrieving a unit not being relevant
    and being relevant its descendant */
    static float v_r_minus_u_minus_u_plus;
    
    /** Utility of not retrieving a unit not being relevant
    and not being relevant its descendant */
    static float v_r_minus_u_minus_u_minus;    
};


#endif

// ==================================================================

