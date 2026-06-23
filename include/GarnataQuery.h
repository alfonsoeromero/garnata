#ifndef __GARNATAQUERY_H__
#define __GARNATAQUERY_H__

#include "Garnata.h"
#include "RetrievalModel.h"
#include "Result.h"
#include <string>

using namespace std;

typedef enum {__BNR_SD=0} model;

class GarnataQuery : public Garnata 
{
  private:
    /** Constant for internal use */
    static const unsigned _FILE = 0x01;
    
    /** Constant for internal use */
    static const unsigned CONSOLE = 0x02;
    
    /** Operation mode */
    unsigned mode;    
    
    /** Stream to write the output */
    ofstream output;
  
    /** Retrieval model we are using */
    RetrievalModel* rm;
    
    /** Tells if the stream is opened */
    bool opened;
    
    /** Shows the help from the program
    @param error if true, shows a brief error message
    */
    void showHelp(bool error);    
    
  public:
    /** Constructor 
    @param collectionName name of the collection to query
    @param indexName name of the corresponding index
    @param identifier id of the retrieval model to be used
    @param doStemming true if we are doing stemming (Porter)
    */
    GarnataQuery(string collectionName, string indexName, model identifier, bool doStemming);
    
    /** Returns the result of a query
    @param s string representing the query    
    */
    vector<Result> makeQuery(const string& s);
    
    /** Process a command sent to the system
    @param s string representing a command
    @return true if we continue, false if we want to
        quit the system
    */
    bool processCommand(const string& s);
    
    /** Tests if a string is a command or not
    @param s string to be tested
    @return true if the string is a command, false if not
    */
    bool isCommand(const string& s) const;
    
    /** Destructor */
    ~GarnataQuery();
};

#endif

// ==================================================================

