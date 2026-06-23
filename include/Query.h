#ifndef __QUERY_H__
#define __QUERY_H__

#include <sstream>
#include <string>
#include <vector>
#include "Globals.h"

using namespace std;

class Query{
  private:
    /** Vector of string with the 
    different terms */
    vector<string> terms;

    /** empty string */
    string empty;

  public:
    /** Main constructor
    @param s string containing the different terms of the
      query separated by blanks
    */ 
    Query(const string& s);

    /** Return the term at "i" position
    @param i position of the term we want to return
    */
    const string& operator[] (unsigned i) const;

    /** Return the number of terms that
    belongs to the query
    */
    unsigned size() const;

    /** Destructor */
    ~Query();
};

#endif // __QUERY_H__
