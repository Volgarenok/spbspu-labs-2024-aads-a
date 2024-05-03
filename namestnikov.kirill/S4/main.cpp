#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <functional>
#include <limits>

void print(std::map< std::string, std::map< size_t, std::string > > & myMap, std::istream & in, std::ostream & out)
{
  std::string name = "";
  in >> name;
  std::map< size_t, std::string > map = myMap[name];
  if (map.empty())
  {
    out << "<EMPTY>\n";
  }
  else
  {
    out << name;
    for (const auto & key: map)
    {
      out << " " << key.first << " " << key.second;
    }
    out << "\n";
  }
}

void makeIntersect(std::map< std::string, std::map< size_t, std::string > > & myMap, std::istream & in)
{
  std::string newName = "";
  in >> newName;
  std::string firstName = "";
  in >> firstName;
  std::string secondName = "";
  in >> secondName;
  std::map< size_t, std::string > res;
  std::map< size_t, std::string > left = myMap[firstName];
  std::map< size_t, std::string > right = myMap[secondName];
  for (const auto & key1: left)
  {
    for (const auto & key2: right)
    {
      if (key1.first == key2.first)
      {
        res.insert(key1);
      }
    }
  }
  myMap[newName] = res;
}

void makeUnion(std::map< std::string, std::map< size_t, std::string > > & myMap, std::istream & in)
{
  std::string newName = "";
  in >> newName;
  std::string firstName = "";
  in >> firstName;
  std::string secondName = "";
  in >> secondName;
  std::map< size_t, std::string > res;
  std::map< size_t, std::string > left = myMap[firstName];
  std::map< size_t, std::string > right = myMap[secondName];
  for (const auto & key1: left)
  {
    res.insert(key1);
  }
  for (const auto & key2: right)
  {
    if (res.find(key2.first) == res.end())
    {
      res.insert(key2);
    }
  }
  myMap[newName] = res;
}

void makeComplement(std::map< std::string, std::map< size_t, std::string > > & myMap, std::istream & in)
{
  std::map< size_t, std::string > res;
}

void inputMaps(std::istream & in, std::map< std::string, std::map< size_t, std::string > > & myMap)
{
  while (!in.eof())
  {
    in.clear();
    std::map< size_t, std::string > tempMap;
    std::string mapName = "";
    in >> mapName;
    size_t keyNumber = 0;
    while (in >> keyNumber)
    {
      std::string value = "";
      in >> value;
      tempMap.insert(std::make_pair(keyNumber, value));
    }
    myMap.insert(std::make_pair(mapName, tempMap));
    std::cout << "here";
  }
}

int main(int argc, char * argv[])
{
  using mapOfDicts = std::map< std::string, std::map< size_t, std::string > >;
  mapOfDicts myMap;
  if (argc == 2)
  {
    std::ifstream in(argv[1]);
    if (!in.is_open())
    {
      std::cerr << "Can not open the file\n";
      return 1;
    }
    inputMaps(in, myMap);
    in.close();
  }
  else
  {
    std::cerr << "Wrong command line arguments\n";
    return 2;
  }
  std::map< std::string, std::function< void(mapOfDicts &, std::istream &) > > commands;
  {
    using namespace std::placeholders;
    commands["union"] = makeUnion;
    commands["intersect"] = makeIntersect;
    commands["complement"] = makeComplement, _1, _2;
    commands["print"] = std::bind(print, _1, _2, std::ref(std::cout));
  }
  std::string commandName = "";
  while (std::cin >> commandName)
  {
    try
    {
      commands.at(commandName)(myMap, std::cin);
    }
    catch (const std::out_of_range &)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');

  }
}
