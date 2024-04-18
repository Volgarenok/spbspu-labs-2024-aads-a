#include <forward_list>
#include <iterator>
#include <iostream>

using ull_list_t = std::forward_list< unsigned long long >;
using data_t = std::pair< std::string, ull_list_t >;
using list_t = std::forward_list< data_t >;

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

data_t read_data(std::istream & in)
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

int main()
{
  auto datal = read_data(std::cin);
  auto & data = datal.second;
  std::copy(data.cbegin(), data.cend(), std::ostream_iterator< unsigned long long >{std::cout, "\n"});
}
