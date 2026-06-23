#ifndef _OCCURRENCEFILE_H__
#define _OCCURRENCEFILE_H__

#include "Quad.h"
#include "Occurrence.h"
#include "Lexicon.h"
#include "Term.h"
#include "OutputCompressedBinaryFile.h"
#include "VariableByteCoder.h"

#include <vector>
#include <queue>
#include <string>

using namespace std;

class OccurrenceFile
{
  private:
    /** Buffer of quads */
    deque<Quad> v;
    
    /** Related lexicon */
    const Lexicon& L;

    /** index of last element of
    v to be processed
    */
    unsigned lastElem;
    
    /** Current offset on the occurrence file */
    long currentOffset;
    
    /** File to write occurrences in */
    static OutputCompressedBinaryFile occFile;
    
    /** Compression algorithm */
    VariableByteCoder vc;
    
    /** Writes the buffer of quads
    @param final tells if it is the final 
        stage of writing
    */
    void flush(bool final);
    
    /** Writes an Occurrence to "occFile" from a 
    vector of Quad
    @param vq vector where to write the Occurrence from
    */
    void writeOccurrence(const vector<Quad>& vq);
    
  public:
    /** Main constructor
    @param _lex related lexicon
    */
    OccurrenceFile (const Lexicon& lex, const string& fileName);
    
    /** Adds all components of a vector to the buffer
    @param _v vector to be added
    */
    void addAll(const vector<Quad>& _v);

    /** Flushes and closes the occurrence file */    
    void write();

    /** Destructor */
    ~OccurrenceFile ();
};

#endif


