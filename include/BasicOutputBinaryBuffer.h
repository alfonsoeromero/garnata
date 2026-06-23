#ifndef __BASIC_OUTPUT_BINARY_BUFFER__
#define __BASIC_OUTPUT_BINARY_BUFFER__

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class BasicOutputBinaryBuffer 
{
  private:
    /** maximum size of the buffer */
    unsigned SIZE;
    
    /** buffer we are writing in */
    char* buffer;
    
    /** flushes current buffer to file */
    void flush();
    
  protected:
    /** writing position */
    unsigned pos; 
  
    /** file we are writing in */
    fstream file;
    
  public:
    /** Empty constructor */
    BasicOutputBinaryBuffer (); 

    /** Main constructor
    @param name name of the file we are writing in
    @param _SIZE size of the buffer
    */
    BasicOutputBinaryBuffer (const string& name, unsigned _SIZE);
    
    /** Writes a single byte into the buffer
    @param byte byte of data we want to write in
    */
    void writeByte(char byte);
    
    /**
    @param name name of the file we are writing to
    @param _SIZE size of the buffer
    */    
    void open (const string& name, unsigned _SIZE); 

    /** Writes several bytes to the buffer
    @param num number of bytes to write in
    @param bytes array of bytes we want to write in
    @pre num must be less or equal than the size of the buffer
    */
    void writeBytes(unsigned num, char* bytes);
    
    /** Moves the file pointer to another position
    @param newPos new writing position 
    */
    void rePosition (long newPos);
    
    /** Destructor */
    virtual ~BasicOutputBinaryBuffer();
};

#endif


