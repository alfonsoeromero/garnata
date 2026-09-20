/*
 * BasicInputBinaryBuffer.cpp - The Garnata Retrieval System
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

#include <cstdlib>
#include "BasicInputBinaryBuffer.h"

// ===========================================================================

BasicInputBinaryBuffer::BasicInputBinaryBuffer () { ; }


// ===========================================================================

void BasicInputBinaryBuffer::open(const string& name, unsigned _SIZE)
{
  SIZE = _SIZE;
  pos = 0;
  base = 0;
  file.open(name.c_str(), ios::in | ios::binary);
  buffer = new char [SIZE];
  eof = false;
  
  if (file.fail())
  {
    cerr << "Error creating file " << name << ". Disk full or read-only media\n";
    exit(-1);
  }
  
  if (!buffer)
  {
    cerr << "Error: not enough memory (BasicInputBinaryBuffer::open)\n";
    exit(-1);
  }
  
  file.seekg (0, std::ios::end ); 
  FILE_SIZE = file.tellg();
  file.seekg (0, std::ios::beg );
  
  readingPos = 0;
  
  refill();  
}


// ===========================================================================

BasicInputBinaryBuffer::BasicInputBinaryBuffer (const string& name, unsigned _SIZE)
  : SIZE(_SIZE), pos(0), base(0), file(name.c_str(), ios::in | ios::binary), buffer(new char[_SIZE]), eof(false)
{
    if (file.fail())
    {
      cerr << "Error creating file " << name << ". Disk full or read-only media\n";
      exit(-1);
    }
    
    if (!buffer)
    {
      cerr << "Error: not enough memory (BasicOutputBinaryBuffer::BasicOutputBinaryBuffer)\n";
      exit(-1);
    }

    file.seekg( 0, std::ios::end ); 
    FILE_SIZE = file.tellg();
    file.seekg( 0, std::ios::beg );
    
    readingPos = 0;
    
    refill();
}

// ===========================================================================

void BasicInputBinaryBuffer::refill()
{
  pos = 0;
  long remainingBytes = FILE_SIZE - readingPos;
  if (remainingBytes >= (long)SIZE)
  {   
    file.read(buffer, SIZE);
    readingPos += SIZE;
    BUFFER_SIZE = SIZE;
    eof = false;
  } else {
    unsigned remnantBytes = (SIZE - base);
    std::copy (buffer + base, buffer + SIZE, buffer);
    base = 0;
    pos = remnantBytes;

    if ( remnantBytes + remainingBytes <= SIZE)
    {
      file.read(buffer + remnantBytes, remainingBytes);
      readingPos += remainingBytes;
      eof = true;
      BUFFER_SIZE = remainingBytes + remnantBytes;

    } else {
      unsigned bytesToRead = SIZE - remnantBytes;
      file.read(buffer + remnantBytes, bytesToRead);
      readingPos += bytesToRead;
      eof = false;
      BUFFER_SIZE = SIZE;
    }
  }
}

// ===========================================================================

bool BasicInputBinaryBuffer::readByte( char& byteRead )
{
  if (pos == BUFFER_SIZE) refill();
  

  if (!eof || pos < BUFFER_SIZE)
  {
    byteRead = buffer[pos++];
    return false;
  } else {
    return true;
  }

}

// ===========================================================================

bool BasicInputBinaryBuffer::rePosition (long newPos)
{
  if (newPos < FILE_SIZE) // everything is O.K.
  {
    file.seekg(newPos, std::ios::beg);
    readingPos = newPos;
    refill();
    return true;
  } else return false; 
}

// ===========================================================================

BasicInputBinaryBuffer& BasicInputBinaryBuffer::clearBaseAddress ()
{
  if (pos == BUFFER_SIZE) refill();
  base = pos;
  return (*this);
}

// ===========================================================================

char BasicInputBinaryBuffer::operator[](unsigned i)
{
   
  if (( (base + i) % SIZE ) == (pos % SIZE))
  {
    char tmp;
    readByte(tmp);
    return tmp;
  } else {
    cerr << "Error: only secuential access allowed (BasicInputBinaryBuffer::operator[])\n";
    exit(-1);
  }
}

// ===========================================================================

BasicInputBinaryBuffer::~BasicInputBinaryBuffer ()
{
    if (buffer)
	delete [] buffer;
}

// ===========================================================================


