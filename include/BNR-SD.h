#ifndef __BNR_SD_H__
#define __BNR_SD_H__

#include "RetrievalModel.h"
#include "Result.h"
#include "NodeResult.h"
#include "NodeGroup.h"
#include "ProcessedQuery.h"
#include "_BNR-SD.h"
#include <vector>
#include <utility>

using namespace std;

class BNR_SD : public _BNR_SD <NodeResult> {
  public:
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    */
    BNR_SD ( const Collection& _c, const string& _identifier );
    
    /** Makes a query to the system
    @param pq 
    @return vector of pairs (document, weitght) 
            sorted by descending weight
    */
    vector< Result > makeQuery(const ProcessedQuery& pq);
};

#endif


