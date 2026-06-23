#ifndef __RESULT_H__
#define __RESULT_H__

#include <string>
#include <iostream>

using namespace std;

// ==================================================================

class Result {
  public:
    Result(const string& _fileName, const string& _route, float _rsv) :
      fileName(_fileName), route(_route), RSV(_rsv) { ; }
      
    Result(const Result& r) : fileName(r.fileName), route(r.route), RSV(r.RSV) { ; }
  
    /** Name of the file */
    string fileName;
    
    /** Route of the represented unit */
    string route;
    
    /** RSV of relevance of this unit */
    float RSV;
};

// ==================================================================

/** Ostream operator to make an XML output of a result */
ostream& operator << (ostream& os, const Result& s);

#endif
