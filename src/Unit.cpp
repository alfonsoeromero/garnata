#include "Unit.h"
#include "Globals.h"

// ==================================================================

Unit::Unit ( unsigned _id,  unsigned _tagId, unsigned _container, unsigned _file) :
   id(_id), tagId(_tagId), position(0), numContained(0), 
   container(_container), file(_file), weight(0.0f), mode(0)
{ }

// ==================================================================

Unit::Unit (const Unit& u) : id(u.id), tagId(u.tagId), position(u.position),
    numContained(u.numContained), container(u.container), 
    file(u.file), weight(u.weight), mode(u.mode) { }

// ==================================================================

Unit::Unit() : id(0), mode(0) { }

// ==================================================================

float Unit::getWeight() const { return weight; }

// ==================================================================

unsigned Unit::getPosition() const { return position; }

// ==================================================================

unsigned Unit::getContainer() const { return container; }

// ==================================================================

unsigned Unit::getNumContained() const { return numContained; }

// ==================================================================

unsigned Unit::getTagId() const { return tagId; }

// ==================================================================

unsigned Unit::getId() const { return id; }

// ==================================================================

bool Unit::isContainer() const { return (bool) ((mode & Globals::container) != 0); }

// ==================================================================

bool Unit::isFinal() const { return (bool) ((mode & Globals::pcdata) != 0); }

// ==================================================================

bool Unit::isInCache() const { return (bool) ((mode & Globals::in_cache) != 0); }

// ==================================================================

bool Unit::isRetrievable() const { return (bool) ((mode & Globals::virtual_unit) == 0); }

// ==================================================================

unsigned Unit::getFile() const { return file; }

// ==================================================================

Unit::~Unit() { }

// ==================================================================

const unsigned Unit::SIZE_UNIT = 5*sizeof(unsigned) + sizeof(float) + sizeof(char);

// ==================================================================

