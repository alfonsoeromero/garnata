/*
 * Result.h - The Garnata Retrieval System
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

#ifndef __RESULT_H__
#define __RESULT_H__

#include <string>
#include <iostream>

using namespace std;

// ==================================================================

class Result {
  public:
    Result(const string& _fileName, const string& _route, float _rsv) :
      fileName(_fileName), route(_route), RSV(_rsv) { ; }
      
    Result(const Result& r) : fileName(r.fileName), route(r.route), RSV(r.RSV) { ; }
  
    /** Name of the file */
    string fileName;
    
    /** Route of the represented unit */
    string route;
    
    /** RSV of relevance of this unit */
    float RSV;
};

// ==================================================================

/** Ostream operator to make an XML output of a result */
ostream& operator << (ostream& os, const Result& s);

#endif
