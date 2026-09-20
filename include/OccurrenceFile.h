/*
 * OccurrenceFile.h - The Garnata Retrieval System
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

#ifndef _OCCURRENCEFILE_H__
#define _OCCURRENCEFILE_H__

#include "Quad.h"
#include "Occurrence.h"
#include "Lexicon.h"
#include "Term.h"
#include "OutputCompressedBinaryFile.h"
#include "VariableByteCoder.h"

#include <vector>
#include <queue>
#include <string>

using namespace std;

class OccurrenceFile
{
  private:
    /** Buffer of quads */
    deque<Quad> v;
    
    /** Related lexicon */
    const Lexicon& L;

    /** index of last element of
    v to be processed
    */
    unsigned lastElem;
    
    /** Current offset on the occurrence file */
    long currentOffset;
    
    /** File to write occurrences in */
    static OutputCompressedBinaryFile occFile;
    
    /** Compression algorithm */
    VariableByteCoder vc;
    
    /** Writes the buffer of quads
    @param final tells if it is the final 
        stage of writing
    */
    void flush(bool final);
    
    /** Writes an Occurrence to "occFile" from a 
    vector of Quad
    @param vq vector where to write the Occurrence from
    */
    void writeOccurrence(const vector<Quad>& vq);
    
  public:
    /** Main constructor
    @param _lex related lexicon
    */
    OccurrenceFile (const Lexicon& lex, const string& fileName);
    
    /** Adds all components of a vector to the buffer
    @param _v vector to be added
    */
    void addAll(const vector<Quad>& _v);

    /** Flushes and closes the occurrence file */    
    void write();

    /** Destructor */
    ~OccurrenceFile ();
};

#endif


