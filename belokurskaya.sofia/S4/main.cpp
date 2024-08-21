#include <cstring>
#include <fstream>
#include <iostream>
#include <functional>

#include "commandCollection.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "No args\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Cannot open file\n";
    return 1;
  }

  belokurskaya::DictionaryCollection dictionaries;
  char buffer[1024];
  while (file.getline(buffer, sizeof(buffer)))
  {
    if (std::strlen(buffer) == 0)
    {
      continue;
    }

    std::string dict_name;
    Dictionary dict;
    }
}
