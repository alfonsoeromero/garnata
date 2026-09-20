/*
 * Unit.h - The Garnata Retrieval System
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

#ifndef __UNIT_H__
#define __UNIT_H__

using namespace std;

#include <fstream>
#include <string>
#include <vector>

class Unit {
  protected:
    /** Unique identifier of the unit */
    unsigned id;
    
    /** Type of the unit (tag) */
    unsigned tagId;
    
    /** Position on the container (0 if root) */
    unsigned position;
    
    /** Number of items contained */
    unsigned numContained;

    /** Id of the unit container (0 if root) */
    unsigned container;

    /** Identifier of the file on the collection */
    unsigned file;
    
    /** Weight in the container (0 if root) */
    float weight;
    
    /** mode of the unit (final, container, retrievable, ...) */
    char mode;
   
  public:
    /** Empty constructor */
    Unit ();
    
    /** Main constructor
    @param _id identifier of the unit
    @param _tagId identifier of the tag of the unit
    @param _container identifier of the unit container
    @param _file identifier of the file this unit belongs to
    */
    Unit ( unsigned _id,  unsigned _tagId, unsigned _container, unsigned _file);

    /** Copy constructor
    @param u entity to copy
    */
    Unit (const Unit& u);

    /** Returns the id of the unit
    @return id of the unit
    */
    unsigned getId() const;
    
    /** Returns the position of the Unit in 
    its container
    @return position of the unit
    */
    unsigned getPosition() const;
    
    /** Returns the id of the container
    of this unit (0 if root)
    @return id of the container of this unit
    */
    unsigned getContainer() const;
    
    /** Returns the number of items contained 
    @return number of items contained
    */
    unsigned getNumContained() const;
    
    /** Returns the id of the tag of this unit 
    @return id of the tag of this unit
    */
    unsigned getTagId() const;
    
    /** Returns the id of the file this unit belongs to 
    @return id of the file of the collection
    */
    unsigned getFile() const;
        
    /** Returns the weight of the unit
    @return weight of the unit    
    */
    float getWeight() const;
    
    /** Tells if the unit is a container or not
    @return true if unit is container, false if not
    */
    bool isContainer() const;

    /** Tells if the unit is final or not
    @return true if unit is final, false if not
    */
    bool isFinal() const;
    
    // COMENTAR!
    bool isInCache() const; 

    /** Tells if the unit is retrievable or not
    @return true if unit is retrievable, false if not
    */
    bool isRetrievable() const;

    /** Size of the unit */
    static const unsigned SIZE_UNIT;
    
    /** Destructor */
    virtual ~Unit();
};

#endif

