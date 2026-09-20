/*
 * OutputIndexFile.cpp - The Garnata Retrieval System
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

#include "OutputIndexFile.h"

// ==============================================================================

template <typename T>
void OutputIndexFile<T>::open(const string& fileName, unsigned SIZE) 
{
  BasicOutputBinaryBuffer::open(fileName, SIZE);
}

// ==============================================================================

template <typename T>
OutputIndexFile<T>::OutputIndexFile() 
{}

// ==============================================================================

template <typename T> 
OutputIndexFile<T>::OutputIndexFile(const string& fileName)
: BasicOutputBinaryBuffer(fileName, 4194304), expectedPosition(0)
{ }

// ==============================================================================

template <typename T>
OutputIndexFile<T>& OutputIndexFile<T>::operator[] (unsigned i)
{
  position = i;
  return *this;
}

// ==============================================================================

template <typename T>
void OutputIndexFile<T>::operator=(T value)
{
  writeValue(position, value);
}

// ==============================================================================

template <typename T>
void OutputIndexFile<T>::writeValue(unsigned pos, T value)
{
  if (pos != expectedPosition)
  {
    // we need to reposition
    this->rePosition( pos * sizeof(T) );  
  }
  
  char* bytes = reinterpret_cast<char *>(&value);
  
  this->writeBytes( sizeof(T), bytes );
  
  // new value of the expected value
  expectedPosition = pos + 1;
}

// ==============================================================================

template <typename T>
OutputIndexFile<T>::~OutputIndexFile() { }

// ==============================================================================


template class OutputIndexFile<long>;
template class OutputIndexFile<float>;
template class OutputIndexFile<unsigned>;

