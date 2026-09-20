/*
 * UnitCache.h - The Garnata Retrieval System
 * Copyright (C) 2005, 2026 Alfonso E. Romero
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

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

