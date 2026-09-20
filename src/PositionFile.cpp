/*
 * PositionFile.cpp - The Garnata Retrieval System
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

#include "PositionFile.h"

// ==================================================================

PositionFile::PositionFile(const string& fileName, CompressionAlgorithm& ca) :
  of() 
  { 
    of.setCompressionAlgorithm(&ca);
    of.open(fileName, 524288);
  }

// ==================================================================

long PositionFile::add (const vector<unsigned>& v)
{
  long pos = of.getPosition();
  of.writeSortedUnsignedList(v, true);
  
/*  
  if (v.size() == 1)
  {
    of.writeUnsigned(v[0]);    
  } else if (v.size() == 2) {
    of.writeUnsigned(v[0]);
    of.writeUnsigned(v[1]);
  } else of.writeSortedUnsignedList(v, true);
 */ 
  return pos;
}

// ==================================================================

PositionFile::~PositionFile() { }

// ==================================================================

