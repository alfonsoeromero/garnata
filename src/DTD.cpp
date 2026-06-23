#include "DTD.h"
using namespace std;

#include <iostream>

// ==================================================================

DTD::DTD () : id(0) { }

// ==================================================================

DTD::DTD (const string& _fileName, unsigned _id) : fileName(_fileName), id(_id) 
{ }

// ==================================================================

DTD::DTD (const DTD& d) : 
  fileName(d.fileName), id(d.getId()), tagsById(d.tagsById), idsByTag(d.idsByTag) 
  { }

// ==================================================================

void DTD::add( const string& s, unsigned _id )
{
  idsByTag[s] = _id;
  tagsById[_id] = s;
}

// ==================================================================

DTD::~DTD() { }

// ==================================================================

unsigned DTD::size() const { return tagsById.size(); }

// ==================================================================

string DTD::getFileName() const { return fileName; }

// ==================================================================

void DTD::write(ofstream& o)
{

  // Format of the file:
  // fileName'\n'id'\n'size'\n'id_1'\n'tag_1'\n'...
  //     'id_size'\n'tag_size'\n'
  
  o << fileName << "\n" << id << "\n" << tagsById.size() << "\n";
  
  for (map<unsigned, string>::const_iterator it=tagsById.begin(), end=tagsById.end(); it!=end; ++it)
    o << it->first << "\n" << it->second << "\n";
  
}

// ==================================================================

void DTD::read(ifstream& ifs)
{
  // Format of the file:
  // fileName'\n'id'\n'size'\n'id_1'\n'tag_1'\n'...
  //     'id_size'\n'tag_size'\n'
  ifs >> fileName;
  ifs >> id;
  unsigned _size;
  ifs >> _size;
  
  for (unsigned i=0; i<_size; ++i)
  {
    unsigned id;
    string tag; 
    ifs >> id;
    ifs >> tag;
    this->add(tag, id);
  }
}

// ==================================================================

string DTD::getTagById(unsigned _id) const
{
  map<unsigned, string>::const_iterator it = tagsById.find(_id);
  if (it != tagsById.end())
    return it->second;
  else return string("");
}

// ==================================================================

bool DTD::getIdByTag(const string& s, unsigned& _id) const
{

  map<string, unsigned>::const_iterator it = idsByTag.find(s);

  if (it != idsByTag.end()) // if found
  {
    _id = it->second;
    return true;
  } else return false;

}

// ==================================================================

unsigned DTD::getId() const { return id; }

// ==================================================================

