#include "commands.hpp"

void namestnikov::print(std::istream & in, std::map< std::string, std::map< size_t, std::string > > & myMap, std::ostream & out)
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

void namestnikov::makeIntersect(std::istream & in, std::map< std::string, std::map< size_t, std::string > > & myMap)
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

void namestnikov::makeUnion(std::istream & in, std::map< std::string, std::map< size_t, std::string > > & myMap)
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

void namestnikov::makeComplement(std::istream & in, std::map< std::string, std::map< size_t, std::string > > & myMap)
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
    if (right.find(key1.first) == right.end())
    {
      res.insert(key1);
    }
  }
  myMap[newName] = res;
}