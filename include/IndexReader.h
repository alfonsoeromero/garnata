#ifndef __INDEXREADER_H__
#define __INDEXREADER_H__

using namespace std;

#include "Collection.h"
#include "DTDList.h"
#include "Unit.h"
#include "Occurrence.h"
#include "Index.h"
#include "Lexicon.h"
#include "VariableByteCoder.h"


class IndexReader : public Index {

  protected:
    /** Lexicon of the collection */
    Lexicon* L;
    
    /** List of DTDs of the collection */
    DTDList* dtds;
    
    /** Compression algorithm */
    VariableByteCoder vc;
  
  public:
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    */
    IndexReader(const Collection& _c, string _identifier);

    /** Destructor */
    virtual ~IndexReader();
};

#endif

