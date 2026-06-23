#include "UnitWriter.h"

// ==================================================================

UnitWriter::UnitWriter () : Unit() { }

// ==================================================================

UnitWriter::UnitWriter(const Unit& u) : Unit(u) {}

// ==================================================================

UnitWriter::UnitWriter ( unsigned _id,  unsigned _tagId, unsigned _container, unsigned _file) :
   Unit (_id, _tagId, _container, _file)
{ } 
    
// ==================================================================

void UnitWriter::write(fstream& ofs)
{
  {
    unsigned tmp[5];
    tmp[0] = getTagId();
    tmp[1] = getPosition();
    tmp[2] = getNumContained();
    tmp[3] = getContainer();
    tmp[4] = getFile();
    
    ofs.write( (char*) tmp, sizeof(unsigned) * 5);
  }
  
  ofs.write( (char*) &weight, sizeof(float) );

  ofs.write( (char*) &mode, sizeof(char) );

  if (ofs.fail())
  {
    cerr << "ERROR: Bad ifs (UnitReader::write), exiting\n";
    exit(-1);
  }
}

// ==================================================================

void UnitWriter::setWeight(float w) { weight = w; }

// ==================================================================

void UnitWriter::setRoute (vector<unsigned>& v) 
{ 
  ifxpath[id] = fxpath.getPosition();

  //we write the xpath itself in fxpath
  fxpath.writeUnsignedList( v );
}

// ==================================================================

void UnitWriter::updateWeight(float w, fstream& fp)
{
  // Weight is located after 7 unsigned
  weight = w;

  long __offset = SIZE_UNIT*id;
  
  // Indirection => we position the pointer of funt
  fp.seekp(__offset, std::ios_base::beg);
  if (fp.fail()) 
  {
    cerr << "Bad funt (UnitWriter::updateWeight I), exiting\n";
    exit (-1);
  }
  
  this->write(fp);
}

// ==================================================================

void UnitWriter::close()
{
  funt.close();
}

// ==================================================================

void UnitWriter::setFiles(const string& Fpar, const string& Fdesc, const string& IFpardesc, const string& Funt, 
	const string& Fdir, const string& IFdir, const string& Fxpath, const string& IFxpath,
	VariableByteCoder& vc)
{
  fpar.setCompressionAlgorithm(&vc);
  fpar.open( Fpar, 262144 );
  fdesc.setCompressionAlgorithm(&vc);
  fdesc.open( Fdesc, 262144 );
  fdir.setCompressionAlgorithm(&vc);
  fdir.open( Fdir, 524288 );
  fxpath.setCompressionAlgorithm(&vc);
  fxpath.open( Fxpath, 524288 );
  
  ifpardesc.open(IFpardesc, 524288 );
  
  funt.open(Funt.c_str(), ios_base::out | ios_base::binary );
  if (funt.fail())
  {
    cerr << "ERROR: Bad funt (UnitWriter::setFiles), exiting\n";
    exit(-1);
  }
  
  ifdir.open(IFdir, 524288 );
  ifxpath.open(IFxpath, 524288 );
}

// ==================================================================

void UnitWriter::modify( ) 
{
  //1st. => we position the pointer of funt
  funt.seekp(id * SIZE_UNIT, std::ios_base::beg);
  if (funt.fail())
  {
    cerr << "ERROR: Bad funt (UnitWriter::modify I), exiting\n";
    exit(-1);
  }
  
  //2nd: we write (modify) the unit
  this->write( funt );
  if (funt.fail())
  {
    cerr << "ERROR: Bad funt (UnitWriter::modify II), exiting\n";
    exit(-1);
  }
}

// ==================================================================

void UnitWriter::store()
{
  funt.seekp(id * SIZE_UNIT, std::ios_base::beg);

  //Indirection => we write the unit on funt
  this->write( funt );
}


// ==================================================================

void UnitWriter::setListOfDescendants ( const vector<unsigned>& v )
{
//  if (!isFinal())
//    cerr << "WARNING: Unit is NOT FINAL, cannot set its list of descendants\n";
//  else {
    ifpardesc[id] = fdesc.getPosition(); 
    fdesc.writeSortedUnsignedList(v, false);
//  }
}

// ==================================================================

void UnitWriter::setListOfParents ( const vector<unsigned>& v )
{
  if ( !isContainer() )
    cerr << "WARNING: Unit is not a container, so it has not parents\n";
  else
  {
    ifpardesc[id] = fpar.getPosition();
    fpar.writeSortedUnsignedList(v, true);
  }
}

// ==================================================================

void UnitWriter::setListOfTerms ( const vector<unsigned>& v, const vector<unsigned>& freqs )
{
    ifdir[id] = fdir.getPosition();
    fdir.writeSortedUnsignedList(v, true);
    fdir.writeUnsignedList(freqs);
}

// ==================================================================

void UnitWriter::clearMode ( ) { mode = 0; }

// ==================================================================

void UnitWriter::setMode (char _mode) { mode |= _mode; }

// ==================================================================

void UnitWriter::setPosition (unsigned _position) { position = _position; }

// ==================================================================

void UnitWriter::setNumContained (unsigned _numContained) { numContained = _numContained; }

// ==================================================================

UnitWriter::~UnitWriter() { }

// ==================================================================

fstream UnitWriter::funt;

OutputIndexFile<long> UnitWriter::ifpardesc;

OutputIndexFile<long> UnitWriter::ifdir;

OutputIndexFile<long> UnitWriter::ifxpath;

OutputCompressedBinaryFile UnitWriter::fxpath;

OutputCompressedBinaryFile UnitWriter::fpar;
    
OutputCompressedBinaryFile UnitWriter::fdesc;

OutputCompressedBinaryFile UnitWriter::fdir;
