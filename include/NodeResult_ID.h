#ifndef __NODERESULT_ID_H__
#define __NODERESULT_ID_H__

#include "Unit.h"
#include "NodeResult.h"
#include <utility>

typedef enum{RUM_u, RUM_d, RUM_q} RUM_mode;

class NodeResult_ID : public NodeResult {
  protected:
    /** Retrieval status value */
    float RSV;
    
    /** Expected utility of retrieving
    this unit */
    float EU_plus;
    
    /** Expected utility of not retrieving
    this unit */
    float EU_minus;
    
    /** Normalization coefficient */
    float nIdf;
    
  public:
    /** Main constructor 
    @param u unit
    @param w weight of the unit
    */
    NodeResult_ID(Unit* _u, float w);
    
    /** Copy constructor 
    @param n node to copy
    */
    NodeResult_ID(const NodeResult_ID& n);
  
    /** Indicates if the unit should be retrieved
    or not
    @return true if unit should be retrieved
    */
    bool shouldBeRetrieved() const;
    
    /** Return RSV of the unit
    @return retrieval status value of the unit 
    */
    float getRSV() const; 
    
    /** Compute the RSV of the unit, from a certain RUM mode
    @param r rum mode to compute RSVs
    */
    void computeRSV(RUM_mode r);
    
    /** Multiplies current RSV by a certain value
    @param f value to multiply RSV
    */
    void operator*=(float f);
    
    /** Adds a certain quantity to
    the nIdf of the node
    @param f nIdf of the node 
    */
    void addNIdf(float f);
    
    /** Compute the two utilities of the node */
    virtual void computeUtilities() = 0;
    
    /** Assignment operator
    */
    const NodeResult_ID& operator=(NodeResult_ID& o);

    /** True if we are dividing by nIdf */
    static bool normalize;

    /** Destructor */
    virtual ~NodeResult_ID();
};


#endif

// ==================================================================

