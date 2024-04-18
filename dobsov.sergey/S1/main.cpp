#include <forward_list>
#include <iterator>
#include <iostream>

using ull_list_t = std::forward_list< unsigned long long >;
using named_list_t = std::pair< std::string, ull_list_t >;
using lists_t = std::forward_list< named_list_t >;

ull_list_t read_ulls(std::istream & in)
{
  ull_list_t data;
  unsigned long long value = 0;
  auto toinsert = data.before_begin();
  while (in >> value)
  {
    toinsert = data.insert_after(toinsert, value);
  }
  return data;
}

named_list_t read_named(std::istream & in)
{
  std::string name;
  std::cin >> name;
  auto ulls = read_ulls(in);
  if (in.fail())
  {
    in.clear(std::ios::failbit);
  }
  return std::make_pair(name, ulls);
}

lists_t read_lists(std::istream & in)
{
  lists_t data{};
  auto toinsert = data.before_begin();
  while (!in.eof())
  {
    named_list_t named = read_named(in);
    toinsert = data.insert_after(toinsert, named);
  }
  return data;
}

int main()
{
  auto lists = read_lists(std::cin);
  auto & data = lists.begin()->second;
  std::copy(data.cbegin(), data.cend(), std::ostream_iterator< unsigned long long >{std::cout, "\n"});
}
