#include "commands.hpp"
#include <istream>
#include <list/list.hpp>
#include <sorts.hpp>
#include <functional>
#include <fstream>

std::string read_specifier(std::istream & in)
{
  std::string str;
  in >> str;
  return str;
}

void isaychev::make_freqlist(collection_t & col, std::istream & in)
{
  std::string str = std::move(read_specifier(in));
  std::ifstream file(str);
  if (!file.is_open())
  {
    throw std::runtime_error("<INVALID_COMMAND>");
  }
  in >> str;
  if (str.empty() || col.find(str) != col.end())
  {
    throw std::runtime_error("<INVALID_COMMAND>");
  }

  FreqList l;
  Word w;
  while (!(file >> w).eof())
  {
    if (file.fail())
    {
      file.clear();
      continue;
    }
    l.insert(w);
  }

  if (l.empty())
  {
    std::runtime_error("<EMPTY>");
  }
  col[str] = l;
}

void isaychev::delete_freqlist(collection_t & col, std::istream & in)
{
  std::string str = std::move(read_specifier(in));
  if (str.empty())
  {
    throw std::runtime_error("<INVALID_COMMAND>");
  }
  size_t res = col.erase(str);
  if (!res)
  {
    throw std::runtime_error("<INVALID_COMMAND>");
  }
}

template< class FreqListIt >
void output_list_part(std::ostream & out, FreqListIt first, size_t count)
{
  for (size_t i = 0; i < count; ++i)
  {
    out << isaychev::convert_to_str(*first) << "\n";
    ++first;
  }
}

template< class Container >
void input_and_sort(const Container & input, isaychev::List< std::pair< isaychev::Word, size_t > > & rhs)
{
  for (auto i = input.begin(); i != input.end(); ++i)
  {
    rhs.push_front(*i);
  }
  quick_sort(rhs.begin(), rhs.end(), isaychev::is_greater);
}

void isaychev::print(const collection_t & col, std::istream & in, std::ostream & out)
{
  const auto & res = col.at(read_specifier(in));
  List< std::pair< Word, size_t > > temp;
  input_and_sort(res.get_map(), temp);
  output_list_part(out, temp.begin(), res.size());
}

void isaychev::count(const collection_t & col, std::istream & in, std::ostream & out)
{
  const auto & fl = col.at(read_specifier(in));
  out << fl.at({read_specifier(in)}) << "\n";
}

void isaychev::get_total(const collection_t & col, std::istream & in, std::ostream & out)
{
  const auto & fl = col.at(read_specifier(in));
  WordCounter counter;
  for (auto i = fl.get_map().begin(); i != fl.get_map().end(); ++i)
  {
    counter(*i);
  }
  out << counter() << "\n";
}

void isaychev::get_unique(const collection_t & col, std::istream & in, std::ostream & out)
{
  const auto & fl = col.at(read_specifier(in));
  out << fl.size() << "\n";
}

void isaychev::print_extremes(const collection_t & col, const std::string & spec, std::istream & in, std::ostream & out)
{
  std::string str = std::move(read_specifier(in));
  size_t num = 0;
  in >> num;
  if (!in)
  {
    throw std::runtime_error("<INVALID_COMMAND>");
  }
  const auto & fl = col.at(str);
  if (num > fl.size())
  {
    num = fl.size();
  }
  List< std::pair< Word, size_t > > temp;
  input_and_sort(fl.get_map(), temp);
  if (spec == "printlast")
  {
    temp.reverse();
  }
  output_list_part(out, temp.begin(), num);
}


bool is_in(const isaychev::BSTree< isaychev::Word, size_t > & col, const std::pair< isaychev::Word, size_t > & rhs)
{
  return col.find(rhs.first) != col.end();
}

void isaychev::merge(collection_t & col, std::istream & in)
{
  std::string list, list2, new_list;
  in >> new_list >> list >> list2;
  if (new_list.empty())
  {
    throw std::runtime_error("<INVALID_COMMAND>");
  }
  const auto & fl1 = col.at(list);
  const auto & fl2 = col.at(list2);
  FreqList temp(fl1);
  for (auto i = fl2.get_map().begin(); i != fl2.get_map().end(); ++i)
  {
    temp.add_element(*i);
  }
  col[new_list] = {std::move(temp)};
}

void isaychev::get_names(const collection_t & col, std::ostream & out)
{
  if (!col.empty())
  {
    auto i = col.begin();
    out << (*i).first;
    for (++i; i != col.end(); ++i)
    {
      out << " " << (*i).first;
    }
    out << "\n";
  }
}

void isaychev::intersect(collection_t & col, std::istream & in)
{
  std::string list, list2, new_list;
  in >> new_list >> list >> list2;
  if (new_list.empty())
  {
    throw std::runtime_error("<INVALID_COMMAND>");
  }
  const auto & fl1 = col.at(list);
  const auto & fl2 = col.at(list2);
  BSTree< Word, size_t > temp2;
  for (auto i = fl2.get_map().begin(); i != fl2.get_map().end(); ++i)
  {
    if (is_in(fl1.get_map(), *i))
    {
      temp2.insert({(*i).first, std::min(fl1.get_map().at((*i).first), (*i).second)});
    }
  }
  col[new_list] = {std::move(temp2)};
}

void isaychev::execlude(collection_t & col, cmp_t cmp, std::istream & in)
{
  using namespace std::placeholders;
  std::string new_list, list;
  size_t total = 0;
  in >> new_list >> list >> total;
  if (!in)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  const auto & fl = col.at(list);
  BSTree< Word, size_t > temp;
  std::pair< Word, size_t > value_cmp{{}, total};
  for (auto i = fl.get_map().begin(); i != fl.get_map().end(); ++i)
  {
    if ((*cmp)(value_cmp, *i))
    {
      temp.insert(*i);
    }
  }
  if (temp.empty())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  col[new_list] = {std::move(temp)};
}
