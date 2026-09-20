/*
 * RetrievalModel.cpp - The Garnata Retrieval System
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

#include "RetrievalModel.h"
#include <algorithm>
#include "PorterStemmer.hpp"
#include "NodeResult.h"

// ==================================================================

RetrievalModel::RetrievalModel (const Collection& _c, string _identifier) :
IndexReader(_c, _identifier), unitCache((unsigned) 2097152, (unsigned) 2097152, NUMUNITS), minWeight(0.0f) 
{  }

// ==================================================================

void RetrievalModel::setNumDocs(unsigned num) { NUMDOCS = num; } 

// ==================================================================

UnitReader* RetrievalModel::getFinalUnit(unsigned i)
{
  return unitCache.getUnitFromCache1(i);  
}

// ==================================================================

UnitReader* RetrievalModel::getComplexUnit(unsigned i)
{
  return unitCache.getUnitFromCache2(i);
}

// ==================================================================

void RetrievalModel::setStem(bool doStemming) { stem = doStemming; }

// ==================================================================

void RetrievalModel::setMinWeight(float mw) { minWeight = mw; } 

// ==================================================================

map<unsigned, float> RetrievalModel::intersect(const map<unsigned, float>& m1, 
                                   const map<unsigned, float>& m2)
{

  map<unsigned, float> result;
  map<unsigned, float>::const_iterator it=m1.begin();
  map<unsigned, float>::const_iterator _end=m1.end();
  
  // for each element in the m1 set...
  for ( ; it!=_end; ++it)
  {
    map<unsigned, float>::const_iterator found = m2.find(it->first);
    
    if (found != m2.end())
      result[it->first] = aggregate(it->second, found->second);    
  }

  return result;
}

// ==================================================================

map<unsigned, float> RetrievalModel::occurrs(unsigned idTerm) const
{
  Term* t = L->getTermFromId(idTerm);
  Occurrence occ = t->getOccurrence();
  
  map<unsigned, float> result;
  
  unsigned num = occ.getNum();
  for (unsigned i=0; i<num; ++i)
    result[ occ[i] ] = occ.getIWeight(i);
  
  return result;
}

// ==================================================================

string RetrievalModel::transform(const string& s) const 
{
  // transform a string for being indexed
  string salida;
  for(unsigned i=0, _size=s.size(); i<_size; ++i)
    if ( isalpha(s[i]) || valid(s[i]) ) 
      salida += tolower(s[i]);

  return salida;
}

// ==================================================================

bool RetrievalModel::valid(char c) const 
{
  // Size MUST be a multiple of four !. DO NOT ADD YOUR OWN CHARACTERS,
  // ONLY GROUPS OF FOUR CHARACTERS

  static const char chars[] = {"áÁéÉíÍóÓúÚñÑçÇüÜïÏÛûàÀèÈêÊöÖ"};
  static const unsigned length = sizeof(chars);

  // The following loop is UNROLLED. It is done that way because of
  // efficiency requirements. PLEASE DO NOT modify it UNLESS 
  // you EXACTLY know what you are doing

  bool found = false;
  for (unsigned i=0; i<length && !found; i+=4)
    found = (c == chars[i]) || (c == chars[i+1]) || (c == chars[i+2]) || (c == chars[i+3]);
	
  return found;
}

// ==================================================================

ProcessedQuery RetrievalModel::processQuery(const Query& q)
{
  vector<unsigned> identifiers;
	
  for (unsigned i=0, _size=q.size(); i<_size; ++i)
  {
    string s = transform (q[i]);
    
    if (s.size() > 0 && find(stopwords.begin(), stopwords.end(), s) == stopwords.end())
    {
      // If we are stemming...is is done here
      if (stem) s = PorterStemmer::stemWord(s);

      if (s.size())
      {
        unsigned id = L->getIdFromString(const_cast<char*>(s.c_str()));
        if (id != 0 && std::find(identifiers.begin(), identifiers.end(), id) == identifiers.end() ) 
        // if the term belongs to the lexicon, and was not already in the list... 
          identifiers.push_back(id);
      }
    }	  
  }
  std::sort(identifiers.begin(), identifiers.end(), MoreDocuments(L) );
  return ProcessedQuery(identifiers);  
}


// ==================================================================

bool RetrievalModel::stem = true;

// ==================================================================

unsigned RetrievalModel::NUMDOCS = 10000;

// ==================================================================

ostream& operator << (ostream& os, const Result& r)
{
  return os << "\t\t<result>\n\t\t\t<file>" << r.fileName.substr(0, r.fileName.length()-4) << "</file>\n"
  	<< "\t\t\t<path>" << r.route << "</path>\n"
	<< "\t\t\t<rsv>" << r.RSV << "</rsv>\n\t\t</result>\n";
}

// ==================================================================

RetrievalModel::~RetrievalModel() { }

// ==================================================================



