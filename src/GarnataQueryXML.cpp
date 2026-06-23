#include <sstream>
#include "GarnataQueryXML.h"
#include "BNR-SD.h"
#include "SID.h"
#include "CID.h"
#include "Globals.h"
#include "Query.h"
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cmath>

// ==================================================================

GarnataQueryXML::GarnataQueryXML(const string& collectionName, const string& indexName, 
  model identifier, bool doStemming, const string& description, const string& task,
   const string& run_id, unsigned _id, ostream& _os) :
  Garnata (), os(_os), totalTime(0), numQueries(0), sumSquares(0)
{

  // 1.- We search for the collection name and index name
  if(!setCurrent(collectionName)) // collection does not exist
    Globals::errorAndExit("ERROR: collection name unknown. Exiting.");

  vector<string> names = current->getIndexes();
  
  // We search the identifier among the others
  if (std::find(names.begin(), names.end(), indexName) == names.end())
    Globals::errorAndExit("ERROR: index name unknown. Exiting.");

  // 2.- Creation of the retrieval model
  switch (identifier) 
  {
    case __BNR_SD:
      rm = new BNR_SD(*current, indexName);
      break;
      
    case __SID:
      rm = new SID(*current, indexName, RUM_u, true);
      // utilities
      SID::specifyUtilities(1.0f, 0.0f, 0.0f, 0.0f);
      break;

    case __CID:
      rm = new CID(*current, indexName, RUM_u, true);
      // utilities
      // "traditional"
      //CID::specifyUtilities(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
      // "experiment 1"
      //CID::specifyUtilities(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
      // "experiment 2"
      //CID::specifyUtilities(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
      // "experiment 3"
      CID::specifyUtilities(1.0f, 1.0f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
      break;

    default:
      Globals::errorAndExit("ERROR: Unknown retrieval model (GarnataQuery::GarnataQuery). Exiting.");
  }

  RetrievalModel::setStem(doStemming);
  RetrievalModel::setNumDocs(1500); 

  os << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n";
  os << "<inex-submission participant-id=\"" << _id << "\" run-id=\"" <<
        run_id << "\" task=\"" << task << "\" query=\"automatic\">\n" << 
        "<topic-fields title=\"yes\" castitle=\"yes\" description=\"no\"" <<
          " narrative=\"no\" ontopic_keywords=\"no\"/>\n" <<   
	"\t<description>" << description << "</description>\n\n" <<
	  "<collections>\n\t<collection>wikipedia</collection>\n</collections>\n\n";
}

// ==================================================================

void GarnataQueryXML::makeQuery(const string& s, unsigned id)
{
  time_t t_inic, t_end;
  time(&t_inic);
  Query q(s);
  ProcessedQuery pq = rm->processQuery(q);
  
  vector<Result> v = rm->makeQuery (pq);
  
  os << "\t<topic topic-id=\"" << id << "\">\n";
  
  for (vector<Result>::const_iterator it=v.begin(), end=v.end(); it!=end; ++it)
    os << *it;
  
  os << "\t</topic>\n";
  time(&t_end);
  totalTime += (t_end - t_inic);
  sumSquares += (t_end - t_inic)*(t_end - t_inic);
  ++numQueries;
}

// =================================================================

void GarnataQueryXML::printStats() const
{
  double avg = (double)totalTime/(double)numQueries;
  double avg_squares = (double)sumSquares/(double)numQueries;
  cout << "----------------------------------------\n";
  cout << "Number of queries: " << numQueries << "\n";
  cout << "Average query time: " << avg << "s \n";
  cout << "Standard deviation: " << sqrt(avg_squares - avg*avg) << endl;
}


// ==================================================================

GarnataQueryXML::~GarnataQueryXML() 
{	
  delete rm; 
  os << "</inex-submission>\n\n";
}

// ==================================================================

