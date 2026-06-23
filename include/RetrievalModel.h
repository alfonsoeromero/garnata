#ifndef __RETRIEVAL_MODEL_H__
#define __RETRIEVAL_MODEL_H__

#include <map>
#include "Unit.h"
#include "Query.h"
#include "Result.h"
#include "ProcessedQuery.h"
#include "IndexReader.h"
#include "UnitCache.h"
#include "NodeResult.h"
#include "UnitReader.h"

class RetrievalModel : public IndexReader {
  protected:
    // Internal class used for array sorting
    class MoreDocuments {
      private:
        //! Lexicon used to compare term identifiers
	Lexicon* Lex;
	
       public:
         /** Main constructor 
	 @param _Lex associated lexicon
	 */
         MoreDocuments (Lexicon* _Lex) : Lex(_Lex) { ; }
	 
	 /** Comparison operator
	 @param id1 identifier of the first term
	 @param id1 identifier of the second term
	 */
	 bool operator()(const unsigned& id1, const unsigned& id2) const
	 {
	    return ( (Lex->getTermFromId(id1))->getNumDocs() > (Lex->getTermFromId(id2))->getNumDocs() ); 
	 }
	 
	 /** Destructor */
	 ~MoreDocuments() {  }  
      };

    // cache of units
    UnitCache unitCache;
  
    /** Maximum number of documents we 
    are going to return */
    static unsigned NUMDOCS;
    
    /** Minimum value of weight that 
    we are accepting to return an unit */
    float minWeight;
    
    /** Intersect two sets (id-document, weight), obtaining
    a new set (id-document, weight) containing the common id-documents 
    and an aggregation (see aggregate) of the weights in the two sets
    @param m1 first set
    @param m2 second set
    @return returning set as specified
    */
    map<unsigned, float> intersect(const map<unsigned, float>& m1, 
                                   const map<unsigned, float>& m2);
    
    /** For a term with identifier 'idTerm', it returns
    a set of (id-document, weight) in which that term occurs
    @param idTerm identifier of the term
    @return returning set as specified
    */
    map<unsigned, float> occurrs(unsigned idTerm) const;
    
    /** While building the intersection list of documents, it
    aggregates two weights of a term in two units 
    @param w1 first weight 
    @param w2 second weight
    */
    virtual float aggregate(float w1, float w2) const = 0;

    /**
    Transform a string to be indexed (case folding and 
    removing punctuation marks)
    @param s string to be transformed
    @return string transformed
    */
    string transform(const string& s) const;
    
    /** Return final unit with identifier "i"
    @param i id of the unit to return
    @return the unit itself
    */
    UnitReader* getFinalUnit(unsigned i);

    /** Return complex unit with identifier "i"
    @param i id of the unit to return
    @return the unit itself
    */
    UnitReader* getComplexUnit(unsigned i);

    /**
    Tells if a character (which is not 'isalpha' valid) is an
    ASCII valid character to be indexed
    @param c character to be tested
    @return true if it is valid
    */
    bool valid(char c) const;

    /** Show if we are doing stemming, or not */
    static bool stem;

  public:
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    */
    RetrievalModel ( const Collection& _c, string _identifier );
   
    /** Changes the value of the minimum weight
    @param mw new weight
    */
    void setMinWeight(float mw);

    /** Changes the value of the maximum number of 
    documents to return 
    @param num new number of documents
    */
    static void setNumDocs(unsigned num);
    
    /** Process a given query
    @param q query to process
    @return processed query
    */
    ProcessedQuery processQuery(const Query& q);

    /** Method to notify this class we are doing stemming (true) or not (false)
    @param doStemming true if we are doing stemming
    */
    static void setStem(bool doStemming);

    /** Makes a query to the system
    @param pq 
    @return vector of pairs (document, weitght) 
            sorted by descending weight
    */
    virtual vector<Result> makeQuery(const ProcessedQuery& pq) = 0;
    
    /** Destructor */
    virtual ~RetrievalModel ();   
};

#endif

