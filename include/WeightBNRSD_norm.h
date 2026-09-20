/*
 * WeightBNRSD_norm.h - The Garnata Retrieval System
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

#ifndef __WEIGHTBNRSD_NORM_H__
#define __WEIGHTBNRSD_NORM_H__

#include "Weight.h"

using namespace std;

class WeightBNRSD_norm : public Weight {

  public:
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    */
    WeightBNRSD_norm (const Collection& _c, string _identifier);
    
    /** Return the importance of a term into a unit
    @param idTerm identifier of the term
    @param idUnit identifier of the unit
    @return importance of idTerm on idUnit
    */
    float rhoTU(unsigned idTerm, unsigned idUnit);

    /** Computes idf for a term
    @param N total number of documents
    @param n_i number of documents the term i appears in
    */
    float computeIdf (unsigned N, unsigned n_i) const;
        
    /** Destructor */
    ~WeightBNRSD_norm();
};

#endif

