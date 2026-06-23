#ifndef __OUTPUT_INDEX_FILE__
#define __OUTPUT_INDEX_FILE__

#include <string>
#include "BasicOutputBinaryBuffer.h"

template<typename T>
class OutputIndexFile : private BasicOutputBinaryBuffer
{
  public:
    /** Empty constructor */
    OutputIndexFile ();
  
    /** Main constructor
        @param fileName name of the index file    
    */
    OutputIndexFile(const string& fileName);
    
    /** Accesing operator */
    OutputIndexFile& operator [] (unsigned i);
    
    /** opens a index file */
    void open (const string& fileName, unsigned SIZE);
    
    /** Equal operator */
    void operator=(T value);
  
    /** Destructor */
    ~OutputIndexFile();  
    
  private:
    /** Next position we expect to write in */
    unsigned expectedPosition;
    
    /** Position to write the value in */
    unsigned position;
    
    /** Writes a certain value in 
    a given position
    @param value value to write in
    @param pos position to write the value
    */
    void writeValue(unsigned pos, T value);
};

#endif


