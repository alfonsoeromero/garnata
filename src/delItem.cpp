/*
 * delItem.cpp - The Garnata Retrieval System
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

#include "Index.h"
#include "Collection.h"
#include "Garnata.h"
#include "Globals.h"
#include <iosfwd>

typedef enum {NOPARAMS=0, COLLECTION=1, INDEX=2, STOPWORD=3, WEIGHT=4, ERR=5} request;

// ==================================================================

request processArgs(int argc, char* argv[])
{  
  request retval;
  
  switch (argc)
  {
    case 1:
      retval = NOPARAMS;
      break;
      
    case 3:
      if (!strcmp(argv[1], "collection"))
        retval = COLLECTION;
      else if (!strcmp(argv[1], "stopword"))
        retval = STOPWORD;
      else retval = ERR;
      break;
  
    case 4:
      if (!strcmp(argv[1], "index"))
        retval = INDEX;
      else retval = ERR;
      break;
    
    case 5:
      if (!strcmp(argv[1], "weight"))
        retval = INDEX;
      else retval = ERR;
      break;
    
    default:
      retval = ERR;
  }	
	
  return retval;
}

// ==================================================================

void showHelp() 
{
  cerr << "'delItem collection X':\tdeletes the collection X, and its " << endl
       << "     associated indexes" << endl
       << "'delitem index X Y':\tdeletes the index Y of the collection Y" << endl
       << "'delItem stopword X':\tdeletes the stopwords file X (indexes using this" << endl
       << "     file may not work properly" << endl
       << "'delItem weight X Y Z':\tdeletes the weight file Z, of the index Y," << endl
       << "     of the collection X" << endl;
}

// ==================================================================

char RUsure(string s)
{
  char c;
  do {
    cout << s << endl;
    cin >> c;
  } while (toupper(c) != 'N' && toupper(c) != 'Y');
  return toupper(c);
}

// ==================================================================


int main(int argc, char* argv[])
{
  Garnata g;
  
  switch (processArgs(argc, argv))
  {
    case NOPARAMS:
      cerr << "USE:\n";
      showHelp();
    break;	  
	  
    case COLLECTION:
    {
      string col(argv[2]);
      if ( RUsure ( "About to remove collection: " + col + 
                    " (and its associated indexes). Are you sure? (y/n)"  ) == 'Y') {

        if(!g.setCurrent(col))
        {
          cerr << "ERROR: bad collection name\n" << flush;
          return -1;
        } else 
          // we delete the collection...
          g.removeCollection (col);
          cout << "Collection " << col << " has been successfully removed!" << endl;	  
      }  else cout << "Operation aborted" << endl;
      
    } break;
    
    
    case INDEX:
    {
      string col(argv[2]), index(argv[3]);
      if(!g.setCurrent(col))
      {
        cerr << "ERROR: bad collection name\n" << flush;
        return -1;
      } else {
        // we delete the index...
        g.removeIndexFromCollection (col, index);
        cout << "Index " << index << " of collection " << col << " has been successfully removed!" << endl;
	    }
    } break;
    
    
    case STOPWORD:
    {
      string file(argv[2]);
      if ( RUsure ( "About to remove file: " + file + ". Are you sure? (y/n)"  ) == 'Y') {
        if (remove((string(Globals::home_stopwords + file)).c_str()) == -1)
        {
          cerr << "ERROR: Stopwords file '" << string(argv[2]) 
               << "' does not exist. Exiting " << endl;
          return -1;
        } else 
          cout << "Stopwords file '" << file << "' successfully removed" << endl;
      } else cout << "Operation canceled" << endl;
      
    } break;
    
    
    case WEIGHT:
    {
      string col(argv[2]), indexName(argv[3]), file(argv[4]);
      if ( RUsure ( "About to remove weight file file: " + file + ". Are you sure? (y/n)"  ) == 'Y') {
        if (!g.setCurrent(col)){
          cerr << "ERROR: bad collection name\n" << flush;
          return -1;
        } else if ( g.delWeightFile(indexName, file) ) 
            cout << "Weight file '" << file << "' successfully removed!" << endl;
    	      else {
              cerr << "ERROR: bad index or weight name\n" << flush;
              return -1;
            }
        } else cout << "Operation canceled" << endl;
    } break;
    
    case ERR:
    default:
      cerr << "ERROR: undefined parameter list\nCorrect values are:\n";
      showHelp();
      return -1;	  
  }
  
  return 0;
}





