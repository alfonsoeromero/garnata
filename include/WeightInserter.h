/*
 * WeightInserter.h - The Garnata Retrieval System
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

#ifndef __WEIGHTINSERTER_H__
#define __WEIGHTINSERTER_H__

using namespace std;

#include "IndexReader.h"
#include "Collection.h"
#include <string>
#include <fstream>

class WeightInserter : public IndexReader
{
  private:
    /** Process and writes a certain unit */
    void processUnit(unsigned id, float weight, fstream& fp) const;

  public:
    
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    */
    WeightInserter(const Collection& _c, string _identifier);

    /**
    Inserts a weight file in an Index
    @param fileName name of the weight file
    @return true if everything went OK, false if file is corrupt  
    */
    bool insert(string fileName);
    
    /** Destructor */
    ~WeightInserter();
};

#endif

