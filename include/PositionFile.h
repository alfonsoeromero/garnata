/*
 * PositionFile.h - The Garnata Retrieval System
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

#ifndef __PositionFile_H__
#define __PositionFile_H__

#include <vector>
#include <fstream>
#include <string>
#include "Globals.h"
#include "OutputCompressedBinaryFile.h"
#include "VariableByteCoder.h"

using namespace std;

class PositionFile {
  private:
    /** File to write in */
    OutputCompressedBinaryFile of;
  
  public:
    /** Main constructor 
    @param fileName name of the file 
    */
    PositionFile (const string& fileName, CompressionAlgorithm& ca);
  
    /** Adds a vector to the file
    @param v vector of positions
    @return offset of added vector
    */
    long add(const vector<unsigned>& v);
    
    /** Destructor */
    ~PositionFile();
};

#endif

