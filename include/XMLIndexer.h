#ifndef __XMLIndexer_H__
#define __XMLIndexer_H__

#include "IndexBuilder.h"
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <string>

XERCES_CPP_NAMESPACE_USE

XERCES_CPP_NAMESPACE_BEGIN
class XMLString;
class Attributes;
class XMLPlatformUtils;
class DefaultHandler;

class XMLIndexer : public DefaultHandler
{
  public:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XMLIndexer( IndexBuilder &_Ib );
    ~XMLIndexer();

    // -----------------------------------------------------------------------
    //  Handlers for the SAX ContentHandler interface
    // -----------------------------------------------------------------------
    void startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
    void endElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
    void characters(const XMLCh* const chars, const unsigned int length);

    void startDTD( const XMLCh* const name, const XMLCh* const publicId, 
      const XMLCh* const systemId);
    
    void startEntity (const XMLCh *const name);
    // -----------------------------------------------------------------------
    //  Handlers for the SAX ErrorHandler interface
    // -----------------------------------------------------------------------
    void warning(const SAXParseException& exc);
    void error(const SAXParseException& exc);
    void fatalError(const SAXParseException& exc);
    void resetErrors();
    
    // own functions
    void parseFile(const string& fileName);


  private:
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fAttrCount
    //  fCharacterCount
    //  fElementCount
    //  fSpaceCount
    //      These are just counters that are run upwards based on the input
    //      from the document handlers.
    //
    //  fSawErrors
    //      This is set by the error handlers, and is queryable later to
    //      see if any errors occured.
    // -----------------------------------------------------------------------

    void startIndexer();
    void finishIndexer();    
    bool            fSawErrors;
    IndexBuilder    &Ib;
    SAX2XMLReader*  parser;
};

XERCES_CPP_NAMESPACE_END

#endif

