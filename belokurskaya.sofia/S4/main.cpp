#include <cstring>
#include <fstream>
#include <functional>

#include "parseLine.hpp"
#include "commands.hpp"
#include "commandCollection.hpp"

using fnc = std::function< void(belokurskaya::DictionaryCollection&, std::istream&, std::ostream&) >;

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

  DictionaryCollection dictionaries;
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
    BinarySearchTree< std::string, fnc > cmds;
    {
      using namespace std::placeholders;
      cmds["complement"] = std::bind(&cmds::complement, _1, _2, _3);
      cmds["intersect"] = std::bind(&cmds::intersect, _1, _2, _3);
      cmds["union"] = std::bind(&cmds::unionDicts, _1, _2, _3);
      cmds["print"] = std::bind(&cmds::printCommand, _1, _2, _3);
    }
    std::string command;
    while (std::cin >> command)
    {
      cmds.at(command)(dictionaries, std::cin, std::cout);

      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
