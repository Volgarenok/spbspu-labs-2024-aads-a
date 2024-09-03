#include "commands.hpp"

void namestnikov::print(std::istream & in, Tree< std::string, Tree< size_t, std::string > > & myMap, std::ostream & out)
{
  std::string name = "";
  in >> name;
  Tree< size_t, std::string > map = myMap.at(name);
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

void namestnikov::makeIntersect(std::istream & in, Tree< std::string, Tree< size_t, std::string > > & myMap)
{
  std::string newName = "";
  in >> newName;
  std::string firstName = "";
  in >> firstName;
  std::string secondName = "";
  in >> secondName;
  Tree< size_t, std::string > res;
  Tree< size_t, std::string > left = myMap.at(firstName);
  Tree< size_t, std::string > right = myMap.at(secondName);
  for (const auto & key1: left)
  {
    for (const auto & key2: right)
    {
      if (key1.first == key2.first)
      {
        res.insert(key1.first, key1.second);
      }
    }
  }
  myMap[newName] = res;
}

void namestnikov::makeUnion(std::istream & in, Tree< std::string, Tree< size_t, std::string > > & myMap)
{
  std::string newName = "";
  in >> newName;
  std::string firstName = "";
  in >> firstName;
  std::string secondName = "";
  in >> secondName;
  Tree< size_t, std::string > res;
  Tree< size_t, std::string > left = myMap.at(firstName);
  Tree< size_t, std::string > right = myMap.at(secondName);
  for (const auto & key1: left)
  {
    res.insert(key1.first, key1.second);
  }
  for (const auto & key2: right)
  {
    if (res.find(key2.first) == res.cend())
    {
      res.insert(key2.first, key2.second);
    }
  }
  myMap[newName] = res;
}

void namestnikov::makeComplement(std::istream & in, Tree< std::string, Tree< size_t, std::string > > & myMap)
{
  std::string newName = "";
  in >> newName;
  std::string firstName = "";
  in >> firstName;
  std::string secondName = "";
  in >> secondName;
  Tree< size_t, std::string > res;
  Tree< size_t, std::string > left = myMap.at(firstName);
  Tree< size_t, std::string > right = myMap.at(secondName);
  for (const auto & key1: left)
  {
    if (right.find(key1.first) == right.cend())
    {
      res.insert(key1.first, key1.second);
    }
  }
  myMap[newName] = res;
}
