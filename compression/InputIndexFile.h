/*
 * InputIndexFile.h - The Garnata Retrieval System
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

#ifndef __INPUT_INDEX_FILE__
#define __INPUT_INDEX_FILE__

#include <string>
#include "BasicInputBinaryBuffer.h"

template <typename T>
class InputIndexFile : private BasicInputBinaryBuffer
{
  public:
    /** Empty constructor */
    InputIndexFile();
  
    /** Main constructor
        @param fileName name of the index file    
    */
    InputIndexFile(const string& fileName);
    
    /** Accesing operator */
    T operator [] (unsigned i); 
    
    /** Opens an index file */
    void open(const string& fileName, unsigned SIZE);
  
    /** Destructor */
    ~InputIndexFile();  
    
  private:
    /** Next position we expect to write in */
    unsigned expectedPosition;
};

#endif


