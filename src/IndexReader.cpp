#include "IndexReader.h"
#include "UnitReader.h"
#include <iostream>

// ==================================================================

IndexReader::IndexReader ( const Collection& _c, string _identifier ) : 
  Index( _c ), vc( )
  {
    vector<string> indexes = c.getIndexes();
    if ( find(indexes.begin(), indexes.end(), _identifier) != indexes.end() )	    
      this->read(_identifier );
    
    else
      Globals::errorAndExit("ERROR: unknown index identifier. Exiting");
  
    L = new Lexicon(lexiconFileName);
    dtds = new DTDList(dtdlistFileName);
    
    if (!L || !dtds)
      Globals::errorAndExit("Not enough memory (IndexReader::IndexReader), exiting");
    // We set the files for reading mode
    UnitReader::setFiles(f_par, f_desc, if_par_desc, f_unt, f_dir, if_dir, f_xpath, if_xpath, vc);
    Occurrence::setFiles (occurrenceFileName.c_str(), positionsFileName.c_str(), vc );
  }

// ==================================================================

IndexReader::~IndexReader() 
{
  delete L;
  delete dtds;
  UnitReader::close();
}

// ==================================================================

