#include <string>
#include "GarnataWeight.h"
#include "Globals.h"

using namespace std;

int main(int argc, char* argv[])
{
  // 1.- wrong parameter number? 
  if (argc != 5)
  {
    cerr << "ERROR: Bad parameter number\n";
    cerr << "USE: " << argv[0] << " collectionName indexName weightFileName (classic|norm_max)" << endl;
    return -1;
  }

  // 2.- Parameter catching
  string collectionName(argv[1]), newIndexName(argv[2]), weightFileName(argv[3]), myWeight(argv[4]);
  
  if (weightFileName == "none")
  {
    cerr << "ERROR: 'none' is not a valid weight file name. Please choose another." << endl;
    return -1;
  }
  
  int idWeight = Garnata::CLASSIC;
  if (myWeight == "norm_max")
  {
    idWeight = Garnata::NORM_MAX;
    cout << "using nomalized_max weighting scheme: normalized(f_(i,j)/max_j(f(i,j)) x idf(i))...\n";
  } else cout << "using classical weighting scheme: normalized(f_(i,j) x idf(i))...\n";
  
  // 3.- Adding weights...
  GarnataWeight g;
  time_t ini, end;
  time(&ini);

  // 4.- Showing output message
  switch (g.addWeights(collectionName, newIndexName, weightFileName, idWeight)) {
    case Garnata::BAD_INDEX : 
      cerr << "ERROR: Unknown index file name\n" << flush;
      return -1;
	  
    case Garnata::BAD_COLLECTION :
      cerr << "ERROR: Unknown collection file name\n" << flush;
      return -1;

    case Garnata::BAD_WEIGHT :
      cerr << "ERROR: file '" << weightFileName << "' already exists. Please specify another name\n" << flush;
      return -1;
      
    case Garnata::ALL_OK :
      cout << "Weight file " << weightFileName << " successfully created\n" << flush;
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


