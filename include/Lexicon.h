#ifndef __LEXICON_H__
#define __LEXICON_H__

#include "Term.h"
#include <functional>
#include <utility>
#include <string> 

using namespace std;

/** @class Lexicon Lexicon.h 
* Represents the entire lexicon in the system
* @author Alfonso E. Romero <aromero@correo.ugr.es>
* @date 20/03/2005
* @version 0.35
*
* Changelog 0.2
* - MetaIndex has been supressed and assumed to be a simple array
*
* Changelog 0.3
* - Bugs in output/input methods corrented
* - Lexicon::add code rewritten (using standard algorithms)
* - Memory is now incremented in a 33% (20% before)
*
*
* * Changelog 0.35 
* - Removed some unused variables
*   + interval
*   + exponent
*   + metaNum
* - Few documentation changes
*
*/
class Lexicon  
{
  private:
    
    //! Functional to be used inside this class
    //! Tells if a term is less than other
    class LexiconSearch {
      public:
        inline bool operator() (const Term* t1, const Term* t2) const
        {
          return (bool)( t1->getTermString() < t2->getTermString() );       
        }
    };
    
    //! Functional to be used inside this class
    //! Given two terms (one term and a string), returns
    //! true if term is less than the string
    struct greaterTerm {
        inline
	bool operator() (const Term* t, const string& c) const
        {
	  return (bool)(t->getTermString() < c);
        }
    };
    
    /** Number of terms this object contains */
    unsigned num;
    
    /** Maximum capacity of the Lexicon (used while building it) */
    unsigned maxCapacity;    
    
    /** Set of contained terms */
    Term** v;
    
    /** Index of terms by identifier */
    Term** metaIndex;
    
    /**
    * Retrieve the values of an object of this class
    * from a binary file
    * @pre file dest MUST be opened and able to be read
    * @param source file to read
    * @post the pointer to file 'source' is moved forward
    */
    void retrieve(ifstream& input);

    /**
    * Compares two Terms (used in conjunction with
    * void bsearch(...) )
    */    
    static int compareTerms (const void* elem1, const void* elem2 );
    
  public:
    /**
    * Main contructor
    * @param _maxCapacity maximum capacity of the Lexicon, it builds
    *   an empty Lexicon with zero Term contained, but _maxCapacity 
    *   Term space
    */
    Lexicon(unsigned _maxCapacity);
    
    /**
    * Constructor from a file (binary dump of a Lexicon)
    * @param lexiconDumped name of the file
    * @post 'num' and 'maxCapacity' will have the same value
    */
    Lexicon(const string& lexiconDumped);
    
    /**
    * Adds a term to the Lexicon
    * @param newTerm Term to be added
    * @pre the term should not belong to the Lexicon
    * @post the Lexicon will have one more term, 'maxCapacity'
    *   would have been modified and 'newTerm' will get a new id
    * @return identifier assigned to the term
    */
    unsigned add(Term* newTerm);
        
    /**
    * Returns the identifier of a term, if exists
    * @param str string of the wanted term
    * @return the identifier of the term, if exists,
    *   0 if not
    */
    unsigned getIdFromString(const string& str) const;
    
    /**
    * Returns a pointer to a Term, identified by 'id'
    * @param id identifier of a term
    * @pre 'id' must be between 1 and this->getNum()
    * @return the pointer to the Term
    */
    Term* getTermFromId(unsigned id) const;
    
    
    /**
    * Returns a pointer to the 'o'th Term
    * @param o order of the term
    * @pre 'o' must be between 0 and this->getNum() - 1
    * @return the pointer to the Term
    */
    Term* getTermFromOrder(unsigned o) const;    
    
    
    /**
    * Returns the num of different terms in this object
    * @return the value of num
    */
    unsigned getNum() const;

    /**
    * Produces a binary dump of the receiving object
    * @pre file dest MUST be opened and able to be written
    * @param name name of the file where lexicon is dumped
    * @post the pointer to file 'dest' is moved forward
    */
    void write(const string& lexiconName) const;


    /** Dumps a cache file with the "size" most frequent terms
    @param fileName COMPLETE name (including route) of the cache file
    @param size number of terms to dump in
    @post cache file will be written
    */
    void dumpCacheFile(const string& fileName, unsigned size) const;
    
    /**
    * Destructor
    */
    ~Lexicon();
};

#endif

