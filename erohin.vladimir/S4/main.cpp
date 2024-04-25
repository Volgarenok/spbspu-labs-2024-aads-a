#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <functional>

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Wrong CLA number\n";
    return 0;
  }
  std::fstream file(argv[1]);
  using dictionary = std::map< size_t, std::string >;
  std::map< std::string, dictionary > context;
  std::string dict_name;
  file >> dict_name;
  while (!file.eof())
  {
    size_t key;
    std::string value;
    while (file >> key >> value)
    {
      context[dict_name][key] = value;
    }
    file.clear();
    file >> dict_name;
    if (!dict_name.size())
    {
      continue;
    }
  }
  file.close();
  std::map< std::string, std::function< void(dictionary &, const dictionary &, const dictionary &) > > command;
  command.empty();
}
