/*
 * WeightBM25.cpp - The Garnata Retrieval System
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

