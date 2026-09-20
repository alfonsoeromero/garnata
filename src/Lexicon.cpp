/*
 * Lexicon.cpp - The Garnata Retrieval System
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

#include "Lexicon.h"
#include <algorithm>
#include <vector>

// ==================================================================

Lexicon::Lexicon(unsigned _maxCapacity=1000) 
  : num(0), maxCapacity(_maxCapacity), metaIndex(0)
{
  v = new Term*[maxCapacity];
  metaIndex = new Term*[maxCapacity];
  if (!v)
    Globals::errorAndExit("ERROR: Insufficient memory for 'v', exiting.");
  if (!metaIndex)
    Globals::errorAndExit("ERROR: Insufficient memory for 'metaIndex', exiting.");
}

// ==================================================================

Lexicon::Lexicon(const string& lexiconDumped)
{
  ifstream input(lexiconDumped.c_str(), ios::in | ios::binary);
  if (input.fail()) Globals::errorAndExit("ERROR: couldn't open file to retrieve Lexicon, exiting.");
  
  retrieve(input);
}

// ==================================================================

void Lexicon::retrieve(ifstream& input)
{
  // Reading header... (num)    
  input.read((char*)&num, sizeof(unsigned));  

  if (input.fail()) Globals::errorAndExit ("Bad 'input' (Lexicon::retrieve), exiting");
  maxCapacity = num;
 
  // Memory allocation
  v = new Term*[num];
  if (!v) Globals::errorAndExit("Not enough memory for 'v' (Lexicon::retrieve), exiting.");
  metaIndex = new Term*[num];
  if (!metaIndex) Globals::errorAndExit("Not enough memory for 'metaIndex' (Lexicon::retrieve), exiting.");
  
  for(unsigned i=0; i<num; ++i)
  {
    // we retrieve the whole term from 'input'
    v[i] = new Term();
    
    v[i]->retrieve(input);
     
    // we adjust metaIndex pointers
    unsigned _id = v[i]->getId();
    metaIndex[_id-1] = v[i];
  }    
}

// ==================================================================

void Lexicon::write(const string& lexiconName) const
{
  ofstream output(lexiconName.c_str(), ios::binary | ios::trunc );
  
  if (output.fail())
   Globals::errorAndExit("ERROR: couldn't open file to dump Lexicon. Exiting.");

  // Writing header... (num)
  output.write((char *)&num, sizeof(unsigned));
  
  for (unsigned i=0; i<num; ++i)
    v[i]->dump(output);
}

// ==================================================================

unsigned Lexicon::getNum() const
{
  return num;
}

// ==================================================================

unsigned Lexicon::add(Term *newTerm)
{
  // 1.- Need more memory?
  if (num == maxCapacity)
  {
    // we need to allocate more memory 
    // We increment a 100% more the current maximum capacity
    maxCapacity *= 2;
    
    Term** vNew = new Term*[maxCapacity];
    if (!vNew) Globals::errorAndExit("ERROR: Insufficient memory for 'vNew', exiting.");
    
    // Copying to new arrays and deletion of old arrays => vNew
    std::copy (v, v+num, vNew);
    delete [] v;
    v = vNew;
        
    // we also increment metaIndex maximum capacity
    Term** _metaIndex = new Term*[maxCapacity];
    if (!_metaIndex) Globals::errorAndExit("ERROR: Insufficient memory for 'metaIndex', exiting.");
      
    std::copy (metaIndex, metaIndex+num, _metaIndex);
    delete [] metaIndex;
    metaIndex = _metaIndex;
  }
  
  // 2.- We search for the place to store 
  // the new term
  
  if ( num>0 && Lexicon::compareTerms(v[num-1], newTerm)>0 ) // if newTerm should NOT be placed at the end...
  {
    Term** pos = std::lower_bound( v, v+num, newTerm, LexiconSearch () );
    copy_backward ( pos, v+num, v+num+1 );
    *pos = newTerm;
  } else 
    v[num] = newTerm;
  
  // 3.- Assignment of the id to the term, adjustment of metaIndex structure  
  newTerm->setId(num);
  // one more term in the Lexicon
  metaIndex[num] = newTerm;
  // increment
  ++num;

  // 4.- return value and end of method 
  return num;
}   

// ==================================================================

unsigned Lexicon::getIdFromString(const string& str) const
{
  unsigned retval = 0;
  
  if (num)
  { 
    // if term is found... And lexicon is not empty
    Term ** t = lower_bound(v, v+num, str, Lexicon::greaterTerm () );
      
    if ( t!=(v+num) && (*t)->getTermString() == str )      
      retval = v[t - v]->getId();
  }

  return retval;
}
    
// ==================================================================
    
Term* Lexicon::getTermFromId(unsigned _id) const
{
  // This function makes usage of the metaIndex structure  
  // First, we verify we are dealing with a valid value of "_id"
  if (_id <= num && _id)
    return metaIndex[_id-1];
  else {
    cout << "id => " << _id << "\n";
    Globals::errorAndExit("Term id provided to the system isn't valid (Lexicon::getTermFromId), exiting (should be between 1 and Lexicon::getNum)");
  }
  
  return 0;
}

// ==================================================================

Term* Lexicon::getTermFromOrder(unsigned o) const
{
  if (o >= num)
    Globals::errorAndExit("Term id provided to the system isn't valid (Lexicon::getTermFromOrder), exiting (should be between 1 and Lexicon::getNum)");
  
  return v[o];
}

// ==================================================================

inline int Lexicon::compareTerms(const void* elem1, const void* elem2)
{
  // Keep an eye open! 
  // elem1 AND elem2 should be both Term* (pointer to term)
  return ((Term *) elem1)->getTermString().compare( ((Term *) elem2)->getTermString() );
}

// ==================================================================

void Lexicon::dumpCacheFile(const string& fileName, unsigned size) const
{

  if (size > num) Globals::errorAndExit("Size too high (Lexicon::dumpCacheFile), exiting");
  
  vector <pair <unsigned, unsigned> > output(size); // (freq, id)
  
  {
    vector <pair <unsigned, unsigned> > temp(num); // (freq, id)
  
    for (unsigned i=0; i<num; ++i)
      temp[i] = make_pair ( v[i]->getFreq(), v[i]->getId() );

    std::partial_sort (temp.begin(), temp.begin() + size, temp.end(), Globals::pair_gt);
    std::copy (temp.begin(), temp.begin() + size, output.begin());
  }
  
  vector <unsigned> cached_terms (size);
  
  for (unsigned i=0; i<size; ++i)
    cached_terms[i] = output[i].second;

  std::sort(cached_terms.begin(), cached_terms.end());
  
  // We dump the file
  
  ofstream of (fileName.c_str());
  if (of.fail()) Globals::errorAndExit("Bad 'of' (Lexicon::dumpCacheFile I), exiting");
  of << size << endl << num << endl;
  
  for (vector<unsigned>::const_iterator it = cached_terms.begin(), end=cached_terms.end(); it!=end; ++it)
    of << *it << endl << v[*it-1]->offsetFileOcc << endl;
  
  if (of.fail()) Globals::errorAndExit("Bad 'of' (Lexicon::dumpCacheFile II), exiting");
  of.close();

}

// ==================================================================

Lexicon::~Lexicon()
{
  if (v)
  {
    for(unsigned i=0; i<num; ++i)
      delete v[i];
    delete [] v;
  }
  
  if (metaIndex)
    delete [] metaIndex;
}

// ==================================================================

