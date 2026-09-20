/*
 * XMLIndexer.cpp - The Garnata Retrieval System
 * Copyright (C) 2005, 2026 Alfonso E. Romero
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <xercesc/util/XMLChar.hpp>
#include "XMLAdditional.h"
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/sax2/Attributes.hpp>

// ==================================================================

XMLIndexer::XMLIndexer( IndexBuilder &_Ib ) :
    fSawErrors(false),
    Ib(_Ib)
{
    startIndexer();
    // we select some features of the parser
    parser->setFeature(XMLUni::fgXercesLoadExternalDTD, false); /** we don't
request external entities, even if validation is turned off */
    parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
    parser->setFeature(XMLUni::fgXercesSchema, true);
    parser->setFeature(XMLUni::fgXercesSchemaFullChecking, false);
    parser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, false);
    parser->setFeature(XMLUni::fgSAX2CoreValidation, false); // turn false if you don't want validation
    parser->setFeature(XMLUni::fgXercesDynamic, true);

    // we set the handlers
    parser->setContentHandler(this);
    parser->setLexicalHandler(this);
    parser->setErrorHandler(this);
}

// ==================================================================

XMLIndexer::~XMLIndexer()
{ }

// ==================================================================

void XMLIndexer::parseFile(const string& fileName)
{
  Ib.startDocument();
  parser->parse( fileName.c_str() );
  Ib.endDocument();
}

// ==================================================================

// ---------------------------------------------------------------------------
//  Implementation of the SAX DocumentHandler interface
// ---------------------------------------------------------------------------
void XMLIndexer::startElement(const XMLCh* const uri
                                   , const XMLCh* const localname
                                   , const XMLCh* const qname
                                   , const Attributes& attrs)
{
    string tagType;
    for(unsigned i=0, len=XMLString::stringLen(qname); i<len; ++i)
    {
      tagType += char(qname[i]);
    }
    
    Ib.startUnit(tagType);
}

// ==================================================================

void XMLIndexer::startEntity (const XMLCh *const name)
{
/*
  string _name;
  for(unsigned i=0, len=XMLString::stringLen(name); i<len; ++i)
  {
    _name += char(name[i]);
  }
  
  cout << "ENTITY => " << name << endl;
*/
}

// ==================================================================

void XMLIndexer::characters(const XMLCh* const chars, 
                            const XMLSize_t length)
{ 

  if(XMLChar1_0::isAllSpaces(chars, length)) return; 

  string s(length, (char) 0);

  if ((length % 4) == 0)
  {

    for (unsigned i=0; i<length; i+=4)
    {
      s[i] = char(chars[i]);
      s[i+1] = char(chars[i+1]);
      s[i+2] = char(chars[i+2]);
      s[i+3] = char(chars[i+3]);
    }

  } else if ((length % 2) == 0) {

    for (unsigned i=0; i<length; i+=2)
    {
      s[i] = char(chars[i]);
      s[i+1] = char(chars[i+1]);
    }

  } else  {

    for (unsigned i=0; i<length; ++i)
      s[i] = char(chars[i]);
  }

  Ib.characters(s);
}

// ==================================================================

void XMLIndexer::endElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname )
{  Ib.endUnit(); }

// ==================================================================

void XMLIndexer::startDTD( const XMLCh* const name, const XMLCh* const publicId, 
    const XMLCh* const systemId)
{
  unsigned len = XMLString::stringLen(name);
  string s;
  for (unsigned i=0; i<len; ++i)
    s += char(name[i]);
 
  Ib.changeDTD(s);
}

// ---------------------------------------------------------------------------
//  Overrides of the SAX ErrorHandler interface
// ---------------------------------------------------------------------------
void XMLIndexer::error(const SAXParseException& e)
{
    fSawErrors = true;
    XERCES_STD_QUALIFIER cerr << "\nError in file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", col. " << e.getColumnNumber()
         << "\n  Message: " << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
}

// ==================================================================

void XMLIndexer::fatalError(const SAXParseException& e)
{
    fSawErrors = true;
    XERCES_STD_QUALIFIER cerr << "\nFatal error in file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", col. " << e.getColumnNumber()
                 << "\n  Message: " << StrX(e.getMessage()) << endl;
}

// ==================================================================

void XMLIndexer::warning(const SAXParseException& e)
{
    XERCES_STD_QUALIFIER cerr << "\nWarning in file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", col. " << e.getColumnNumber()
         << "\n  Message: " << StrX(e.getMessage()) << endl;
}


// ==================================================================

void XMLIndexer::resetErrors()
{
    fSawErrors = false;
}

// ==================================================================

void XMLIndexer::startIndexer()
{
    try {
          XMLPlatformUtils::Initialize();
    } catch (const XMLException& toCatch) {
        XERCES_STD_QUALIFIER cerr << "Error during initialization! Message:\n"
            << StrX(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
        exit(-1);
    }
    parser = XMLReaderFactory::createXMLReader();
}

// ==================================================================

void XMLIndexer::finishIndexer() 
{
    delete parser;
    // we call the termination method
    XMLPlatformUtils::Terminate();
}

// ==================================================================


