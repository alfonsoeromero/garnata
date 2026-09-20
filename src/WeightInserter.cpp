/*
 * WeightInserter.cpp - The Garnata Retrieval System
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

#include <fstream>
#include <cmath>
#include "WeightInserter.h"
#include "Globals.h"
#include "Unit.h"
#include "Occurrence.h"
#include "Term.h"
#include "UnitWriter.h"
#include "UnitReader.h"
#include "OutputCompressedBinaryFile.h"

// ==================================================================

WeightInserter::WeightInserter(const Collection& _c, string _identifier) : IndexReader(_c, _identifier) 
{ 
    //UnitWriter::setFiles(f_par, f_desc, if_par_desc, f_unt, f_dir, if_dir, f_xpath, if_xpath, vc);
//    we only set f_unt ...
}

// ==================================================================

inline
void WeightInserter::processUnit(unsigned id, float w, fstream& fp) const
{
  UnitReader u(id);
  UnitWriter v(u);
  v.updateWeight(w, fp);
}

// ==================================================================

bool WeightInserter::insert(string fileName)
{
  cout << "Weight file insertion started\n ";
  ifstream fp(fileName.c_str(), ios::binary);
  if (fp.fail())
  {
    cerr << "ERROR: File " + fileName + "does not exist" << endl;
    return false;
  }
  
  OutputCompressedBinaryFile output;
  output.setCompressionAlgorithm(&vc);
  output.open(occurrenceFileName + "v2", 10485760);

  string myname = f_unt + "v2";
  fstream unitsFile(myname.c_str(), ios::out | ios::binary);
  
  // -------------------------------------------
  // 1.- We insert weights into Units
  // -------------------------------------------
  
  unsigned block = Globals::weightInserterSize;
  float* buffer = new float[block];
  if (!buffer) Globals::errorAndExit("Not enough memory for buffer (WeightInserter::insert, I). Exiting.");
  
  unsigned quotient = NUMUNITS/block;
  unsigned remainder = NUMUNITS%block;
  
  unsigned processed = 0; // processed units
  
  // we process block*quotient + remainder units
  
  //1.1 quotient blocks
  for (unsigned i=0; i<quotient; ++i)
  {
    fp.read((char*) buffer, sizeof(float)*block);
    if (fp.fail()) Globals::errorAndExit("Bad fp (WeightInserter::insert, I). Exiting");
    for (unsigned j=0; j<block; ++j)
    {
      /*UnitReader u(processed);
      
      UnitWriter v(u);
      
      v.setWeight(buffer[j]);
      
      unitsFile.seekp(u.getId() * Unit::SIZE_UNIT, std::ios_base::beg);
      v.write(unitsFile);*/
      processUnit (processed, buffer[j], unitsFile);
    
      ++processed;
    } 
  }
  
  //1.2 remainder units 
  if (remainder>0)
  {
    fp.read((char*) buffer, sizeof(float)*remainder);
    if (fp.fail()) Globals::errorAndExit("Bad fp (WeightInserter::insert, II). Exiting");
    for (unsigned j=0; j<remainder; ++j)
    {
     /* UnitReader u(processed);
      
      UnitWriter v = u;
            
      v.setWeight(buffer[j]);
      unitsFile.seekp(u.getId() * Unit::SIZE_UNIT, std::ios_base::beg);
      
      v.write(unitsFile);*/
      processUnit (processed, buffer[j], unitsFile);
    
      ++processed;
    }
  }
  
  // -------------------------------------------
  // 2.- We insert weights into Occurrences
  // -------------------------------------------
  
  for (unsigned i=0; i<L->getNum(); i++)
  {
    // 1.- We get the term
    Term* t = L->getTermFromId(i+1);
    
    // 2.- Retrieve the occurrence
    Occurrence occ = t->getOccurrence();
    
    // 3.- Number of weights to read?
    unsigned number = t->getNumDocs();
    
    if (number > block) 
    {
      // we must reallocate buffer!!!
      delete [] buffer;
      block = number;
      buffer = new float[block];
      if (!buffer)
        Globals::errorAndExit("Not enough memory for buffer (WeightInserter::insert, II). Exiting.");   
    }
  
    // 4.- We read the weights from the file (ONLY 'number' weights!!!)
    fp.read((char*) buffer, sizeof(float)*number);
    
    if (fp.fail())
    {
	cerr << "Fail at term " << i+1 << endl;
//	Globals::deleteFile(occurrenceFileName + "v2");
//	Globals::deleteFile(f_unt + "v2");
	Globals::errorAndExit("Bad fp (WeightInserter::insert, III). Exiting");
    }
    
    // 5.- Assignment of the new Weight and storage of the occurrence
    
    occ.setWeightList(buffer); // assignment
    t->updateOccurrence(occ, output);  // storage    
  }
  
  unitsFile.close();
  fp.close();
    
  Globals::deleteFile(occurrenceFileName);
  Globals::renameFile(occurrenceFileName + "v2", occurrenceFileName);
  
  Globals::deleteFile(f_unt);
  Globals::renameFile(f_unt + "v2", f_unt);
  
  // -------------------------------------------
  // 3.- Memory unallocation
  // -------------------------------------------
  
  delete [] buffer;
  return true;
}

// ==================================================================

WeightInserter::~WeightInserter() {  }

// ==================================================================

