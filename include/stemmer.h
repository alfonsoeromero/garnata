#ifndef __STEMMER_H__
#define __STEMMER_H__

using namespace std;

#include <string>

/** A namespace to allocate several stemming algorithms
*/
namespace Stemmer {
    
    /** Implements Porter's stemmer (for English language)
    @param s input string
    @return string s stemmed
    @author Written by B. Frakes and C. Cox, 1986. Changed by C. Fox, 1990.
    */
    string porterStemmer( const string& s);
   
}
  
#endif
