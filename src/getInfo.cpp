#include "Collection.h"
#include "Index.h"
#include "Garnata.h"
#include <iostream>

typedef enum {NOPARAMS=0, COLS=1, COLLECTION=2, INDEX=3, ERR=4} request;

// ==================================================================

void showHelp()
{
  cerr <<
    "  'getInfo collections':\tgives information about the collections of the system\n" <<
    "  'getInfo collection X':\tgives information about the collection X\n" <<
    "  'getInfo index X Y':\tgives information about the index Y belonging to the collection X" <<
  endl;
} 

// ==================================================================

request processArgs(int argc, char* argv[])
{
  
  request retval;
  
  switch (argc)
  {
    case 1:
      retval = NOPARAMS;
      break;
      
    case 2:
      if (!strcmp(argv[1], "collections"))
        retval = COLS;
      else retval = ERR;
      break;
      
    case 3:
      if (!strcmp(argv[1], "collection"))
        retval = COLLECTION;
      else retval = ERR;
      break;
  
    case 4:
      if (!strcmp(argv[1], "index"))
        retval = INDEX;
      else retval = ERR;
      break;  
    
    default:
      retval = ERR;
  }	
	
  return retval;
}

// ==================================================================

int main(int argc, char* argv[])
{
  // 1.- Parameter catching
  request r = processArgs(argc, argv);
  
  // 2.- Reading of the configuration file
  Garnata g;
  
  // 3.- Processing request, and showing results...
  switch (r)
  {
    case NOPARAMS:
      cerr << "USE:\n";
      showHelp();
    break;
    
    case COLS:
    {
      vector <string> cols = g.getCollectionNames();      
      if (cols.size())
      {
	cout << "List of collection of the system:\n";
	for (vector<string>::iterator it=cols.begin(); it!=cols.end(); it++)
           cout << "+ " << *it << "\n";
        cout << flush;
      }
      else
        cout << "There are not any collections in the system" << endl;
    } break;
      
    case COLLECTION:
        if(!g.setCurrent(string (argv[2])))
	{
	  cerr << "ERROR: bad collection name\n" << flush;
	  return -1;
	} else 
	  g.getCurrent()->printInfo();  	  
    break;
	  
    case INDEX:
       if(!g.setCurrent(string (argv[2])))
	{
	  cerr << "ERROR: bad collection name\n" << flush;
	  return -1;
	} else if (!g.printInfoIndex(string (argv[3])))
	  {
	    cerr << "ERROR: unknown index identifier\n" << flush;
	    return -1;
	  }		
    break;
	  
	  
    case ERR:
    default:
        cerr << "ERROR: undefined parameter list\nCorrect values are:\n";
	showHelp();
	return -1;
  }
  
  return 0;
}


