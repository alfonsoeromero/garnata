/*
 * UnitReader.cpp - The Garnata Retrieval System
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

#include "UnitReader.h"
#include "DTD.h"
#include <sstream>

// ==================================================================

UnitReader::UnitReader() : Unit () { }

// ==================================================================

void UnitReader::setMode(char _mode) { mode |= _mode; }

// ==================================================================

void UnitReader::read(fstream& ifs)
{
  unsigned tmp[5];
  ifs.read( (char*) &tmp, sizeof(unsigned) * 5);

  tagId = tmp[0];
  position = tmp[1];
  numContained = tmp[2];
  container = tmp[3];
  file = tmp[4];
  
  ifs.read( (char*) &weight, sizeof(float) );

  ifs.read( (char*) &mode, sizeof(char) );

  if (ifs.fail())
  {
    cerr << "Bad ifs (UnitReader::read), exiting\n";
    exit(-1);
  }
}

// ==================================================================

UnitReader :: UnitReader (unsigned _id) : Unit ()
{
  // 'id' belongs to the base class, so it cannot be set in the
  // initialiser list; the remaining fields are filled in by read()
  id = _id;

  //1st: we position the pointer of funt
  funt.seekg(_id * SIZE_UNIT, std::ios_base::beg);
  if (funt.fail())
  {
    cerr << "ERROR: Bad funt (UnitReader::UnitReader I), exiting\n";
    exit(-1);
  }  

  //2nd: we read the unit
  read( funt );

  if (funt.fail())
  {
    cerr << "ERROR: Bad funt (UnitReader::UnitReader II), exiting\n";
    exit(-1);
  }
  
}

// ==================================================================

UnitReader::UnitReader (const Unit& u) : Unit(u) {  }

// ==================================================================

string UnitReader::getRoute(DTD* dtd) const 
{ 
  long __offset = ifxpath[id];
  
  fxpath.rePosition(__offset);
  
  vector<unsigned> v;
  fxpath.readUnsignedList( v );

  unsigned t = 0;
  string res;
  
  for (vector<unsigned>::const_iterator it=v.begin(), end=v.end(); it!=end; ++it)
  {
        t = 1 - t;
        
        if (t == 1)
        {
          res += "/";
	  res += dtd->getTagById(*it);
        } else {
          
          unsigned u = *it;
        
          if (u > 0)
          {
            res += "[";
            ostringstream s;
            s << u;
            res += s.str();
            res += "]";
          } else { // añaido para que funcione con wikipedia!!
            res += "[1]";          
          }
	}
  }
  
  return res;
}

// ==================================================================

void UnitReader::getListOfDescendants (vector<unsigned>& l) 
{
  if (! isFinal() )
    cerr << "Warning: Unit is NOT FINAL, should not use 'getListOfDescendants' method\n";
  else {
    
    long _offset = ifpardesc[id];
    fdesc.rePosition(_offset);    
    fdesc.readSortedUnsignedList(l, false);
  }
}

// ==================================================================

void UnitReader::getListOfParents (vector<unsigned>& l)
{
  long _offset = ifpardesc[id];
  fpar.rePosition(_offset);  
  fpar.readSortedUnsignedList(l, true);
}

// ==================================================================

void UnitReader::getListOfTerms (vector<unsigned>& l, vector<unsigned>& freq)
{
  // ------------------------------------
  // Returns the list of unit's parents
  // ------------------------------------

  if ( !isFinal() )
    cerr << "WARNING: Unit is NOT FINAL, does not contains terms\n";
  else 
  {
    long _offset = ifdir[id];
    fdir.rePosition(_offset);    
    fdir.readSortedUnsignedList(l, true);
    fdir.readUnsignedList(freq);
  }
}

// ==================================================================

void UnitReader::setFiles(const string& Fpar, const string& Fdesc, const string& IFpardesc,
      const string& Funt, const string& Fdir, const string& IFdir, const string& Fxpath, 
      const string& IFxpath, CompressionAlgorithm& ca)
{
    
    funt.open(Funt.c_str(), ios_base::in | ios_base::binary );
    if (funt.fail())
    {
      cerr << "ERROR: Bad funt (UnitReader::setFiles), exiting\n";
      exit(-1);
    }
	
    ifpardesc.open(IFpardesc, 8192 );
    ifdir.open(IFdir, 8192 );
    ifxpath.open(IFxpath, 8192);
    fxpath.setCompressionAlgorithm(&ca);
    fxpath.open(Fxpath);
    fdir.setCompressionAlgorithm(&ca);
    fdir.open(Fdir);
    fpar.setCompressionAlgorithm(&ca);
    fpar.open(Fpar);
    fdesc.setCompressionAlgorithm(&ca);
    fdesc.open(Fdesc);
}

// ==================================================================

void UnitReader::close()
{
  funt.close();
}

// ==================================================================

unsigned UnitReader::depth() const
{
  unsigned depthLevel = 0;
  UnitReader current = *this;

  while (current.getPosition() != 0)
  {
    current = UnitReader ( current.getContainer() );
    ++depthLevel;
  }

  return depthLevel;
}

// ==================================================================

UnitReader::~UnitReader() { }

// ==================================================================

fstream UnitReader::funt;

InputIndexFile<long> UnitReader::ifpardesc;

InputIndexFile<long> UnitReader::ifdir;

InputIndexFile<long> UnitReader::ifxpath;

InputCompressedBinaryFile UnitReader::fxpath;

InputCompressedBinaryFile UnitReader::fpar;
    
InputCompressedBinaryFile UnitReader::fdesc;

InputCompressedBinaryFile UnitReader::fdir;
