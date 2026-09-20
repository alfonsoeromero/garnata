/*
 * GarnataMakeIndex.cpp - The Garnata Retrieval System
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

