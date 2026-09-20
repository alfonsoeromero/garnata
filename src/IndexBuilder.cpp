/*
 * IndexBuilder.cpp - The Garnata Retrieval System
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

#include "IndexBuilder.h"

const bool _DEBUG_ = false;

// ==================================================================

IndexBuilder::IndexBuilder (const Collection& c, const string& identifier, bool doStemming) :
  Index(c, identifier),
  L( new Lexicon(Globals::initialLexiconSize) ),
  dtdlist( DTDList() ),
  vc(), pf( positionsFileName, vc)
 {
	  
  // Initialization of variables
  currentUnit = 0;
  currentFile = 0;
  currentTag  = 0;
  currentDTD  = 0;
  quex      = 0;
  sizeFUnit = 0;
  sizeXPath = 0;
  depth = 0;
  extractors = stack<QuadExtractor*>();

  // setting of the stemmer mode
  QuadExtractor::setStem(doStemming);
  
  // Opening of some files
  UnitWriter::setFiles (f_par, f_desc, if_par_desc, f_unt, f_dir, if_dir, f_xpath, if_xpath, vc); 
  
  // Memory allocation
  occFile = new OccurrenceFile( *L, occurrenceFileName ); 
  if (!occFile) Globals::errorAndExit("Not enough memory for occFile(IndexBuilder::IndexBuilder), exiting");
  
  qp = new QuadPool( Globals::quadPoolKBytes, quadFileName );  
  if (!qp) Globals::errorAndExit("Not enough memory for qp (IndexBuilder::IndexBuilder), exiting");
}

// ==================================================================

bool IndexBuilder::setStopwordList(const string& stopwordsFileName)
{
  bool ret = Index::setStopwordList(stopwordsFileName);
  if (ret)
    QuadExtractor::setStopwordList(stopwords);
  
  return ret;
}

// ==================================================================

void IndexBuilder::addRoot(unsigned id)
{
  if (_DEBUG_) cout << "new root: " << id << "\n";
  roots.push_back(id);
}

// ==================================================================

void IndexBuilder::characters (const string& s)
{
  // "currentUnit" was incremented when receiving the event
  // "startUnit", so we pass to the QuadExtractor currentUnit - 1
  if (_DEBUG_) cout << " receiving characters...\n";
  if (!quex) // if the extractor was not built
  {
    // we build it
    quex = new QuadExtractor(s, current->getUnit()->getId(), *L, pf);
    if (!quex) Globals::errorAndExit("Not enough memory for 'quex' (IndexBuilder::characters), exiting ");
  } else 
    quex->add(s);
    
  ((UnitWriter*)current->getUnit())->setMode (Globals::pcdata); // current unit is final
}

// ==================================================================

void IndexBuilder::changeDTD ( const string& dtdName )
{	
  unsigned _id;
  
  // if the DTD identified by that file already existed ...
  if (dtdlist.getDTDIdByFilename(dtdName, _id))
    currentDTD = dtdlist.getDTDbyId(_id);  // we take it as the current DTD
  else  // otherwise, we create it
    currentDTD = dtdlist.addNewDTD(dtdName);
  
  hasDtdDeclared = true;
}

// ==================================================================

void IndexBuilder::startDocument ()
{ 
  // We prepare the tree structure to contain information
  // about different structural units
  current = 0;
  hasDtdDeclared = false;
  if (_DEBUG_) cout << "----------------------------------------------------- new file!!\n";
}

// ==================================================================

void IndexBuilder::endDocument ()
{ 
  ++currentFile; // we increment the number of processed files
  if (_DEBUG_) cout << "end of file...\n";
}

// ==================================================================

void IndexBuilder::startUnit ( const string& tagType ) 
{
  // if the file didn't declared a DTD previously, we set it
  // manually one
  if (!hasDtdDeclared) changeDTD("__default");

  if (_DEBUG_) cout << "New unit:\n";
	
  //0.- We preserve the previous extractor (if any)
  if (quex || !extractors.empty() )
  {
    extractors.push(quex);
    quex = 0;
  }
  
  //1.- We get (on _idUnit) the identifier of
  // the tag of this unit
  unsigned _idUnit;
  
  if (!currentDTD->getIdByTag(tagType, _idUnit)) // 2.- Does this identifier exist?
  {
    // if the identifier did not exist, we create it
    ++currentTag;
    _idUnit = currentTag;
    currentDTD->add(tagType, _idUnit);
  }

  //3.-We build the node
  unsigned _idContainer;
  NodeTree* nt = new NodeTree(currentUnit, _idUnit);
  if (!nt) Globals::errorAndExit("Not enough memory for 'nt' (IndexBuilder::startUnit), exiting ");

  if (current)
  {
    nt->setContainer(current);
    current->addContained(nt);
    _idContainer = current->getId();
  } else {
    nt->setRoot();
    this->addRoot(currentUnit);
    _idContainer = 0;
  }
  current = nt;

  //4.-We build the Unit object
  UnitWriter *u = new UnitWriter( currentUnit,  _idUnit, _idContainer, currentFile ); 
  if (_DEBUG_) cout << " id: " << currentUnit << "\n  tagType:" << _idUnit << "\n  container:" << _idContainer << "\n  file:" << currentFile << "\n---\n";
  if (!u) Globals::errorAndExit("Not enough memory for 'u' (IndexBuilder::startUnit), exiting ");
    // and we associate it to the node 
  current->setUnit(u);
  
  //5.-We set the parent of this unit not to be final
  NodeTree* f_current = current->getContainer();
  if (f_current) // if not root
  {
    ((UnitWriter*)f_current->getUnit())->setMode( Globals::container );
    // we also arrange the position of the unit
    u->setPosition(f_current->getContained().size());
  } else
    u->setPosition(0);
  
  //6.- Finally, we increment the counter of units and the number of units
  ++currentUnit;
  ++NUMUNITS;
}

// ==================================================================

void IndexBuilder::endUnit ()
{
  // 1.- If unit was container and final, we create a virtual unit
  UnitWriter* u = (UnitWriter*)(current->getUnit());
  UnitWriter* tmp = u;
  
  if (_DEBUG_) cout << "unit " << u->getId() << " finished\n" << u->isContainer() << " " << u->isFinal();
  
  bool virtualUnitCreated = false;
  unsigned virtualUnitId;
//  if (u->isContainer() && u->isFinal())
  if (quex && u->isContainer())
  {
    if (_DEBUG_) cout << "we must create a virtual node!!\n";
    // we create a virtual unit, and we get its Id
    u = (UnitWriter*) arrangeVirtualNode();
    virtualUnitCreated = true;
    virtualUnitId = u->getId();
    if (_DEBUG_) cout << "virtual node " << virtualUnitId << " created\n";
  }
  
  // 2.- We process the list of Quads, if any
  if (quex)
  {
    if (_DEBUG_) cout << "unit is final, not container\n";
    
    // 2.1.- We obtain a list of quads from the current extractor
    vector<Quad> q = quex->getList();
    // 2.2.- We add them to the QuadPool, changing its id if needed
    for (vector<Quad>::iterator it=q.begin(), end=q.end(); it!=end; ++it)
    {
      if (virtualUnitCreated) it->setUnit(virtualUnitId);
      qp->add(*it);
    }
    
    // 2.3.- Because u is a final unit, we write the direct index
    //       and its number of contained terms
    u->setNumContained ( quex->getNumContained() );
    vector<unsigned> terms, freqs;
    quex->getTermListAndFrequencies(terms, freqs);
    u->setListOfTerms ( terms, freqs );
    if (_DEBUG_) cout << " setting unit " << u->getId() << " as final!\n";
//    u->setMode (Globals::pcdata); // current unit is final
    
    // 2.4.- We increment the number of final units, if it was not incremented
    //       in "arrangeVirtualNode"
    if(!virtualUnitCreated)
    {
      // If unit is final, we store the path to root of this unit
      u->setListOfDescendants ( current->getPathToRoot() );
      ++NUMFINALUNITS;
    }
    
    // 2.5.- we free memory associated with the extrator (textual information of unit)
    delete quex;
  } 

  
  // 3.- We rearrange the extractors, setting the current extractor to
  //     be the one that my parent had (0 if any)
  quex = 0;
  if (!extractors.empty())
  {
    quex = extractors.top();
    extractors.pop();
  }
  
  // 4.- We continue processing "current" unit, so we get the old
  // value of "u"
  std::swap<UnitWriter*>(u, tmp);
  
  if (_DEBUG_) cout << " after processing virtual unit (if any), we process " << u->getId() << " as a container\n";

  // 5.- Is u a container?
  if ( u->isContainer() )
  {
    // 5.1.- If so, we get the list of contained units, and write
    //       the list of parents and the number of contained
    vector<unsigned> _v = current->_getContained();
    u->setNumContained (_v.size());
    u->setListOfParents ( _v );
    
    if (_DEBUG_){ cout << " unit " << u->getId() << " is container. Fathers: "; for (vector<unsigned>::const_iterator it=_v.begin(), end=_v.end(); it!=end; ++it) cout << *it << " "; cout << endl;}

  } else if ( !u->isFinal() ) {
    // Unit is not final, nor container => we set it to be virtual 
    u->setMode( Globals::virtual_unit );
    if (_DEBUG_) cout << " Dummy unit (neither final nor container (" << u->getId() << ")\n";
  }
  
  // 6.- Rearrangement of the "current" NodeTree*: 
  // we make "current" to point its container unit (if current unit
  // if it is the root element, we arrange the tree and write it to disk)
  NodeTree* myContainer = current->getContainer(); 
  if (myContainer)
    current = myContainer;
  else arrangeTree();
}

// ==================================================================

Unit* IndexBuilder::arrangeVirtualNode(void)
{
  // 1.- We create the new unit, we take the (int) older one
  UnitWriter* old = (UnitWriter*) current->getUnit();
  UnitWriter* u = new UnitWriter(currentUnit, old->getTagId(), old->getId(), currentFile);
  if (_DEBUG_) cout << " new virtual node " << currentUnit << " tag: " << old->getTagId() << " container: " << old->getId() << " file: " << currentFile << "\n";  
  
  // 1.1.- statistics
  ++currentUnit;
  ++NUMUNITS;
  ++NUMFINALUNITS;
  
  // 1.2.- new node
  NodeTree* nt = new NodeTree(u->getId(), current->getTagType());
  nt->setUnit(u);
  nt->setContainer(current);
  
  // 1.3.- The new node is a parent of the old one
  current->addContained(nt);
  
  // 2.- arrangement of modes (pcdata is arranged afterwards)
  old->clearMode();
  old->setMode(Globals::container);
  u->setMode(Globals::virtual_unit);
  u->setMode(Globals::pcdata);
  u->setListOfDescendants ( nt->getPathToRoot() );
  u->setPosition (current->getContained().size());  
  
  return u;
}

// ==================================================================

void IndexBuilder::arrangeTree(void) 
{
  UnitWriter* u = (UnitWriter*) current->getUnit();
  NodeTree* nt = current;

  vector<unsigned> _base;
  _base.push_back(nt->getTagType());
  _base.push_back(0);

  u->setRoute ( _base );
  if (_DEBUG_) cout << "Storing: unit " << u->getId() << "\n";
  u->store();

  queue<NodeTree *> contained;
  vector<NodeTree *> parents = nt->getContained();
  if (_DEBUG_) cout << "Fathers of the unit: ";
  for (vector<NodeTree*>::const_iterator it = parents.begin(), end=parents.end(); it!=end; ++it)
  {
    contained.push(*it);
    if (_DEBUG_) cout << *it << " ";
  }
  
  cout << "\n";
  
  queue< vector<unsigned> > xpaths;
  xpaths.push(_base);

  while ( !contained.empty() )
  {
    nt = contained.front();
    contained.pop();
    if (_DEBUG_) cout << "Processing unit " << nt->getUnit()->getId() << " and its brothers: ";
    // We process nt and all its brothers
    
    // Processing _some_ nodes at level "i"
    
    // 1.- we take the container of them (unit at level "i-1")
    NodeTree* container = nt->getContainer();
    
    // 2.- we set the base XPath
    vector<unsigned> base = xpaths.front();
    xpaths.pop();
  
    // 3.- a place to store the brothers of the unit
    vector <NodeTree *> brothers, virtualUnits;
    brothers.push_back(nt); // we put the unit itself
      
    // we retrieve all the brothers of the unit (if any)
    while (!contained.empty() && contained.front()->getContainer() == container)
    {
      NodeTree* nt = contained.front();
      if (nt->getUnit()->isRetrievable())
        brothers.push_back(nt);
      else // virtual Unit
        virtualUnits.push_back(nt);
      contained.pop();
    }
    
    // 4.- map unit identifier => position in the list of units
    // with the same type
    map <unsigned, unsigned> position;

    // 5.- map for counting the number of units
    //     of each type
    map <unsigned, unsigned> amount;
        
    // 6.- we fill the counters
    for (vector<NodeTree *>::const_iterator it=brothers.begin(), end=brothers.end(); it!=end; ++it)
    {
      unsigned tagId = (*it)->getTagType();
      unsigned pos = ++amount[ tagId ];
      position.insert( pair<unsigned, unsigned>( (*it)->getId(), pos) );
    }
    
    // 7.- we process the units
    
    // 7.1.- Unretrievable (virtual) units
    for (vector<NodeTree*>::const_iterator it=virtualUnits.begin(), end=virtualUnits.end(); it!=end; ++it)
    {
      u = static_cast<UnitWriter*>((*it)->getUnit());
      u->store();
    }
    
    // 7.2.- Retrievable units
    for (vector<NodeTree *>::const_iterator it=brothers.begin(), end=brothers.end(); it!=end; ++it)
    {
      u = (UnitWriter*)(*it)->getUnit();
      
      unsigned tagId = u->getTagId();
      vector<unsigned> xpath = base;
      xpath.push_back( (*it)->getTagType() );

      if ( amount[tagId] > 1 )
        xpath.push_back( position[(*it)->getId()] );
      else 
        xpath.push_back(0);
        
      u->setRoute( xpath );
      if (_DEBUG_) cout << "Storing: unit " << u->getId() << "\n";
      u->store();

      // 8.- Re-insertion of contained units (if any) or, otherwise
      //    deletion of the unit
      parents = (*it)->getContained();

      if (parents.size())
      {
        for (vector<NodeTree*>::const_iterator vit=parents.begin(), end=parents.end(); vit!=end; ++vit)
          contained.push(*vit);
        xpaths.push(xpath);
      } else delete *it;
    }//for (list ...
    
    // 9.- Once of the unit with the container "container" have been
    //      processed, we delete it
    delete container;
  }
}

// ==================================================================

void IndexBuilder::writeIndexes()
{
  dtdlist.write(dtdlistFileName);
  this->write(); // writes the index itself
  qp->writeOccurrences(*occFile);
  occFile->write();
  // We dump the cache file of occurrences (the most 
  // frequent terms).
  L->dumpCacheFile ( this->cacheFileName, std::min(Globals::cacheSize, L->getNum()));

  L->write (lexiconFileName);
}

// ==================================================================

IndexBuilder::~IndexBuilder ()
{
  UnitWriter::close(); // closes files related to Units
  
  delete qp;
  delete occFile;
  delete L;
}

// ==================================================================


