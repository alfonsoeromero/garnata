#include "GarnataMakeIndex.h"
#include "IndexBuilder.h"
#include "XMLIndexer.h"
#include <algorithm>

// ==================================================================

GarnataMakeIndex::GarnataMakeIndex() : Garnata() { ; }

// ==================================================================

int GarnataMakeIndex::makeIndex 
     ( string collectionName, string identifier, string stopwordsListFile, bool doStemming )
{
  if(!setCurrent(collectionName))
    return BAD_COLLECTION; // collection does not exist

  vector<string> names = current->getIndexes();
  
  // We search the identifier among the others
  if (find(names.begin(), names.end(), identifier) != names.end())
    return BAD_INDEX; // identifier found... return
  
  // we create the index
  IndexBuilder ib (*current, identifier, doStemming);

  // We set the stopword list for this index
  if (!ib.setStopwordList( Globals::home_stopwords +  stopwordsListFile ))
  {
    cout << Globals::home_stopwords + stopwordsListFile << endl;
    return BAD_STOPWORDS;
  }

  // Construction of the parser
  XMLIndexer x(ib);

  // We parse files of the collection
  vector<string> files = current->getFiles(); 
  unsigned i = 1, size = files.size();

  for (vector<string>::const_iterator it=files.begin(), end=files.end(); it!=end; ++it, ++i)
  {
    cout << "Parsing file: " << *it << " (" << i << " of " << size << ")\n";
         
    x.parseFile ( current->getPath() + *it );

    cout << "File: " << *it << " parsed\n" << endl;
  }
  
  // if everyThing went O.K.
  ib.writeIndexes();
  current->addIndex(identifier);
  writeConfFile();
  current->writeToFile ( Globals::home_collections + current->getName() );
  
  return ALL_OK;
}



// ==================================================================

GarnataMakeIndex::~GarnataMakeIndex() { ; }

// ==================================================================

