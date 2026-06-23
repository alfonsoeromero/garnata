#ifndef __TERMFORWEIGHT_H__
#define __TERMFORWEIGHT_H__

#include "Term.h"
#include "QuasiOccurrence.h"

class TermForWeight : public Term {

  public: 
    /**
    * Returns the QuasiOccurrence object linked to this term
    * @return that QuasiOccurrence
    */
    QuasiOccurrence getQuasiOccurrence() const
    {
      return QuasiOccurrence(offsetFileOcc);
    }

};

#endif

