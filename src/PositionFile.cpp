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

