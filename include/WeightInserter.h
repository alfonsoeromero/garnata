#ifndef __WEIGHTINSERTER_H__
#define __WEIGHTINSERTER_H__

using namespace std;

#include "IndexReader.h"
#include "Collection.h"
#include <string>
#include <fstream>

class WeightInserter : public IndexReader
{
  private:
    /** Process and writes a certain unit */
    void processUnit(unsigned id, float weight, fstream& fp) const;

  public:
    
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    */
    WeightInserter(const Collection& _c, string _identifier);

    /**
    Inserts a weight file in an Index
    @param fileName name of the weight file
    @return true if everything went OK, false if file is corrupt  
    */
    bool insert(string fileName);
    
    /** Destructor */
    ~WeightInserter();
};

#endif

