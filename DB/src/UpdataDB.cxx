// STL include(s)
#include <iostream>
#include <fstream>

int main(int argc,char* argv[])
{
  std::cout << argc << " " << argv[1] << std::endl;
  std::ifstream infile(argv[1]);
  float fOpen, fHigh, fLow, fClose;
  unsigned long int iVolume;
  while(infile.good())
  {
    
  }
  return 0;
}
