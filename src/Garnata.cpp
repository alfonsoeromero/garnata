/*
 * Garnata.cpp - The Garnata Retrieval System
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

// ==================================================================

#include "Garnata.h"
#include "Index.h"
#include <fstream>
#include <iostream>
#include <algorithm>

// ==================================================================

Garnata::Garnata()
{
  ifstream _file(Globals::conf_file.c_str());
  
  if (_file.fail())
    Globals::errorAndExit("ERROR: Could not read the configuration file (Garnata::Garnata), exiting...");

  _file >> cols;
  _file >> nextId;
  
  for (unsigned i=0; i<cols; i++)
  {
    string s;
    _file >> s;
    names.push_back(s);
  }
  current = 0;
  _file.close();
}

// ==================================================================

bool Garnata::createCollection( Collection& col )
{
  // 1st.- we search collection name in the list
  string _name = col.getName();

  if (std::find(names.begin(), names.end(), _name) == names.end()) // not found
  {
   // 2nd.- if the name wasn't found, 
   // we create the collection file
    ++cols;
    col.setId (nextId);
    ++nextId;
    names.push_back(_name);    
    writeConfFile();
    
    col.writeToFile( Globals::home_collections + col.getName() );
    
    return true;
  } else return false;

}

// ==================================================================

void Garnata::writeConfFile() const
{
  ofstream _file;
  _file.open(Globals::conf_file.c_str());
  
  if (!_file)
    Globals::errorAndExit("Could not open the configuration file, exiting...");
  
  _file << cols << endl;
  _file << nextId << endl;
    
  for (unsigned i=0; i<cols; i++)
    _file << names[i] << endl;
  
  _file.close();

}

// ==================================================================

const Collection* Garnata::getCurrent() const
{ 
  if(current) return current; 
  else return 0;
}

// ==================================================================

bool Garnata::printInfoIndex(string indexName) const
{
  if (!current)
    return false;
  else {
    vector<string> v = current->getIndexes();
    if (find(v.begin(), v.end(), indexName) != v.end())
    {
      Index i(*current);
      i.read (indexName);
      i.printInfo();
      return true;
    }
    else return false;
  }
}

// ==================================================================


bool Garnata::setCurrent(string colName)
{
  if (current)
  {
    if (current->getName() == colName) return true;
    else delete current;
  }
	
  bool found = false;
  for (unsigned i=0; i<names.size() && !found; i++)
    found = (names[i] == colName);
  
  if (!found) return false;
  
  current = new Collection();
  current->readFromFile ( Globals::home_collections + colName );

  return true;
}

// ==================================================================

vector<string> Garnata::getCollectionNames() const { return names; }

// ==================================================================

Garnata::~Garnata() 
{ 
  if (current)
    delete current; 
}

// ==================================================================

void Garnata::removeCollection (string id)
{
  if (current)
  {
    vector<string> indexes = current->getIndexes();
    for (vector<string>::iterator it = indexes.begin(); it!=indexes.end(); it++)
      Index::remove(id, *it);
	    
    remove((string(Globals::home_collections + id)).c_str());
  
    vector<string> nnames;
    for (unsigned i=0; i<names.size(); i++)
      if (names[i] != id)
        nnames.push_back(names[i]);

    names = nnames;
    --cols;
    writeConfFile();
  } else 
    Globals::showWarning("WARNING: 'current' is not set!");
}

// ==================================================================

void  Garnata::removeIndexFromCollection (string idCol, string idIndex)
{
  if (current)
  {
    vector<string> indexes = current->getIndexes();
    if (std::find(indexes.begin(), indexes.end(), idIndex) == indexes.end())
        Globals::errorAndExit("ERROR: index does not exist");
    else {
      Index::remove(idCol, idIndex);
      
      // we modify the collection file
      current->removeIndex(idIndex);
      current->writeToFile(Globals::home_collections + idCol);    
    }
    
  } else 
    Globals::showWarning("WARNING: 'current' is not set!");

}

// ==================================================================

bool Garnata::delWeightFile(string indexName, string file)
{
  if (current)
  {
    vector <string> v = current->getIndexes();
    if (std::find(v.begin(), v.end(), indexName) == v.end()) // not found
      return false;

    // check that the weight file exists before touching the index
    string weightFile = Globals::home_weight + current->getName() + "_" + indexName + "_" + file;
    if (!Globals::fileExists(weightFile))
      return false;

    Index in(*current);
    in.read(indexName);
    in.delWeight(file);
    in.write();
    
    if (remove(weightFile.c_str()) == -1)
      return false;
	  
	  
  } else { 
    Globals::showWarning("WARNING: 'current' is not set!");
    return false;
  }

  return true;
}



