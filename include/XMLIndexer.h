/*
 * XMLIndexer.h - The Garnata Retrieval System
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
    void startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs) override;
    void endElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname) override;
    void characters(const XMLCh* const chars, const XMLSize_t length) override;

    void startDTD( const XMLCh* const name, const XMLCh* const publicId, 
      const XMLCh* const systemId) override;
    
    void startEntity (const XMLCh *const name) override;
    // -----------------------------------------------------------------------
    //  Handlers for the SAX ErrorHandler interface
    // -----------------------------------------------------------------------
    void warning(const SAXParseException& exc) override;
    void error(const SAXParseException& exc) override;
    void fatalError(const SAXParseException& exc) override;
    void resetErrors() override;
    
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

