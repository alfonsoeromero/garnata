#ifndef __TERM_H__
#define __TERM_H__

#include "Globals.h"
#include "Occurrence.h"
#include "OutputCompressedBinaryFile.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/** @class Term Term.h 
* Represents a term of the system
* @author Alfonso E. Romero <aromero@correo.ugr.es>
* @date 20/03/2005
* @version 0.5
*
* Changelog 0.2
* - There is not next pointer due to new 'metaIndex'
*   structure on the Lexicon
*
* Changelog 0.5
* - Terms are now stored as strings
*/
class Term
{
  protected:  
    /**
    * Unique identifier of the term in the system. Term identifiers
    *   goes from 0 to |T|-1 (internally), while we (externally) will work
    *   from 1 to |T|
    */
    unsigned id;

    /**
    * Absolute frequency of the term on the 
    * collection whose Lexicon belongs to.
    */    
    unsigned freq;

    /**
    *	Number of documents this term appears in
    */
    unsigned numDocs;
        
    /**
    * Offset in the file of occurrences
    */
    long offsetFileOcc;
  
    /**
    * String representing the term
    */
    string termString;

    /**
    * Produces a binary dump of the receiving object
    * @pre file dest MUST be opened and able to be written
    * @param out a pointer to a file where objects are dumped
    * @post the pointer to file 'dest' is moved forward
    */
    void dump(ofstream& out) const;
  
    /**
    * Retrieve the values of an object of this class
    * from a binary file
    * @pre file dest MUST be opened and able to be read
    * @param in file to read
    * @post the pointer to file 'source' is moved forward
    */
    void retrieve(ifstream& in);

    /**
    * Sets the Id of a term
    * @param _id new id of the term
    */    
    void setId(unsigned _id);
    
  public:    
    /**
    * Empty constructor
    */
    Term();
    
    /**
    * Main Constructor
    * @param _termString string representing the term
    * @param _id identifier assigned to the term by the 
    *       parent
    * @param _freq frequency of the term
    * @pre parameter _termString must have been previously
    *       allocated on dynamic memory, and must not be
    *       deallocated by anybody but THIS class   
    */
    Term(const string& _termString, unsigned _id, unsigned _freq);

    /**
    * Another Constructor
    * @param _termString string representing the term
    * @param _freq frequency of the term
    * @pre parameter _termString must have been previously
    *       allocated on dynamic memory, and must not be
    *       deallocated by anybody but THIS class   
    */
    Term(const string& _termString, unsigned _freq);
                        
    /**
    * Returns the identifier of this term
    * @return the identifier of the receiver of this message
    */
    unsigned getId() const;
    
    /**
    * Returns the length of this term
    */
    unsigned getLength() const;
    
    /**
    * Returns the string of the term
    * @return an array of char that contains the string of the term
    */
    string getTermString() const;
    
    /**
    * Returns the absolute frequency of the term
    * @return the number of times this term appears in the collection
    */
    unsigned getFreq() const;
    
    /**
    * Returns number of documents this term appears in
    * @return numDocs
    */
    unsigned getNumDocs() const;

    /**
    * Returns the Occurrence object linked to this term
    * @return that Occurrence
    */
    Occurrence getOccurrence() const; 

    /**
    * Updates the value of the corresponding Occurrence
    * @param occ new occurrence
    * @param occFile compressed file of occurrences
    */
    void updateOccurrence(Occurrence& occ, OutputCompressedBinaryFile& occFile);
    
    /**
    * Sets the value of the offset in the file of Occurrences,
    * corresponding to this Term's Occurrence
    * @param offset value of the offset
    */
    void setOffsetFileOcc(long offset);
    
    /** Increments in 1 the absolute frequency
    of the term
    */
    void incFrequency();
    
    /** Increments in 1 the number of documents 
    this term appears in
    */
    void incDocuments();
    
    /**
    * Destructor
    */
    ~Term();  
    
    friend class Lexicon;
    friend class Occurrence;
};

#endif


