/*
 * WeightBNRSD.cpp - The Garnata Retrieval System
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



