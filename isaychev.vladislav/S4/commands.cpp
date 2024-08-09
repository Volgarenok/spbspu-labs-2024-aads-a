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
    out << " " << (*i).first << " " << (*i).second;
  }
  out << "\n";
}

void complement_impl(isaychev::dataset_t & n3, const isaychev::dataset_t & n1, const isaychev::dataset_t & n2)
{
  for (auto i = n1.cbegin(); i != n1.cend(); ++i)
  {
    bool in_both = false;
    for (auto j = n2.cbegin(); j != n2.cend(); ++j)
    {
      if ((*i).first == (*j).first)
      {
        in_both = true;
      }
    }
    if (!in_both)
    {
      n3.insert(*i);
    }
  }
}

void isaychev::complement(map_t & dicts, std::istream & in)
{
  std::string new_name, name1 , name2;
  in >> new_name >> name1 >> name2;
  const dataset_t & n1 = dicts.at(name1);
  const dataset_t & n2 = dicts.at(name2);
  dataset_t n3;
  if (n1.size() > n2.size())
  {
    complement_impl(n3, n1, n2);
  }
  else
  {
    complement_impl(n3, n2, n1);
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
  for (auto i = n1.cbegin(); i != n1.cend(); ++i)
  {
    for (auto j = n2.cbegin(); j != n2.cend(); ++j)
    {
      if ((*i).first == (*j).first)
      {
        n3.insert(*i);
      }
    }
  }
  dicts[new_name] = std::move(n3);
}

void insert_elems(isaychev::dataset_t & n1, const isaychev::dataset_t & n2)
{
  for (auto j = n2.cbegin(); j != n2.cend(); ++j)
  {
    n1.insert(*j);
  }
}

void isaychev::unite(map_t & dicts, std::istream & in)
{
  std::string new_name, name1 , name2;
  in >> new_name >> name1 >> name2;
  const dataset_t & n1 = dicts.at(name1);
  const dataset_t & n2 = dicts.at(name2);
  dataset_t n3;
  insert_elems(n3, n1);
  insert_elems(n3, n2);
  dicts[new_name] = std::move(n3);
}
