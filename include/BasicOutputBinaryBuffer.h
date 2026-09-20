/*
 * BasicOutputBinaryBuffer.h - The Garnata Retrieval System
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

#ifndef __BASIC_OUTPUT_BINARY_BUFFER__
#define __BASIC_OUTPUT_BINARY_BUFFER__

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class BasicOutputBinaryBuffer 
{
  private:
    /** maximum size of the buffer */
    unsigned SIZE;
    
    /** buffer we are writing in */
    char* buffer;
    
    /** flushes current buffer to file */
    void flush();
    
  protected:
    /** writing position */
    unsigned pos; 
  
    /** file we are writing in */
    fstream file;
    
  public:
    /** Empty constructor */
    BasicOutputBinaryBuffer (); 

    /** Main constructor
    @param name name of the file we are writing in
    @param _SIZE size of the buffer
    */
    BasicOutputBinaryBuffer (const string& name, unsigned _SIZE);
    
    /** Writes a single byte into the buffer
    @param byte byte of data we want to write in
    */
    void writeByte(char byte);
    
    /**
    @param name name of the file we are writing to
    @param _SIZE size of the buffer
    */    
    void open (const string& name, unsigned _SIZE); 

    /** Writes several bytes to the buffer
    @param num number of bytes to write in
    @param bytes array of bytes we want to write in
    @pre num must be less or equal than the size of the buffer
    */
    void writeBytes(unsigned num, char* bytes);
    
    /** Moves the file pointer to another position
    @param newPos new writing position 
    */
    void rePosition (long newPos);
    
    /** Destructor */
    virtual ~BasicOutputBinaryBuffer();
};

#endif


