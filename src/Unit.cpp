/*
 * Unit.cpp - The Garnata Retrieval System
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

#include "Unit.h"
#include "Globals.h"

// ==================================================================

Unit::Unit ( unsigned _id,  unsigned _tagId, unsigned _container, unsigned _file) :
   id(_id), tagId(_tagId), position(0), numContained(0), 
   container(_container), file(_file), weight(0.0f), mode(0)
{ }

// ==================================================================

Unit::Unit (const Unit& u) : id(u.id), tagId(u.tagId), position(u.position),
    numContained(u.numContained), container(u.container), 
    file(u.file), weight(u.weight), mode(u.mode) { }

// ==================================================================

Unit::Unit() : id(0), mode(0) { }

// ==================================================================

float Unit::getWeight() const { return weight; }

// ==================================================================

unsigned Unit::getPosition() const { return position; }

// ==================================================================

unsigned Unit::getContainer() const { return container; }

// ==================================================================

unsigned Unit::getNumContained() const { return numContained; }

// ==================================================================

unsigned Unit::getTagId() const { return tagId; }

// ==================================================================

unsigned Unit::getId() const { return id; }

// ==================================================================

bool Unit::isContainer() const { return (bool) ((mode & Globals::container) != 0); }

// ==================================================================

bool Unit::isFinal() const { return (bool) ((mode & Globals::pcdata) != 0); }

// ==================================================================

bool Unit::isInCache() const { return (bool) ((mode & Globals::in_cache) != 0); }

// ==================================================================

bool Unit::isRetrievable() const { return (bool) ((mode & Globals::virtual_unit) == 0); }

// ==================================================================

unsigned Unit::getFile() const { return file; }

// ==================================================================

Unit::~Unit() { }

// ==================================================================

const unsigned Unit::SIZE_UNIT = 5*sizeof(unsigned) + sizeof(float) + sizeof(char);

// ==================================================================

