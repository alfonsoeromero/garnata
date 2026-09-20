/*
 * CID.h - The Garnata Retrieval System
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

#ifndef __CID_H__
#define __CID_H__

#include "NodeResult_CID.h"
#include "ID.h"

using namespace std;

class CID : public ID<NodeResult_CID> {
  public:
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    @param _mode mode to compute RSV
    @param normalize true if we are dividing RSV of each unit by its nIdf
    */
    CID ( const Collection& _c, const string& _identifier, RUM_mode _mode, bool normalize );
    
    
    /** Asess the four parameters of the model
    @param v_r_plus_u_plus_u_plus utility of retrieving the unit, being relevant and being relevant its descendant
    @param v_r_plus_u_plus_u_minus utility of retrieving the unit, being relevant and not being relevant its descendant
    
    @param v_r_plus_u_minus_u_plus utility of retrieving the unit, not being relevant and being relevant its descendant
    @param v_r_plus_u_minus_u_minus utility of retrieving the unit, not being relevant and not being relevant its descendant
    
    @param v_r_minus_u_plus_u_plus utility of not retrieving the unit, being relevant and being relevant its descendant
    @param v_r_minus_u_plus_u_minus utility of not retrieving the unit, being relevant and not being relevant its descendant
    
    @param v_r_minus_u_minus_u_plus utility of not retrieving the unit, not being relevant and being relevant its descendant
    @param v_r_minus_u_minus_u_minus utility of not retrieving the unit, not being relevant and not being relevant its descendant
    */
    static void specifyUtilities(float v_r_plus_u_plus_u_plus, float v_r_plus_u_plus_u_minus, 
    			float v_r_plus_u_minus_u_plus, float v_r_plus_u_minus_u_minus,
 			float v_r_minus_u_plus_u_plus, float v_r_minus_u_plus_u_minus,
			float v_r_minus_u_minus_u_plus, float v_r_minus_u_minus_u_minus);
};

#endif


