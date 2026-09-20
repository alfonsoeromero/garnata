/*
 * queryINEX.cpp - The Garnata Retrieval System
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

#include "GarnataQueryXML.h"
#include <iostream>
#include <fstream>   
#include <sstream> 

int main (int argc, char* argv[])
{

  if (argc != 5)
  {
    cerr << "ERROR: bad arguments number. \nUSE:\n"
         << "queryINEX collectionName indexName stem=(yes|no) model=(BNR-SD|SID|CID)" << endl;
    return -1;
  }

  string collectionName(argv[1]), indexName(argv[2]), stem(argv[3]), myModel(argv[4]);
  bool doStemming = false;

  if (stem == "stem=yes")
  {
    doStemming = true;
  } else if (stem != "stem=no") 
    {
    cerr << "ERROR: bad parameters. \nUSE:\n"
         << "queryIndex collectionName indexName stem=(yes|no)" << endl;
    return -1;
    }
    
    
    
  model mode;
  
  if (myModel == "model=BNR-SD") 
    mode = __BNR_SD;  
  else if (myModel == "model=SID")
    mode = __SID;  
  else // CID
    mode = __CID;

  ofstream of(string(string("salida_") + myModel.substr(6, 12) + string(".xml")).c_str());
  
  GarnataQueryXML g(collectionName, indexName, mode, doStemming, "description", "Thorough", "9", 0, of);

  char buff[1024];
  
  bool keepAsking;
  
  unsigned NUMQUERIES = 111;
  
  for (unsigned j=0; j<NUMQUERIES; ++j)
  {
    cout << "Parsing query " <<j+1 << " of " << NUMQUERIES << endl;  
    unsigned u;
    cin >> u;
        
    for (unsigned i=0; i<100; i++) buff[i] = '\0';
    cin.getline(buff, 1023);
    string s(buff);
    
    istringstream ss(s);
    //unsigned u;
    //ss >> u;
    
    keepAsking = !ss.bad();
    
    if (keepAsking)
    {
      g.makeQuery(ss.str(), u);
    }
	  
  } 
  
  g.printStats();

  return 0;
}
