#include "SID.h"

// ==================================================================

SID::SID ( const Collection& _c, const string& _identifier, RUM_mode _mode, bool normalize ) :
  ID<NodeResult_SID>(_c, _identifier, _mode, normalize) {}

// ==================================================================

void SID :: specifyUtilities(float _v_r_plus_u_plus, float _v_r_plus_u_minus,
  float _v_r_minus_u_plus, float _v_r_minus_u_minus)
  {
    NodeResult_SID::v_r_plus_u_plus = _v_r_plus_u_plus;
    NodeResult_SID::v_r_plus_u_minus = _v_r_plus_u_minus;
    NodeResult_SID::v_r_minus_u_plus = _v_r_minus_u_plus;
    NodeResult_SID::v_r_minus_u_minus = _v_r_minus_u_minus;
  }

// ==================================================================

