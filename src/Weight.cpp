#include "Weight.h"
#include "UnitReader.h"
#include <utility>
#include <algorithm>

unsigned floats = 0;
unsigned terms = 0;

// ==================================================================

Weight :: Weight ( const Collection& _c, string _identifier, bool _normalize ) :
IndexReader(_c, _identifier), NUM( L->getNum() ), normalize(_normalize) 
{
  _idf = new float[NUM];
  if (!_idf) Globals::errorAndExit ("Not enough memory for '_idf' (Weight::Weight), exiting");
  tp = new TriadPool(Globals::quadPoolKBytes );
  if (!tp) Globals::errorAndExit ("Not enough memory for 'tp' (Weight::Weight), exiting");
}

// ==================================================================

float Weight::idf (unsigned i) const 
{ 
  if (i > NUM)
    Globals::errorAndExit("Index too high (Weight::getIdf). Exiting");

  return _idf[i-1];
}

// ==================================================================

unsigned Weight::tf (unsigned i, unsigned j) 
{
  if (currentUnitIdentifier == j)
    return f_i[i];
  else 
  {
    cout << "Error: unit " << j << " is not loaded. Exiting\n";
    exit(-1);
  }
}

// ==================================================================

float Weight::tf_norm (unsigned i, unsigned j) 
{
  return static_cast<float>(tf(i,j))*maxInv;
}

// ==================================================================

void Weight::setWeightOnUnit(unsigned _id, float _w)
{
  weightUnit[_id] = _w;
}

// ==================================================================

void Weight::setWeightTermOnUnit(unsigned _idTerm, unsigned _idUnit, float _w)
{
  Triad t(_idTerm, _idUnit, _w);
  tp->add(t);
  ++floats;
  ++terms;
}

// ==================================================================

void Weight::createWeightFile (const string& fileName)
{
   // Precomputation of the idf
  for (unsigned i=1; i<=NUM; ++i)
    _idf[i-1] = computeIdf (NUMFINALUNITS, L->getTermFromId(i)->getNumDocs());

  ofstream _output(fileName.c_str(), ios::binary);
  if (_output.fail()) Globals::errorAndExit("Invalid file name. Exiting.");

  unsigned total = roots.size();
  unsigned computed = 0;
  
  unsigned deberia, tiene;

  for (vector<unsigned>::const_iterator it=roots.begin(), end=roots.end(); it!=end; ++it)
  {
    tiene = floats - terms;
  
    // For every root unit we compute the weight on it
    // and on the ascendants
    computeWeight(*it);
    setWeightOnUnit(*it, 0.0f); // A root unit has no descendants,
                                  // so its weight is 0.0
    // After processing a file, we write the whole block of weights...
    for (map<unsigned,float>::const_iterator mit=weightUnit.begin(), mend=weightUnit.end(); mit!=mend; ++mit)
    {
       float f = mit->second;
       _output.write((char *) &f, sizeof(float) );
       ++floats;
    }				  
    weightUnit.clear();
    
    if (_output.fail()) Globals::errorAndExit("Bad weightFile (I). Exiting.");

    //  we show an output
    ++computed;
    cout << "Processed " << computed << " files of " << total << "\n";
    
    /** BEGIN DEBUG OUTPUT */
    tiene = floats - terms - tiene;
    unsigned deberia;
    if (it+1!=end) deberia=*(it+1)-*it;
    else deberia = NUMUNITS- *it;
    if(tiene!=deberia) cout << "!!!!!!!!!!!problema en el archivo " << computed << " tiene=> " << tiene << " , deberia=> " << deberia<<endl;
    /** END DEBUG OUTPUT */
  }
  
  /** Begin debug output */
  cout << "estimated size: " << floats*4 << " bytes\n";
  cout << "units:  " << NUMUNITS << " " << (floats-terms) << endl;
  /** End debug output */
  
  tp->writeWeightFile( _output );
  if (_output.fail()) Globals::errorAndExit("Bad weightFile (II). Exiting.");
}

// ==================================================================

float Weight::computeWeight (unsigned id)
{
  UnitReader u(id);
  map <unsigned, float> mp;
  float res = 0.0f;
  
  if (u.isContainer())
  {
    vector<unsigned> v;
    u.getListOfParents(v);
    float acc = 0.0f;
    for (vector<unsigned>::const_iterator it=v.begin(), end=v.end(); it!=end; ++it)
    {
      float tmp = computeWeight(*it);
      acc += tmp;
      mp[*it] = tmp;
    }
    
    if (normalize)
    {
      float inv;
      
      if (acc > 0.0f)
        inv = 1.0f/acc;
      else
        inv = 0.0f;
      
      for (vector<unsigned>::const_iterator it=v.begin(), end=v.end(); it!=end; ++it)
        setWeightOnUnit (*it, mp[*it] * inv);

    } else {
      for (vector<unsigned>::const_iterator it=v.begin(), end=v.end(); it!=end; ++it)
        setWeightOnUnit (*it, mp[*it] );
    }
    
    res = acc;
    
  } 
  
  if (u.isFinal()) {
    // 1.- we set the current unit identifier
    currentUnitIdentifier = id;
    
    // 2.- unit is final, we read the list of terms and frequencies
    vector<unsigned> terms_id, freq;
    u.getListOfTerms(terms_id, freq);
    
    // 3.- we set f_i (for each term in the list, we set its frequency)
    maxFreq = 0;
    for (unsigned i=0, n=terms_id.size(); i<n; ++i)
    {
       f_i[terms_id[i]] = freq[i];
       maxFreq = std::max(maxFreq, freq[i]);
    }
    
    // 4.- we arrange the maximum values (for tf_norm)
    maxFreq = std::max(static_cast<unsigned>(1), maxFreq);
    maxInv = 1.0f/((float) maxFreq);
    
    // 5.- for each term, we compute its importance (rho(term, unit))
    float acc = 0.0f;
    
    for (vector<unsigned>::const_iterator it=terms_id.begin(), end=terms_id.end(); it!=end; ++it)
    {
      float tmp = rhoTU (*it, id);      
      acc += tmp;
      mp[*it] = tmp;
    }
    
    if (normalize)
    {
      float inv = 1.0f/acc;
      
      for (vector<unsigned>::const_iterator it=terms_id.begin(), end=terms_id.end(); it!=end; ++it)
        setWeightTermOnUnit (*it, id, mp[*it] * inv);
            
    } else {
      for (vector<unsigned>::const_iterator it=terms_id.begin(), end=terms_id.end(); it!=end; ++it)
        setWeightTermOnUnit (*it, id, mp[*it] );	    
    }
    f_i.clear();
    f_i.swap(f_i);
    currentUnitIdentifier = 0;
    
    res = acc;
  }
  
  return res;
}

// ==================================================================

Weight::~Weight () 
{
  delete [] _idf;
  delete tp;
}

// ==================================================================

