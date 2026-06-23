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

