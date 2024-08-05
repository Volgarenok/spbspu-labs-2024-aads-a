#include "commands.hpp"
#include <iostream>

void strelyaev::print(std::istream& in, const Tree< std::string, Tree< int, std::string > >& map, std::ostream& out)
{
  std::string inner_map_name = "";
  in >> inner_map_name;
  Tree< int, std::string > inner_map = map.at(inner_map_name);
  if (inner_map.empty())
  {
    out << "<EMPTY>\n";
    return;
  }
  out << inner_map_name;
  for (auto it = inner_map.cbegin(); it != inner_map.cend(); it++)
  {
    out << " " << it->first << " " << it->second;
  }
  out << "\n";
}

void strelyaev::getComplement(std::istream& in, Tree< std::string, Tree< int, std::string > >& map)
{
  std::string new_name = "";
  std::string first_name = "";
  std::string second_name = "";
  in >> new_name >> first_name >> second_name;
  Tree< int, std::string > result;
  Tree< int, std::string > first = map.at(first_name);
  Tree< int, std::string > second = map.at(second_name);
  for (auto it = first.cbegin(); it != first.cend(); it++)
  {
    if (second.find(it->first) == second.end())
    {
      result.insert(*it);
    }
  }
  map[new_name] = result;
}

void strelyaev::getIntersect(std::istream& in, Tree< std::string, Tree< int, std::string > >& map)
{
  std::string new_name = "";
  std::string first_name = "";
  std::string second_name = "";
  in >> new_name >> first_name >> second_name;
  Tree< int, std::string > result;
  Tree< int, std::string > first = map.at(first_name);
  Tree< int, std::string > second = map.at(second_name);
  for (auto it = first.cbegin(); it != first.cend(); it++)
  {
    if (second.find(it->first) != second.end())
    {
      result.insert(*it);
    }
  }
  map[new_name] = result;
}

void strelyaev::getUnion(std::istream& in, Tree< std::string, Tree< int, std::string > >& map)
{
  std::string new_name = "";
  std::string first_name = "";
  std::string second_name = "";
  in >> new_name >> first_name >> second_name;
  Tree< int, std::string > result;
  Tree< int, std::string > first = map.at(first_name);
  Tree< int, std::string > second = map.at(second_name);
  for (auto it = first.cbegin(); it != first.cend(); it++)
  {
    result.insert(*it);
  }
  for (auto it = second.cbegin(); it != second.cend(); it++)
  {
    if (result.find(it->first) == result.end())
    {
      result.insert(*it);
    }
  }
  map[new_name] = result;
}

