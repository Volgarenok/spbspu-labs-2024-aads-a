#include <iostream>
#include <fstream>
#include <string>
#include <map>

void print(std::ostream & out, const std::map< size_t, std::string > & map, const std::string & name)
{
  if (map.empty())
  {
    out << "<EMPTY>\n";
  }
  else
  {
    out << name;
    for (auto key: map)
    {
      out << " " << key.first << " " << key.second;
    }
  }
}

std::map< size_t, std::string > makeIntersect(const std::map< size_t, std::string > & left, const std::map< size_t, std::string > & right)
{
  std::map< size_t, std::string > res;
  for (auto key1: left)
  {
    for (auto key2: right)
    {
      if (key1.first == key2.first)
      {
        res.insert(key1);
      }
    }
  }
  return res;
}

std::map< size_t, std::string > makeUnion(const std::map< size_t, std::string > & left, const std::map< size_t, std::string > & right)
{
  std::map< size_t, std::string > res;
  for (auto key1: left)
  {
    res.insert(key1);
  }
  for (auto key2: right)
  {
    if (res.find(key2.first) == res.end())
    {
      res.insert(key2);
    }
  }
  return res;
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
  std::map< size_t, std::string > temp1;
  temp1.insert(std::make_pair(1, "hello"));
  temp1.insert(std::make_pair(2, "jeez"));
  std::map< size_t, std::string > temp2;
  temp2.insert(std::make_pair(2, "hi"));
  temp2.insert(std::make_pair(3, "jeezus"));
  auto temp3 = makeUnion(temp1, temp2);
  print(std::cout, temp3, "third");
}
