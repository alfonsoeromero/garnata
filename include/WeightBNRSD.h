#ifndef __WEIGHTBNRSD_H__
#define __WEIGHTBNRSD_H__

#include "Weight.h"

using namespace std;

class WeightBNRSD : public Weight {

  public:
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    */
    WeightBNRSD (const Collection& _c, string _identifier);
    
    /** Return the importance of a term into a unit
    @param idTerm identifier of the term
    @param idUnit identifier of the unit
    @return importance of idTerm on idUnit
    */
    float rhoTU(unsigned idTerm, unsigned idUnit);

    /** Computes idf for a term
    @param N total number of documents
    @param n_i number of documents the term i appears in
    */
    float computeIdf (unsigned N, unsigned n_i) const;
        
    /** Destructor */
    ~WeightBNRSD();
};

#endif

