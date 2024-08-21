#include <cstring>
#include <fstream>
#include <iostream>
#include <functional>

#include "commandCollection.hpp"
#include "parseLine.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace belokurskaya;
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
    parseLine(buffer, dict_name, dict);

    dictionaries.add(dict_name, std::move(dict));
  }

  try
  {
    BinarySearchTree<std::string, fnc> cmds;
    {
      using namespace std::placeholders;
      cmds["complement"] = std::bind(&complement, _1, _2, _3);
      cmds["intersect"] = std::bind(&intersect, _1, _2, _3);
      cmds["union"] = std::bind(&unionDicts, _1, _2, _3);
      cmds["print"] = std::bind(&printCommand, _1, _2, _3);
    }
  }
}
