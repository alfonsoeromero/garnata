#ifndef __INPUT_INDEX_FILE__
#define __INPUT_INDEX_FILE__

#include <string>
#include "BasicInputBinaryBuffer.h"

template <typename T>
class InputIndexFile : private BasicInputBinaryBuffer
{
  public:
    /** Empty constructor */
    InputIndexFile();
  
    /** Main constructor
        @param fileName name of the index file    
    */
    InputIndexFile(const string& fileName);
    
    /** Accesing operator */
    T operator [] (unsigned i); 
    
    /** Opens an index file */
    void open(const string& fileName, unsigned SIZE);
  
    /** Destructor */
    ~InputIndexFile();  
    
  private:
    /** Next position we expect to write in */
    unsigned expectedPosition;
};

#endif


