#ifndef __GARNATA_WEIGHT_H__
#define __GARNATA_WEIGHT_H__

#include "Garnata.h"
#include <string>

using namespace std;

class GarnataWeight : public Garnata
{
  public:
    /** Empty constructor */
    GarnataWeight();
    
    /** Add a new weight file
    @param collectionName name of the collection
    @param indexName name of the index
    @param weightFileName name of the weight file
    @return ALL_OK if everything went OK 
    */
    int addWeights(string collectionName, string newIndexName, string weightFileName, int type);
    
    /** Inserts a weight file into an index
    @param collectionName name of the collection
    @param indexName name of the index
    @param weightFileName name of the weight file
    @return ALL_OK if everything went OK 
    */
    int insertWeights(string collectionName, string newIndexName, string weightFileName);
    
    /** Destructor */
    ~GarnataWeight(); 
};

#endif


