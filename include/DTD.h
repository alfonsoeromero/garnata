#ifndef __DTD_H__
#define __DTD_H__

using namespace std;
#include <string>
#include <vector>
#include <fstream>
#include <map>

// forward declaration needed
class DTDList;

class DTD {
  private:
    /** Name of the DTD that represents */
    string fileName;
  
    /** Id of the DTD */
    unsigned id;
  
    /** tags by id */
    map < unsigned, string > tagsById;
    
    /** ids by tag */
    map< string, unsigned > idsByTag;
    
    /** Writes the DTD to a file */
    void write(ofstream& o);
    
    /** Reads the DTD from a file */
    void read(ifstream& i);
    
  public:
    /** Empty constructor */
    DTD ();
  
    /** Main constructor 
    @param fileName name of the file this DTD represents
    @param _id identifier of this DTD
    */
    DTD (const string& _fileName, unsigned _id);
    
    /** Copy constructor
    @param d entity to copy
    */
    DTD (const DTD& d);
    
    /** Adds a new tag to the list */
    void add( const string& s, unsigned _id );
    
    /** Returns the number of diferent tags
    this DTD contains
    @return number of tags */
    unsigned size() const;
    
    /** Returns the id of the DTD
    @return id of the DTD
    */
    unsigned getId() const;
    
    /** Returns */
    string getFileName() const;
    
    /** Returns the tag correnponding to the
    id given as a parameter. Returns "" if it
    does not belong to this DTD
    @param _id identifier whose tag is wanted
    @return string that represents that tag
    */
    string getTagById(unsigned _id) const;
    
    /** Returns the id corresponding to the 
    given string tag. Returns false if it does
    not belong to this DTD. 
    @param s tag whose identifier is wanted
    @param _id returns the identifier, if found 
    @return true if found, false if not
    */
    bool getIdByTag(const string& s, unsigned& _id) const;
    
    /** Destructor */
    ~DTD();
    
    friend class DTDList;
};

#endif


