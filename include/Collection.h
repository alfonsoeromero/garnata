/*
 * Collection.h - The Garnata Retrieval System
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

#ifndef __COLLECTION_H__
#define __COLLECTION_H__

using namespace std;

#include <string>
#include <vector>

class Collection {
  private:
    /** Identifier of the collection in the system */
    unsigned id;
  
    /** Short name (1 word) of the collection in the system */
    string name;
  
    /** Short description (<= 256 characters) of the collection in the system */
    string description;
    
    /** Path in the system to this collection */
    string path;
  
    /** List of component files */
    vector<string> files;

    /** List of built indexes  */
    vector<string> indexes;

  public:
    /** Empty constructor */
    Collection();
    
    /** Copy constructor 
    @param c collection to be copied on this
    */
    Collection (const Collection& c);

    /** Assignment operator 
    @param c collection to be assigned on this
    */    
    const Collection& operator=(const Collection& c);
  
    /** Main constructor      
    @param _name short name of the collection in the system
    @param _description short description of the collection
    @param _path full path to the collection
    @param _files list of files of the collection 
    */
    Collection (string _name, string _description, string _path, vector<string> _files);

    /** Reads the name of the collection 
    @return name of the collection
    */
    string getName() const;

    /** Reads the path where the collection is located
    @return path of the collection
    */
    string getPath() const;
    
    /** Reads the description of the collection
    @return short description of the collection
    */
    string getDescription() const;
    
    /** Sets collection's id
    @param _id identifier of the collection in the system
    */
    void setId(unsigned _id);

    /** Writes the collection to a file
    @param fileName name of the file to write the collection in
    @return true if operation could be completed, false if not
    */
    bool writeToFile(string fileName) const;
    
    /** Reads the collection from a file
    @param fileName name of the file to read the collection from
    @return true if operation could be completed, false if not
    */
    bool readFromFile(string fileName);
    
    /** Return collection's indexes (empty array if not any)
    @return vector with indexes identifiers
    */
    vector<string> getIndexes() const;

    /** Return collection's files (empty array if not any)
    @return vector with files identifiers
    */
    vector<string> getFiles() const;

    /** Prints the info of the collection */
    void printInfo() const;
    
    /** Adds a new index to the collection
    @pre indexName should be a valid index identifier
    @param indexName index to be added
    @post the collection file WILL NOT BE MODIFIED 
         (that should be done from outside)
    */
    void addIndex(string indexName);

    /** Remove an index to the collection
    @pre indexName should be a valid index identifier
    @param indexName index to be removed
    @post the collection file WILL NOT BE MODIFIED 
         (that should be done from outside)
    */
    void removeIndex(string indexName);
    
    /** Destructor */
    ~Collection();
};

#endif

