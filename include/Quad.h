#ifndef __QUAD_H__
#define __QUAD_H__

using namespace std;
#include <fstream>

/** @class Quad Quad.h 
* Represents a temporal representation of the fact that a
*  particular term appears in a particular unit (document) a 
*  certain number of times
* @author Alfonso E. Romero <aromero@correo.ugr.es>
* @date 16/06/2005
* @version 0.1
*/
class Quad {
  private:
	/** Identifier of the term */
	unsigned id;
	
	/** Identifier of the unit (document) */
	unsigned unit;
	
	/** Frequency of the term in the previous unit (or document) */
	unsigned freq;
	
	/** Offset in positions file (if any) */
	long ptrPos;
		
  public:
  	/** Empty constructor */
  	Quad();
	
	/** Copy constructor 
	@param q entity to copy
	*/
	Quad(const Quad& q);
  
	/** Main constructor
	@param _id identifier of the term
	@param _unit identifier of the unit or document
	@param _freq number of times the term appears
	@param _ptrPos offset in position file	*/
  	Quad(unsigned _id, unsigned _unit, unsigned _freq, long _ptrPos);

	/** Assignment operator
	@param q Quad to be copied
	*/
	const Quad& operator=(const Quad& q);
	
	/** Less operator
	@param q0 quad to be compared to this
	@return true if this object is less tan q0
	*/
	bool operator<(const Quad& q0) const;

	/** Great operator
	@param q0 quad to be compared to this
	@return true if this object is greater tan q0
	*/
	bool operator>(const Quad& q0) const;
	
	/** Return Quad's id */
	unsigned getId() const;
	
	/** Return Quad's unit */
	unsigned getUnit() const;
	
	/** Return Quad's freq */
	unsigned getFreq() const;
	
	/** Return Quad's ptrPos */
	long getPtrPos() const;
	
	/** Reads a Quad from a file
	@param fp file to read from
	*/
	void read(ifstream& fp);
	
	/** Writes a Quad to a file
	@param fp file to write in
	*/
	void write(ofstream& fp) const;
	
	/** Reassigns current Quad to a new unit
	@param _unit new unit identifier to assign the Quad
	*/
	void setUnit(unsigned _unit);
		
	/** Returns the size of a Quad object */
	static unsigned size();
	
	/** Destructor */
	~Quad();
};

#endif

