/*
 * OutputIndexFile.h - The Garnata Retrieval System
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

#ifndef __OUTPUT_INDEX_FILE__
#define __OUTPUT_INDEX_FILE__

#include <string>
#include "BasicOutputBinaryBuffer.h"

template<typename T>
class OutputIndexFile : private BasicOutputBinaryBuffer
{
  public:
    /** Empty constructor */
    OutputIndexFile ();
  
    /** Main constructor
        @param fileName name of the index file    
    */
    OutputIndexFile(const string& fileName);
    
    /** Accesing operator */
    OutputIndexFile& operator [] (unsigned i);
    
    /** opens a index file */
    void open (const string& fileName, unsigned SIZE);
    
    /** Equal operator */
    void operator=(T value);
  
    /** Destructor */
    ~OutputIndexFile();  
    
  private:
    /** Next position we expect to write in */
    unsigned expectedPosition;
    
    /** Position to write the value in */
    unsigned position;
    
    /** Writes a certain value in 
    a given position
    @param value value to write in
    @param pos position to write the value
    */
    void writeValue(unsigned pos, T value);
};

#endif


