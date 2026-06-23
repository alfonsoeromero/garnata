#include "CID.h"


// ==================================================================

CID::CID ( const Collection& _c, const string& _identifier, RUM_mode _mode, bool normalize ) :
  ID<NodeResult_CID>(_c, _identifier, _mode, normalize) {}

// ==================================================================

void CID::specifyUtilities(float _v_r_plus_u_plus_u_plus, float _v_r_plus_u_plus_u_minus, 
    			float _v_r_plus_u_minus_u_plus, float _v_r_plus_u_minus_u_minus,
			float _v_r_minus_u_plus_u_plus, float _v_r_minus_u_plus_u_minus,
			float _v_r_minus_u_minus_u_plus, float _v_r_minus_u_minus_u_minus)
  {
    NodeResult_CID::v_r_plus_u_plus_u_plus = _v_r_plus_u_plus_u_plus;
    NodeResult_CID::v_r_plus_u_plus_u_minus = _v_r_plus_u_plus_u_minus;
    
    NodeResult_CID::v_r_plus_u_minus_u_plus = _v_r_plus_u_minus_u_plus;
    NodeResult_CID::v_r_plus_u_minus_u_minus = _v_r_plus_u_minus_u_minus;
    
    NodeResult_CID::v_r_minus_u_plus_u_plus = _v_r_minus_u_plus_u_plus;
    NodeResult_CID::v_r_minus_u_plus_u_minus = _v_r_minus_u_plus_u_minus;
    
    NodeResult_CID::v_r_minus_u_minus_u_plus = _v_r_minus_u_minus_u_plus;
    NodeResult_CID::v_r_minus_u_minus_u_minus = _v_r_minus_u_minus_u_minus;
  }

