/*
 * DTDList.h - The Garnata Retrieval System
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

#ifndef __DTDList_H__
#define __DTDList_H__

using namespace std;

#include <vector>
#include <string>
#include "DTD.h"
#include "Globals.h"

class DTDList {
  private:
    /** List of the different DTDs */
    vector <DTD*> dtds;
    
  public:
    /** Empty constructor */
    DTDList ();
    
    /** Constructs the DTDList from a file 
    (should be created with the 'write' operation) */
    DTDList (const string& fileName);
    
    /** Writes the DTDList to a file (not binary) 
    @param fileName name of the file
    */
    void write(const string& fileName);

    /** Returns the next id 
    corresponding to the next DTD
    @return the next id
    */
    unsigned getNextId() const;
    
    /** Search for the id of an specified file
    @param fileName name of the DTD whose identifier we want
    @param _id identifier of the DTD, if found
    @return true if found, false if not
    */
    bool getDTDIdByFilename(const string& fileName, unsigned& _id) const;

    /** Adds a new DTD to the list. 
    @param fileName name of the new DTD
    @return pointer to the DTD added
    */
    DTD* addNewDTD(const string& fileName);
    
    /** Returns the tag correnponding to the
    id given as a parameter. Returns "" if it
    does not belong to any DTD
    @param _id identifier whose tag is wanted
    @return string that represents that tag
    */
    string getTagById(unsigned _id) const;
    
    /** Returns the id of the DTD corresponding 
    to the DTD that the tag identifier identified
    by "_id" belongs to
    @param _id identifier whose tag is wanted
    @return string that represents that tag
    */
    unsigned getIdDTDId(unsigned _idTag) const;
    
    /** Returns the n-th DTD. 
    @param n identifier of the required DTD
    @post exits if n does not correspond to a valid DTD identifier
    */    
    DTD* getDTDbyId(unsigned n);
    
    /** Destructor */
    ~DTDList();
  
};

#endif

