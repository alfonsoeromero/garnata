/*
 * GarnataQueryXML.h - The Garnata Retrieval System
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

#ifndef __GARNATAQUERY_H__
#define __GARNATAQUERY_H__

#include "Garnata.h"
#include "RetrievalModel.h"
#include "Result.h"
#include <string>
#include <iostream>

using namespace std;

typedef enum {__BNR_SD=0, __SID, __CID} model;

class GarnataQueryXML : public Garnata 
{
  private:
    /** Retrieval model we are using */
    RetrievalModel* rm;
    
    /** Output stream */
    ostream& os;
    
    /** Time doing the queries */
    unsigned totalTime;
    
    /** Number of queries done to the system */
    unsigned numQueries;
    
    /** Sum of the sqares of the time */
    unsigned sumSquares;
    
  public:
    /** Constructor 
    @param collectionName name of the collection to query
    @param indexName name of the corresponding index
    @param identifier id of the retrieval model to be used
    @param doStemming true if we are doing stemming (Porter)
    */
    GarnataQueryXML(const string& collectionName, const string& indexName,
      model identifier, bool doStemming, const string& description,
      const string& task, const string& run_id, unsigned _id, ostream& _os);
    
    /** Returns the result of a query
    @param s string representing the query    
    */
    void makeQuery(const string& s, unsigned id);
    
    /** Print statistics */
    void printStats() const;
    
    /** Destructor */
    ~GarnataQueryXML();
};

#endif

// ==================================================================

