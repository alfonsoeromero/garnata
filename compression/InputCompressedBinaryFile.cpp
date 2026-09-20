/*
 * InputCompressedBinaryFile.cpp - The Garnata Retrieval System
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

#include "InputCompressedBinaryFile.h"

// ===========================================================================

InputCompressedBinaryFile::InputCompressedBinaryFile () {}

// ===========================================================================

void InputCompressedBinaryFile::open (const string& name)
{
  BasicInputBinaryBuffer::open (name, 1024);
}

// ===========================================================================

InputCompressedBinaryFile::InputCompressedBinaryFile (const string& name)
	: BasicInputBinaryBuffer (name, 1024) {  }

// ===========================================================================

void InputCompressedBinaryFile::readFloat (float& f) 
{
  ca->deflateFloat(f, this->clearBaseAddress() );
}

// ===========================================================================

void InputCompressedBinaryFile::readUnsigned (unsigned& u) 
{
  ca->deflateUnsigned(u, this->clearBaseAddress() );
}

// ===========================================================================

void InputCompressedBinaryFile::readLong(long& l) 
{
  ca->deflateLong(l, this->clearBaseAddress() );
}

// ===========================================================================

void InputCompressedBinaryFile::readUnsignedList(vector<unsigned>& array)
{
  unsigned _size;
  readUnsigned (_size);
  array = vector<unsigned>(_size);
  //for_each(array.begin(), array.end(), bind1st(mem_fun(&InputCompressedBinaryFile::readUnsigned), this));
  for (vector<unsigned>::iterator it=array.begin(), end=array.end(); it != end; ++it)
	  this->readUnsigned(*it);
}

// ===========================================================================

void InputCompressedBinaryFile::readFloatList(vector<float>& array)
{
  unsigned _size;
  readUnsigned (_size);
  array = vector<float>(_size);
  //for_each(array.begin(), array.end(), bind1st(mem_fun(&InputCompressedBinaryFile::readFloat), this));
  for (vector<float>::iterator it=array.begin(), end=array.end(); it != end; ++it)
	  this->readFloat(*it);
}

// ===========================================================================

void InputCompressedBinaryFile::readLongList(vector<long>& array)
{
  unsigned _size;
  readUnsigned (_size);
  array = vector<long>(_size);
  //for_each(array.begin(), array.end(), bind1st(mem_fun(&InputCompressedBinaryFile::readLong), this));
  for (vector<long>::iterator it=array.begin(), end=array.end(); it != end; ++it)
	  this->readLong(*it);
}

// ===========================================================================

void InputCompressedBinaryFile::readSortedUnsignedList(vector<unsigned>& array, bool ascending)
{
  readUnsignedList(array);
  
  // we compute element differences
  partial_sum (array.begin(), array.end(), array.begin() );
  
  if (!ascending) std::reverse(array.begin(), array.end());
}

// ===========================================================================

void InputCompressedBinaryFile::readSortedLongList(vector<long>& array, bool ascending)
{
  readLongList(array);
  
  // we compute element differences
  partial_sum (array.begin(), array.end(), array.begin());
  
  if (!ascending) std::reverse(array.begin(), array.end());
}

// ===========================================================================

void InputCompressedBinaryFile::readBoundedLongList(vector<long>& array)
{

  long mini;
  readLong(mini);
  readLongList(array);
  
  std::transform(array.begin(), array.end(), array.begin(), bind2nd(plus<long>(), mini));
}

// ===========================================================================

InputCompressedBinaryFile::~InputCompressedBinaryFile () {}

// ===========================================================================

void InputCompressedBinaryFile::setCompressionAlgorithm (CompressionAlgorithm* _ca)
{
  ca = _ca;
}

// ===========================================================================

bool InputCompressedBinaryFile::rePosition (long newPos)
{
  return BasicInputBinaryBuffer::rePosition(newPos);
}

// ===========================================================================

CompressionAlgorithm* InputCompressedBinaryFile::ca = 0;

// ===========================================================================



