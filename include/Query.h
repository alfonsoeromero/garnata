/*
 * Query.h - The Garnata Retrieval System
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

#ifndef __QUERY_H__
#define __QUERY_H__

#include <sstream>
#include <string>
#include <vector>
#include "Globals.h"

using namespace std;

class Query{
  private:
    /** Vector of string with the 
    different terms */
    vector<string> terms;

    /** empty string */
    string empty;

  public:
    /** Main constructor
    @param s string containing the different terms of the
      query separated by blanks
    */ 
    Query(const string& s);

    /** Return the term at "i" position
    @param i position of the term we want to return
    */
    const string& operator[] (unsigned i) const;

    /** Return the number of terms that
    belongs to the query
    */
    unsigned size() const;

    /** Destructor */
    ~Query();
};

#endif // __QUERY_H__
