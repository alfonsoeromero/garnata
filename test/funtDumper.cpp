/*
 * funtDumper.cpp - The Garnata Retrieval System
 * Copyright (C) 2005, 2026 Alfonso E. Romero
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{  
  fstream fp(argv[1], ios_base::in | ios_base::binary);
  
  unsigned id = 0;
  unsigned v[6];
  char tmp;
  float w;
  
  while (!fp.fail())
  {
    fp.seekg(29*id, ios_base::beg);
    fp.read((char*) &v, sizeof(unsigned)*6);
    fp.read((char*) &w, sizeof(float));
    fp.read(&tmp, sizeof(char));
    cout << id << " Unit: " << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << " " << v[4] << " " << v[5] << " " << w << " " << tmp << " (" << int(tmp) << ")\n";
    ++id;
  }

  return 0;
}

