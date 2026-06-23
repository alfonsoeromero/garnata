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

