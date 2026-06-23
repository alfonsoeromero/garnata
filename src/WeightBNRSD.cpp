#include "WeightBNRSD.h"
#include <string>
#include <cmath>
#include "Collection.h"

// ==================================================================

WeightBNRSD::WeightBNRSD (const Collection& _c, string _identifier) :
Weight(_c, _identifier, true) 
{ }

// ==================================================================

float WeightBNRSD::computeIdf (unsigned N, unsigned n_i) const
{
   return log10f ( static_cast<float>(N) / static_cast<float>(n_i) );
}

// ==================================================================

float WeightBNRSD::rhoTU(unsigned idTerm, unsigned idUnit)
{
  return static_cast<float>(tf(idTerm, idUnit))*idf(idTerm);
}

// ==================================================================

WeightBNRSD::~WeightBNRSD() { }

// ==================================================================



