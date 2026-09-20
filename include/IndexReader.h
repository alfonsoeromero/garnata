/*
 * IndexReader.h - The Garnata Retrieval System
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

#ifndef __INDEXREADER_H__
#define __INDEXREADER_H__

using namespace std;

#include "Collection.h"
#include "DTDList.h"
#include "Unit.h"
#include "Occurrence.h"
#include "Index.h"
#include "Lexicon.h"
#include "VariableByteCoder.h"


class IndexReader : public Index {

  protected:
    /** Lexicon of the collection */
    Lexicon* L;
    
    /** List of DTDs of the collection */
    DTDList* dtds;
    
    /** Compression algorithm */
    VariableByteCoder vc;
  
  public:
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    */
    IndexReader(const Collection& _c, string _identifier);

    /** Destructor */
    virtual ~IndexReader();
};

#endif

