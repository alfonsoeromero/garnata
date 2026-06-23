#include "DTDList.h"
#include <fstream>

// ==================================================================

DTDList::DTDList () { } 

// ==================================================================

DTDList::DTDList (const string& fileName)
{

  ifstream ifs;
  ifs.open( fileName.c_str() );
  
  if (!ifs) Globals::errorAndExit( const_cast<char*>(fileName.c_str()) );

  unsigned _size;
  ifs >> _size;
  
  for (unsigned i=0; i<_size; i++)
  {
    DTD* _d = new DTD();
    if (!_d) Globals::errorAndExit("Not enough memory for '_d' (DTDList::DTDList), exiting ");
    _d->read(ifs);
    dtds.push_back(_d);
  }
}

// ==================================================================

void DTDList::write(const string& fileName)
{
  ofstream ofs;
  ofs.open( fileName.c_str() );
  
  if (!ofs) Globals::errorAndExit( const_cast<char*>(fileName.c_str()) );

  ofs << dtds.size() << "\n";
  
  for (vector<DTD*>::const_iterator it=dtds.begin(), end=dtds.end(); it<end; ++it)
    (*it)->write(ofs);
}

// ==================================================================

bool DTDList::getDTDIdByFilename(const string& fileName, unsigned& _id) const
{
  bool found = false;
  unsigned i, size;
  
  for (i=0, size=dtds.size(); i<size && !found; ++i)
  {
    found = (dtds[i]->getFileName() == fileName);
    if (found)
    {
      _id = dtds[i]->getId();
      return true;
    }
  }

  return false;
}

// ==================================================================

unsigned DTDList::getNextId() const { return dtds.size(); } 

// ==================================================================

string DTDList::getTagById(unsigned _idTag) const
{
  bool found = false;
  string s("");
  for (unsigned i=0, size=dtds.size(); i<size && !found; ++i)
  {
    s = dtds[i]->getTagById(_idTag);
    found = (s.length() > 0);
  }
  return s;
}

// ==================================================================

unsigned DTDList::getIdDTDId(unsigned _idTag) const
{
/** THIS METHOD IS NOT WORKING PROPERLY!!!!!!!!!*/
  bool found = false;
  string s("");
  unsigned i;
  for (i=0; i<dtds.size() && !found; i++)
  {
    s = dtds[i]->getTagById(_idTag);
    found = (s.length() > 0);
  }
/** NOTE THAT WE SHOULD DO return i -1, or find a 
better way to search teh DTDList*/
  return i;
}

// ==================================================================

DTD* DTDList::getDTDbyId(unsigned n) 
{
  if (n>=dtds.size()) Globals::errorAndExit("The given DTD identifier is not valid, exiting");
  return dtds[n];
}

// ==================================================================

DTD* DTDList::addNewDTD(const string& fileName)
{
  DTD* _dtd = new DTD( fileName, getNextId() );

  if (!_dtd) Globals::errorAndExit("Not enough memory for '_dtd' (DTDList::DTDList), exiting ");
  dtds.push_back(_dtd);

  return dtds.back();
}

// ==================================================================

DTDList::~DTDList() 
{ 
  for (unsigned i=0, size=dtds.size(); i<size; ++i) 
    delete dtds[i];
}

// ==================================================================

