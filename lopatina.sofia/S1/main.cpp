#include <iostream>
#include <cstddef>
#include <string>
#include <utility>
#include "node.hpp"
#include "iterator.hpp"
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
  for (auto iter = list.begin(); iter != list.end(); ++iter)
  {
    if (iter == list.tail)
    {
      std::cout << (*iter).first;
    }
    else
    {
      std::cout << (*iter).first << ' ';
    }
  }
  std::cout << '\n';

  List<size_t> list_sum;
  if (max_size == 0)
  {
    list_sum.push_back(0);
  }
  int space_flag = 0;
  for (size_t i = 0; i < max_size; ++i)
  {
    size_t sum = 0;
    for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
      List<size_t> sub_list = (*iter).second;
      size_t size = 0;
      if (iter == list.tail)
      {
        space_flag = 1;
      }
      for (auto sub_iter = sub_list.begin(); sub_iter != sub_list.end(); ++sub_iter)
      {
        if (size == i)
        {
          sum += *sub_iter;
          if (space_flag)
          {
            std::cout << *sub_iter;
            space_flag = 0;
          }
          else
          {
            std::cout << *sub_iter << ' ';
          }
        }
        ++size;
      }
    }
    std::cout << '\n';
    list_sum.push_back(sum);
  }
  for (auto iter = list_sum.begin(); iter != list_sum.end(); ++iter)
    {
      if (iter == list_sum.tail)
      {
        std::cout << *iter;
      }
      else
      {
        std::cout << *iter << ' ';
      }
    }
  std::cout << '\n';
}
