#include "GarnataWeight.h"
#include "WeightBNRSD.h"
#include "WeightBNRSD_norm.h"
#include "Globals.h"
#include "WeightInserter.h"

// ==================================================================

GarnataWeight::GarnataWeight() : Garnata () { }

// ==================================================================

int GarnataWeight::insertWeights(string collectionName, string indexName, string _weightFileName)
{
  if(!setCurrent(collectionName))
    return BAD_COLLECTION; // collection does not exist

  vector<string> names = current->getIndexes();
  
  if (std::find(names.begin(), names.end(), indexName) == names.end())
    return BAD_INDEX; // identifier not found
  
  string weightFileName = Globals::home_weight + collectionName + "_" + indexName + "_" + _weightFileName; 

  // If the file did not exist, we return an error
  if (!Globals::fileExists(weightFileName))
    return BAD_WEIGHT;

  WeightInserter w(*current, indexName);
  if (!w.insert(weightFileName))
    return BAD_WEIGHT;
  
  return ALL_OK;
}

// ==================================================================

int GarnataWeight::addWeights(string collectionName, string indexName, string _weightFileName, int type)
{
  if(!setCurrent(collectionName))
    return BAD_COLLECTION; // collection does not exist

  vector<string> names = current->getIndexes();
  
  if (std::find(names.begin(), names.end(), indexName) == names.end())
    return BAD_INDEX; // identifier not found

  string weightFileName = Globals::home_weight + collectionName + "_" + indexName + "_" + _weightFileName; 

  // If the file already existed, we return an error
  if (Globals::fileExists(weightFileName))
    return BAD_WEIGHT;
  
  /** We create the weight object **/
  Weight* w;
  // here could be a selection of the different kind of
  // weighting scheme... if they were implemented
  
  switch(type)
  {
    case NORM_MAX:
      w = new WeightBNRSD_norm(*current, indexName);
    break;
    
    case CLASSIC:
    default:
      w = new WeightBNRSD(*current, indexName);
  }
  
  w->createWeightFile(weightFileName);
  delete w;
  
  // We update the index file...
  Index in (*current);
  in.read (indexName);
  in.addWeight(_weightFileName);
  in.write();
  
  return ALL_OK;
}

// ==================================================================

GarnataWeight::~GarnataWeight() { }

// ==================================================================


