#include "OutputCompressedBinaryFile.h"

// ===========================================================================

OutputCompressedBinaryFile::OutputCompressedBinaryFile () {}

// ===========================================================================

OutputCompressedBinaryFile::OutputCompressedBinaryFile (const string& name)
	: BasicOutputBinaryBuffer (name, 4096) { ; }

// ===========================================================================

void OutputCompressedBinaryFile::open (const string& name, unsigned _SIZE=4096)
{
  BasicOutputBinaryBuffer::open (name, _SIZE);
}

// ===========================================================================

inline void OutputCompressedBinaryFile::writeFloat (float f) 
{
  // the size of this buffer is 8 because of alignment purposes. It could be only 5
  char buff[8];
  unsigned num = 0;

  // compression...
  ca->compressFloat (f, buff, num);
  
  writeBytes(num, buff);
}

// ===========================================================================

inline void OutputCompressedBinaryFile::writeUnsigned (unsigned u) 
{
  // the size of this buffer is 8 because of alignment purposes. It could be only 5
  char buff[8];
  unsigned num = 0;

  // compression...
  ca->compressUnsigned (u, buff, num);
  
  writeBytes(num, buff);
}

// ===========================================================================

inline void OutputCompressedBinaryFile::writeLong(long l) 
{
  // the size of this buffer is 10 because of alignment purposes. It could be only 9
  char buff[10];
  unsigned num = 0;

  // compression...
  // compression...
  ca->compressLong (l, buff, num);
  
  writeBytes(num, buff);
}

// ===========================================================================

void OutputCompressedBinaryFile::writeUnsignedList(const vector<unsigned>& array)
{
  writeUnsigned (array.size());
  for_each(array.begin(), array.end(), bind1st(mem_fun(&OutputCompressedBinaryFile::writeUnsigned), this));
}

// ===========================================================================

void OutputCompressedBinaryFile::writeFloatList(const vector<float>& array)
{
  writeUnsigned (array.size());
  for_each(array.begin(), array.end(), bind1st(mem_fun(&OutputCompressedBinaryFile::writeFloat), this));
}

// ===========================================================================

void OutputCompressedBinaryFile::writeLongList(const vector<long>& array)
{
  writeUnsigned (array.size());
  for_each(array.begin(), array.end(), bind1st(mem_fun(&OutputCompressedBinaryFile::writeLong), this));
}

// ===========================================================================

void OutputCompressedBinaryFile::writeSortedUnsignedList(const vector<unsigned>& array, bool ascending)
{
  vector<unsigned> temp(array);
  if (!ascending) std::reverse(temp.begin(), temp.end());
 
  // we compute element differences
  adjacent_difference (temp.begin(), temp.end(), temp.begin());
  
  writeUnsignedList(temp);
}

// ===========================================================================

void OutputCompressedBinaryFile::writeSortedLongList(const vector<long>& array, bool ascending)
{
  vector<long> temp(array);
  if (!ascending) std::reverse(temp.begin(), temp.end());
  
  // we compute element differences
  adjacent_difference (temp.begin(), temp.end(), temp.begin());
  
  writeLongList(temp);
}

// ===========================================================================

void OutputCompressedBinaryFile::writeBoundedLongList(const vector<long>& array)
{
  vector<long>::const_iterator mini = std::min_element(array.begin(), array.end());
  vector<long> array2 = array;
  long minimum = *mini;
  transform(array2.begin(), array2.end(), array2.begin(), bind2nd(minus<long>(), minimum) );

  writeLong(minimum);  
  writeLongList(array2);
}

// ===========================================================================

OutputCompressedBinaryFile::~OutputCompressedBinaryFile () {}

// ===========================================================================

void OutputCompressedBinaryFile::setCompressionAlgorithm (CompressionAlgorithm* _ca)
{
  ca = _ca;
}

// ===========================================================================

long OutputCompressedBinaryFile::getPosition()
{
  return (long) file.tellp() + (long) pos;
}

// ===========================================================================

CompressionAlgorithm* OutputCompressedBinaryFile::ca = 0;

// ===========================================================================
