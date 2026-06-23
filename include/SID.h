#ifndef __SID_H__
#define __SID_H__

#include "ID.h"
#include "NodeResult_SID.h"

using namespace std;

class SID : public ID<NodeResult_SID> {
  public:
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    @param _mode mode to compute RSV
    @param normalize true if we are dividing RSV of each unit by its nIdf
    */
    SID ( const Collection& _c, const string& _identifier, RUM_mode _mode, bool normalize );
    
    
    /** Asess the four parameters of the model
    @param v_r_plus_u_plus utility of retrieving the unit, being relevant
    @param v_r_plus_u_minus utility of retrieving the unit, not being relevant
    @param v_r_minus_u_plus utility of not retrieving the unit, being relevant
    @param v_r_minus_u_minus utility of not retrieving the unit, not being relevant
    */
    static void specifyUtilities(float v_r_plus_u_plus, float v_r_plus_u_minus,
           float v_r_minus_u_plus, float v_r_minus_u_minus);
};

#endif


