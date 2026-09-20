/*
 * Triad.cpp - The Garnata Retrieval System
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

#include "Triad.h"
#include "Globals.h"

// ==================================================================

Triad ::Triad () : id(0), unit(0), weight(0.0) { ; }

// ==================================================================

Triad ::Triad (const Triad & t) :
	id(t.id), unit(t.unit), weight(t.weight) { ; }

// ==================================================================
	
Triad ::Triad (unsigned _id, unsigned _unit, float _weight) :
	id(_id), unit(_unit), weight(_weight) { ; }

// ==================================================================

const Triad& Triad::operator=(const Triad& q)
{
  id = q.getId();
  unit = q.getUnit();
  weight = q.getWeight();
  return (*this);
}
	
// ==================================================================

unsigned Triad::getId() const { return id; }

// ==================================================================

unsigned Triad::getUnit() const { return unit; }

// ==================================================================

float Triad::getWeight() const { return weight; }

// ==================================================================

void Triad::read(ifstream& fp)
{
  unsigned tmp[2];
  fp.read( (char*) &tmp, sizeof(unsigned) * 2);
  id = tmp[0];
  unit = tmp[1];  
  fp.read( (char*) &weight, sizeof(float) );
  if (fp.fail()) Globals::errorAndExit("Bad 'fp' (Triad::read), exiting");
}

// ==================================================================

void Triad::write(ofstream& fp) const
{
  unsigned tmp[] = {id, unit};
  fp.write( (char*) &tmp, sizeof(unsigned) * 2);
  fp.write( (char*) &weight, sizeof(float) );
  if (fp.fail()) Globals::errorAndExit("Bad 'fp' (Triad::write), exiting"); 
}

// ==================================================================

bool Triad::operator<(const Triad& t0) const
{
  if (id < t0.getId() )
    return true;
  else {
    if ( id > t0.getId() )
      return false;
    else 
      return (bool) ( unit < t0.getUnit() );
  }
}

// ==================================================================

bool Triad::operator>(const Triad& t0) const
{
  if (id > t0.getId() )
    return true;
  else {
    if ( id < t0.getId() )
      return false;
    else 
      return (bool) ( unit > t0.getUnit() );
  }
}

// ==================================================================

unsigned Triad::size() { return 2*sizeof(unsigned) + sizeof(float); }

// ==================================================================

Triad::~Triad() { ; }

// ==================================================================

