#ifndef __GARNATAMAKEINDEX_H__
#define __GARNATAMAKEINDEX_H__

#include "Garnata.h"

class GarnataMakeIndex : public Garnata {

  public:
    /** Constructor */
    GarnataMakeIndex();

    /**
    Makes an index of a collection
    @param collectionName name of the collection to index
    @param identifier of the index
    @param stopwordsListFile name of the stopwords file
    @param doStemming must be true if we want Porter's stemming
    */
    int makeIndex ( string collectionName, string identifier, string stopwordsListFile, bool doStemming );
  
    /** Destructor */
    ~GarnataMakeIndex();

};

#endif

