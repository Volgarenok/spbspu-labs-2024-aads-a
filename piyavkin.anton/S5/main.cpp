#include <iostream>
#include <tree.hpp>

struct Sumkey
{
  void operator()(const std::pair< int, std::string >& val)
  {
    str += val.second;
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
}
