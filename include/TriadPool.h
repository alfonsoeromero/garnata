/*
 * TriadPool.h - The Garnata Retrieval System
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

#ifndef __TriadPOOL_H__
#define __TriadPOOL_H__

#include <vector>
#include <queue>
#include <fstream>
#include "Triad.h"
#include "Globals.h"
#include "OccurrenceFile.h"

using namespace std;

/** @class TriadPool TriadPool.h 
* Wraps the temporal file where the Triads are written in, and
*  sorts them before writing weights
* @author Alfonso E. Romero <aromero@correo.ugr.es>
* @date 18/08/2005
* @version 0.1
*/
class TriadPool {
  private:
  
    /************ Internal declarations **********************/  
    class Inverted 
    {
      public:
       bool operator () (const Triad& q1, const Triad& q2) const
       {
         return (bool) (q1 < q2);
       }
    };
    
    struct TL 
    {
      Triad t;
      unsigned lot;
      TL() { ; }
      TL(Triad& _t, unsigned _lot) : t(_t), lot(_lot) { ; }
      TL(const TL& tl) : t((tl.t)), lot(tl.lot)  { ; }
        // WATCH OUT!, order in priority queue is from greater to less
	// Operator < should return 
      bool operator<(const TL& t0) const { return (bool) (t > t0.t); }
      ~TL(){ ; }
    };
    
    /** Maximum number of elements in the vector of Quads */
    const unsigned MAX_SIZE;
    
    /** Number of Triads written to the temporal file */
    unsigned writtenTriads;
    
    /** Temporal storage Triads */
    deque<Triad> tmp;
    
    /** Buffer of Triads for writing 
    to the file*/
    deque<Triad> tbuffer;

    /** List of marks */
    vector<unsigned> marks;
    
    /** Current Triad to be written in */
    unsigned current;
    
    /** Temporal file */
    ofstream tempFile;
    
    /** Name of the temporal file */
    string fileName;
    
    /** Writes the last Triads to the file and closes it */
    void flush();
    
    /** Sorts the temporal file for being converted into an weight file 
    @param ofs stream where to dump the weights of the terms 
    */
    void sortInverted(ofstream& ofs);
    
    /**
    
    */
    void dumpWeightList(ofstream& fp, bool last);
    
  public:
    /** Main constructor 
    @param KBytes maximum number of KBytes of memory to be used
    by this TriadPool 
    */
    TriadPool(const unsigned KBytes);

    /** Adds a Triad to the temporal file 
    @param t triad to be added
    */
    void add(const Triad& t);
    
    /** Writes a file of weights
    @param fp stream that represents the file
    */
    void writeWeightFile(ofstream& fp);

    /** Destructor */
    ~TriadPool();
};

#endif

