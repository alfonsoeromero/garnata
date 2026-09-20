/*
 * TermForWeight.h - The Garnata Retrieval System
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

#ifndef __TERMFORWEIGHT_H__
#define __TERMFORWEIGHT_H__

#include "Term.h"
#include "QuasiOccurrence.h"

class TermForWeight : public Term {

  public: 
    /**
    * Returns the QuasiOccurrence object linked to this term
    * @return that QuasiOccurrence
    */
    QuasiOccurrence getQuasiOccurrence() const
    {
      return QuasiOccurrence(offsetFileOcc);
    }

};

#endif

