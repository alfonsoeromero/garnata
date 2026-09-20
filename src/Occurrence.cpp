/*
 * Occurrence.cpp - The Garnata Retrieval System
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

#include "Occurrence.h"
#include "InputCompressedBinaryFile.h"
#include <algorithm>

// ==================================================================

Occurrence::Occurrence(unsigned _num, const vector<unsigned>& _unit, const vector<unsigned>& _freq, 
                      const vector<long>& _offset, const vector<float>& _weight) :
  num(_num), unit(_unit), freq(_freq), offset(_offset), weight(_weight) 
  { }
 
// ==================================================================

Occurrence::Occurrence() : num(0) { }

// ==================================================================

Occurrence::Occurrence(long offset) : 
   num(0) 
{
    occFile.rePosition(offset); 
    this->retrieve(occFile);
}

// ==================================================================

void Occurrence::update(long _offset, OutputCompressedBinaryFile& occ) 
{
   occ.rePosition(_offset);
   this->dump(occ);
}

// ==================================================================

Occurrence::Occurrence(const Occurrence& _o)
{
    num = _o.getNum();
    unit = _o.unit;
    freq = _o.freq;
    offset = _o.offset;
    weight = _o.weight;
}

// ==================================================================

const Occurrence& Occurrence::operator=(const Occurrence& _o)
{
  num = _o.getNum();
  unit = _o.unit;
  freq = _o.freq;
  offset = _o.offset;
  weight = _o.weight;  
  return *this;
}

// ==================================================================

unsigned Occurrence::getNum() const
{
  return num;
}
   
// ==================================================================

Occurrence::~Occurrence()
{ }

// ==================================================================

unsigned Occurrence::operator [](unsigned n) const
{
  if (n>=num)
    Globals::errorAndExit("ERROR: accessing beyond boundaries of the occurrence, exiting");
  return unit[n];
}

// ==================================================================

void Occurrence::dump(OutputCompressedBinaryFile& dest)
{
  dest.writeUnsigned(num);
  dest.writeSortedUnsignedList(unit, true);
  dest.writeUnsignedList( freq );
  dest.writeBoundedLongList( offset );
  dest.writeFloatList( weight );
}


// ==================================================================

void Occurrence::retrieve(InputCompressedBinaryFile& fileOcc) 
{
  // 1.- we read the number of units
  fileOcc.readUnsigned(num);
  
  // 2.- we read 4 vectors: unit, freq, offset and weight
  fileOcc.readSortedUnsignedList(unit, true);
  fileOcc.readUnsignedList(freq);
  fileOcc.readBoundedLongList(offset);
  fileOcc.readFloatList(weight);
}

// ==================================================================

float Occurrence::getIWeight(unsigned i) const
{
  if (i >= num)
    Globals::errorAndExit("ERROR: accessing beyond boundaries of the array of weights of the occurrence, exiting");
  return weight[i];
}

// ==================================================================

unsigned Occurrence::getIFreq(unsigned i) const
{
  if (i >= num)
    Globals::errorAndExit("ERROR: accessing beyond boundaries of the array of frequencies of the occurrence, exiting");
  return freq[i];
}

// ==================================================================

void Occurrence::getListIPos(unsigned i, vector<unsigned>& pos) const
{
  // 1st, is 'i' a valid index?
  if (i >= num)
    Globals::errorAndExit("ERROR: accessing beyond boundaries of the array of units of the occurrence, exiting");
 
  // 2nd, we move the pointer of the file	
  
  if (! posFile.rePosition(offset[i]) )
  {
    cerr << "Invalid file address access at address " << offset[i] << " (Occurrence::getListIPos). Exiting\n";
    exit (-1);
  }

  // 3rd, we read the list
  posFile.readSortedUnsignedList(pos, true);
}

// ==================================================================

unsigned Occurrence::getFreqOn(unsigned u) const
{
  vector<unsigned>::const_iterator it = std::lower_bound(unit.begin(), unit.end(), u);
  
  if (it != unit.end())
    return freq[ it - unit.begin() ];	
  else return 0;
}

// ==================================================================

float Occurrence::getWeightOn(unsigned u) const
{
  vector<unsigned>::const_iterator it = std::lower_bound(unit.begin(), unit.end(), u);
  
  if (it != unit.end())
    return weight[ it - unit.begin() ];	
  else return -100000000.0;
}

// ==================================================================

void Occurrence::setFiles(const string& _occFile, const string& _posFile, CompressionAlgorithm& ca)
{
  occFile.setCompressionAlgorithm(&ca);
  occFile.open(_occFile);
  posFile.setCompressionAlgorithm(&ca);
  posFile.open(_posFile);
}

// ==================================================================

int Occurrence::setWeight(unsigned j, float w)
{

  vector<unsigned>::iterator it = std::lower_bound(unit.begin(), unit.end(), j);
  
  if (it != unit.end())
  {
    unsigned ind = it - unit.begin();
    weight[ind] = w; 
    return (int) ind;	
  } else return -1;
}

// ==================================================================

void Occurrence::setWeightList(float* _w)
{
  weight = vector<float> (num);
  std::copy(_w, _w+num, weight.begin());
}

// ==================================================================

InputCompressedBinaryFile Occurrence::occFile;
InputCompressedBinaryFile Occurrence::posFile;

