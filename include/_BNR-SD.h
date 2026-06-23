#ifndef ___BNR_SD_H__
#define ___BNR_SD_H__

#include "RetrievalModel.h"
#include "Result.h"
#include "Lexicon.h"
#include "NodeResult.h"
#include "NodeGroup.h"
#include "ProcessedQuery.h"
#include "DTD.h"
#include <vector>
#include <utility>

using namespace std;

template <typename T>
class _BNR_SD : public RetrievalModel {
  protected :
    /** While building the intersection list of documents, it
    aggregates two weights of a term in two units 
    @param w1 first weight 
    @param w2 second weight
    */
    float aggregate(float w1, float w2) const;
    
    //! Internal class for sorting the resulting vector
    template <typename TT>
    class NodeResultPtr {
      public:
        bool operator () (const TT* n1, const TT* n2) const
        {
          return (n1->getProb() > n2->getProb());
        }
    };
    
    /** Minimum weight to consider a result */
    float minWeight;
    
    /** Statistical timers */
    time_t init, t_end;
    
    /** Statistical clocks */
    clock_t INICIO, FIN, _INICIO, _FIN, ACUM;

    /** Vector with root nodes */
    vector <T*> rootNodes;
    
  public:
    /**
    Main constructor
    @param _c collection associated to the index
    @param identifier name of the index
    */
    _BNR_SD ( const Collection& _c, const string& _identifier );
    
    /** Makes a query to the system
    @param pq 
    @return vector of pairs (document, weitght) 
            sorted by descending weight
    */
    virtual vector< Result > makeQuery(const ProcessedQuery& pq) = 0;
    
    /** Propagates probabilities to the final units, following the scheme of the BNR-SD model
    @param pq processed query
    @param N_final map that associates a node (containing RSV) to each final unit identifier    
    @param groups list of nodeGroups (nodes representing each part of the query) 
    */
    void propagateFinalUnits(const ProcessedQuery& pq, map<unsigned, T*>& N_final, vector<NodeGroup<T> >& groups);
    
    /** Propagates probabilities to the complex units, begining
    from final units, following the scheme of the BNR-SD model
    @param pq processed query
    @param N_final map that associates a node (containing RSV) to each final unit identifier
    @param N_complex map that associates a node (containing RSV) to each final unit identifier    
    */
    void propagateComplexUnits(const map<unsigned, T*>& N_final, map<unsigned, T*>& N_complex);

    /** we readjusts probability values, and
     construct a list of nodes instead two maps, using only retrievable units
     @param vec list of nodes to build 
     @param N_final map that associates a node (containing RSV) to each final unit identifier
     @param N_complex map that associates a node (containing RSV) to each final unit identifier    
     @post N_final and N_complex will be cleared in this function
    **/
    void makeListOfNodes (vector<T*>& vec, map<unsigned, T*> N_final, map<unsigned, T*> N_complex);

    void buildResult(vector<Result>& res, vector<T*>& vec, DTD* current);
    
    void cutDownNodeResultVector (vector<T*>& vec);

    /** Destructor */
    virtual ~_BNR_SD ();
};

#endif


