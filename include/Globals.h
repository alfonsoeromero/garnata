/*
 * Globals.h - The Garnata Retrieval System
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

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <cstdlib>
#include <string>
#include <iostream>
#include <utility>
#include <ctime>

using namespace std;

class Globals {
  public:
   //! Home of the system 
   static string home;
   
   //! Configuration file
   static string conf_file;
   
   //! Home of the different indexes
   static string home_index;

   //! Home of the different weights
   static string home_weight;
   
   //! Home of the different collections
   static string home_collections;
      
   //! Home of the different stopwordlists
   static string home_stopwords;
   
   //! constant for using in class Unit (represents a container unit)
   static const char container = 0x01;  

   //! constant for using in class Unit (represents a final unit)
   static const char pcdata = 0x02;  

   //! constant for using in class Unit (represents a virtual unit)
   static const char virtual_unit = 0x04;  
   
   //! constant .... (in cache)
   static const char in_cache = 0x08;

   //! size of the cache of occurrences (used during indexation)
   static unsigned cacheSize;
   
   //! Size of Quad Cache (used during indexation)
   static unsigned quadPoolKBytes; 
   
   //! initial size of the lexicon (used during indexation)
   static unsigned initialLexiconSize;
   
   //! size of the buffer of the Position file (used during indexation)
   static unsigned positionFileBufferSize;

   //! size of the buffer of the WeightInserter (used during reading from file)
   static unsigned weightInserterSize;
   
   /** 
   *  Informs of an error and exits execution 
   *  @param _error error string which will be printed
   *  @post the execution is aborted
   */
  static void errorAndExit(char *_error);

  /** 
   *  Informs of a tiny error and continues execution
   *  @param _message warning string which will be printed
   */
  static void showWarning(char* _message);
  
  /** Tells if a pair is greater than other (using the first
	  component)
  @param a first pair
  @param b second pair
  */
  static bool pair_gt(const pair<unsigned, unsigned> &a,
    const pair<unsigned, unsigned> &b);
  
  /** Checks if a file exists or not
  @param fileName complete route of the file which existance
       we are testing
  @return true if the file exists, false if not
  */
  static bool fileExists(const string& fileName);
  
  
  /** Copies one file into another
  @param source name of the source file
  @param destiny name of the destiny file  
  @return true if everything went OK
  */
  static bool copyFile(const string& source, const string& destiny);
  
  /** Renames one file into another fileName
  @param oldname old name of the file
  @param newname new name of the file  
  @return true if everything went OK
  */
  static bool renameFile(const string& oldname, const string& newname);
  
  /** Delete one file
  @param fileName name of the file to delete
  @return true if everything went OK
  */
  static bool deleteFile(const string& fileName);

  /** Prints elapsed time between two time marks
  @param initial first time mark
  @param end second time mark
  */
  static void printTime(time_t initial, time_t end);
};

class Term;

#endif
