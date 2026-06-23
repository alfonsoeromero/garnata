#include "BNR-SD.h"
#include <ctime>
#include "Globals.h"
#include "UnitReader.h"
#include "NodeGroup.h"


// ==================================================================

BNR_SD :: BNR_SD ( const Collection& _c, const string& _identifier ) :
 _BNR_SD<NodeResult> (_c, _identifier) { }

// ==================================================================

vector< Result >  BNR_SD ::makeQuery(const ProcessedQuery& pq)
{
   // lists with final units and complex units, respectively...
  map<unsigned, NodeResult*> N_final, N_complex;
  
  time(&init);

  // if there are no terms in the query...
  if (!pq.size())
  {
    time(&t_end);
    return vector < Result >();
  }  

  vector<NodeGroup<NodeResult> > groups;  
  // ================= 1st step: we propagate probabilities to the final units ===================
  time(&init);  
  propagateFinalUnits(pq, N_final, groups);
  time(&t_end);  

  // =================== 2nd step: we propagate probabilities to the complex units ===================
  propagateComplexUnits(N_final, N_complex);

  // =================== 3rd step: we readjust probability values, and
  // =================== construct a list of nodes instead two maps  
  vector<NodeResult*> vec;
  makeListOfNodes(vec, N_final, N_complex);
  
  // ================ 4th step: list is cut down, if needed =====================================
  std::partial_sort(vec.begin(), vec.begin() + std::min((unsigned)vec.size(), NUMDOCS), vec.begin(), _BNR_SD<NodeResult>::NodeResultPtr<NodeResult>() );
  cutDownNodeResultVector (vec);

  // ================ 6th step: building of the result =====================================
  vector<Result> res;
  buildResult(res, vec, dtds->getDTDbyId(0) );

  time(&t_end);

// Return value  
  return res;
}


