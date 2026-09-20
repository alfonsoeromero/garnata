/*
 * BasicInputBinaryBuffer.h - The Garnata Retrieval System
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

#ifndef __BASIC_INPUT_BINARY_BUFFER__
#define __BASIC_INPUT_BINARY_BUFFER__

#include <fstream>
#include <iostream>

using namespace std;

class BasicInputBinaryBuffer {

  private:
    /** maximum size of the buffer */
    unsigned SIZE;
    
    /** reading position */
    unsigned pos;
    
    /** size of the buffer */
    unsigned BUFFER_SIZE;
    
    /** base address (for [] operator) */
    unsigned base;
    
    /** file we are reading from */
    fstream file;

    /** buffer we are reading from */
    char* buffer;
    
    /** number of bytes of the file */
    long FILE_SIZE;
    
    /** Reading position for the file */
    long readingPos;
    
    /** true if we have read the last file chunk */
    bool eof;
    
    /** refills the buffer with data at current file position */
    void refill();
    
  public:
    /** Empty constructor */
    BasicInputBinaryBuffer (); 
    
    /**
    @param name name of the file we are reading from 
    @param _SIZE size of the buffer
    */
    BasicInputBinaryBuffer (const string& name, unsigned _SIZE);
    
    /**
    @param name name of the file we are reading from
    @param _SIZE size of the buffer
    */    
    void open (const string& name, unsigned _SIZE); 
    
    /** Reads a single byte
    @param byteRead byte read
    @return true if it has been reached the end of file and the buffer
     (no more bytes to read)
    */
    bool readByte( char& byteRead );

    /** Moves the file pointer to another position
    @param newPos new reading position 
    @return false if position does not exist
    */
    bool rePosition (long newPos);
    
    /** Clears base address (for [] operator)
    @return a reference to itself
    */
    BasicInputBinaryBuffer& clearBaseAddress ();
    
    /** Uses binary buffer as an array
    @param i index to access the buffer
    */
    char operator[](unsigned i);
    
    /** Destructor */
    virtual ~BasicInputBinaryBuffer (); 
};

#endif


