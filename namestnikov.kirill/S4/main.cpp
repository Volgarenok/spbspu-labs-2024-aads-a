#include <iostream>
#include <fstream>
#include <string>
#include <map>

void print(std::ostream & out, const std::map< size_t, std::string > & map, const std::string & name)
{
  out << name;
  auto begin = map.cbegin();
  auto end = map.cend();
  --end;
  while (begin != end)
  {
    out << begin->first << " " << begin->second << " ";
    ++begin;
  }
  out << begin->first << " " << begin->second << " ";
}

int main(int argc, char * argv[])
{
  std::map< std::string, std::map< size_t, std::string > > myMap;
  if (argc == 2)
  {
    std::ifstream in(argv[1]);
    if (!in.is_open())
    {
      std::cerr << "Can not open the file\n";
      return 1;
    }
    std::map< size_t, std::string > tempMap;
    std::string mapName = "";
    in >> mapName;
    while (!in.eof())
    {
      size_t keyNumber = 0;
      std::string value = "";
      while (in >> keyNumber >> value)
      {
        tempMap.insert(std::make_pair(keyNumber, value));
      }
      if (!in.eof())
      {
        in.clear();
      }
      myMap.insert(std::make_pair(mapName, tempMap));
    }
    in.close();
  }
  for (const auto & pair : myMap)
  {
    for (const auto & pair2 : pair.second)
    {
      std::cout << pair2.first << " " << pair2.second;
    }
  }
  print(std::cout, myMap["first"], "first");
}
