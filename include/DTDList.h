#ifndef __DTDList_H__
#define __DTDList_H__

using namespace std;

#include <vector>
#include <string>
#include "DTD.h"
#include "Globals.h"

class DTDList {
  private:
    /** List of the different DTDs */
    vector <DTD*> dtds;
    
  public:
    /** Empty constructor */
    DTDList ();
    
    /** Constructs the DTDList from a file 
    (should be created with the 'write' operation) */
    DTDList (const string& fileName);
    
    /** Writes the DTDList to a file (not binary) 
    @param fileName name of the file
    */
    void write(const string& fileName);

    /** Returns the next id 
    corresponding to the next DTD
    @return the next id
    */
    unsigned getNextId() const;
    
    /** Search for the id of an specified file
    @param fileName name of the DTD whose identifier we want
    @param _id identifier of the DTD, if found
    @return true if found, false if not
    */
    bool getDTDIdByFilename(const string& fileName, unsigned& _id) const;

    /** Adds a new DTD to the list. 
    @param fileName name of the new DTD
    @return pointer to the DTD added
    */
    DTD* addNewDTD(const string& fileName);
    
    /** Returns the tag correnponding to the
    id given as a parameter. Returns "" if it
    does not belong to any DTD
    @param _id identifier whose tag is wanted
    @return string that represents that tag
    */
    string getTagById(unsigned _id) const;
    
    /** Returns the id of the DTD corresponding 
    to the DTD that the tag identifier identified
    by "_id" belongs to
    @param _id identifier whose tag is wanted
    @return string that represents that tag
    */
    unsigned getIdDTDId(unsigned _idTag) const;
    
    /** Returns the n-th DTD. 
    @param n identifier of the required DTD
    @post exits if n does not correspond to a valid DTD identifier
    */    
    DTD* getDTDbyId(unsigned n);
    
    /** Destructor */
    ~DTDList();
  
};

#endif

