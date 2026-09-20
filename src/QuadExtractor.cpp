/*
 * QuadExtractor.cpp - The Garnata Retrieval System
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

#include "QuadExtractor.h"
#include <algorithm>
#include <sstream>
#include "PorterStemmer.hpp"

// ==================================================================

QuadExtractor::QuadExtractor (const string& s, unsigned _currentUnit, const Lexicon& _lex, const PositionFile& _pf) :
  pf(const_cast<PositionFile&>(_pf)), lex(& const_cast<Lexicon&>(_lex) ), currentUnit(_currentUnit) 
{
    position = 0;
    add(s);
}

// ==================================================================

void QuadExtractor::setStem(bool doStemming) { stem = doStemming; }

// ==================================================================


void QuadExtractor::add(const string& _s)
{
    string s = _s;
    // for each term appearing on this unit
    std::replace_if(s.begin(), s.end(), std::bind2nd(std::equal_to<char>(),'\\'), ' ');
    
    istringstream is(s);
    
    do{
      // 1.- we extract the next string
      string tmp;
      is >> tmp;
      ++position;
      
      // 2.- we transform it ("case folding", get rid of strange characters,...)
      tmp = transform(tmp);
      
      // 3.- Is the string a stopword?
      if ( tmp.size() && !std::binary_search (stopwords.begin(), stopwords.end(), tmp) )
      {
        // 3.0.- we stem it, if required (Porter)
        if (stem)
          tmp = PorterStemmer::stemWord(tmp);
        
        if (tmp.size())
        {
          // 3.1.- no => we get the identifier of the term
          unsigned _id = lex->getIdFromString( tmp );

          if (_id == 0)
          {
            // if the id did not exist, we create a new term...
            Term* t = new Term(tmp, 1);
            _id = lex->add(t); // ... and we add it to the lexicon
     
            // add to the list of unique terms
            terms.insert (_id);

          } else {
             // Otherwise (the term existed)
             // ... we increment the frequency of this term
             Term* t = lex->getTermFromId(_id); // O(1)
             t->incFrequency();

             if ( !std::binary_search(terms.begin(), terms.end(), _id) )
             {
               // if the term appeared for the first time on this
               // document.. we add it to the list of unique terms
               terms.insert (_id);
               t->incDocuments(); // the term appears in one more document
             } 

	  }
	
          positions[_id].push_back(position);

        } // if (tmp.size())

      }//if (tmp.size() && !std::binary_search...
      
    } while (!is.eof());	
	
}

// ==================================================================

unsigned QuadExtractor::getNumContained() const
{
  unsigned retval = 0;
  for (unsigned i=0, num=v.size(); i<num; ++i)
    retval += v[i].getFreq();

  return retval;
}

// ==================================================================

const vector<Quad>& QuadExtractor::getList() {

  // Construction of the quad vector
  for (set<unsigned>::const_iterator it=terms.begin(), end=terms.end(); it!=end; ++it)
    v.push_back( Quad (*it, currentUnit, positions[*it].size(), pf.add(positions[*it])) );

  return v;
}

// ==================================================================

vector<unsigned> QuadExtractor::getUniqueTermsList() const 
  { return vector<unsigned>(terms.begin(), terms.end()); }

// ==================================================================

void QuadExtractor::getTermListAndFrequencies(vector<unsigned>& _terms, vector<unsigned>& _freqs)
  { 
    _terms = vector<unsigned>(terms.begin(), terms.end()); 
    _freqs = vector<unsigned>(terms.size());
    unsigned i=0;
    for (set<unsigned>::const_iterator it=terms.begin(), end=terms.end(); it!=end; ++it)
      _freqs[i++] = positions[ *it ].size();
//      freqs[i++] = positions[*iter].size();
  }

// ==================================================================

inline string QuadExtractor::transform(const string& s) const
{
  // transform a string for being indexed
  string salida;
  for(unsigned i=0, size=s.size(); i<size; ++i)
    if ( isalpha(s[i]) || valid(s[i]) ) 
      salida += tolower(s[i]);

  return salida;
}

// ==================================================================

inline bool QuadExtractor::valid(char c) const
{
  // Size MUST be a multiple of four !. DO NOT ADD YOUR OWN CHARACTERS,
  // ONLY GROUPS OF FOUR CHARACTERS

  static const char chars[] = {"áÁéÉíÍóÓúÚñÑçÇüÜïÏÛûàÀèÈêÊöÖ"};
  static const unsigned length = sizeof(chars);

  // The following loop is UNROLLED. It's been done that way 
  // due to efficiency requirements. PLEASE DO NOT modify it UNLESS ¡
  // you EXACTLY know what you are doing

  bool found = false;
  for (unsigned i=0; i<length && !found; i+=4)
    found = (c == chars[i]) || (c == chars[i+1]) || (c == chars[i+2]) || (c == chars[i+3]);
	
  return found;
}

// ==================================================================

bool QuadExtractor::stem = false;

// ==================================================================

QuadExtractor::~QuadExtractor() { ; }

// ==================================================================

vector<string> QuadExtractor::stopwords;

// ==================================================================

void QuadExtractor::setStopwordList(const vector<string>& stop) {
  stopwords = stop;
}

// ==================================================================

