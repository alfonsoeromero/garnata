#include "InputCompressedBinaryFile.h"
#include "OutputCompressedBinaryFile.h"
#include "InputIndexFile.h"
#include "OutputIndexFile.h"
#include "VariableByteCoder.h"

#include <vector>

using namespace std;
template class InputIndexFile<long>;
template class OutputIndexFile<long>;

int main(void) 
{
  const unsigned TAM1 = 300000;
  
  vector<unsigned> array1(TAM1);
  vector<unsigned> array2(TAM1);
  vector<long> positions; 
  
  unsigned base = 0;
  
  // we fill both arrays
  for (unsigned i=0; i<TAM1; ++i)
  {
    unsigned random_u = rand() % 1000;
    array1[i] = random_u;
    array2[i] = random_u + base;
    base = array2[i];
  }
  
  // ----------------------------------

  vector<long> array1l(TAM1);
  vector<long> array2l(TAM1);
  
  long basel = 0;
  
  // we fill both arrays
  for (unsigned i=0; i<TAM1; ++i)
  {
    long random_u = ( rand() % 1000 );
    array1l[i] = random_u;
    array2l[i] = random_u + basel;
    basel = array2l[i];
  }
  
  // ----------------------------------
  
  vector<float> array1f(TAM1);
  
  // we fill both arrays
  for (unsigned i=0; i<TAM1; ++i)
  {
    float random_u = rand() / (float) RAND_MAX;
    array1f[i] = random_u;
  }
  
  // ----------------------------------


  cout << "1. Arrays loaded" << endl;
  
  VariableByteCoder vc;
  
  {
    OutputCompressedBinaryFile oc("salida");
    oc.setCompressionAlgorithm (&vc);
    cout << "\t output file created\n" << endl;
    
    positions.push_back (oc.getPosition());
    
    oc.writeUnsignedList(array1);
    
    positions.push_back (oc.getPosition());
    
    cout << "\t unsigned list written" << endl;
    oc.writeSortedUnsignedList(array2, true);
    cout << "\t unsigned sorted list written" << endl;
    
    positions.push_back(oc.getPosition());
    
    oc.writeLongList(array1l);

    cout << "\t long list written" << endl;
    
    positions.push_back(oc.getPosition());
    
    oc.writeSortedLongList(array2l, true);
    cout << "\t long sorted list written" << endl;
    
    positions.push_back(oc.getPosition());   
    
    oc.writeFloatList(array1f);
    
    cout << "\t float list written" << endl;
  }
  
  cout << "2. Arrays written to binary file" << endl;
  
  InputCompressedBinaryFile ic("salida");
  ic.setCompressionAlgorithm (&vc);
  vector<unsigned> v1, v2;
  vector<long> l1, l2;
  vector<float> f;
  
  ic.readUnsignedList(v1);
  cout << "\t unsigned list read" << endl;
    bool equal = true;
  
  for (unsigned i=0; i<TAM1 && equal; ++i)
  {
    equal = (array1[i] == v1[i]);
    if (!equal)
      cerr << "i = " << i << ", read array = " << v1[i] << ", original = " << array1[i] << endl;
  }
  
  if (equal)
    cout << "\t >>> The list of unsigned has been retrieved sucessfully!!" << endl;
  else 
  {
    cout << "ERROR: inconsistent data. Exiting" << endl;
    return -1;
  }

  ic.readSortedUnsignedList(v2, true);
  cout << "\t sorted unsigned list read" << endl;

  for (unsigned i=0; i<TAM1 && equal; ++i)
  {
    equal = (array2[i] == v2[i]);
    if (!equal)
      cerr << "i = " << i << ", read array = " << v2[i] << ", original = " << array2[i] << endl;
  }
  
  if (equal)
    cout << "\t >>> The sorted list of unsigned has been retrieved sucessfully!!" << endl;
  else 
  {
    cout << "ERROR: inconsistent data. Exiting" << endl;
    return -1;
  }
  
  ic.readLongList(l1);
  cout << "\t long list read" << endl;

   for (unsigned i=0; i<TAM1 && equal; ++i)
  {
    equal = (array1l[i] == l1[i]);
    if (!equal)
      cerr << "i = " << i << ", read array = " << l1[i] << ", original = " << array1l[i] << endl;
  }
  
  if (equal)
    cout << "\t >>> The list of long has been retrieved sucessfully!!" << endl;
  else 
  {
    cout << "ERROR: inconsistent data. Exiting" << endl;
    return -1;
  }
   
  ic.readSortedLongList(l2, true);
  cout << "\t sorted long list read" << endl;
    for (unsigned i=0; i<TAM1 && equal; ++i)
  {
    equal = (array2l[i] == l2[i]);
    if (!equal)
      cerr << "i = " << i << ", read array = " << l2[i] << ", original = " << array2l[i] << endl;
  }
  
  if (equal)
    cout << "\t >>> The sorted list of long has been retrieved sucessfully!!" << endl;
  else 
  {
    cout << "ERROR: inconsistent data. Exiting" << endl;
    return -1;
  }


  ic.readFloatList(f);
  cout << "\t float list read" << endl;
 
  for (unsigned i=0; i<TAM1 && equal; ++i)
  {
    equal = (array1f[i] == f[i]);
    if (!equal)
      cerr << "i = " << i << ", read array = " << f[i] << ", original = " << array1f[i] << endl;
  }
  
  if (equal)
    cout << "\t >>> The list of float has been retrieved sucessfully!!" << endl;
  else 
  {
    cout << "ERROR: inconsistent data. Exiting" << endl;
    return -1;
  }
  cout << "3. All arrays read from file" << endl;  
  cout << "4. Test successful. Data is consistent." << endl;
  
  
  // testing file repositioning
  
  cout << "--- TESTING FILE REPOSITIONING ---" << endl;
  
  
  ic.rePosition (positions[0]);
  
  ic.readUnsignedList(v1);
  cout << "\t unsigned list read" << endl;
  equal = true;
  
  for (unsigned i=0; i<TAM1 && equal; ++i)
  {
    equal = (array1[i] == v1[i]);
    if (!equal)
      cerr << "i = " << i << ", read array = " << v1[i] << ", original = " << array1[i] << endl;
  }
  
  if (equal)
    cout << "\t >>> The list of unsigned has been retrieved sucessfully!!" << endl;
  else 
  {
    cout << "ERROR: inconsistent data. Exiting" << endl;
    return -1;
  }
  
  ic.rePosition (positions[1]);
  
  ic.readSortedUnsignedList(v2, true);
  cout << "\t sorted unsigned list read" << endl;

  for (unsigned i=0; i<TAM1 && equal; ++i)
  {
    equal = (array2[i] == v2[i]);
    if (!equal)
      cerr << "i = " << i << ", read array = " << v2[i] << ", original = " << array2[i] << endl;
  }
  
  if (equal)
    cout << "\t >>> The sorted list of unsigned has been retrieved sucessfully!!" << endl;
  else 
  {
    cout << "ERROR: inconsistent data. Exiting" << endl;
    return -1;
  }
  

  ic.rePosition (positions[2]);
  
  ic.readLongList(l1);
  cout << "\t long list read" << endl;

   for (unsigned i=0; i<TAM1 && equal; ++i)
  {
    equal = (array1l[i] == l1[i]);
    if (!equal)
      cerr << "i = " << i << ", read array = " << l1[i] << ", original = " << array1l[i] << endl;
  }
  
  if (equal)
    cout << "\t >>> The list of long has been retrieved sucessfully!!" << endl;
  else 
  {
    cout << "ERROR: inconsistent data. Exiting" << endl;
    return -1;
  }
   
  ic.rePosition (positions[3]);
  
  ic.readSortedLongList(l2, true);
  cout << "\t sorted long list read" << endl;
  for (unsigned i=0; i<TAM1 && equal; ++i)
  {
    equal = (array2l[i] == l2[i]);
    if (!equal)
      cerr << "i = " << i << ", read array = " << l2[i] << ", original = " << array2l[i] << endl;
  }
  
  if (equal)
    cout << "\t >>> The sorted list of long has been retrieved sucessfully!!" << endl;
  else 
  {
    cout << "ERROR: inconsistent data. Exiting" << endl;
    return -1;
  }

  ic.rePosition (positions[4]);

  ic.readFloatList(f);
  cout << "\t float list read" << endl;
 
  for (unsigned i=0; i<TAM1 && equal; ++i)
  {
    equal = (array1f[i] == f[i]);
    if (!equal)
      cerr << "i = " << i << ", read array = " << f[i] << ", original = " << array1f[i] << endl;
  }
  
  if (equal)
    cout << "\t >>> The list of float has been retrieved sucessfully!!" << endl;
  else 
  {
    cout << "ERROR: inconsistent data. Exiting" << endl;
    return -1;
  }
  cout << "3. All arrays read from file" << endl;  
  cout << "4. Test successful. Data is consistent." << endl;
  
  
  // testing file repositioning
  
  
  // -------------------------------------------------------------------------------------
  // testing array
 
  { 
  
  OutputIndexFile<long> oif ("delete_me");
 
  for (unsigned i=0; i<array1l.size(); ++i)
  {
    oif[i] = array1l[i];  
  }
  
    // we force the destructor to be called...
  }

  cout << "array written" << endl;  
  
  InputIndexFile<long> iif ("delete_me");
  
  bool equalv = true;
  
  for (unsigned i=0; i<array1l.size() && equalv; ++i)
  {
    equalv = (iif[i] == array1l[i]);
    if (!equalv) cerr << i << " " << iif[i] << " " << array1l[i] << endl;
  }
  
  if (! equalv)
  {
    cerr<< "ERROR: IndexFile is not consistent while read sequentially!!!!!!" << endl;  
  }
  
  equalv = true;
  unsigned tam = array1l.size();
  for (unsigned i=0; i<array1l.size() && equalv; ++i)
  {
    equalv = (iif[tam-i-1] == array1l[tam-1-i]);  
    if (!equal) cerr << i << " " << iif[i] << " " << array1l[i] << endl;
  }
  
  if (!equalv)
    cerr << "ERROR: Index file is not consistent while read randomly!!!!!!!!!" << endl;
  
  return 0;
}


