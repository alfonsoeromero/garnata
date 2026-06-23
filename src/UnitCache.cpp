#include "UnitCache.h"
#include "UnitReader.h"
#include "Globals.h"
#include <algorithm>
#include <iostream>
#include <ctime>

// ==================================================================

UnitCache::~UnitCache() 
{
  for (vector<UnitReader*>::iterator it=staticCache1.begin(), end=staticCache1.end(); it!=end; ++it)
    delete *it;

  for (vector<UnitReader*>::iterator it=staticCache2.begin(), end=staticCache2.end(); it!=end; ++it)
    delete *it;
 }

// ==================================================================

void UnitCache::printStatus() const
{
  cout << "cache size " << staticCache1.size() << " " << staticCache2.size() << endl;
  for (unsigned i=0; i<staticCache1.size(); ++i)  
      if (staticCache1[i] != 0)
        cout << staticCache1[i]->getId() << " "<< flush;
  
  cout << endl;
  for (unsigned i=0; i<staticCache2.size(); ++i)  
      if (staticCache2[i] != 0)
        cout << staticCache2[i]->getId() << " "<< flush;
  cout << endl;
}


// ==================================================================

UnitCache::UnitCache ( unsigned _SIZE_STATIC1, unsigned _SIZE_STATIC2, unsigned _NUM_UNITS ) :
            SIZE_STATIC1 ( _SIZE_STATIC1 > _NUM_UNITS ? _NUM_UNITS : _SIZE_STATIC1 ), 
            SIZE_STATIC2 ( _SIZE_STATIC2 > _NUM_UNITS ? _NUM_UNITS : _SIZE_STATIC2 ), 
            NUM_UNITS(_NUM_UNITS), cache1Accesses(0), cache1Hits(0), cache2Accesses(0), cache2Hits(0)
            { 
              cout << "Loading cache...\n";
              preloadCache();
            }


// ==================================================================

UnitReader* UnitCache::getUnitFromCache1(unsigned id)
{
  unsigned assignedSlot = (id % SIZE_STATIC1);
  ++cache1Accesses;

  // 1st.- we test if Unit is on static cache ( O(1) )
  if (staticCache1[assignedSlot]->getId() == id)
  {
    ++cache1Hits;
    return staticCache1[assignedSlot];

  // 2nd.- if not, we return the unit itself
  } else return new UnitReader(id);
}

// ==================================================================

UnitReader* UnitCache::getUnitFromCache2(unsigned id)
{
  unsigned assignedSlot = (id % SIZE_STATIC2);
  ++cache2Accesses;

  // 1st.- we test if Unit is on static cache ( O(1) )
  if (staticCache2[assignedSlot]->getId() == id)
  {
    ++cache2Hits;
    return staticCache2[assignedSlot];

  // 2nd.- if not, we return the unit itself
  } else return new UnitReader(id);
}

// ==================================================================

