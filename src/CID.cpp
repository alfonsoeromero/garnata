/*
 * CID.cpp - The Garnata Retrieval System
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

#include "CID.h"


// ==================================================================

CID::CID ( const Collection& _c, const string& _identifier, RUM_mode _mode, bool normalize ) :
  ID<NodeResult_CID>(_c, _identifier, _mode, normalize) {}

// ==================================================================

void CID::specifyUtilities(float _v_r_plus_u_plus_u_plus, float _v_r_plus_u_plus_u_minus, 
    			float _v_r_plus_u_minus_u_plus, float _v_r_plus_u_minus_u_minus,
			float _v_r_minus_u_plus_u_plus, float _v_r_minus_u_plus_u_minus,
			float _v_r_minus_u_minus_u_plus, float _v_r_minus_u_minus_u_minus)
  {
    NodeResult_CID::v_r_plus_u_plus_u_plus = _v_r_plus_u_plus_u_plus;
    NodeResult_CID::v_r_plus_u_plus_u_minus = _v_r_plus_u_plus_u_minus;
    
    NodeResult_CID::v_r_plus_u_minus_u_plus = _v_r_plus_u_minus_u_plus;
    NodeResult_CID::v_r_plus_u_minus_u_minus = _v_r_plus_u_minus_u_minus;
    
    NodeResult_CID::v_r_minus_u_plus_u_plus = _v_r_minus_u_plus_u_plus;
    NodeResult_CID::v_r_minus_u_plus_u_minus = _v_r_minus_u_plus_u_minus;
    
    NodeResult_CID::v_r_minus_u_minus_u_plus = _v_r_minus_u_minus_u_plus;
    NodeResult_CID::v_r_minus_u_minus_u_minus = _v_r_minus_u_minus_u_minus;
  }

