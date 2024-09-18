#include <iostream>
#include <cstddef>
#include <string>
#include <utility>
#include <limits>
#include <node.hpp>
#include <list_iterator.hpp>
#include <const_list_iterator.hpp>
#include <list.hpp>

using listOfPairs = lopatina::List< std::pair< std::string, lopatina::List< size_t > > >;

size_t inputListOfPairs(std::istream & in, listOfPairs & list)
{
  std::string name = "";
  std::string num_str = "";
  size_t max_size = 0;
  while (in >> name)
  {
    size_t loc_size = 0;
    lopatina::List< size_t > list_num;
    std::getline(in, num_str);
    size_t idx = 0;
    while (!num_str.empty())
    {
      size_t number = 0;
      number = std::stoull(num_str, &idx);
      num_str = num_str.substr(idx);
      list_num.push_back(number);
      loc_size += 1;
    }
    list.push_back(std::make_pair(name, list_num));
    if (loc_size > max_size)
    {
      max_size = loc_size;
    }
  }
  return max_size;
}

template < typename T >
void outputList(std::ostream & out, lopatina::List< T > list)
{
  out << list.front();
  for (auto iter = ++(list.begin()); iter != list.end(); ++iter)
  {
    out << ' ' << *iter;
  }
}

int main()
{
  using namespace lopatina;
  List< std::pair< std::string, List< size_t > > > list;
  size_t max_size = inputListOfPairs(std::cin, list);

  if (list.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  List< std::string > list_names;
  for (auto iter = list.begin(); iter != list.end(); ++iter)
  {
    list_names.push_back((*iter).first);
  }

  List< size_t > list_sums;
  if (max_size == 0)
  {
    list_sums.push_back(0);
  }

  bool overflow = false;

  List< List< size_t > > list_nums;
  for (size_t i = 0; i < max_size; ++i)
  {
    size_t sum = 0;
    List< size_t > list_num;
    for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
      List< size_t > sub_list = (*iter).second;
      size_t size = 0;
      for (auto sub_iter = sub_list.begin(); sub_iter != sub_list.end(); ++sub_iter)
      {
        if (size == i)
        {
          if ((std::numeric_limits< unsigned long long >::max() - sum) >= *sub_iter)
          {
            sum += *sub_iter;
          }
          else
          {
            overflow = true;
          }
          list_num.push_back(*sub_iter);
        }
        ++size;
      }
    }
    list_sums.push_back(sum);
    list_nums.push_back(list_num);
  }

  outputList(std::cout, list_names);
  std::cout << '\n';
  for (auto iter_nums = list_nums.begin(); iter_nums != list_nums.end(); ++iter_nums)
  {
    outputList(std::cout, *iter_nums);
    std::cout << '\n';
  }
  if (overflow)
  {
    std::cerr << "Overflow\n";
    return 1;
  }
  outputList(std::cout, list_sums);
  std::cout << '\n';
  return 0;
}