void UnitCache::preloadCache(void)
{

  time_t t_ini, t_end;
  time(&t_ini);
  unsigned cas=1;

  /********************************************************************
  *       FIRST STEP: preloading of the first cache                   *
  ********************************************************************/

  unsigned lastFactor = NUM_UNITS / SIZE_STATIC1 + 1;
  vector<unsigned> factors (lastFactor);
  
  for (unsigned i=0; i<lastFactor; ++i)
    factors[i] = i;

  vector<unsigned> cachesize ( factors.size() );
  std::fill (cachesize.begin(), cachesize.end(), SIZE_STATIC1);
  transform(factors.begin(), factors.end(), cachesize.begin(), factors.begin(), multiplies<unsigned>());

  // We fill factors with 0*SIZE_STATIC1, 1*SIZE_STATIC1, ..., (NUM_UNIT/SIZE_STATIC1)*SIZE_STATIC1
  staticCache1.reserve(SIZE_STATIC1);

  for (unsigned i=0; i<SIZE_STATIC1; ++i)
  {
    if ((float)(i+1)/SIZE_STATIC1*100.0f >= cas*25.0f)
    {
      cout << "+ First cache at " << cas*25.0f << "%\n";
      ++cas;
    }
  
    // for each cache slot... we get the candidates vec(i) + vec(factor)
    vector<unsigned> candidates = factors;
    transform(candidates.begin(), candidates.end(), candidates.begin(), bind2nd(plus<unsigned>(), i));
    
    // we remove those greater than NUM_UNITS
    vector<unsigned>::iterator new_end = upper_bound(candidates.begin(), candidates.end(), NUM_UNITS-1);
    if (new_end != candidates.end()) candidates.erase(new_end, candidates.end());

    // 'candidates' contains the list of unit identifiers that could be placed
    //  at slot "i" in the cache. We get the first candidate CONTAINING MORE TERMS

    UnitReader* best = 0;
    unsigned maxTerms = 0;
  
    for (vector<unsigned>::const_iterator it=candidates.begin(), end=candidates.end(); it!=end; ++it)
    {
      UnitReader* current = new UnitReader(*it);
      current->setMode(Globals::in_cache);
      bool inCache = false;
      if (current->isFinal())
      {
        unsigned thisTerms = current->getNumContained();
        if ( thisTerms > maxTerms )
        {
          if (best) delete best;
          best = current;
          maxTerms = thisTerms;
          inCache = true;
        } 
      }     
      if (!inCache) delete current;
    }
    staticCache1.push_back (best);
  }

  time(&t_end);

  /********************************************************************
  *       SECOND STEP: preloading of the second cache                 *
  ********************************************************************/

  lastFactor = NUM_UNITS / SIZE_STATIC2 + 1;
  factors = vector<unsigned> (lastFactor);
  cas = 1;
  
  for (unsigned i=0; i<lastFactor; ++i)
    factors[i] = i;

  cachesize = vector<unsigned> ( factors.size() );
  std::fill (cachesize.begin(), cachesize.end(), SIZE_STATIC2);
  transform(factors.begin(), factors.end(), cachesize.begin(), factors.begin(), multiplies<unsigned>());

  // We fill factors with 0*SIZE_STATIC2, 1*SIZE_STATIC2, ..., (NUM_UNIT/SIZE_STATIC2)*SIZE_STATIC2
  staticCache2.reserve(SIZE_STATIC2);
  for (unsigned i=0; i<SIZE_STATIC2; ++i)
  {
    if ((float)(i+1)/SIZE_STATIC2*100.0f >= cas*25.0f)
    {
      cout << "+ Second cache at " << cas*25.0f << "%\n";
      ++cas;
    }
  
    // for each cache slot... we get the candidates vec(i) + vec(factor)
    vector<unsigned> candidates = factors;
    transform(candidates.begin(), candidates.end(), candidates.begin(), bind2nd(plus<unsigned>(), i));

    // we remove those greater than NUM_UNITS
    vector<unsigned>::iterator new_end = upper_bound(candidates.begin(), candidates.end(), NUM_UNITS-1);
    if (new_end != candidates.end()) candidates.erase(new_end, candidates.end());

    // 'candidates' contains the list of unit identifiers that could be placed
    //  at slot "i" in the cache. We get the first candidate CONTAINING MORE UNITS
    UnitReader* best = 0;
    unsigned maxUnits = 0;

    for (vector<unsigned>::const_iterator it=candidates.begin(), end=candidates.end(); it!=end; ++it)
    {
      UnitReader* current = new UnitReader(*it);
      current->setMode(Globals::in_cache);
      bool inCache = false;
      if (current->isContainer())
      {
        unsigned thisUnits = current->getNumContained();
        if( thisUnits > maxUnits )
        {
          if (best) delete best;
          best = current;
          maxUnits = thisUnits;
          inCache = true;
        } 
      } 
      if (!inCache) delete current;
    }      
    staticCache2.push_back (best);
  }// for

  time(&t_end);
}

// ==================================================================

void UnitCache::resetStats(){
  cache1Hits = 0;
  cache2Hits = 0;
  cache1Accesses = 0;
  cache2Accesses = 0;
}

// ==================================================================

void UnitCache::printStats() const{
  cout << "Static cache 1: (" << cache1Hits << "/" << cache1Accesses << "): "
       << ((float) cache1Hits * 100 )/((float) cache1Accesses) << "%\n";
  cout << "Static cache 2: (" << cache2Hits << "/" << cache2Accesses << "):"
       << ((float) cache2Hits * 100 )/((float) cache2Accesses) << "%\n";
}

// ==================================================================
