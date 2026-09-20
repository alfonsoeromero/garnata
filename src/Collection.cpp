/*
 * Collection.cpp - The Garnata Retrieval System
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

#include "Collection.h"
#include "Globals.h" 
#include <fstream>
#include <iosfwd>

// ==================================================================

Collection::Collection() { }

// ==================================================================

Collection::Collection (string _name, string _description, string _path, vector<string> _files) :
	name(_name), description(_description), path(_path), files(_files)
{ }

// ==================================================================
    
Collection::Collection (const Collection& c) : 
  id (c.id), name(c.name), description(c.description),
  path (c.path), files(c.files), indexes(c.indexes)
{ }

// ==================================================================

const Collection& Collection::operator=(const Collection& c)
{
  id = c.id;
  name = c.name;
  description = c.description;
  path = c.path;
  files = c.files;
  indexes = c.indexes;
  return (*this);
}

// ==================================================================

string Collection::getDescription() const { return description; }

// ==================================================================

string Collection::getName() const { return name; }

// ==================================================================

void Collection::setId(unsigned _id) { id = _id; }

// ==================================================================

Collection::~Collection() { }

// ==================================================================

vector<string> Collection::getFiles() const { return files; }

// ==================================================================

vector<string> Collection::getIndexes() const { return indexes; }

// ==================================================================

bool Collection::writeToFile(string fileName) const
{
  ofstream _file(fileName.c_str());
  
  if (_file.fail())  return false;
  
  _file << id << "\n" << name << "\n";
  _file << description.substr(0, 255) << "_\n";
  _file << path << "\n" << files.size() << "\n";
  
  for (vector<string>::const_iterator it=files.begin(), end=files.end(); it!=end; ++it)
    _file << *it << "\n";
  
  _file << indexes.size() << "\n";
  for (vector<string>::const_iterator it=indexes.begin(), end=indexes.end(); it!=end; ++it)
      _file << *it << "\n";
  
  if (_file.fail())
    Globals::errorAndExit("Bad '_file' (Collection::writeToFile), exiting");
  
  return true;
}

// ==================================================================

bool Collection::readFromFile(string fileName)
{
  ifstream _file(fileName.c_str());
  
  if ( _file.fail() ) return false;

  _file >> id;
  _file >> name;
  
  char tmp[256];
  _file.getline(tmp, 255, '_');
  if ( _file.fail() ) { return false; }
  
  unsigned j=0, tam=strlen(tmp);
  for (unsigned i=0; i<tam; ++i)
    if (tmp[i]!='\n')
      tmp[j++] = tmp[i];  
  tmp[j] = '\0';
  description = string(tmp);
  
  _file >> path;
  
  unsigned _num;
  _file >> _num;

  files = vector<string> (_num);
  
  for (unsigned i=0; i<_num; ++i)
  {
    _file >> files[i];
  }
  _file >> _num;
  indexes = vector<string> (_num);

  for (unsigned i=0; i<_num; ++i)
  {
    _file >> indexes[i];
  
    if (_file.fail())
    {
      cerr << "At file num " << i << endl;
      Globals::errorAndExit("Bad '_file' (Collection::readFromFile), exiting");
    }
  }
  
  _file.close();
  
  return true;
}

// ==================================================================

void Collection::addIndex(string indexName)
{
  indexes.push_back(indexName);
}

// ==================================================================

void Collection::removeIndex(string indexName)
{
  indexes.erase( remove( indexes.begin(), indexes.end(), indexName ), indexes.end() );
}

// ==================================================================

string Collection::getPath() const
{
  return path;
}

// ==================================================================

void Collection::printInfo() const
{
  cout << "Collection '" << name << "'\n"
  << "   + id: " << id << "\n"  
  << "   + Brief description: " << description << "\n"
  << "   + Path to the files: " << path << "\n"
  << "   + List of the different files:\n";
  
  for (vector<string>::const_iterator it=files.begin(), end=files.end(); it!=end; ++it)
    cout << "\t> " << *it << "\n";

  cout << "   + List of built indexes:\n";
  for (vector<string>::const_iterator it=indexes.begin(), end=indexes.end(); it!=end; ++it)
    cout << "\t> " << *it << "\n";  

  cout << flush;
}

// ==================================================================


