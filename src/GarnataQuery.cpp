/*
 * GarnataQuery.cpp - The Garnata Retrieval System
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

#include <sstream>
#include "GarnataQuery.h"
#include "BNR-SD.h"
#include "Globals.h"
#include "Query.h"
#include <algorithm>

// ==================================================================

GarnataQuery::GarnataQuery(string collectionName, string indexName, model identifier, bool doStemming) :
  Garnata (), mode(CONSOLE), opened(false) 
{

  // 1.- We search for the collection name and index name
  if(!setCurrent(collectionName)) // collection does not exist
    Globals::errorAndExit("ERROR: collection name unknown. Exiting.");

  vector<string> names = current->getIndexes();
  
  // We search the identifier among the others
  if (std::find(names.begin(), names.end(), indexName) == names.end())
    Globals::errorAndExit("ERROR: index name unknown. Exiting.");

  // 2.- Creation of the retrieval model
  switch (identifier) 
  {
    case __BNR_SD:
      rm = new BNR_SD(*current, indexName);
      
      break;
      
    // Here we can include more models...
    
    default:
      Globals::errorAndExit("ERROR: Unknown retrieval model (GarnataQuery::GarnataQuery). Exiting.");
  }

  RetrievalModel::setStem(doStemming);
}

// ==================================================================

bool GarnataQuery::isCommand(const string& s) const
{
  unsigned i=0;
  while ( isspace(s[i]) ) 
	  ++i;
  return (bool)(s[i]=='#');
}

// ==================================================================

bool GarnataQuery::processCommand(const string& s)
{
  // 0.- We remove the trailing sharp sign
  unsigned i=0;
  while (isspace(s[i]) || s[i] == '#') 
	  ++i;
  
  // 1.- we obtain the list of words, removing the "sharp sign"
  
  istringstream is(s.substr(i, s.size()-i));
  vector<string> res;
  while (!is.eof())
  {
    string s("");
    is >> s;
    res.push_back(s);
  }
  
  // 2.- We search for a correct number of arguments
  unsigned num = res.size();
  if (num == 1)
  {
    if (res[0] == "help")
      showHelp(false);
    else if (res[0] == "quit")
      return false;
    else showHelp(true);
  } else if (num == 3) {
    if (res[0] == "set")
    {
      if (res[1] == "docs")
      {
      
        istringstream _is(res[2]);
	unsigned mini;
	_is >> mini;
        if (_is.fail()) showHelp(true);
	else rm->setNumDocs(mini);
	
      } else if (res[1] == "minimum") {
      
        istringstream _is(res[2]);
	float w;
	_is >> w;
        if (_is.fail()) showHelp(true);
	else rm->setMinWeight(w);
	
      } else if (res[1] == "output") {
        
	if (opened) 
	{
	  opened = false;
	  output.close();
	}
	  
        if (res[2] == "none")
	  mode &= (~_FILE);
	  
	else {
	  mode |= _FILE;
	  output.open(res[2].c_str());
	  if (!output.fail()) opened = true;
	   else cerr << "ERROR: could not open file " << res[3] << endl;
	}
      }
      
    } else showHelp(true);
    
  } else if (num == 4) {
  
    if (res[1] == "console" && res[2] == "output")
    {
      if (res[3] == "on")
        mode |= CONSOLE;
      else if (res[3] == "off")
        mode &= (~CONSOLE);
	
    } else showHelp(true);
  
  
  } else showHelp(true); 
  return true;
}

// ==================================================================

void GarnataQuery::showHelp(bool error)
{

  if (error)
    cerr << "ERROR: unknown command, please try one of these:\n";
  else cerr << "HELP:\n";

  cerr << "  (Note that every command should be preceded by a sharp sign => #)\n"
       << "  '# help': shows this help\n"
       << "  '# set docs X': sets the maximum number of documents to retrieve to X\n"
       << "  '# set output X': sets the output of this program to the file X, besides using the console\n"
       << "  '# set output none': turns off the output to the file (if there were any opened) of this program\n"
       << "  '# set console output on|off': turn on (resp. off) the output of this program to the console\n"
       << "  '# quit': terminates the execution of this program\n" 
       << "  ANY OTHER LIST OF TERMS NOT BEING PRECEDED BY '#' WILL BE TREATED AS A QUERY\n" 
       << "    (as a conjunction of the listed term)\n" << endl;       
}

// ==================================================================

vector<Result> GarnataQuery::makeQuery(const string& s)
{
  Query q(s);
  ProcessedQuery pq = rm->processQuery(q);
  vector <Result> v = rm->makeQuery (pq);
  
  
  if (v.size() && s.size())
  {
    string head = " - File name -\t- XPath Route -\t-P(relevance)\n";
    if (mode | _FILE) output << head;
    if (mode | CONSOLE) cout << head;
  
    // We process the output of the retrieval model
    for (unsigned i=0; i<v.size(); i++)
    {
      char buff[30];
      sprintf(buff, "%.5f", v[i].RSV);
      string num(buff);
      string s = v[i].fileName + "\t" + v[i].route + "\t" + num + "\n";
	  
      if (mode | _FILE) output << s;
      if (mode | CONSOLE) cout << s;   
    }
    
    if (mode | _FILE) output << "\n";
    if (mode | CONSOLE) cout << "\n";
    
  } else { 
    string head = " No documents matching the query have been found\n\n";
    if (mode | _FILE) output << head;
    if (mode | CONSOLE) cout << head;
    
  }
  
  if (mode | _FILE) output << flush;
  if (mode | CONSOLE) cout << flush;
  
  return v;
}

// ==================================================================

GarnataQuery::~GarnataQuery() { delete rm; }
