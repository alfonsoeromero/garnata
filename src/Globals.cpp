#include "Globals.h"
#include <iostream>
#include <cstdio>
#include <fstream>

using namespace std;

// ==================================================================

// ---------------------------------------------------------
// --------------- Indexation parameters -------------------
// ---------------------------------------------------------

unsigned Globals::cacheSize = 30;
unsigned Globals::initialLexiconSize = 600000;
unsigned Globals::positionFileBufferSize = 2000000;
unsigned Globals::quadPoolKBytes = 1000000; 
unsigned Globals::weightInserterSize = 100000; 

// ==================================================================
char *__myHome = getenv("HOME");
string Globals::home(string(__myHome) + string("/.garnata/"));
string Globals::conf_file( string(home) + string("conf_file") );
string Globals::home_index = home + string("indexes/");
string Globals::home_weight = home + string("weight/");
string Globals::home_collections = home + string("collections/");
string Globals::home_stopwords = home + string("stopwords/");


// ==================================================================

void Globals::showWarning(char* _message)
{
  std::cerr << _message << endl << flush;
  std::clog << "[WARNING!] " << _message << endl << flush;
}

// ==================================================================

void Globals::errorAndExit(char* _error) 
{
  std::cerr << _error << endl << flush;
  exit(-1);
}

// ==================================================================

bool Globals::pair_gt(const pair<unsigned, unsigned> &a,
    const pair<unsigned, unsigned> &b)
  {
    return a.first > b.first;
  }

// ==================================================================

bool Globals::fileExists(const string& fileName)
{
 return (bool) (access(fileName.c_str(), 00) == 0);
}

// ==================================================================

bool Globals::deleteFile(const string& fileName)
{
  return (remove(fileName.c_str()) == 0);
}

// ==================================================================

bool Globals::renameFile(const string& oldName, const string& newName)
{
  return (rename(oldName.c_str(), newName.c_str()) == 0);
}

// ==================================================================

bool Globals::copyFile(const string& source, const string& destiny)
{
  char* buffer;
  long size;

  ifstream infile  (source.c_str(),  ios::binary);
  if (infile.fail()){
    cerr << "ERROR: file " << source << " does not exist. Exiting" << endl;   
    return false;
  }
  
  ofstream outfile (destiny.c_str(), ios::binary);
  if (outfile.fail()){
    cerr << "ERROR: problem opening output file file " << source << ". Exiting" << endl;   
    return false;
  }
  
  // get size of file
  infile.seekg(0,ifstream::end);
  size=infile.tellg();
  infile.seekg(0);

  // allocate memory for file content
  buffer = new char [size];
  
  
  // read content of infile
  infile.read (buffer,size);

  // write to outfile
  outfile.write (buffer,size);
  if (outfile.fail()){
    cerr << "ERROR: file " << source << " not ready. Exiting" << endl;   
    return false;
  }
  // release dynamically-allocated memory
  delete[] buffer;

  outfile.close();
  infile.close();
  return true;
}

// ==================================================================

void Globals::printTime(time_t initial, time_t end)
{
  // ------ time computation -----

  unsigned seconds = (unsigned)(end - initial);
  unsigned sec = seconds;
  unsigned mins = 0, hours = 0;
  if (seconds >= 60)
  {
    mins = seconds/60;
    seconds %= 60;

    if (mins >= 60)
    {
      hours = mins/60;
      mins %= 60;
    }
  }

  cout << "* Time elapsed: " << hours << "h, " << mins << "m, " << seconds << "s."
       << "(" << sec << ")" << endl;
}

// ==================================================================
