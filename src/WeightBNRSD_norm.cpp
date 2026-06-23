#include "WeightBNRSD_norm.h"
#include <string>
#include <cmath>
#include "Collection.h"

// ==================================================================

WeightBNRSD_norm::WeightBNRSD_norm (const Collection& _c, string _identifier) :
Weight(_c, _identifier, true) 
{ }

// ==================================================================

float WeightBNRSD_norm::computeIdf (unsigned N, unsigned n_i) const
{
   return log10f ( static_cast<float>(N) / static_cast<float>(n_i) );
}

// ==================================================================

float WeightBNRSD_norm::rhoTU(unsigned idTerm, unsigned idUnit)
{
  return tf_norm(idTerm, idUnit)*idf(idTerm);
}

// ==================================================================

WeightBNRSD_norm::~WeightBNRSD_norm() { }

// ==================================================================



