#ifndef __COMPRESSION_ALGORITHM__
#define __COMPRESSION_ALGORITHM__

using namespace std;
#include "BasicInputBinaryBuffer.h"

class CompressionAlgorithm 
{
  public:
    /**  Compress an unsigned into a byte buffer
    @param u unsigned to compress
    @param buff binary buffer
    @param num number of occupied bytes    
    */
    virtual void compressUnsigned(unsigned u, char* buff, unsigned& num) = 0;

    /**  Compress a long into a byte buffer
    @param l long to compress
    @param buff binary buffer
    @param num number of occupied bytes    
    */
    virtual void compressLong(long l, char* buff, unsigned& num) = 0;

    /**  Compress a float into a byte buffer
    @param f float to compress
    @param buff binary buffer
    @param num number of occupied bytes    
    */
    virtual void compressFloat(float f, char* buff, unsigned& num) = 0;

    /**  Deflates a float from a byte buffer
    @param f float to deflate
    @param buff binary buffer
    */
    virtual void deflateFloat(float& f, BasicInputBinaryBuffer& buff) = 0;
    
    /**  Deflates an unsigned from a byte buffer
    @param u unsigned to deflate
    @param buff binary buffer
    */
    virtual void deflateUnsigned(unsigned& u, BasicInputBinaryBuffer& buff) = 0;

    /**  Deflates a long into a byte buffer
    @param l long to deflate
    @param buff binary buffer
    */
    virtual void deflateLong(long& l, BasicInputBinaryBuffer& buff) = 0;

    /** Destructor */
    virtual ~CompressionAlgorithm() { }
};

#endif
