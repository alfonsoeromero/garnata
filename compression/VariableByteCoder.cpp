#include "VariableByteCoder.h"
// ===========================================================================

void VariableByteCoder::deflateUnsigned(unsigned& u, BasicInputBinaryBuffer& buff)
{
    unsigned index = 0;
    char b = buff [index++];
    unsigned i = b & 0x7F;
    
    for (unsigned shift = 7; (b & 0x80) != 0; shift += 7) 
    {
      b = buff [index++];
      i |= (b & 0x7F) << shift;
    }
    
    u = i;
}

// ===========================================================================

void VariableByteCoder::compressUnsigned(unsigned u, char* buff, unsigned& num)
{
  num = 0;
  unsigned i = u;
  
  while ((i & ~0x7F) != 0) 
  {
    buff[num++] = ((char)((i & 0x7f) | 0x80));
    i >>= 7;
  }
  buff[num++] = (char) i;
}

// ===========================================================================

void VariableByteCoder::deflateLong(long& u, BasicInputBinaryBuffer& buff)
{
    long index = 0;
    char b = buff [index++];
    
    long i = b & 0x7F;
    
    for (unsigned shift = 7; (b & 0x80) != 0; shift += 7) 
    {
      b = buff [index++];
      i |= (b & 0x7F) << shift;
    }
    
    u = i;
}

// ===========================================================================

void VariableByteCoder::compressLong(long u, char* buff, unsigned& num)
{
  num = 0;
  long i = u;
  
  while ((i & ~0x7F) != 0) 
  {
    buff[num++] = ((char)((i & 0x7f) | 0x80));
    i >>= 7;
  }
  buff[num++] = (char) i;
}

// ===========================================================================

void VariableByteCoder::compressFloat(float f, char* buff, unsigned& num)
{
  char* c = reinterpret_cast<char*>(&f);
  
  for (num=0; num<sizeof(float); ++num)
    buff[num] = c[num];
}

 
// ===========================================================================

void VariableByteCoder::deflateFloat(float& f, BasicInputBinaryBuffer& buff)
{
  char c[ sizeof(float) ];
  for (unsigned num=0; num<sizeof(float); ++num)
    c[num] = buff[num];
  
  float* ftemp = reinterpret_cast<float*>(&c);
  f = *ftemp;
}

// ===========================================================================

