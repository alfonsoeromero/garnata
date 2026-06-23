#include "Query.h"

// ==================================================================

Query::Query( const string& s ) : empty(string(""))
{
  istringstream is(s);

  while (!is.eof())
  {
    string str("");
    is >> str;
    if (str.size())
    {
     if (str[0] != '<')
      terms.push_back(str);
    }
  }
}

// ==================================================================

unsigned Query::size(void) const { return terms.size(); }

// ==================================================================

const string& Query::operator[] (unsigned i) const 
{ 
  if( i < terms.size() )
    return terms[i];
  else
  {
   Globals::showWarning("Array bounds out of range (Query::operator[]), returning null string");
   return empty;
  }
}


// ==================================================================

Query::~Query() { ; }

// ==================================================================
