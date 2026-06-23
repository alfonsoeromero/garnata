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

