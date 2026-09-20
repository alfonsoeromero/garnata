/*
 * Query.cpp - The Garnata Retrieval System
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

#include "Query.h"

// ==================================================================

Query::Query( const string& s ) : empty(string(""))
{
  istringstream is(s);

  while (!is.eof())
  {
    string str("");
    is >> str;
    if (str.size())
    {
     if (str[0] != '<')
      terms.push_back(str);
    }
  }
}

// ==================================================================

unsigned Query::size(void) const { return terms.size(); }

// ==================================================================

const string& Query::operator[] (unsigned i) const 
{ 
  if( i < terms.size() )
    return terms[i];
  else
  {
   Globals::showWarning("Array bounds out of range (Query::operator[]), returning null string");
   return empty;
  }
}


// ==================================================================

Query::~Query() { ; }

// ==================================================================
