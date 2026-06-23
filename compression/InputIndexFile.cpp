#include "InputIndexFile.h"

// ==============================================================================

template <typename T>
InputIndexFile<T>::InputIndexFile() { }

// ==============================================================================

template <typename T>
InputIndexFile<T>::InputIndexFile(const string& fileName) :
   BasicInputBinaryBuffer(fileName, 4096), expectedPosition(0)
{ }

// ==============================================================================

template <typename T>
void InputIndexFile<T>::open(const string& fileName, unsigned SIZE) {
  BasicInputBinaryBuffer::open(fileName, SIZE);
}

// ==============================================================================

template <typename T>
T InputIndexFile<T>::operator[] (unsigned i)
{
  if (i != expectedPosition)
  {
    rePosition(sizeof(T) * i);
  }

  //long ret = 0;
  this->clearBaseAddress();
  
  char c[ sizeof(T) ];
  for (unsigned num=0; num<sizeof(T); ++num)
  {
    readByte(c[num]);
  }
  
  T* ltemp = reinterpret_cast<T*>(&c);
  T ret = *ltemp;
  
  expectedPosition = i + 1;
  
  return ret;
}

// ==============================================================================

template <typename T>
InputIndexFile<T>::~InputIndexFile() { }

// ==============================================================================


template class InputIndexFile<long>;
template class InputIndexFile<unsigned>;
template class InputIndexFile<float>;

