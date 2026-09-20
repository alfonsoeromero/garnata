/*
 * IndexBuilder.h - The Garnata Retrieval System
 * Copyright (C) 2005, 2026 Alfonso E. Romero
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __INDEXBUILDER_H__
#define __INDEXBUILDER_H__

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
#include "UnitWriter.h"
#include "VariableByteCoder.h"


using namespace std;

class IndexBuilder : public Index {
  private:
    /** Storage of (t, doc, f, ptr) entities */
    QuadPool *qp;
    
    /** Lexicon of the collection being
    processed */
    Lexicon* L;
    
    /** Occurrence file */
    OccurrenceFile *occFile;
    
    /** Identificator of the current unit */
    unsigned currentUnit;
    
    /** Number of the current file
    being processed */
    unsigned currentFile;
 
    /** Number of tag */
    unsigned currentTag;
    
    /** Size of the Unit file */
    unsigned sizeFUnit;
    
    /** Size of the XPath stored in the Unit file */
    unsigned sizeXPath;

    /** Depth level of XPath routes */
    unsigned depth;
    
    /** Pointer to the current node 
    being processed */
    NodeTree* current;
    
    /** DTD of the file being processed */
    DTD* currentDTD;
    
    /** Extractor used to take out the terms 
    from the 'characters' event */
    QuadExtractor* quex;
    
    /** List of the differents DTDs */
    DTDList dtdlist;

    /** Compression Algorithm*/
    VariableByteCoder vc;

    /** Position file */
    PositionFile pf;

    /** Stack of different extractors (to allow
      	both container/final units)
    */
    stack<QuadExtractor*> extractors;
    
    /** True if the file has a DTD declaration */
    bool hasDtdDeclared;
    
    /** Adds a unit identifier as root unit
    @param id identifier of a root unit
    */
    void addRoot(unsigned id);
    
    void arrangeTree(void); 

    Unit* arrangeVirtualNode(void);
        
    
  public:
    /** Builds a new index
    @param c Collection to be indexed
    @param identifier index identifier
    @param doStemming must be true if we want Porter's stemming
    */
    IndexBuilder (const Collection& c, const string& identifier, bool doStemming);
    
    /** Starts a new file */
    void startDocument ();
    
    /** Ends a file */
    void endDocument ();
    
    /** Starts a new unit 
    @param tagType type of the unit (string)
    */
    void startUnit (const string& tagType);
    
    /** Ends current unit */
    void endUnit ( );
    
    /** Process a block of characters
    @param s string of characters being processed
    */
    void characters (const string& s);
    
    /** Initializing the stopword list from a file
    @param stopwordListFileName name of the file with the stopwords
    @return true if file existed
    */
    bool setStopwordList (const string& stopwordListFileName);
    
    /** Changes the DTD to another
    @param dtdname name of the DTD being used with this file
    */
    void changeDTD (const string& dtdName);

    /** Writes the indexes to disk */
    void writeIndexes();
    
    /** Destructor */
    ~IndexBuilder ();
};

#endif

