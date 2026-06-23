#ifndef __INDEX_H__
#define __INDEX_H__

#include <string>
#include <stack>
#include "Collection.h"
#include "Globals.h"

using namespace std;

class Index {
  protected:  
    /** Collection this index represents */
    const Collection& c;
  
    /** Identifier of the index */
    string identifier;
  
    /** Name of the file containing the lexicon */
    string lexiconFileName;
    
    /** Name of the file containing the file of occurrences */
    string occurrenceFileName;
    
    /** Name of the file of positions */
    string positionsFileName;
    
    /** Name of the file of units */
    string f_unt;
    
    /** Name of the inverted file of units */
//    string if_unt;
    
    /** Name of the file of parents */
    string f_par;
    
    /** Name of the file of descendants */
    string f_desc;
    
    /** Name of the inverted file for the two 
    previous files */
    string if_par_desc;
    
    /** Name of the file that contains information 
    about the different DTDs */
    string dtdlistFileName; 
    
    /** File of cache of occurrences */
    string cacheFileName;
    
    /** File of Quads */
    string quadFileName;

    /** File of stopwords */
    string stopwordsFileName;
        
    /** Direct index file name */
    string f_dir;
        
    /** Inverted file to search the direct index */
    string if_dir;

    /** Xpaths file name */
    string f_xpath;
        
    /** Inverted file to search the xpath file */
    string if_xpath;
    
    /** Name of the current weight file*/
    string currentWeight;
    
    /** stopwords list */
    vector<string> stopwords;
    
    /** list of possible weight files */
    vector<string> weights;
    
    /** roots list */
    vector<unsigned> roots;
    
    /** Total number of units in the index */
    unsigned NUMUNITS;
    
    /** Total number of final units in the index */
    unsigned NUMFINALUNITS;

  public:
    /** Constructor */
    Index( const Collection& _c );    
    
    /** Main constructor (used for writing an index)
    @param _c collection this index represents
    @param _identifier identifier of the index
    */
    Index ( const Collection& _c, const string& _identifier );

    /** Reads the index from a file
    @param indexFileName name of the file where the index is stored in
    @param collectionName name of the associated collection
    */
    void read( const string& collectionName );
    
    /** Writes (or updates) the file containing the 
    information of the index. It also updates the entries
    for indexes in the collection object
    */
    void write() const;

    /** Sets the list of stopwords
    @param _stopwordsFileName file of stopwords
    @return true if everyting went OK, false if file is corrupt
       or does not exist
    */
    bool setStopwordList(const string& _stopwordsFileName);

    /** Prints information about the index */
    void printInfo() const;
    
    /** Removes the files associated to a certain index
    @param colName name of the collection that index belongs to
    @param indexName name of the index
    */
    static void remove(const string& colName, const string& indexName);

    /**  Removes a weight from the list of the index
    @pre the weight 'name' should exist and should not be equal to 'none'
    @param name name of the weight file to delete
    @post the index file will not be modified after this (so, it should be written
	    from outside)
    */
    void delWeight(const string& name);

    /** Adds a weight to the list of the index
    @pre the weight 'name' should not exist and should not be equal to 'none'
    @param name name of the weight file to add
    @post the index file will not be modified after this (so, it should be written
	    from outside)
    */
    void addWeight(const string& name);
    
    /** Destructor */
    ~Index();
};

#endif

