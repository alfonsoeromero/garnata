#ifndef __UNIT_WRITER_H__
#define __UNIT_WRITER_H__

using namespace std;

#include <fstream>
#include <string>
#include <vector>
#include "Unit.h"
#include "OutputCompressedBinaryFile.h"
#include "VariableByteCoder.h"
#include "OutputIndexFile.h"

class UnitWriter : public Unit 
{
  protected:
    /** Index file for the file of parents and the file
    of descendants */
    static OutputIndexFile<long> ifpardesc;

    /** file for units */
    static fstream funt;

    /** Index file for the direct index */
    static OutputIndexFile<long> ifdir;

    /** Index file for the file of xpaths */
    static OutputIndexFile<long> ifxpath;

    /** file for xpaths */
    static OutputCompressedBinaryFile fxpath;

    /** File of parents */
    static OutputCompressedBinaryFile fpar;

    /** File of descendants */
    static OutputCompressedBinaryFile fdesc;

    /** file for direct index */
    static OutputCompressedBinaryFile fdir;

  public:
    /** Empty constructor */
    UnitWriter ();
    
    /** Writes the unit from a stream 
    @param ofs output stream
    */
    void write(fstream& ofs);
    
    /** Main constructor
    @param _id identifier of the unit
    @param _tagId identifier of the tag of the unit
    @param _container identifier of the unit container
    @param _file identifier of the file this unit belongs to
    */
    UnitWriter ( unsigned _id,  unsigned _tagId, unsigned _container, unsigned _file);

    /** Copy constructor
    @param u entity to copy
    */
    UnitWriter (const Unit& u);

    /** Set Unit's route
    @param v new route of the unit
    */
    void setRoute( vector<unsigned>& v ); 

    /** Store unit in the correspondant file */
    void store();

    /** Sets the weight of the unit
    @param w new weight of the unit
    */
    void setWeight(float w);

    /** MODIFY the content of the files
    'funt' and 'ifunt' related to this unit
    @pre Unit should be already written on the files
    */
    void modify();

    /** Updates the weight of the unit to a new one
    @param w new weight of the unit
    @param fp file to write the unit
    @post unit will be written to disk
    */
    void updateWeight(float w, fstream& fp);

    /** Sets the list of descendants of this unit
    @param v list of descendants to be copied
    */
    void setListOfDescendants ( const vector<unsigned>& v );

    /** Sets the list of parents of this unit
    @param v list of parents to be copied
    */
    void setListOfParents ( const vector<unsigned>& v );

    /** Changes the value of 'mode' in the unit
    @param _mode new value of 'mode' parameter (\see Globals.h)
    */
    void setMode (char _mode);
    
    /** Changes the value of 'position' in the unit
    @param _position new value of 'position' parameter (0 if root)
    */
    void setPosition (unsigned _position);
    
    /** Changes the value of 'numContained' in the unit
    @param _num new value of 'numContained' parameter
    */
    void setNumContained (unsigned _numContained);

    /** Sets the list of terms (direct index) of this unit
    @pre v should be sorted in ascending order
    @param v list of terms to be written
    @param freq list of frequencies
    */
    void setListOfTerms ( const vector<unsigned>& v, const vector<unsigned>& freq );
 
    /** Clear current unit's mode
    */
    void clearMode (); 

    /** Open some internal files to be used with this class
    @param Fpar name of the file of parents
    @param Fdesc name of the file of descendants
    @param IFpardesc name of the index file for the previous two
    @param Funt file of units
    @param Fdir name of the file containing the direct index
    @param IFdir index file for the previous one
    @param Fxpath name of the file containing the xpaths
    @param IFxpath index file for the previous one
    @param vc compression algorithm
    */
    static void setFiles(const string& Fpar, const string& Fdesc, const string& IFpardesc,
      const string& Funt, const string& Fdir, const string& IFdir, const string& Fxpath, 
      const string& IFxpath, VariableByteCoder& vc);

    /** Closes UnitWriter's associated files */
    static void close();

    /** Destructor */
    ~UnitWriter();
};

#endif


