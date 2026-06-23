#include "TriadPool.h"
#include <iostream>
#include <algorithm>
#include <cstdio>

// ==================================================================

TriadPool::TriadPool(const unsigned KBytes) : 
  MAX_SIZE( KBytes*1024/( Triad::size() ) ), writtenTriads(0), 
  current(0)
{
  // 1.- Memory allocation for array of Triads
  tmp = deque<Triad> ( MAX_SIZE );
  tbuffer = deque<Triad> ( 0 );

  // 2.- Creation and opening of the temporal file
  char buffer[L_tmpnam];
  tmpnam(buffer);
  fileName = string(buffer);
  tempFile.open(fileName.c_str(), ios::binary );
  if (!tempFile) Globals::errorAndExit("Bad 'tempFile' (TriadPool::TriadPool). Exiting");
}

// ==================================================================

void TriadPool::flush()
{
  std::sort(tmp.begin(), tmp.begin()+current, Inverted ());
  
  if (tempFile.fail()) Globals::errorAndExit("Bad 'tempFile' (TriadPool::flush). Exiting");
  
  if (marks.size() > 0) // if there are more than one lots
    for(deque<Triad>::const_iterator it=tmp.begin(), end=tmp.begin()+current; it!=end; ++it)
      it->write(tempFile);

  marks.push_back(writtenTriads);
  writtenTriads += current;
  marks.push_back(writtenTriads);
  tempFile.close();
}

// ==================================================================

void TriadPool::add(const Triad& q)
{
  tmp[current] = q;
  ++current;
  
  if (current >= MAX_SIZE)
  {
    std::sort( tmp.begin(), tmp.end(), Inverted () );
   
    for(deque<Triad>::const_iterator it=tmp.begin(), end=tmp.end(); it!=end; ++it)
      it->Triad::write(tempFile);
    
    current = 0;
    marks.push_back (writtenTriads);
    writtenTriads += MAX_SIZE;
  }
}

// ==================================================================

void TriadPool::sortInverted(ofstream& output)
{
  flush();
  unsigned lots = marks.size() - 1;
  
  if (lots > 1) // if not, they are sorted
  {
    ifstream fp(fileName.c_str(), ios::binary);
    if (fp.fail()) Globals::errorAndExit("Bad 'fp' (TriadPool::sortInverted), exiting");
    priority_queue <TL> triadList;
    vector <unsigned> remaining (lots);
    vector <unsigned> _read     (lots, 1);
    
    for (unsigned i=0; i<lots; i++)
    {
      Triad triad;
      fp.seekg ( marks[i]*Triad::size(), std::ios_base::beg );
      triad.read ( fp );
      triadList.push( TL(triad, i) );
      remaining[i] = (marks[i+1] - marks[i]) - 1;
    }
    
    // clearing of the vector
    tmp.clear();
    
    // Sorting of the file:
    // Triad from lot i is read from 
    // marks[i] + _read[i] ... while
    // remaining[i] > 0
    
    while (!triadList.empty())
    {
      // We get the min element of the list...
      TL q = triadList.top();      
      triadList.pop(); // ...and we remove it from the list
      
      // add q to the list of elements
      tmp.push_back( q.t );
      
      if (tmp.size() == MAX_SIZE)
        dumpWeightList(output, false);	
      
      // if there are remaining Triads in this lot, we read a new one
      if (remaining[q.lot] > 0)
      {
        fp.seekg ( Triad::size()*(marks[q.lot] + _read[q.lot]), std::ios_base::beg );
        Triad triad;
	triad.read ( fp );
        triadList.push( TL(triad, q.lot) );
	++_read[q.lot];
	--remaining[q.lot];
      }
      
    }
    
    if (tmp.size())
      dumpWeightList(output, true);
    
    
  } else {
    // we pass the entire vector to the 
    // occurrence builder (no need to read the file)
    vector<Triad> tmp2 (current);
    
    // Triads are sorted ( using () )
    std::copy(tmp.begin(), tmp.begin()+current, tmp2.begin());
    dumpWeightList(output, true);
    tmp.clear();
    
    // We write the weights
  }
  
  // We delete TriadPool file
  remove(fileName.c_str());
}

// ==================================================================

void TriadPool::dumpWeightList(ofstream& fp, bool last)
{

  // 1.- We store in "number" how many changes of id
  //   are there in the vector tmp
  unsigned number = 0;
  unsigned curr_id;
  
  // 2.- Tbuffer shoul store only some triads
  //   with the same id
  if (tbuffer.size())
  {
    ++number;
    curr_id = tbuffer.back().getId();
  } else 
    curr_id = tmp[0].getId();  
  
  unsigned _size = tmp.size();
  unsigned __size = tbuffer.size();
  
  vector<unsigned> frontier;
  // 3.- For every element of tmp...
  for (unsigned i=0; i<_size; i++)
  {
    tbuffer.push_back( tmp.front() );
    unsigned _id = tmp.front().getId();
    if (_id != curr_id)
    {
	curr_id = _id;
	frontier.push_back(__size + i);
	++number;
    }
    tmp.pop_front();
  }
  
  frontier.push_back(tbuffer.size());
  
  // if last = false, we only process
  // (number - 1) terms, else, we process number  
  if (!last) --number;
  
  unsigned triadsToDelete = 0;

  for (unsigned k=0, j=0; k<number; ++k)
  {
    // we process from j to frontier[k]
    unsigned num = frontier[k] - j;    
    
    for (unsigned i=0; i<num; ++i)
    {
      float _w = tbuffer[j+i].getWeight();
      fp.write((char *) &_w, sizeof(float));
    }
    
    triadsToDelete += num;
    j = frontier[ k ];
  }
  
  // We extract the triads from tbuffer...
  for (unsigned i=0; i<triadsToDelete; ++i)
    tbuffer.pop_front();
}

// ==================================================================

void TriadPool::writeWeightFile(ofstream& fp)
{
  this->sortInverted(fp);
}

// ==================================================================

TriadPool::~TriadPool() { }

// ==================================================================


