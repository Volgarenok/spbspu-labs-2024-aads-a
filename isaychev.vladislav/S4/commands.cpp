#include "commands.hpp"
#include <iostream>

void isaychev::print(const map_t & dicts, std::ostream & out, std::istream & in)
{
  std::string name;
  in >> name;
  const dataset_t & current = dicts.at(name);
  if (current.empty())
  {
    throw std::runtime_error("<EMPTY>");
  }
  out << name;
  for (auto i = current.cbegin(); i != current.cend(); ++i)
  {
    out << " " << i->first << " " << i->second;
  }
  out << "\n";
}

void isaychev::complement(map_t & dicts, std::istream & in)
{
  std::string new_name, name1 , name2;
  in >> new_name >> name1 >> name2;
  const dataset_t & n1 = dicts.at(name1);
  const dataset_t & n2 = dicts.at(name2);
  dataset_t n3;
  for (auto i = n1.begin(); i != n1.end(); ++i)
  {
    if (n2.find(i->first) == n2.end())
    {
      n3.insert(*i);
    }
  }
  dicts[new_name] = std::move(n3);
}

void isaychev::intersect(map_t & dicts, std::istream & in)
{
  std::string new_name, name1 , name2;
  in >> new_name >> name1 >> name2;
  const dataset_t & n1 = dicts.at(name1);
  const dataset_t & n2 = dicts.at(name2);
  dataset_t n3;
  for (auto i = n1.begin(); i != n1.end(); ++i)
  {
    if (n2.find(i->first) != n2.end())
    {
      n3.insert(*i);
    }
  }
  dicts[new_name] = std::move(n3);
}

void isaychev::unite(map_t & dicts, std::istream & in)
{
  std::string new_name, name1 , name2;
  in >> new_name >> name1 >> name2;
  const dataset_t & n1 = dicts.at(name1);
  const dataset_t & n2 = dicts.at(name2);
  dataset_t n3(n1);
  for (auto j = n2.cbegin(); j != n2.cend(); ++j)
  {
    n3.insert(*j);
  }
  dicts[new_name] = std::move(n3);
}
