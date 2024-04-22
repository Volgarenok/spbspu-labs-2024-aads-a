#include <fstream>
#include <iosfwd>
#include <iostream>
#include <list>
#include <map>
#include <string>

int main(int argc, char** argv)
{
  /*if (argc != 2)
  {
    std::cerr << "Wrong input file\n";
    return 1;
  }*/
  //std::fstream fileinp(argv[1]);
  std::map< std::string, std::map< int, std::string > > maps;
  std::string name;
  using basicMap = std::pair<int, std::string>;
  using mapOfMaps = std::pair< std::string, std::map<int, std::string>>;
  while (std::cin)
  {
    std::map<int, std::string > map;
    int key{};
    std::string val{};
    std::cin >> name;
    while (std::cin >> key >> val)
    {
      map.insert(basicMap(key, val));
    }
    maps.insert(mapOfMaps(name, map));
  }
  for (const auto& dict : maps)
  {
    for (const auto& res : dict.second)
    {
      std::cout << res.first << " - " << res.second;
    }
    std::cout << '\n';
  }
}
