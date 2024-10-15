#ifndef INPUT_OUTPUT_HPP
#define INPUT_OUTPUT_HPP
#include <iostream>
#include <list>
#include <deque>
#include <random>
#include "list.hpp"

namespace sakovskaia
{
  template < typename T >
  void fill(std::deque< T > & deque, List< T > & fwdList, std::list< T > & biList, std::mt19937 & rnmd, size_t count, std::string & type)
  {
    if (count == 0)
    {
      throw std::invalid_argument("count = 0");
    }
    if (type == "ints")
    {
      std::uniform_int_distribution< int > nums(-500, 500);
      for (size_t i = 0; i < count; ++i)
      {
        T value = nums(rnmd);
        fwdList.push_back(value);
        biList.push_back(value);
        deque.push_back(value);
      }
    }
    else if ("floats")
    {
      std::uniform_real_distribution< float > nums(0.0f, 99.9f);
      for (size_t i = 0; i < count; ++i)
      {
        T value = nums(rnmd);
        fwdList.push_back(value);
        biList.push_back(value);
        deque.push_back(value);
      }
    }
  }
}
#endif
