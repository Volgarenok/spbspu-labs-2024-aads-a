#include <iostream>
#include <forward_list>
#include <list.hpp>
#include <deque>
#include <string>

int main(int argc, char* argv[])
{
if (argc == 3)
  {
    try
    {
      std::ifstream file(argv[2]);
      inputMap(file, map);
    }
    catch (...)
    {
      std::cerr << "Bad input\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "No file argument";
    return 1;
  }


}
