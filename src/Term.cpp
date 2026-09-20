/*
 * Term.cpp - The Garnata Retrieval System
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

#include <cstring>
#include "Term.h"
#include "OutputCompressedBinaryFile.h"

// ==================================================================

Term::Term() :
  id(0), freq(0), numDocs(0), offsetFileOcc(0)
  { }

// ==================================================================

Term::Term(const string& _termString, unsigned _freq, unsigned _id) : 
  id(_id-1), freq(_freq), offsetFileOcc(0), termString(_termString)
  { 
    // By default, one term (if created) appears in 1 document
    numDocs=1; 
  }
  
// ==================================================================

Term::Term(const string& _termString, unsigned _freq) :
  id(0), freq(_freq), offsetFileOcc(0), termString(_termString)
  { 
    // By default, one term (if created) appears in 1 document
    numDocs=1; 
  }
  
// ==================================================================
            
unsigned Term::getId() const
{
  return (id + 1);
}

// ==================================================================

unsigned Term::getLength() const
{
  return (unsigned) termString.size();
}

// ==================================================================

string Term::getTermString() const { return termString; }

// ==================================================================

unsigned Term::getFreq() const { return freq; }

// ==================================================================

void Term::dump(ofstream& out) const
{
  unsigned length = this->getLength();
  
  // 1st. Computation of the total amount of bytes =>
  // -  3 unsigned => id, freq and numdocs
  // -  length of termString + 1 ('\0')
  // -  offset in the occurrence file
  unsigned tmp[] = {static_cast<unsigned>(4*sizeof(unsigned) + (length+1)*sizeof(char) + sizeof(long)), id, freq, numDocs};

  // Order in binary file =>
  // 1st, 2nd, 3rd, 4th => totalsize, id, freq, numDocs 
  out.write((char *)&tmp, sizeof(unsigned)*4);

  // 5th => offset in the occurrence file
  out.write((char *) &offsetFileOcc, sizeof(long));
                          
  // 6th => string
  out.write(termString.c_str(), sizeof(char)*(length + 1));
  
  if (out.fail())
    Globals::errorAndExit ("Bad 'out' (Term::dump), exiting");
}    

// ==================================================================

void Term::incDocuments() { ++numDocs; }

// ==================================================================

void Term::incFrequency() { ++freq; }

// ==================================================================

void Term::setOffsetFileOcc(long off) { offsetFileOcc = off; }

// ==================================================================

Occurrence Term::getOccurrence() const
{
  Occurrence occ( this->offsetFileOcc );
  return occ;
}

// ==================================================================

void Term::updateOccurrence(Occurrence& occ, OutputCompressedBinaryFile& occFile)
{
  if (numDocs == occ.getNum())
  {
    occ.update(offsetFileOcc, occFile);
  } else {
    Globals::showWarning("Occurrence does not correspond to this term (Term::updateOccurrence)");
  }
}

// ==================================================================

void Term::setId(unsigned _id) { id = _id; }

// ==================================================================


void Term::retrieve (ifstream& in)
{
  // Order in binary file =>
  // 1st, 2nd, 3rd, 4th => totalsize, id, freq (unsigned), numDocs

  unsigned tmp[4];
  in.read((char*)&tmp, sizeof(unsigned)*4);

  if (in.fail()) Globals::errorAndExit ("Bad 'in' (Term::retrieve, I), exiting");

  unsigned totalsize = tmp[0];
  id = tmp[1];
  freq = tmp[2];  
  numDocs = tmp[3];

  // 5th => offsetFileOcc
  in.read((char*)&offsetFileOcc, sizeof(long));  
  if (in.fail()) Globals::errorAndExit ("Bad 'in' (Term::retrieve, II), exiting");
 
  unsigned remaining = totalsize - 4*sizeof(unsigned) - sizeof(long);

  char* _termString = new char[remaining];
  if (!_termString) Globals::errorAndExit("ERROR: Insufficient memory for '_termString', exiting.");

  // 6th => termString
  in.read(_termString, sizeof(char)*remaining);
  _termString[remaining-1] = '\0';
  if (in.fail()) Globals::errorAndExit ("Bad 'in' (Term::retrieve, III), exiting");
  
  termString = string(_termString);
  
  delete [] _termString;
}

// ==================================================================

unsigned Term::getNumDocs() const
{
  return numDocs;
}

// ==================================================================

Term::~Term()
{ }

// ==================================================================

