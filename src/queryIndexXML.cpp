#include "GarnataQuery.h"
#include <iostream>

int main (int argc, char* argv[])
{

  if (argc != 4)
  {
    cerr << "ERROR: bad arguments number. \nUSE:\n"
         << "queryIndex collectionName indexName stem=(yes|no)" << endl;
    return -1;
  }

  string collectionName(argv[1]), indexName(argv[2]), stem(argv[3]);
  bool doStemming = false;

  if (stem == "stem=yes")
  {
    doStemming = true;
  } else if (stem != "stem=no") {
    cerr << "ERROR: bad parameters. \nUSE:\n"
         << "queryIndex collectionName indexName stem=(yes|no)" << endl;
    return -1;
  }

  GarnataQueryXML g(collectionName, indexName, _BNR_SD, doStemming);
  char buff[1024];
  unsigned id = 1;
  bool keepAsking;
  do {
    for (unsigned i=0; i<100; i++) buff[i] = '\0';
    cin.getline(buff, 1023);
    string s(buff);
    
    keepAsking = true;
    if (g.isCommand(s))
    {
      keepAsking = g.processCommand(s);
    } else if (s.size()) {
      g.makeQuery(s);

    }
	  
  } while (keepAsking);

  return 0;
}
