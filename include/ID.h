/*
 * ID.h - The Garnata Retrieval System
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

#ifndef __ID_H__
#define __ID_H__

#include "RetrievalModel.h"
#include "Result.h"
#include "NodeResult_ID.h"
#include "ProcessedQuery.h"
#include "BNR-SD.h"
#include <vector>
#include <utility>

using namespace std;

template <typename T>
class ID : public _BNR_SD<T> {
  protected :
    //! Internal class for sorting the resulting vector
    template <typename TT>
    class NodeResult_ID_Ptr
    {
      public:
        bool operator () (const TT* n1, const TT* n2) const
        {
          return (n1->getRSV() > n2->getRSV());
        }
    };
    
    /** Mode to compute RSV from utilities */
    RUM_mode mode;
    
  public:
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    @param _mode mode to compute RSV
    @param normalize true if we are dividing RSV of each unit by its nIdf
    */
    ID ( const Collection& _c, const string& _identifier, RUM_mode _mode, bool normalize );
    
    /** Compute the NIdfs of the list of nodes
    @param groups list of grous, whose descendants are the nodes
    @param L current index lexicon
    */
    void computeNIdf(vector<NodeGroup<T> >& groups, const Lexicon& L);

    /** Compute the NIdfs of the list of nodes, assigning the nIdf of the container article
    @param groups list of grous, whose descendants are the nodes
    @param L current index lexicon
    */
    void computeGlobalNIdf(vector<NodeGroup<T> >& groups, const Lexicon& L);

    /** Makes a query to the system
    @param pq 
    @return vector of pairs (document, weitght) 
            sorted by descending weight
    */
    vector< Result > makeQuery(const ProcessedQuery& pq);
  
    /** Destructor */
    virtual ~ID ();
};

#endif


