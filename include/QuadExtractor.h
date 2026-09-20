/*
 * QuadExtractor.h - The Garnata Retrieval System
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

#ifndef _QUADEXTRACTOR_H__
#define _QUADEXTRACTOR_H__

using namespace std;

#include <string>
#include <set>
#include <vector>
#include <map>
#include "Quad.h"
#include "Lexicon.h"
#include "PositionFile.h"
#include "Globals.h"

class QuadExtractor {
  private:
    /** Stopword list */
    static vector<string> stopwords;

    /** List of term identifiers appearing in this unit */
    set<unsigned> terms;
   
    /** Obtained quads */
    vector<Quad> v;
    
    /** File with positions of terms */
    PositionFile& pf;
    
    /** Lexicon used during inversion process */
    Lexicon* lex;
    
    /** Current position of processed term */
    unsigned position;
    
    /** Id of the unit being processed */
    unsigned currentUnit;
    
    /** For each term, we store here its list of positions */
    map< unsigned, vector<unsigned> > positions; 
    
    /**
    Transforms a string that is going to be 
    indexed (doing case folding and 
    removing punctuation marks)
    @param s string to be transformed
    @return string transformed
    */
    string transform(const string& s) const;
    
    /**
    Tells if a character (which is not 'isalpha' valid) is an
    ASCII valid character to be indexed
    @param c character to be tested
    @return true if it is valid
    */
    bool valid(char c) const;

    /** Show if we are doing stemming, or not */
    static bool stem;

  public:
    /** Main constructor 
    @param s string where to extract the Quads from
    @param currentUnit identifier of current document
    @param _lex lexicon
    @param _pf PositionFile
    */
    QuadExtractor ( const string& s, 
                    unsigned currentUnit, 
                    //const vector<string>& _stopwords, 
                    const Lexicon& _lex, 
                    const PositionFile& _pf);

    /** Returns the number of terms 
    (sum of absolute frequencies of the different
    terms associated to this QuadPool).
    @return unsigned number of terms
    */
    unsigned getNumContained() const;

    /** Adds a line of text to the extractor for being processed
    @param s string with the terms
    */
    void add(const string& s);
    
    /** Returns the list of
        unique terms appearing in this text fragment
    @return vector with the term identifiers
    */
    vector<unsigned> getUniqueTermsList() const;

    /** Returns the list of
        unique terms appearing in this text fragment and the list of frequencies
    @param terms vector with the term identifiers
    @param freqs vector with frequencies
    */
    void getTermListAndFrequencies(vector<unsigned>& terms, vector<unsigned>& freqs);

    /** Returns the list of Quads corresponding to the string
    given in the constructor
    @return list of quads
    */
    const vector<Quad>& getList();

    /** Method to notify this class we are doing steemming (true) or not (false)
    @param doStemming true if we are doing stemming
    */
    static void setStem(bool doStemming);

    /** Sets the stopword list
    @param stop stopword list
    */
    static void setStopwordList(const vector<string>& stop);

    /** Destructor */
    ~QuadExtractor ();
};

#endif

