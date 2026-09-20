/*
 * QuadPool.h - The Garnata Retrieval System
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

#ifndef __QUADPOOL_H__
#define __QUADPOOL_H__

#include <vector>
#include <queue>
#include <fstream>
#include "Quad.h"
#include "Globals.h"
#include "OccurrenceFile.h"

using namespace std;

/** @class QuadPool QuadPool.h 
* Wraps the temporal file where the Quads are written in, and
*  sorts them before creating inverted indexes
* @author Alfonso E. Romero <aromero@correo.ugr.es>
* @date 16/06/2005
* @version 0.1
*/
class QuadPool {
  private:
  
    /************ Internal declarations **********************/  
    class Inverted 
    {
      public:
       bool operator () (const Quad& q1, const Quad& q2) const
       {
         return (bool) (q1 < q2);
       }
    };
    
    struct QL 
    {
      Quad q;
      unsigned lot;
      QL() { ; }
      QL(Quad& _q, unsigned _lot) : q(_q), lot(_lot) { ; }
      QL(const QL& ql) : q((ql.q)), lot(ql.lot)  { ; }
        // WATCH OUT!, order in priority queue is from greater to less
	// Operator < should return 
      bool operator<(const QL& q0) const { return (bool) (q > q0.q); }
      ~QL(){ ; }
    };
    
    /** Maximum number of elements in the vector of Quads */
    const unsigned MAX_SIZE;
    
    /** Number of Quads written to the temporal file */
    unsigned writtenQuads;
    
    /** Temporal storage of Quads */
    vector<Quad> tmp;

    /** List of marks */
    vector<unsigned> marks;
    
    /** Current Quad to be written in */
    unsigned current;
    
    /** Temporal file */
    ofstream tempFile;
    
    /** Name of the temporal file */
    string fileName;
    
    /** Writes the last Quads to the file and closes it */
    void flush();
    
   
  public:
    /** Main constructor 
    @param KBytes maximum number of KBytes of memory to be used
    by this QuadPool 
    @param fileName name of the file
    */
    QuadPool(const unsigned KBytes, const string& fileName);

    /** Adds a Quad to the temporal file */
    void add(const Quad& q);

    /** Sorts the temporal file for being converted into an inverted index 
    @param _occFile associated OccurrenceFile
    */
    void writeOccurrences(OccurrenceFile& occFile);

    /** Destructor */
    ~QuadPool();
};

#endif

