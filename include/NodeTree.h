#ifndef __NODETREE_H__
#define __NODETREE_H__

using namespace std;

#include <vector>
#include "Unit.h"


class NodeTree {
  private:
    /** Represented unit's id */
    unsigned id;
    
    /** tag of the unit */
    unsigned tagType;
    
    /** Depth of the node */
    unsigned _depth;
    
    /** Container of the unit (0 if root) */
    NodeTree* container;

    /** Pointer to the correnpondent root node */
    NodeTree* root;

    /** Pointer to represented unit */
    Unit* u;  
    
    /** Units contained by this one */
    vector<NodeTree *> contained;
    
  public:
    /** Main constructor 
    @param _id id of the represented unit 
    @param tagType type of the represented unit
    */
    NodeTree (unsigned _id, unsigned _tagType);
    
    /** Copy constructor 
    @param n entity to copy */
    NodeTree (const NodeTree& n);

    /** Assignment operator 
    @param _c entity to assign
    */
    const NodeTree& operator=(const NodeTree& _c);

    /** Sets the receiver unit as the root 
    element */
    void setRoot ();
    
    /** Returns a pointer to the represented unit
    @return pointer to u
    */
    Unit* getUnit() const;
    
    /** Sets the units object
    @param _u unit to associate to this node
    */
    void setUnit (Unit* _u);
    
    /** Gets the id of the unit */
    unsigned getId () const;
    
    /** Returns the container of the unit 
    @return container of the unit */
    NodeTree* getContainer () const;

    /** Returns the root of the unit 
    @return root of the unit */
    NodeTree* getRoot () const;

    /** Returns the only virtual unit contained (if any) 
    @return virtual unit contained */
    NodeTree* getVirtualUnitContained() const;

    /** Returns the identifier of the tag of the unit 
    @return tag of the unit */
    unsigned getTagType () const;
    
    /** Sets the container of the unit
    @param _container container of the unit */
    void setContainer (NodeTree* _container);

    /** Sets the root of the unit
    @param _root root of the unit */
    void setRoot (NodeTree* _root);

    /** Sets the only virtual unit contained of the node
    @param vuc virtual unit contained of the node */
    void setVirtualUnitContained(NodeTree* vuc); 
    
    /** Returns the identifiers of the 
    units in the path to the root 
    element, including this unit
    @return array of unsigned */
    vector<unsigned> getPathToRoot () const;
    
    /** Returns the identifiers of the
    contained units (if any) 
    @return array of unsigned */
    vector<unsigned> _getContained () const;

    /** Returns pointers to the
    contained units (if any) 
    @return array of pointers */
    vector<NodeTree *> getContained () const;
    
    /** Returns the depth of one node
    @return one node's depth
    */
    unsigned depth() const;

    /** Adds one unit to the units contained 
    by the receiver 
    @pre _container SHOULD RESIDE in the heap!
    @param n unit to be added */
    void addContained (NodeTree* _container);
    
    /** Destructor */
    ~NodeTree ();
};

#endif

