#ifndef __PositionFile_H__
#define __PositionFile_H__

#include <vector>
#include <fstream>
#include <string>
#include "Globals.h"
#include "OutputCompressedBinaryFile.h"
#include "VariableByteCoder.h"

using namespace std;

class PositionFile {
  private:
    /** File to write in */
    OutputCompressedBinaryFile of;
  
  public:
    /** Main constructor 
    @param fileName name of the file 
    */
    PositionFile (const string& fileName, CompressionAlgorithm& ca);
  
    /** Adds a vector to the file
    @param v vector of positions
    @return offset of added vector
    */
    long add(const vector<unsigned>& v);
    
    /** Destructor */
    ~PositionFile();
};

#endif

