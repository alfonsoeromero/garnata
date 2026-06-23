#include "GarnataMakeIndex.h"
#include "Collection.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main (int argc, char* argv[])
{
  // 1.- wrong parameter number? 
  if (argc != 5)
  {
    cerr << "ERROR: Bad parameter number\n";
    cerr << "USE: " << argv[0] << " collectionName newIndexName stopwordsListFile stem=(yes|no)" << endl;
    return -1;
  }

  // 2.- Parameter catching
  string collectionName, newIndexName, stopwordsListFile;
  collectionName = string(argv[1]);
  newIndexName = string(argv[2]);
  stopwordsListFile = string(argv[3]);
  string stem(argv[4]);
  bool doStemming = false;
  if (stem == "stem=yes")
  {
    doStemming = true;
  } else if (stem != "stem=no") {
    cerr << "ERROR: Bad parameters\n";
    cerr << "USE: " << argv[0] << " collectionName newIndexName stopwordsListFile stem=(yes|no)" << endl;
    return -1;
  }


  time_t ini_time, end_time;
  
  // 3.- Indexation
  GarnataMakeIndex g;
  time (&ini_time);
  cout << "Making index..." << endl;
  int res = g.makeIndex(collectionName, newIndexName, stopwordsListFile, doStemming);
  time (&end_time);


  // 4.- Shows result
  switch (res)
  {
    case Garnata::BAD_COLLECTION:
      cerr << "ERROR: Collection '" << collectionName 
           << "' is not present in the system. Exiting" << endl;
      return -1;
      
    case Garnata::BAD_INDEX:
      cerr << "ERROR: Index '" << newIndexName << "' already exist for collection '" 
           << collectionName << "'. Exiting" << endl;
      return -1;
      
    case Garnata::BAD_STOPWORDS:
      cerr << "ERROR: Corrupt stopwords file (" << stopwordsListFile 
           << ") or it does not exist in the system\n (you should write just the name" 
           << ", not the entire route).  Exiting" << endl;
      return -1;
      
    case Garnata::ALL_OK:
      cout << "Indexation successfully finished!" << endl;      
      Globals::printTime(ini_time, end_time);
      
  }
  
  // 4.- End
  return 0;
}


