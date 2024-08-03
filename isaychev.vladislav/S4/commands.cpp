#include "commands.hpp"
#include <iostream>

void isaychev::print(std::ostream & out, cstr_ref name, const map_t & dicts)
{
  const dataset_t & current = dicts.at(name);
  if (current.empty())
  {
    throw std::runtime_error("< empty dataset >");
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

void isaychev::complement(cstr_ref new_name, cstr_ref name1, cstr_ref name2, map_t & dicts)
{
  const dataset_t & n1 = dicts.at(name1);
  const dataset_t & n2 = dicts.at(name2);
  auto result = dicts.insert(std::make_pair(new_name, dataset_t()));
  if (result.second)
  {
    if (n1.size() > n2.size())
    {
      complement_impl((*(result.first)).second, n1, n2);
    }
    else
    {
      complement_impl((*(result.first)).second, n2, n1);
    }
  }
  else
  {
    throw std::runtime_error("< dataset with such name already exists >");
  }
}

void isaychev::intersect(cstr_ref new_name, cstr_ref name1, cstr_ref name2, map_t & dicts)
{
  const dataset_t & n1 = dicts.at(name1);
  const dataset_t & n2 = dicts.at(name2);
  auto result = dicts.insert(std::make_pair(new_name, dataset_t()));
  if (result.second)
  {
    dataset_t & n3 = (*(result.first)).second;
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
  }
  else
  {
    throw std::runtime_error("< dataset with such name already exists >");
  }
}

void insert_elems(isaychev::dataset_t & n1, const isaychev::dataset_t & n2)
{
  for (auto j = n2.cbegin(); j != n2.cend(); ++j)
  {
    n1.insert(*j);
  }
}

void isaychev::unite(cstr_ref new_name, cstr_ref name1, cstr_ref name2, map_t & dicts)
{
  const dataset_t & n1 = dicts.at(name1);
  const dataset_t & n2 = dicts.at(name2);
  auto result = dicts.insert(std::make_pair(new_name, dataset_t()));
  if (result.second)
  {
    dataset_t & n3 = (*(result.first)).second;
    insert_elems(n3, n1);
    insert_elems(n3, n2);
  }
  else
  {
    throw std::runtime_error("< dataset with such name already exists >");
  }
}
