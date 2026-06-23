#include "QuadPool.h"
#include <iostream>
#include <algorithm>

// ==================================================================

QuadPool::QuadPool(const unsigned KBytes, const string& _fileName) : 
  MAX_SIZE( KBytes*1024/( Quad::size() ) ), writtenQuads(0), 
  current(0), fileName(_fileName)
{
  tmp = vector<Quad> ( MAX_SIZE ); 
  tempFile.open(fileName.c_str(), ios::binary );
  if (!tempFile) Globals::errorAndExit("Bad 'tempFile' (QuadPool::QuadPool), exiting");
}

// ==================================================================

void QuadPool::flush()
{
  std::sort(tmp.begin(), tmp.begin()+current, Inverted ());
  
  if (tempFile.fail()) Globals::errorAndExit("Bad 'tempFile' (QuadPool::flush), exiting");
  
  if (marks.size() > 0) // if there are more than one lots, we write the file
    for(vector<Quad>::const_iterator it=tmp.begin(), end=tmp.begin()+current; it<end; ++it)
      it->Quad::write(tempFile);

  marks.push_back(writtenQuads);
  writtenQuads += current;
  marks.push_back(writtenQuads);
  tempFile.close();
}

// ==================================================================

void QuadPool::add(const Quad& q)
{
  tmp[current] = q;
  ++current;
  
  if (current >= MAX_SIZE)
  {
    std::sort( tmp.begin(), tmp.end(), Inverted () );
   
    for(vector<Quad>::const_iterator it=tmp.begin(), end=tmp.end(); it<end; ++it)
      it->Quad::write(tempFile);
    
    current = 0;
    marks.push_back (writtenQuads);
    writtenQuads += MAX_SIZE;
  }
}

// ==================================================================

void QuadPool::writeOccurrences(OccurrenceFile& occFile)
{
  flush();
  unsigned lots = marks.size() - 1;
  
  if (lots > 1) // if not, they are sorted
  {
    vector <unsigned> remaining (lots);
    vector <unsigned> _read     (lots);
    ifstream fp(fileName.c_str(), ios::binary);
    if (fp.fail()) Globals::errorAndExit("Bad 'fp' (QuadPool::sortInverted), exiting");
    
    priority_queue <QL> quadList;
    
    for (unsigned i=0; i<lots; ++i)
    {
      Quad quad;
      fp.seekg ( marks[i]*Quad::size(), std::ios_base::beg );
      quad.read ( fp );
      quadList.push( QL (quad, i) );      
      remaining[i] = (marks[i+1] - marks[i]) - 1;
      _read[i] = 1;
    }
    
    // clearing of the vector
    tmp.clear();
   
    // Sorting of the file:
    // Quad from lot i is read from 
    // marks[i] + _read[i] ... while
    // remaining[i] > 0
    
    unsigned tamanio = 0;
    
    while (!quadList.empty())
    {
      // We get the min element of the list...
      QL q = quadList.top();      
      quadList.pop(); // ...and we remove it from the list
      
      // add q to the list of elements
      tmp.push_back( q.q );
      
      if (tmp.size() == MAX_SIZE)
      {
        occFile.addAll(tmp);
	tamanio += tmp.size();
	tmp.clear();
      }
     
      // if there are remaining Quads in this lot, we read a new one
      if (remaining[q.lot] > 0)
      {
        fp.seekg ( Quad::size()*(marks[q.lot] + _read[q.lot]), std::ios_base::beg );
        Quad quad;
	quad.read ( fp );
        quadList.push( QL (quad, q.lot) );
	++_read[q.lot];
	--remaining[q.lot];
      }
    }
    
    if (tmp.size())
    {
      occFile.addAll(tmp);
      tamanio += tmp.size();
      tmp.clear();
    }
    
  } else { // there is only one lot

    // we pass the entire vector to the
    // occurrence builder (no need to read the file)

    vector<Quad> tmp2 (current);
    
    // Quads are sorted ( using flush() )
    std::copy(tmp.begin(), tmp.begin()+current, tmp2.begin());
    tmp.clear();
    occFile.addAll(tmp2);
  }
  tempFile.open(fileName.c_str(), ios::trunc);  
}

// ==================================================================

QuadPool::~QuadPool()
{ 
}

// ==================================================================


