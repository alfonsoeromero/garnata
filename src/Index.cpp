/*
 * Index.cpp - The Garnata Retrieval System
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

#include <algorithm>
#include "Index.h"
#include "Globals.h"
#include <fstream>

// ==================================================================

Index::Index(const Collection& _c, const string& _identifier) : 
  c(_c), identifier(_identifier) 
  {
    string my_id = c.getName() + string("_") + identifier;
    string pre = Globals::home_index + my_id;
    
    lexiconFileName = pre + string(".lexicon");
    occurrenceFileName = pre + string(".fOcc");
    positionsFileName = pre + string(".fPos");
    
    f_unt = pre + string(".f_unt");
//    if_unt = pre + string(".if_unt");
    f_par = pre + string(".f_par");
    f_desc = pre + string(".f_desc");
    if_par_desc = pre + string(".if_par_desc");
    dtdlistFileName = pre + string(".dtds");
    cacheFileName = pre + string(".cache");    
    quadFileName = pre + string(".quad");
    
    f_dir = pre + string(".f_dir");
    if_dir = pre + string(".if_dir");
    
    f_xpath = pre + string(".f_xpath");
    if_xpath = pre + string(".if_xpath");

    currentWeight = "none";
    
    NUMUNITS = 0;    
    NUMFINALUNITS = 0;
  }
  

// ==================================================================

Index::Index (const Collection& _c) : c(_c), currentWeight("none") { ; }

// ==================================================================

void Index::read( const string& id )
{
  string my_id = c.getName() + string("_") + id;
  string pre = Globals::home_index + my_id + string(".index");
  
  ifstream ifs( pre.c_str() );
  if (ifs.fail())
    Globals::errorAndExit("Bad ifs (Index::read), exiting ");	
  
  ifs >> identifier;
  ifs >> lexiconFileName; 
  ifs >> occurrenceFileName;
  
  ifs >> positionsFileName;
  ifs >> stopwordsFileName;
  ifs >> f_unt;
//  ifs >> if_unt;
  
  ifs >> f_par;
  ifs >> f_desc; 
  ifs >> if_par_desc;
  ifs >> dtdlistFileName;
  
  ifs >> cacheFileName;
  ifs >> quadFileName;
  
  ifs >> currentWeight;
  unsigned num;
  ifs >> num;
  weights = vector<string>(num);
  for (unsigned i=0; i<num; i++)
    ifs >> weights[i];

  ifs >> f_dir;
  ifs >> if_dir;
  ifs >> f_xpath;
  ifs >> if_xpath;

  ifs >> NUMUNITS;
  ifs >> NUMFINALUNITS;
  
  unsigned numroots;
  ifs >> numroots;
  
  roots = vector<unsigned>(numroots);
  for (unsigned i=0; i<numroots; i++)
  {
    ifs >> roots[i];
    if (ifs.fail())
      Globals::errorAndExit("Bad ifs (Index::read, II), exiting");
  }
  
  if (ifs.fail())
    Globals::errorAndExit("Bad ifs (Index::read, III), exiting");

  ifs.close();  
  
  if (!this->setStopwordList(stopwordsFileName))
    Globals::errorAndExit("ERROR: Selected index has an obsolete stopwords list. Exit");	  
}

// ==================================================================

void Index::write() const
{
  string my_id = c.getName() + string("_") + identifier;
  string pre = Globals::home_index + my_id + string(".index");
  
  ofstream fp( pre.c_str() );

  fp << identifier << "\n" << lexiconFileName << "\n" << occurrenceFileName << "\n";
  fp << positionsFileName << "\n" << stopwordsFileName << "\n" << f_unt << "\n";
  fp << f_par << "\n" << f_desc << "\n" << if_par_desc << "\n" << dtdlistFileName << "\n";
  fp << cacheFileName << "\n" << quadFileName << "\n";

  fp << currentWeight << "\n";
  fp << weights.size()  << "\n";
  for (unsigned i=0, numWeights=weights.size(); i<numWeights; ++i)
    fp << weights[i]  << "\n";
  
  fp << f_dir << "\n" << if_dir << "\n";
  fp << f_xpath << "\n" << if_xpath << "\n";
  fp << NUMUNITS << "\n" << NUMFINALUNITS << "\n";
  fp << roots.size() << "\n";
  
  for (unsigned i=0, numroots=roots.size(); i<numroots; ++i)
    fp << roots[i] << "\n";
  
  if (fp.fail()) Globals::errorAndExit("Bad fp (Index::write), exiting ");
}

// ==================================================================

void Index::printInfo() const
{
  cout << "Index '" << identifier << "', of the collection '" << c.getName() << "'\n" 
       << "  + List of stopwords used during indexation: " << stopwordsFileName << "\n"
       << "  + Number of units (total): " << NUMUNITS << "\n"
       << "  + Number of final units: " << NUMFINALUNITS << "\n" << flush;  
}

// ==================================================================

bool Index::setStopwordList(const string& _stopwordsFileName)
{
  stopwordsFileName = _stopwordsFileName;
  ifstream fp( stopwordsFileName.c_str() );
  
  if (fp.fail()) return false;
  
  while(!fp.eof())
  {
    string s("");
    fp >> s;
    if (s.length())
      stopwords.push_back(s);
  }
  
  std::sort(stopwords.begin(), stopwords.end() );

  return true;
}

// ==================================================================

Index::~Index() { }

// ==================================================================

void Index::addWeight(const string& name)
{
  weights.push_back(name);
}

// ==================================================================

void Index::delWeight(const string& name)
{
  weights.erase( std::remove(weights.begin(), weights.end(), name), weights.end());
}

// ==================================================================

void Index::remove(const string& colName, const string& indexName)
{
    string pre = Globals::home_index + colName + string("_") + indexName;
    
    string curr = pre + string(".lexicon");
    std::remove (curr.c_str());
       
    curr = pre + string(".fOcc");
    std::remove (curr.c_str());
    
    curr = pre + string(".fPos");
    std::remove (curr.c_str());
    
    curr = pre + string(".f_unt");
    std::remove (curr.c_str());
    
/*
    curr = pre + string(".if_unt");
    std::remove (curr.c_str());
*/
    
    curr = pre + string(".f_par");
    std::remove (curr.c_str());
    
    curr = pre + string(".f_desc");
    std::remove (curr.c_str());
    
    curr = pre + string(".if_par_desc");
    std::remove (curr.c_str());
    
    curr = pre + string(".dtds");
    std::remove (curr.c_str());
    
    curr = pre + string(".cache");
    std::remove (curr.c_str());
    
    curr = pre + string(".quad");
    std::remove (curr.c_str());
    
    curr = pre + string(".f_dir");
    std::remove (curr.c_str());
    
    curr = pre + string(".if_dir");
    std::remove (curr.c_str());

    curr = pre + string(".f_xpath");
    std::remove (curr.c_str());
    
    curr = pre + string(".if_xpath");
    std::remove (curr.c_str());
    
    curr = pre + string(".index");
    std::remove (curr.c_str());
}

// ==================================================================

