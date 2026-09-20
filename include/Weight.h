/*
 * Weight.h - The Garnata Retrieval System
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

#ifndef __WEIGHT_H__
#define __WEIGHT_H__
#include <string>
#include <fstream>
#include <cmath>
#include <map>

#include "Globals.h"
#include "TriadPool.h"
#include "IndexReader.h"
#include "Occurrence.h"

using namespace std;

class Weight : public IndexReader {

  protected:
  
    /** Number of terms in the system */
    unsigned NUM;
  
    /** Idf of the term "i" */
    float* _idf;

    /** Associates every unit identifier to
    its weight */
    std::map<unsigned, float, less<unsigned> > weightUnit;
    
    /** Number of times a certain term appears in current unit */
    std::map<unsigned, unsigned> f_i;

    /** Place where storing temporally the triads */
    TriadPool* tp;

    /** Identifier of the final unit we are processing */
    unsigned currentUnitIdentifier;
    
    /** Maximum frequency of the terms on this unit (currentUnit Identifier) */
    unsigned maxFreq;
    
    /** 1/maxFreq */
    float maxInv;
    
    /** Tells if normalization is activated */
    bool normalize;
    
    /** Sets the weight of a unit on its container on the file of weights 
    @param _id  identifier of the unit whose weight on its container
           we are going to update
    @param _w numerical value of the weight
    */
    void setWeightOnUnit(unsigned _id, float _w);
    
    
    /** Sets the weight of a term in its containing unit  on the file of weights
    @param _idTerm identifier of the term
    @param _idUnit identifier of the unit
    @param _w numerical value of the weight
    */
    void setWeightTermOnUnit(unsigned _idTerm, unsigned _idUnit, float _w);
    
    
    /** Computes weight on a root unit and in all its ascendants
    @param id identifier of the root unit
    @pre unit identified by id should be root
    */
    float computeWeight (unsigned id);    
    
  public:
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    @param _normalize true if normalization is neede (weight for all terms
	    in a unit sum 1, and weights for all units contained in another
	    unit sum 1)
    */
    Weight ( const Collection& _c, string _identifier, bool _normalize );

    
    /** Creates the weight file specified by fileName
    @param fileName name of the weight file
    */
    void createWeightFile (const string& fileName);

    
    /** Return the importance of a term into a unit
    @param idTerm identifier of the term
    @param idUnit identifier of the unit
    @return importance of idTerm on idUnit
    */
    virtual float rhoTU(unsigned idTerm, unsigned idUnit) = 0;

    
    /** Computes idf for a term
    @param N total number of documents
    @param n_i number of documents the term i appears in
    */
    virtual float computeIdf (unsigned N, unsigned n_i) const = 0;

    
    /** Returns the idf for the term i (i=1,...,NUM)
    @param i index of the term
    */
    float idf (unsigned i) const;
    
    
    /** Return the number of occurrences of a term in 
    an unit
    @param i identifier of the term
    @param j identifier of the unit    
    */
    unsigned tf(unsigned i, unsigned j);
        
    /** Return the (normalized) number of occurrences of a term in 
    an unit. This normalized tf is obtained by dividing the classical
    tf by the maximum frequency of the terms of that document
    @param i identifier of the term
    @param j identifier of the unit    
    */
    float tf_norm(unsigned i, unsigned j);
    
    /** Destructor */
    virtual ~Weight ();    
};

#endif

