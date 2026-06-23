#ifndef __INPUT_COMPRESSED_BINARY_FILE__
#define __INPUT_COMPRESSED_BINARY_FILE__

#include "BasicInputBinaryBuffer.h"
#include "CompressionAlgorithm.h"
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class InputCompressedBinaryFile : public BasicInputBinaryBuffer 
{
  private:
    /** Compression algorithm we are using */
    static CompressionAlgorithm* ca;

  public:
    /** Reads a single unsigned from the file
    @param u unsigned to be read
    @pre compression algorithm must be initiated
    */
    void readUnsigned (unsigned& u);
    
    /** Reads a single float from the file
    @param f float to be read
    */
    void readFloat (float& f);
    
    /** Reads a single long from the file
    @param l long to be read
    @pre compression algorithm must be initiated
    */
    void readLong (long& l);
    
    /** Empty constructor */
    InputCompressedBinaryFile ();  
  
    /** Main constructor
    @param name Name of the file
    */
    InputCompressedBinaryFile (const string& name);
    
    /** Opens a file
    @param name name of the file    
    */
    void open(const string& name);
  
    /** Reads a list of unsigned to the file
    @param array list of unsigned to w in
    @pre compression algorithm must be initiated
    */
    void readUnsignedList(vector<unsigned>& array);
    
    /** Reads a list of floats to the file
    @param array list of floats to w in
    */
    void readFloatList(vector<float>& array);
    
    /**  Reads a list of longs to the file
    @param array list of longs to in
    @pre compression algorithm must be initiated
    */
    void readLongList(vector<long>& array);
    
    /** Reads a sorted list of integers
    @param array list of integers to be read
    @param ascending must be true if the list is ascending, false if descending
    @pre compression algorithm must be initiated
    */
    void readSortedUnsignedList(vector<unsigned>& array, bool ascending);

    /** Reads a sorted list of longs
    @param array list of longs to w in
    @param ascending must be true if the list is ascending, false if descending
    @pre compression algorithm must be initiated
    */
    void readSortedLongList(vector<long>& array, bool ascending);
    
    
    /** Reads a bounded (i.e, with a minimum positive value) long list from the stream
    @param array vector to be read
    */
    void readBoundedLongList(vector<long>& array);

    /** Repositions the read pointer of the file
    @param newPos new position of the pointer
    @return true if position is valid
    */
    bool rePosition (long newPos);

    /** Initiates the compression algorithm
    @param _ca compression algorithm to use
    */
    static void setCompressionAlgorithm (CompressionAlgorithm* _ca);
    
    /** Destructor */
    ~InputCompressedBinaryFile ();
};

#endif


