#ifndef __ProcessedQuery_H__
#define __ProcessedQuery_H__ 

#include <vector>

using namespace std;

class ProcessedQuery {
  private:
    /** List of term identifiers */
    vector<unsigned> terms;
    
  public:
    /** Main constructor
    @param t list of term identifiers
    */
    ProcessedQuery(vector<unsigned> t);

    /** Copy constructor
    @param p entity to copy
    */
    ProcessedQuery(const ProcessedQuery& p);

    /** Returns the size of the query
    @return size of vector "terms"
    */
    unsigned size() const;
    
    /** Returns the i-th identifier
    @param i index of the identifier wanted
    @return terms[i]
    */
    unsigned operator[](unsigned i) const;
    
    /** Destructor */
    ~ProcessedQuery();
};

#endif
