#include "BasicOutputBinaryBuffer.h"
#include <cassert>

// ===========================================================================

BasicOutputBinaryBuffer::BasicOutputBinaryBuffer() {}

// ===========================================================================

BasicOutputBinaryBuffer::BasicOutputBinaryBuffer(const string& name, unsigned _SIZE) :
  SIZE(_SIZE), buffer(new char[_SIZE]), pos(0), file(name.c_str(), ios::out | ios::binary)
  {
    if (file.fail())
    {
      cerr << "Error creating file " << name << ". Disk full or read-only media\n";
      exit(-1);
    }
    
    if (!buffer)
    {
      cerr << "Error: not enough memory (BasicOutputBinaryBuffer::BasicOutputBinaryBuffer)\n";
      exit(-1);
    }
  }
  
// ===========================================================================

void BasicOutputBinaryBuffer::open(const string& name, unsigned _SIZE)
{
  SIZE = _SIZE;
  pos = 0;
  buffer = new char[SIZE];

  if (!buffer)
  {
    cerr << "Error: not enough memory (BasicOutputBinaryBuffer::BasicOutputBinaryBuffer)\n";
    exit(-1);
  }

  file.open(name.c_str(), ios::out | ios::binary );
  if (file.fail())
  {
    cerr << "Error creating file " << name << ". Disk full or read-only media\n";
    exit(-1);
  }

}

// ===========================================================================

inline void BasicOutputBinaryBuffer::flush()
{
  file.write ((char*) buffer, pos);
  pos = 0;
}

// ===========================================================================

void BasicOutputBinaryBuffer::writeByte(char byte)
{
  buffer[pos++] = byte;
  if (pos == SIZE) flush();
}

// ===========================================================================

void BasicOutputBinaryBuffer::writeBytes(unsigned num, char* bytes)
{
  assert(num <= SIZE);

  if (pos + num >= SIZE)
    flush();
  
  std::copy(bytes, bytes+num, buffer + pos);
  pos += num;
}

// ===========================================================================

void BasicOutputBinaryBuffer::rePosition(long newPos)
{
  if (pos) flush();
  
  file.seekp(newPos, std::ios::beg);
}

// ===========================================================================

BasicOutputBinaryBuffer::~BasicOutputBinaryBuffer()
{
  if (pos) flush();
	
  if (buffer)
    delete [] buffer;
}

// ===========================================================================

