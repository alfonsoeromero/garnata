/*
 * Triad.h - The Garnata Retrieval System
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

#ifndef __TRIAD_H__
#define __TRIAD_H__

using namespace std;
#include <fstream>

/** @class Triad Triad.h 
* Represents a temporal representation of the fact that a
*  particular term has a certain weight in a particular unit 
* @author Alfonso E. Romero <aromero@correo.ugr.es>
* @date 17/08/2005
* @version 0.2
*/

class Triad {
  private:
	/** Identifier of the term */
	unsigned id;
	
	/** Identifier of the unit (document) */
	unsigned unit;
	
	/** Weight in unit */
	float weight;
		
  public:
  	/** Empty constructor */
  	Triad ();
	
	/** Copy constructor 
	@param q entity to copy
	*/
	Triad (const Triad & t);
  
	/** Main constructor
	@param _id identifier of the term
	@param _unit identifier of the unit or document
	@param _weight weight of the term in the unit */
  	Triad (unsigned _id, unsigned _unit, float _weight);

	/** Assignment operator
	@param t Triad to be copied
	*/
	const Triad& operator=(const Triad& q);
	
	/** Less operator
	@param t0 triad to be compared to this
	@return true if this object is less tan t0
	*/
	bool operator<(const Triad& t0) const;

	/** Greater operator
	@param t0 triad to be compared to this
	@return true if this object is greater tan t0
	*/
	bool operator>(const Triad& t0) const;
	
	/** Return Triad's id */
	unsigned getId() const;
	
	/** Return Triad's unit */
	unsigned getUnit() const;
	
	/** Return Triad's weight */
	float getWeight() const;
	
	/** Reads a Triad from a file
	@param fp file to read from
	*/
	void read(ifstream& fp);
	
	/** Writes a Triad to a file
	@param fp file to write in
	*/
	void write(ofstream& fp) const;
		
	/** Returns the size of a Triad object */
	static unsigned size();
	
	/** Destructor */
	~Triad ();
};

#endif

