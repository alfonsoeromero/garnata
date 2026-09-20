/*
 * OutputCompressedBinaryFile.h - The Garnata Retrieval System
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

#ifndef __OUTPUT_COMPRESSED_BINARY_FILE__
#define __OUTPUT_COMPRESSED_BINARY_FILE__

#include "BasicOutputBinaryBuffer.h"
#include "CompressionAlgorithm.h"
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class OutputCompressedBinaryFile : public BasicOutputBinaryBuffer
{
  private:
    /** Compression algorithm we are using */
    static CompressionAlgorithm* ca;

  public:
    /** Writes a single unsigned into the file
    @param u unsigned to write in
    @pre compression algorithm must be initiated
    */
    void writeUnsigned(unsigned u);
    
    /** Writes a single float into the file
    @param f float to write in
    */
    void writeFloat (float f);
    
    /** Writes a single long into the file
    @param l long to write in
    @pre compression algorithm must be initiated
    */
    void writeLong (long l);
    
    /** Empty constructor */
    OutputCompressedBinaryFile ();  

    /** Main constructor
    @param name Name of the file
    */
    OutputCompressedBinaryFile (const string& name);
  
    /** Opens a file
    @param name name of the file    
    @param _SIZE size of the buffer
    */
    void open(const string& name, unsigned _SIZE);

    /** Writes a list of unsigned to the file
    @param array list of unsigned to write in
    @pre compression algorithm must be initiated
    */
    void writeUnsignedList(const vector<unsigned>& array);
    
    /** Writes a list of floats to the file
    @param array list of floats to write in
    */
    void writeFloatList(const vector<float>& array);
    
    /** Writes a list of longs to the file
    @param array list of longs to write in
    @pre compression algorithm must be initiated
    */
    void writeLongList(const vector<long>& array);
    
    /** Writes a sorted list of integers
    @param array list of integers to write in
    @param ascending must be true if the list is ascending, false if descending
    @pre compression algorithm must be initiated
    */
    void writeSortedUnsignedList(const vector<unsigned>& array, bool ascending);

    /** Writes a sorted list of longs
    @param array list of longs to write in
    @param ascending must be true if the list is ascending, false if descending
    @pre compression algorithm must be initiated
    */
    void writeSortedLongList(const vector<long>& array, bool ascending);
    
    
    /** Writes a list that is bounded by a minimum positive value
    @param array list of longs to write in    
    */
    void writeBoundedLongList(const vector<long>& array);
    
    /** Return current stream's position
    @return long with the position
    */
    long getPosition();
    
    /** Initiates the compression algorithm
    @param _ca compression algorithm to use
    */
    static void setCompressionAlgorithm (CompressionAlgorithm* _ca);
    
    /** Destructor */
    ~OutputCompressedBinaryFile ();
};

#endif


