/*
 * ProcessedQuery.h - The Garnata Retrieval System
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

#ifndef __ProcessedQuery_H__
#define __ProcessedQuery_H__ 

#include <vector>

using namespace std;

class ProcessedQuery {
  private:
    /** List of term identifiers */
    vector<unsigned> terms;
    
  public:
    /** Main constructor
    @param t list of term identifiers
    */
    ProcessedQuery(vector<unsigned> t);

    /** Copy constructor
    @param p entity to copy
    */
    ProcessedQuery(const ProcessedQuery& p);

    /** Returns the size of the query
    @return size of vector "terms"
    */
    unsigned size() const;
    
    /** Returns the i-th identifier
    @param i index of the identifier wanted
    @return terms[i]
    */
    unsigned operator[](unsigned i) const;
    
    /** Destructor */
    ~ProcessedQuery();
};

#endif
