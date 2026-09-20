/*
 * BNR-SD.h - The Garnata Retrieval System
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

#ifndef __BNR_SD_H__
#define __BNR_SD_H__

#include "RetrievalModel.h"
#include "Result.h"
#include "NodeResult.h"
#include "NodeGroup.h"
#include "ProcessedQuery.h"
#include "_BNR-SD.h"
#include <vector>
#include <utility>

using namespace std;

class BNR_SD : public _BNR_SD <NodeResult> {
  public:
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    */
    BNR_SD ( const Collection& _c, const string& _identifier );
    
    /** Makes a query to the system
    @param pq 
    @return vector of pairs (document, weitght) 
            sorted by descending weight
    */
    vector< Result > makeQuery(const ProcessedQuery& pq);
};

#endif


