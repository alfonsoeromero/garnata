/*
 * Occurrence.h - The Garnata Retrieval System
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

#ifndef __OCCURRENCE_H__
#define __OCCURRENCE_H__

#include "Globals.h"
#include "InputCompressedBinaryFile.h"
#include "OutputCompressedBinaryFile.h"
#include "CompressionAlgorithm.h"
#include <fstream>
#include <vector>

class OccurrenceFile;

using namespace std;

/** @class Occurrence Occurrence.h 
* Represents one occurrence of a term (the list of the units 
*   [or documents] where it appears)
* @author Alfonso E. Romero <aromero@correo.ugr.es>
* @date 21/03/2005
* @version 0.1
*/
class Occurrence
{
  protected:
    unsigned num;     // Number of distinct units where the term appears
    vector<unsigned> unit;   // Array of the 'num' units where the term appears
    vector<unsigned> freq;   // Array of the frequencies of the term of each of the 'num' units it appears in 
    vector<long>  offset;     // Offsets in the position file
    vector<float> weight;    // Weights of the term in each unit 

    static InputCompressedBinaryFile occFile;       // Occurrence file
    static InputCompressedBinaryFile posFile;       // Position file
    
    /**
    * Produces a binary dump of the receiving object
    * @pre file dest MUST be opened and able to be written
    * @param dest a pointer to a file where objects are dumped
    * @post the pointer to file 'dest' is moved forward
    */
    void dump(OutputCompressedBinaryFile& dest);
  
    /**
    * Retrieve the values of an object of this class
    * from a binary file
    * @pre file dest MUST be opened and able to be read
    * @param source file to read
    * @post the pointer to file 'source' is moved forward
    * @note constant overload version
    */
    void retrieve(InputCompressedBinaryFile& source);	
    
  public:
    /** Empty constructor */
    Occurrence ();		

    /** Copy constructor */
    Occurrence ( const Occurrence& _o );

    /** Constructor with an offset
    @param id identifier of the associated term
    @param offset offset of the Occurrence in its file
    */	
    Occurrence ( long offset );

    /**
    * Main constructor
    * @param _num Number of distinct units
    * @param _unit array of identifiers of unit
    * @param _freq array of frequencies on corresponding units
    * @param _offset array of offsets on the position file
    * @param _weight array of weights of term in unit
    * @pre all the arrays MUST be allocated on dynamic memory
    */
    Occurrence(unsigned _num, const vector<unsigned>& _unit, const vector<unsigned> &_freq, 
              const vector<long>& _offset, const vector<float>& _weight);
    
    /**
    * Returns the number of distinct units the term appears in
    * @return the number of units
    */
    unsigned getNum() const;
	
    /** Copy operator */
    const Occurrence& operator=(const Occurrence& _o);

    /**
    * Returns the identifier of the n-esim units
    * where appears the term this Occurrence belongs to
    * @param n index to consult
    * @return identifier of the unit
    * @note n must be between 0 and num - 1. If not, this 
    *   method will abort execution
    */
    unsigned operator [](unsigned n) const;
	
    /** 
    *  Returns the weight corresponding to the i-th appearance of the term
    *  @param i number of the term whose weight we want (must be between 0 and getNum()-1)
    *  @return that weigth
    */
    float getIWeight (unsigned i) const;
	
    /** 
    *  Returns the frequency corresponding to the i-th appearance of the term
    *  @param i number of the term whose frequency we want (must be between 0 and getNum()-1)
    *  @return that frequency
    */		
    unsigned getIFreq (unsigned i) const;

    /** 
    *  Returns the list of positions corresponding to the i-th appearance of the term
    *  @param i number of the term whose positions we want (must be between 0 and getNum()-1)
    *  @return list of positions
    */				
    void getListIPos (unsigned i, vector<unsigned>& pos) const;

    /**
    * Prepares for its use the Occurrence class.
    *  @pre must be called at the beginning of execution, before using any
    *   Occurrence
    *  @param _occFile name of the file where the occurrences are stored in
    *  @param _posFile name of the file with the position lists of the terms
    *  @param ca compressionAlgorithm used
    *  @post Occurrence class is usable from now on
    */		
    static void setFiles (const string& _occFile, const string& _posFile, CompressionAlgorithm& ca);

    /** 
    *  Releases all the resources related to this class. Must be called at the end of
    *   the execution
    */
    static void close();

    /** Sets the weight on the unit j 
    @param j id of the unit
    @param w new weight
    @post this method does not write the unit back to file
    @return index of the unit j, -1 if j does not appears at occurrence
    */
    int setWeight(unsigned j, float w);

    /** Sets the entire weight list on this occurrence  
    @param _w new weight list
    @pre _w should be longer as needed
    @post this method DOES NOT write the unit back to file and
      copy the values from _w to w (no substitution of the array
      is done)
    */
    void setWeightList(float* _w);
    
    /** Updates the occurrence to a new value
    @param _offset offset in the file of occurrences
    @param occ compressed file of occurrences
    */
    void update(long _offset, OutputCompressedBinaryFile& occ);

    /** Return the weight of a term in the unit */
    float getWeightOn(unsigned u) const;

    /** Return the frequency of a term in the unit */
    unsigned getFreqOn(unsigned u) const;
    
    /**
    * Destructor
    */
    ~Occurrence();

    friend class OccurrenceFile;
};

#endif

