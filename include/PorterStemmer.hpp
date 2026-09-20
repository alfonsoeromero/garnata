/*
 * PorterStemmer.hpp - The Garnata Retrieval System
 * Copyright (C) 2005, 2026 Alfonso E. Romero
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version. See the LICENSE file for details.
 */

#ifndef __PORTER_STEMMER_HPP__
#define __PORTER_STEMMER_HPP__

#include <string>

/** C++ interface to Martin Porter's reference implementation of the
    Porter stemming algorithm (see porter_stemmer.cpp).
*/
class PorterStemmer {
  public:
    /** Stems a single word.
    Only words starting with a lowercase letter are stemmed, so that
    acronyms and proper names are left untouched. Callers are expected
    to case-fold the input beforehand.
    @param word word to be stemmed
    @return stemmed word (or the input, unchanged, if not stemmed)
    */
    static std::string stemWord(const std::string& word);
};

#endif
