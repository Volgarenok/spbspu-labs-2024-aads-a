#include <iostream>
#include <fstream>
#include <string>
#include <tree.hpp>

int main(int argc, char* argv[])
{
  using namespace nikitov;

  Tree< long long, std::string > dictionary;
  if (argc == 2)
  {
    std::ifstream input(argv[2]);
    size_t key = {};
    while (input >> key)
    {
      std::string value = {};
      input >> value;
      dictionary.insert({ key, value });
    }
  }
  else
  {
    std::cerr << "Error: Wrong input parameters" << '\n';
    return 1;
  }
  return 0;
}
