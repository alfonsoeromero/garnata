/*
 * PorterStemmer.cpp - The Garnata Retrieval System
 * Copyright (C) 2005, 2026 Alfonso E. Romero
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version. See the LICENSE file for details.
 */

#include "PorterStemmer.hpp"

#include <cctype>
#include <vector>

using namespace std;

// Defined in porter_stemmer.cpp (Martin Porter's reference implementation).
// Stems p[i..j] in place and returns the new index of the last character.
extern int porter_stem(char* p, int i, int j);

// ==================================================================

string PorterStemmer::stemWord(const string& word)
{
  if (word.empty() || !islower(static_cast<unsigned char>(word[0])))
    return word;

  // Writable, null-terminated copy of the word
  vector<char> buffer(word.begin(), word.end());
  buffer.push_back('\0');

  int last = porter_stem(&buffer[0], 0, static_cast<int>(word.size()) - 1);
  return string(&buffer[0], last + 1);
}

// ==================================================================
