/*
 * IndexReader.cpp - The Garnata Retrieval System
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

#include "IndexReader.h"
#include "UnitReader.h"
#include <iostream>

// ==================================================================

IndexReader::IndexReader ( const Collection& _c, string _identifier ) : 
  Index( _c ), vc( )
  {
    vector<string> indexes = c.getIndexes();
    if ( find(indexes.begin(), indexes.end(), _identifier) != indexes.end() )	    
      this->read(_identifier );
    
    else
      Globals::errorAndExit("ERROR: unknown index identifier. Exiting");
  
    L = new Lexicon(lexiconFileName);
    dtds = new DTDList(dtdlistFileName);
    
    if (!L || !dtds)
      Globals::errorAndExit("Not enough memory (IndexReader::IndexReader), exiting");
    // We set the files for reading mode
    UnitReader::setFiles(f_par, f_desc, if_par_desc, f_unt, f_dir, if_dir, f_xpath, if_xpath, vc);
    Occurrence::setFiles (occurrenceFileName.c_str(), positionsFileName.c_str(), vc );
  }

// ==================================================================

IndexReader::~IndexReader() 
{
  delete L;
  delete dtds;
  UnitReader::close();
}

// ==================================================================

