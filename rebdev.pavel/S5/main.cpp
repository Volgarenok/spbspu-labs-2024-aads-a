#include <iostream>
#include <fstream>

int main(int argc, char ** argv)
{
  if (argc != 3)
  {
    str::cerr << "Bad number of input arguments!\n";
    return 1;
  }
  std::ifstream inFile(argv[1]);
  if ((!inFile.open()) || (inFile.eof()))
  {
    str::cerr << "Empty tree file!\n";
    return 1;
  }
  switch(argv[2])
  {
    case "ascending":
      //some work
      break;
    case "descending":
      //some work
      break;
    case "breadth":
      //some work
      break;
    default:
      std::cerr << "Bad argument input!\n";
      return 1;
  }
  return 0;
}
