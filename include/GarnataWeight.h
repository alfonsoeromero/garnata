/*
 * GarnataWeight.h - The Garnata Retrieval System
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

#ifndef __GARNATA_WEIGHT_H__
#define __GARNATA_WEIGHT_H__

#include "Garnata.h"
#include <string>

using namespace std;

class GarnataWeight : public Garnata
{
  public:
    /** Empty constructor */
    GarnataWeight();
    
    /** Add a new weight file
    @param collectionName name of the collection
    @param indexName name of the index
    @param weightFileName name of the weight file
    @return ALL_OK if everything went OK 
    */
    int addWeights(string collectionName, string newIndexName, string weightFileName, int type);
    
    /** Inserts a weight file into an index
    @param collectionName name of the collection
    @param indexName name of the index
    @param weightFileName name of the weight file
    @return ALL_OK if everything went OK 
    */
    int insertWeights(string collectionName, string newIndexName, string weightFileName);
    
    /** Destructor */
    ~GarnataWeight(); 
};

#endif


