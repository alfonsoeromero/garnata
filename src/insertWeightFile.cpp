#include <string>
#include "GarnataWeight.h"

using namespace std;

int main(int argc, char* argv[])
{
  // 1.- wrong parameter number? 
  if (argc != 4)
  {
    cerr << "ERROR: Bad parameter number\n";
    cerr << "USE: " << argv[0] << " collectionName indexName weightFileName" << endl;
    return -1;
  }

  // 2.- Parameter catching
  string collectionName(argv[1]), indexName(argv[2]), weightFileName(argv[3]);
  
  // 3.- Inserting weights
  GarnataWeight g;
  time_t ini, end;
  time(&ini);

  // 4.- Showing output message
  switch (g.insertWeights(collectionName, indexName, weightFileName)) {
    case Garnata::BAD_INDEX : 
      cerr << "ERROR: Unknown index file name\n" << flush;
      return -1;
	  
    case Garnata::BAD_COLLECTION :
      cerr << "ERROR: Unknown collection file name\n" << flush;
      return -1;
      
    case Garnata::BAD_WEIGHT:
      cerr << "ERROR: file '" << weightFileName << "' does not exist, or it if corrupt\n" << flush;
      return -1;
      
    case Garnata::ALL_OK :
	    cout << "Weight file '" << weightFileName << "' successfully inserted into collection: " 
           << collectionName << ", index: " << indexName << endl;
      time(&end);

      Globals::printTime(ini, end);
      break;
	  
    default :
      cerr << "ERROR: unspecified error\n" << flush;
      return -1;
  }
  
  // 5.- End
  return 0;
}


