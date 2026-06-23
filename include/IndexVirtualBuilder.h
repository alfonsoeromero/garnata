#ifndef __INDEXVIRTUALBUILDER_H__
#define __INDEXVIRTUALBUILDER_H__

#include <fstream>
#include <string>
#include "QuadPool.h"
#include "NodeTree.h"
#include "Lexicon.h"
#include "DTDList.h"
#include "DTD.h"
#include "Index.h"
#include "Occurrence.h"
#include "OccurrenceFile.h"
#include "PositionFile.h"
#include "QuadExtractor.h"


using namespace std;

class IndexVirtualBuilder : public Index {
  private:
    /** Storage of (t, doc, f, ptr) entities */
    QuadPool *qp;
    
    /** Lexicon of the collection being
    processed */
    Lexicon *L;
    
    /** Position file */
    PositionFile *pf;
    
    /** Occurrence file */
    OccurrenceFile *occFile;
    
    /** List of the differents DTDs */
    DTDList *dtdlist;
    
    /** Identificator of the current unit */
    unsigned currentUnit;
    
    /** Number of the current file
    being processed */
    unsigned currentFile;
 
    /** Number of tag */
    unsigned currentTag;
    
    /** Pointer to the current node 
    being processed */
    NodeTree* current;
    
    /** DTD of the file being processed */
    DTD* currentDTD;
    
    /** Extractor used to take out the terms 
    from the 'characters' event */
    QuadExtractor* quex;
    
    /** Stack of different extractors (to allow
      	both container/final units)
    */
    stack<QuadExtractor*> extractors;
  
    /** Adds a unit identifier as root unit
    @param id identifier of a root unit
    */
    void addRoot(unsigned id);
    
    void arrangeTree(void); 
        
    
  public:
    /** Builds a new index
    @param c Collection to be indexed
    @param identifier index identifier
    @param doStemming must be true if we want Porter's stemming
    */
    IndexVirtualBuilder (const Collection& c, string identifier, bool doStemming);
    
    /** Starts a new file */
    void startDocument ();
    
    /** Ends a file */
    void endDocument ();
    
    /** Starts a new unit 
    @param tagType type of the unit (string)
    */
    void startUnit (string tagType);
    
    /** Ends current unit */
    void endUnit ( );
    
    /** Process a block of characters
    @param s string of characters being processed
    */
    void characters (const string& s);
    
    /** Changes the DTD to another
    @param dtdname name of the DTD being used with this file
    */
    void changeDTD (string dtdName);
    
    /** Destructor */
    ~IndexVirtualBuilder ();
};

#endif

