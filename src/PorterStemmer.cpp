/*==========================================================================
 *
 *  Original source copyright (c) 2001, Carnegie Mellon University.
 *  See copyright.cmu for details.
 *  Modifications copyright (c) 2002, University of Massachusetts.
 *  See copyright.umass for details.
 *
 *==========================================================================
*/

/*
 * NAME DATE - COMMENTS
 * pto 2001 - created
 * dmf 9/2002 - modified stemWord to return char*
 *
 *========================================================================*/

#include "PorterStemmer.hpp"

#include <cctype>
#include <cstring>

// the Porter stemmer is in C
extern int porter_stem(char * p, int i, int j);


string PorterStemmer::stemWord(const string& _word) {
  char* word = new char[_word.size() + 1];
  strcpy(word, _word.c_str());  

  // only stem words that begin with a lowercase letter 
  // (don't stem acronyms or names)
  if (islower(*word)) {
    int len = strlen(word);
    len = porter_stem(word, 0, len - 1) + 1;
    word[len] = '\0';
  }

  string s(word);
  delete [] word;
  return s;
}

