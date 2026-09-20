/*
 * queryIndexXML.cpp - The Garnata Retrieval System
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

#include "GarnataQuery.h"
#include <iostream>

int main (int argc, char* argv[])
{

  if (argc != 4)
  {
    cerr << "ERROR: bad arguments number. \nUSE:\n"
         << "queryIndex collectionName indexName stem=(yes|no)" << endl;
    return -1;
  }

  string collectionName(argv[1]), indexName(argv[2]), stem(argv[3]);
  bool doStemming = false;

  if (stem == "stem=yes")
  {
    doStemming = true;
  } else if (stem != "stem=no") {
    cerr << "ERROR: bad parameters. \nUSE:\n"
         << "queryIndex collectionName indexName stem=(yes|no)" << endl;
    return -1;
  }

  GarnataQueryXML g(collectionName, indexName, _BNR_SD, doStemming);
  char buff[1024];
  unsigned id = 1;
  bool keepAsking;
  do {
    for (unsigned i=0; i<100; i++) buff[i] = '\0';
    cin.getline(buff, 1023);
    string s(buff);
    
    keepAsking = true;
    if (g.isCommand(s))
    {
      keepAsking = g.processCommand(s);
    } else if (s.size()) {
      g.makeQuery(s);

    }
	  
  } while (keepAsking);

  return 0;
}
