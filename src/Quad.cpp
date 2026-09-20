/*
 * Quad.cpp - The Garnata Retrieval System
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

#include "Quad.h"
#include "Globals.h"

// ==================================================================

Quad::Quad() : id(0), unit(0), freq(0), ptrPos(0) { }

// ==================================================================

Quad::Quad(const Quad& q) :
	id(q.id), unit(q.unit), freq(q.freq), ptrPos(q.ptrPos) { }

// ==================================================================
	
Quad::Quad(unsigned _id, unsigned _unit, unsigned _freq, long _ptrPos) :
	id(_id), unit(_unit), freq(_freq), ptrPos(_ptrPos) { }

// ==================================================================

const Quad& Quad::operator=(const Quad& q)
{
  id = q.getId();
  unit = q.getUnit();
  freq = q.getFreq();
  ptrPos = q.getPtrPos();
  return (*this);
}
	
// ==================================================================

void Quad::setUnit(unsigned _unit)
{
  unit = _unit;
}

// ==================================================================

unsigned Quad::getId() const { return id; }

// ==================================================================

unsigned Quad::getUnit() const { return unit; }

// ==================================================================

unsigned Quad::getFreq() const { return freq; }

// ==================================================================

long Quad::getPtrPos() const { return ptrPos; }

// ==================================================================

void Quad::read(ifstream& fp)
{
  unsigned tmp[3];
  fp.read( (char*) &tmp, sizeof(unsigned) * 3);
  id = tmp[0];
  unit = tmp[1];
  freq = tmp[2];
  fp.read( (char*) &ptrPos, sizeof(long) );
}

// ==================================================================

void Quad::write(ofstream& fp) const
{
  unsigned tmp[] = {id, unit, freq};
  fp.write( (char*) &tmp, sizeof(unsigned) * 3);
  fp.write( (char*) &ptrPos, sizeof(long) );
  if (fp.fail()) Globals::errorAndExit("Bad 'fp' (Quad::write), exiting"); 
}

// ==================================================================

bool Quad::operator<(const Quad& q0) const
{
  if (id < q0.getId() )
    return true;
  else {
    if ( id > q0.getId() )
      return false;
    else 
      return (bool) ( unit < q0.getUnit() );
  }
}

// ==================================================================

bool Quad::operator>(const Quad& q0) const
{
  if (id > q0.getId() )
    return true;
  else {
    if ( id < q0.getId() )
      return false;
    else 
      return (bool) ( unit > q0.getUnit() );
  }
}

// ==================================================================

Quad::~Quad() { ; }

// ==================================================================

unsigned Quad::size() { return (3*sizeof(unsigned) + sizeof(long)); }

// ==================================================================

