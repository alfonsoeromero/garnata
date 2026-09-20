/*
 * BasicOutputBinaryBuffer.cpp - The Garnata Retrieval System
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

#include "BasicOutputBinaryBuffer.h"
#include <cassert>

// ===========================================================================

BasicOutputBinaryBuffer::BasicOutputBinaryBuffer() {}

// ===========================================================================

BasicOutputBinaryBuffer::BasicOutputBinaryBuffer(const string& name, unsigned _SIZE) :
  SIZE(_SIZE), buffer(new char[_SIZE]), pos(0), file(name.c_str(), ios::out | ios::binary)
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
  }
  
// ===========================================================================

void BasicOutputBinaryBuffer::open(const string& name, unsigned _SIZE)
{
  SIZE = _SIZE;
  pos = 0;
  buffer = new char[SIZE];

  if (!buffer)
  {
    cerr << "Error: not enough memory (BasicOutputBinaryBuffer::BasicOutputBinaryBuffer)\n";
    exit(-1);
  }

  file.open(name.c_str(), ios::out | ios::binary );
  if (file.fail())
  {
    cerr << "Error creating file " << name << ". Disk full or read-only media\n";
    exit(-1);
  }

}

// ===========================================================================

inline void BasicOutputBinaryBuffer::flush()
{
  file.write ((char*) buffer, pos);
  pos = 0;
}

// ===========================================================================

void BasicOutputBinaryBuffer::writeByte(char byte)
{
  buffer[pos++] = byte;
  if (pos == SIZE) flush();
}

// ===========================================================================

void BasicOutputBinaryBuffer::writeBytes(unsigned num, char* bytes)
{
  assert(num <= SIZE);

  if (pos + num >= SIZE)
    flush();
  
  std::copy(bytes, bytes+num, buffer + pos);
  pos += num;
}

// ===========================================================================

void BasicOutputBinaryBuffer::rePosition(long newPos)
{
  if (pos) flush();
  
  file.seekp(newPos, std::ios::beg);
}

// ===========================================================================

BasicOutputBinaryBuffer::~BasicOutputBinaryBuffer()
{
  if (pos) flush();
	
  if (buffer)
    delete [] buffer;
}

// ===========================================================================

