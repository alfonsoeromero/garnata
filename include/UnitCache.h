#ifndef __UNIT_CACHE_H__
#define __UNIT_CACHE_H__

#include "Unit.h"
#include "UnitReader.h"

using namespace std;

class UnitCache {
  private:
    /** Size of the static cache for final units */
    const unsigned SIZE_STATIC1;
    
    /** Size of the static cache for complex units */
    const unsigned SIZE_STATIC2;

    /** Total number of units */
    const unsigned NUM_UNITS;

    /** Number of cache1 accesses */
    unsigned cache1Accesses;

    /** Hits of the cache2 */
    unsigned cache1Hits;

    /** Number of cache 2 accesses */
    unsigned cache2Accesses;
        
    /** Hits of the cache 2*/
    unsigned cache2Hits;

    /** Static cache: final units */
    vector<UnitReader*> staticCache1; 

    /** Static cache: complex units */
    vector<UnitReader*> staticCache2;

    /** Preloads static cache */
    void preloadCache(void);    
  
  public:
    /** Constructor
    @param _SIZE_STATIC1 size of the first static cache
    @param _SIZE_STATIC2 size of the second static cache
    @param _NUM_UNITS number of units
    */
    UnitCache ( unsigned _SIZE_STATIC1, unsigned _SIZE_STATIC2, unsigned _NUM_UNITS );

    /** Returns the final unit with identifier id, even if it is not in cache
    @param id identifier of the unit
    @return the desired unit
    */
    UnitReader* getUnitFromCache1 (unsigned id);
   
    /** Returns the complex unit with identifier id, even if it is not in cache
    @param id identifier of the unit
    @return the desired unit
    */
    UnitReader* getUnitFromCache2 (unsigned id);

    void resetStats();
    
    void printStats() const;

    /** Returns true if a certain unit is in cache */
    bool isInCache(unsigned id);

    /** Prints cache's current status */
    void printStatus() const;

    /** Destructor */
    ~UnitCache();  
};

#endif

