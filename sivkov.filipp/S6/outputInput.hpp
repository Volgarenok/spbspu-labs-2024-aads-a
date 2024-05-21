#ifndef OUTPUTINPUT_HPP
#define OUTPUTINPUT_HPP

#include <ostream>
#include <string>
#include <deque>
#include <list>
#include <cstdlib>
#include <stdexcept>
#include <iomanip>
#include <list.hpp>

namespace sivkov
{
  template < typename T >
  void generateRandom(size_t numElements, const std::string& type, std::deque< T >& dq, List< T >& fwdList, std::list< T >& biList)
  {
    if (numElements <= 0)
    {
      throw std::invalid_argument("empty");
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    if (type == "ints" || type == "floats")
    {
      for (size_t i = 0; i < numElements; ++i)
      {
        T value;
        if (type == "ints")
        {
          std::uniform_int_distribution< int > dis(-228, 1337);
          value = dis(gen);
        }
        else if (type == "floats")
        {
          std::uniform_real_distribution< float > dis(0.0f, 99.9f);
          value = dis(gen);
        }
        dq.push_back(value);
        fwdList.push_back(value);
        biList.push_back(value);
      }
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

