#include "ProcessedQuery.h"
#include "Globals.h" 

// ==================================================================

ProcessedQuery::ProcessedQuery (vector<unsigned> t) : terms(t) { ; }

// ==================================================================

ProcessedQuery::ProcessedQuery (const ProcessedQuery& p) : terms(p.terms) { ; }

// ==================================================================

unsigned ProcessedQuery::size() const { return terms.size(); }

// ==================================================================

unsigned ProcessedQuery::operator[](unsigned i) const
{
  if (i < terms.size()) return terms[i];
  else {
    Globals::showWarning("WARNING: Array out of bounds! (ProcessedQuery::operator[])");
    return 0;
  }
}

// ==================================================================

ProcessedQuery::~ProcessedQuery () { ; }

// ==================================================================

