#include <iostream>
#include <fstream>
#include <tree.hpp>

struct Sumkey
{
  void operator()(const std::pair< int, std::string >& val)
  {
    str += " " + val.second;
    key += val.first;
  }
  std::string str;
  long long int key;
};


int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cerr << "File entered incorrectly\n";
    return 1;
  }
  using namespace piyavkin;
  std::ifstream in(argv[2]);
  if (!in.is_open())
  {
    std::cerr << "The file is not open\n";
    return 2;
  }
  Tree< int, std::string > tree;
  int key = 0;
  std::string val = "";
  while (in >> key >> val)
  {
    tree.insert(std::pair< int, std::string >(key, val));
  }
  if (!in.eof())
  {
    std::cerr << "Bad input\n";
    return 3;
  }
}
