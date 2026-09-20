/*
 * OccurrenceFile.cpp - The Garnata Retrieval System
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

#include "OccurrenceFile.h"
#include "VariableByteCoder.h"

// ==================================================================

OutputCompressedBinaryFile OccurrenceFile::occFile;

// ==================================================================

OccurrenceFile::OccurrenceFile (const Lexicon& lex, const string& fileName) : L(lex), vc()
{ 
  lastElem = 0;
  currentOffset = 0;
  
  occFile.setCompressionAlgorithm(&vc);
  occFile.open(fileName, 10485760 ); // 10 MB of buffer
}

// ==================================================================

inline void OccurrenceFile::writeOccurrence(const vector<Quad>& vq)
{
  unsigned termId = vq[0].getId();
  unsigned _num = vq.size();
  vector<unsigned> _unit(_num), _freq(_num);
  vector<float> _weight(_num);
  vector<long> _offset(_num);
      
  for (unsigned i=0; i<_num; ++i)
  {
     _unit[i] = vq[i].getUnit();
     _freq[i] = vq[i].getFreq();
     _offset[i] = vq[i].getPtrPos();
     _weight[i] = 0.0;  // weight is not obtained in this stage of the process
  }
      
  Occurrence occ(_num, _unit, _freq, _offset, _weight);
  occ.dump(occFile);
      
  L.getTermFromId(termId)->setOffsetFileOcc ( currentOffset );
      
  currentOffset = occFile.getPosition();
}

// ==================================================================

inline void OccurrenceFile::flush(bool final)
{
  unsigned end;
  if (!final)
    end = lastElem;
  else end = v.size();
  
  unsigned lastId = v[0].getId();
  vector<Quad> vq;
  vq.reserve(end);  

  for (unsigned i=0; i<end; ++i)
  {
    unsigned _id = v[i].getId();
    if (_id == lastId)
      vq.push_back(v[i]);
    else {
      // write an Occurrence from 'vq'... 
      this->writeOccurrence(vq);
      
      // we empty vq
      // and we refill it with one member (v[i])
      vq.clear();
      vq.push_back(v[i]);
      
      // we also change the value of lastId (to _id)
      lastId = _id;
    }
  }
  
  // if there were some elements 
  // in vq, we should write it
  if (vq.size())
  {
    this->writeOccurrence(vq);
    vq.clear();
  }
  
  // we pop "end" elements from the
  // beginning of v
  for (unsigned i=0; i<end; ++i)
    v.pop_front();
  
  // lastElem is set to 0 because of the size of v has 
  // changed, and it could be empty now. It will
  // get a new value next time in adAll
  
  // NOTE THAT a call to adAll does not neccesary implies
  // lastElem to be changed and, consequently, this method
  // wouldn't do nothing
  lastElem = 0;
}

// ==================================================================

void OccurrenceFile::addAll(const vector<Quad>& _v)
{
  unsigned lastId;
  
  if (v.size())
    lastId = v.back().getId();
  else lastId = _v[0].getId();

  for (vector<Quad>::const_iterator it=_v.begin(), end=_v.end(); it!=end; ++it)
  {
    unsigned id = it->getId();
    if (id != lastId)
    {
      lastId = id;
      lastElem = v.size();
    }
    v.push_back(*it);
  }
  
  flush(false);
}

// ==================================================================

void OccurrenceFile::write()
{
  flush(true); 
}

// ==================================================================

OccurrenceFile::~OccurrenceFile () 
{
}

// ==================================================================

