/*==========================================================================
 *
 *  Original source copyright (c) 2001, Carnegie Mellon University.
 *  See copyright.cmu for details.
 *  Modifications copyright (c) 2002, University of Massachusetts.
 *  See copyright.umass for details.
 *
 *==========================================================================
*/

#ifndef _PORTERSTEMMER_HPP
#define _PORTERSTEMMER_HPP


#include <string>

///
///  Provides a wrapper to the Porter stemmer
///

using namespace std;

class PorterStemmer {

public:
  
  /// Stem a word using the Porter Stemmer.
  static string stemWord(const string& word);

};

#endif
