#ifndef __UNIT_READER_H__
#define __UNIT_READER_H__

using namespace std;


#include <fstream>
#include <string>
#include <vector>
#include "DTD.h"
#include "InputCompressedBinaryFile.h"
#include "Unit.h"
#include "VariableByteCoder.h"
#include "InputIndexFile.h"

class UnitReader : public Unit {
  private:
    /** Reads the unit from a stream 
    @param ifs input stream
    */
    void read(fstream& ifs);
    
    /** file for units */
    static fstream funt;
    
    /** Index file for the file of parents and the file
    of descendants */
    static InputIndexFile<long> ifpardesc;

    /** Index file for the direct index */
    static InputIndexFile<long> ifdir;

    /** Index file for the file of xpaths */
    static InputIndexFile<long> ifxpath;

    /** file for xpaths */
    static InputCompressedBinaryFile fxpath;
    
    /** File of parents */
    static InputCompressedBinaryFile fpar;
    
    /** File of descendants */
    static InputCompressedBinaryFile fdesc;
 
    /** file for direct index */
    static InputCompressedBinaryFile fdir;
    
  public:
    /** Empty constructor */
    UnitReader ();
    
    /** Constructor from the id
    @param _id identifier of the Unit
          we want to build
    */
    UnitReader (unsigned _id);

    /** Copy constructor
    @param u Unit to be copied
    */
    UnitReader (const Unit& u);

    /** Assignment operator
    @param u entity to copy
    */
    const UnitReader& operator=(const Unit& u);
    
    /** Returns XPath route of this unit
    @param dtd DTD of this unit
    @return route of the unit
    */
    string getRoute(DTD* dtd) const;

    /** Return the list of descendants of this unit
    @param l list of descendants (modified)
    */
    void getListOfDescendants (vector<unsigned>& l);
    
    /** Return the list of parents of this unit
    @param l list of parents (modified)
    */
    void getListOfParents (vector<unsigned>& l);

    /** Return the list of term (direct index) of this unit
    @param l list of terms (modified)
    @param freq list of frequencies (modified)
    */
    void getListOfTerms (vector<unsigned>& l, vector<unsigned>& freq);
    
    /** Returns unit's depth (i.e. distance to the closest root element) 
      @return unit's depth
    */
    unsigned depth() const;

    // COMENTA!    
    void setMode(char mode);
    
    /** Open some internal files to be used with this class
    @param Fpar name of the file of parents
    @param Fdesc name of the file of descendants
    @param IFpardesc name of the index file for the previous two
    @param Funt file of units
    @param Fdir name of the file containing the direct index
    @param IFdir index file for the previous one
    @param Fxpath name of the file containing the xpaths
    @param IFxpath index file for the previous one
    @param output true if we are creating an index
    @param vc compression algorithm
    */
    static void setFiles(const string& Fpar, const string& Fdesc, const string& IFpardesc,
      const string& Funt, const string& Fdir, const string& IFdir, const string& Fxpath, 
      const string& IFxpath, CompressionAlgorithm& vc);
    
    /** Close the internal files */
    static void close();
    
    /** Destructor */
    ~UnitReader();
};

#endif

