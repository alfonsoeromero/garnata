#include "WeightBM25.h"
#include <string>
#include <cmath>
#include "Collection.h"

// ==================================================================

WeightBM25::WeightBM25 (const Collection& _c, string _identifier) :
Weight(_c, _identifier, true) 
{ ; }

// ==================================================================

float WeightBM25::computeIdf (unsigned N, unsigned n_i) const
{
   return log10f ( (float)N ) / ( (float) n_i );
}

// ==================================================================

float WeightBM25::rhoTU(unsigned idTerm, unsigned idUnit)
{
  return ((float) tf(idTerm, idUnit))*idf(idTerm);
}

// ==================================================================

WeightBM25::~WeightBM25() { }

// ==================================================================

float WeightBM25::b  = 0.0;

float WeightBM25::k1 = 0.0;

// ==================================================================

