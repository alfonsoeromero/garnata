/*
 * InputIndexFile.cpp - The Garnata Retrieval System
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

#include "InputIndexFile.h"

// ==============================================================================

template <typename T>
InputIndexFile<T>::InputIndexFile() { }

// ==============================================================================

template <typename T>
InputIndexFile<T>::InputIndexFile(const string& fileName) :
   BasicInputBinaryBuffer(fileName, 4096), expectedPosition(0)
{ }

// ==============================================================================

template <typename T>
void InputIndexFile<T>::open(const string& fileName, unsigned SIZE) {
  BasicInputBinaryBuffer::open(fileName, SIZE);
}

// ==============================================================================

template <typename T>
T InputIndexFile<T>::operator[] (unsigned i)
{
  if (i != expectedPosition)
  {
    rePosition(sizeof(T) * i);
  }

  //long ret = 0;
  this->clearBaseAddress();
  
  char c[ sizeof(T) ];
  for (unsigned num=0; num<sizeof(T); ++num)
  {
    readByte(c[num]);
  }
  
  T* ltemp = reinterpret_cast<T*>(&c);
  T ret = *ltemp;
  
  expectedPosition = i + 1;
  
  return ret;
}

// ==============================================================================

template <typename T>
InputIndexFile<T>::~InputIndexFile() { }

// ==============================================================================


template class InputIndexFile<long>;
template class InputIndexFile<unsigned>;
template class InputIndexFile<float>;

