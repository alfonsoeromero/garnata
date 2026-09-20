/*
 * Garnata.h - The Garnata Retrieval System
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

#ifndef __GARNATA_H__
#define __GARNATA_H__

#include "Globals.h"
#include "Collection.h"
#include <vector>
#include <string>

using namespace std;

/** class Garnata Garnata.h
*/
class Garnata {

  protected:
    /** Number of collections in the system */
    unsigned cols;
    
    /** Next identifier to be assigned to a new collection */
    unsigned nextId;
    
    /** List of collection's names */
    vector<string> names;
    
    /** Re-writes configuration file */
    void writeConfFile() const;
    
    /** Collection we are using */
    Collection* current;
    
  public:
    /** Constructor */
    Garnata();

    /** Different results */
    typedef enum { BAD_COLLECTION=0, BAD_INDEX=1, ALL_OK=2, BAD_STOPWORDS=3, BAD_WEIGHT=4 } result;
    
    /** Different weighting schemes */
    typedef enum { CLASSIC=0, NORM_MAX=1 } weights;

    /** Reads the names of the different collections 
    of the system
    @return vector with the names
    */
    vector<string> getCollectionNames() const;

    /** Returns a pointer to the current collection (0 if any)
    @return pointer to te current collection
    */
    const Collection* getCurrent() const;
    
    /** Prepares the system for using a certain Collection 
    @param col collection to be added to the system
    @return true if operation could be completed, false if not
    */
    bool createCollection ( Collection& col );

    /** Removes a collection from the system, and, consequently,
    all its associated indexes
    @param id identifier of the collection
    */
    void removeCollection (string id);
    
    /** Removes a index associated to a certain collection
    @param idCol identifier of the collection
    @param idIndex identifier of the index
    */
    void removeIndexFromCollection (string idCol, string idIndex);
    
    /** Sets 'colName' as the current collection
      for being used in the system
    @param colName name of the collection
    */
    bool setCurrent(string colName);

    /** Print information of an index of the current collection
    @param indexName name of the index
    @return true if index existed, false if not
    */
    bool printInfoIndex(string indexName) const;
    
    /** Deletes a certain weight file
    @pre indexName should be a valid index identifier for 'current' collection
    @param indexName name of the index
    @param file name of the weight file to delete 
    */
    bool delWeightFile(string indexName, string file);
    
    /** Destructor */
    virtual ~Garnata();
};

#endif

