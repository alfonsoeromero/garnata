#ifndef __ID_H__
#define __ID_H__

#include "RetrievalModel.h"
#include "Result.h"
#include "NodeResult_ID.h"
#include "ProcessedQuery.h"
#include "BNR-SD.h"
#include <vector>
#include <utility>

using namespace std;

template <typename T>
class ID : public _BNR_SD<T> {
  protected :
    //! Internal class for sorting the resulting vector
    template <typename TT>
    class NodeResult_ID_Ptr
    {
      public:
        bool operator () (const TT* n1, const TT* n2) const
        {
          return (n1->getRSV() > n2->getRSV());
        }
    };
    
    /** Mode to compute RSV from utilities */
    RUM_mode mode;
    
  public:
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    @param _mode mode to compute RSV
    @param normalize true if we are dividing RSV of each unit by its nIdf
    */
    ID ( const Collection& _c, const string& _identifier, RUM_mode _mode, bool normalize );
    
    /** Compute the NIdfs of the list of nodes
    @param groups list of grous, whose descendants are the nodes
    @param L current index lexicon
    */
    void computeNIdf(vector<NodeGroup<T> >& groups, const Lexicon& L);

    /** Compute the NIdfs of the list of nodes, assigning the nIdf of the container article
    @param groups list of grous, whose descendants are the nodes
    @param L current index lexicon
    */
    void computeGlobalNIdf(vector<NodeGroup<T> >& groups, const Lexicon& L);

    /** Makes a query to the system
    @param pq 
    @return vector of pairs (document, weitght) 
            sorted by descending weight
    */
    vector< Result > makeQuery(const ProcessedQuery& pq);
  
    /** Destructor */
    virtual ~ID ();
};

#endif


