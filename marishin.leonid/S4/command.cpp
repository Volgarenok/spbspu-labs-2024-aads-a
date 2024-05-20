#include "command.hpp"

void marishin::print(std::istream& in, const tree& myMap, std::ostream& out)
{
  std::string name = "";
  in >> name;
  BinarySearchTree< size_t, std::string > map = myMap.at(name);
  if (map.empty())
  {
    out << "<EMPTY>\n";
  }
  else
  {
    out << name;
    for (const auto& key: map)
    {
      out << " " << key.first << " " << key.second;
    }
    out << "\n";
  }
}

void marishin::doUnion(std::istream& in, tree& myMap)
{
  std::string newName = "";
  in >> newName;
  std::string firstName = "";
  in >> firstName;
  std::string secondName = "";
  in >> secondName;
  BinarySearchTree< size_t, std::string > res;
  BinarySearchTree< size_t, std::string > left = myMap.at(firstName);
  BinarySearchTree< size_t, std::string > right = myMap.at(secondName);
  for (const auto& key1: left)
  {
    res.insert(key1.first, key1.second);
  }
  for (const auto& key2: right)
  {
    if (res.find(key2.first) == res.cend())
    {
      res.insert(key2.first, key2.second);
    }
  }
  myMap[newName] = res;
}

void marishin::doComplement(std::istream& in, tree& myMap)
{
  std::string newName = "";
  in >> newName;
  std::string firstName = "";
  in >> firstName;
  std::string secondName = "";
  in >> secondName;
  BinarySearchTree< size_t, std::string > res;
  BinarySearchTree< size_t, std::string > left = myMap.at(firstName);
  BinarySearchTree< size_t, std::string > right = myMap.at(secondName);
  for (const auto& key1: left)
  {
    if (right.find(key1.first) == right.cend())
    {
      res.insert(key1.first, key1.second);
    }
  }
  myMap[newName] = res;
}

void marishin::doIntersect(std::istream& in, tree& myMap)
{
  std::string newName = "";
  in >> newName;
  std::string firstName = "";
  in >> firstName;
  std::string secondName = "";
  in >> secondName;
  BinarySearchTree< size_t, std::string > res;
  BinarySearchTree< size_t, std::string > left = myMap.at(firstName);
  BinarySearchTree< size_t, std::string > right = myMap.at(secondName);
  for (const auto& key1: left)
  {
    for (const auto& key2: right)
    {
      if (key1.first == key2.first)
      {
        res.insert(key1.first, key1.second);
      }
    }
  }
  myMap[newName] = res;
}
