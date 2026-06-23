#include "Globals.h"
#include "Garnata.h"
#include <fstream>

typedef enum {NOPARAMS=0, COLLECTION=1, STOPWORD=2, ERR=3} request;

// ==================================================================

void showHelp()
{
  cerr <<
    "  'addItem collection name file route':\tAdds the collection represented by the list of files \n"
        <<  " on the file 'file' with the identifier 'collection', on the path 'route'\n" <<
    "  'addItem stopword X Y':\t adds to the system the stopword represented by the file X, with \n"
        <<  " the new name Y"
  << endl;
} 

// ==================================================================

string eraseBlanks(const string& s)
{
  unsigned i=0;
  string res;
  // leading blanks...
  for (i=0; i<s.size() && isspace(s[i]); ++i)
    ;

  // we copy the string (getting rid of trailing blanks)
  for (unsigned j=i; j<s.size() && !isspace(s[j]); ++j)
    res += s[j];

  return res;
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
      
    case 4:  // stopword
      if (!strcmp(argv[1], "stopword"))
        retval = STOPWORD;
      else retval = ERR;
      break;
      
    case 5: // collection
      if (!strcmp(argv[1], "collection"))
        retval = COLLECTION;
      else retval = ERR;
      break;
  
    case 2:
    case 3:
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
    
    case COLLECTION:
    { // name file route
      string name(argv[2]), file(argv[3]), path(argv[4]);
      ifstream ifs(file.c_str());
      if (ifs.fail()) 
      {
        cerr << "ERROR: Problem opening file " << file << ". Fix the name\n";
        return -1;
      }
      
      vector <string> files;
      while (!ifs.eof())
      {
        string s;
        ifs >> s;
        s = eraseBlanks(s);
        if (s.length()) files.push_back(s);
      }
      
      if (!files.size())
      {
        cerr << "ERROR:  file " << file << " should contain a list of files of the collection.\n";
        return -1;
      }
      
      char buff[256];
      cout << "Write a brief description (< 256 chars) of the collection:\n";
      cin.getline(buff, 255);
      string desc(buff);
      
      Collection c(name, desc, path, files);
      if (!g.createCollection(c))
      {
        cerr << "ERROR: creating collection. Please choose another name\n";
        return -1;      
      } else 
        cout << "Collection " << name << " successfully created!" << endl;
 	  
    }break;
    
    case STOPWORD:
    {
      string newName(argv[3]), fileToCopy(argv[2]);
      if (!Globals::fileExists(Globals::home_stopwords + newName))
      {
        if (Globals::copyFile(fileToCopy, Globals::home_stopwords + newName))
          cout << "Stopwords file " << newName << " successfully installed!\n";
        else {
          cerr << "Problems inserting file " << newName << ", or reading " 
               << fileToCopy << " Maybe the media is read-only?\n";
          return -1;
	      }
      } else {
        cerr << "File name " << newName << " is already used. Please choose another.\n";
        return -1;
      }
    } break;
    
    case ERR:
    default:
      cerr << "ERROR: undefined parameter list\nCorrect values are:\n";
      showHelp();
      return -1;
  }

  return 0;
}


