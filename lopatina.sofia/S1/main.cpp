#include <iostream>
#include <cstddef>
#include <string>
#include <utility>
#include <limits>
#include "node.hpp"
#include "list_iterator.hpp"
#include "const_list_iterator.hpp"
#include "list.hpp"

int main()
{
  using namespace lopatina;
  List<std::pair<std::string,List<size_t>>> list;
  std::string name = "";
  std::string num_str = "";
  size_t number = 0;
  size_t max_size = 0;
  while (std::cin >> name)
  {
    size_t loc_size = 0;
    List<size_t> list_num;
    std::getline(std::cin,num_str);
    size_t sz = 0;
    while (!num_str.empty())
    {
      number = 0;
      number = std::stoull(num_str,&sz);
      num_str = num_str.substr(sz);
      list_num.push_back(number);
      loc_size += 1;
    }
    list.push_back(std::make_pair(name, list_num));
    if (loc_size > max_size)
    {
      max_size = loc_size;
    }
  }
  if (list.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  List<std::string> list_names;
  for (auto iter = list.begin(); iter != list.end(); ++iter)
  {
    list_names.push_back((*iter).first);
  }

  List<size_t> list_sum;
  if (max_size == 0)
  {
    list_sum.push_back(0);
  }
  //
  bool overflow = false;
  //
  List<List<size_t>> list_nums;
  for (size_t i = 0; i < max_size; ++i)
  {
    size_t sum = 0;
    List<size_t> list_num;
    for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
      List<size_t> sub_list = (*iter).second;
      size_t size = 0;
      for (auto sub_iter = sub_list.begin(); sub_iter != sub_list.end(); ++sub_iter)
      {
        if (size == i)
        {
          if ((std::numeric_limits<unsigned long long>::max() - sum) >= *sub_iter)
          {
            sum += *sub_iter;
          }
          else
          {
            //std::cerr << "Overflow\n";
            //return 1;
            overflow = true;
          }
          list_num.push_back(*sub_iter);
        }
        ++size;
      }
    }
    list_sum.push_back(sum);
    list_nums.push_back(list_num);
  }
  std::cout << list_names.front();
  for (auto iter0 = ++(list_names.begin()); iter0 != list_names.end(); ++iter0)
  {
    std::cout << ' ' << *iter0;
  }
  std::cout << '\n';
  for (auto iter1 = list_nums.begin(); iter1 != list_nums.end(); ++iter1)
  {
    std::cout << (*iter1).front();
    for (auto iter2 = ++((*iter1).begin()); iter2 != (*iter1).end(); ++iter2)
    {
      std::cout << ' ' << *iter2;
    }
    std::cout << '\n';
  }
//
  if (overflow)
  {
    std::cerr << "Overflow\n";
    return 1;
  }
//
  for (auto iter = list_sum.begin(); iter != list_sum.end(); ++iter)
  {
    auto iter_next = iter;
    ++iter_next;
    if (iter_next == nullptr)
    {
      std::cout << *iter;
    }
    else
    {
      std::cout << *iter << ' ';
    }
  }
  std::cout << '\n';
  return 0;
}
