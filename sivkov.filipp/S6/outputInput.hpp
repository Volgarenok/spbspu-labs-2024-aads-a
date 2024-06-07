#ifndef OUTPUTINPUT_HPP
#define OUTPUTINPUT_HPP

#include <ostream>
#include <string>
#include <deque>
#include <list>
#include <cstdlib>
#include <stdexcept>
#include <iomanip>
#include <random>
#include <list.hpp>

namespace sivkov
{
  template < typename T >
  void filRandom(size_t numElements, std::deque< T >& dq, List< T >& fwdList, std::list< T >& biList, std::mt19937& gen)
  {
    if (numElements == 0)
    {
      throw std::invalid_argument("error number elements");
    }
    if (std::is_same< T, int >::value)
    {
      std::uniform_int_distribution< int > dis(-100, 100);
      for (size_t i = 0; i < numElements; ++i)
      {
        T value = dis(gen);
        dq.push_back(value);
        fwdList.push_back(value);
        biList.push_back(value);
      }
    }
    else if (std::is_same< T, float >::value)
    {
      std::uniform_real_distribution< float > dis(0.0f, 99.9f);
      for (size_t i = 0; i < numElements; ++i)
      {
        T value = dis(gen);
        dq.push_back(value);
        fwdList.push_back(value);
        biList.push_back(value);
      }
    }
    else
    {
      throw std::invalid_argument("Unsupported type");
    }
  }

  template < typename T >
  void print(std::ostream& out, const T& con)
  {
    out << std::fixed << std::setprecision(1);
    out << *con.cbegin();
    for (auto it = ++con.cbegin(); it != con.cend(); ++it)
    {
      out << ' ' << *it;
    }
    out << '\n';
  }
}

#endif


