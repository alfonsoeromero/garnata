#include "OutputIndexFile.h"

// ==============================================================================

template <typename T>
void OutputIndexFile<T>::open(const string& fileName, unsigned SIZE) 
{
  BasicOutputBinaryBuffer::open(fileName, SIZE);
}

// ==============================================================================

template <typename T>
OutputIndexFile<T>::OutputIndexFile() 
{}

// ==============================================================================

template <typename T> 
OutputIndexFile<T>::OutputIndexFile(const string& fileName)
: BasicOutputBinaryBuffer(fileName, 4194304), expectedPosition(0)
{ }

// ==============================================================================

template <typename T>
OutputIndexFile<T>& OutputIndexFile<T>::operator[] (unsigned i)
{
  position = i;
  return *this;
}

// ==============================================================================

template <typename T>
void OutputIndexFile<T>::operator=(T value)
{
  writeValue(position, value);
}

// ==============================================================================

template <typename T>
void OutputIndexFile<T>::writeValue(unsigned pos, T value)
{
  if (pos != expectedPosition)
  {
    // we need to reposition
    this->rePosition( pos * sizeof(T) );  
  }
  
  char* bytes = reinterpret_cast<char *>(&value);
  
  this->writeBytes( sizeof(T), bytes );
  
  // new value of the expected value
  expectedPosition = pos + 1;
}

// ==============================================================================

template <typename T>
OutputIndexFile<T>::~OutputIndexFile() { }

// ==============================================================================


template class OutputIndexFile<long>;
template class OutputIndexFile<float>;
template class OutputIndexFile<unsigned>;

