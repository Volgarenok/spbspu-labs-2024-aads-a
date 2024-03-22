#ifndef OPERATORS_HPP
#define OPERATORS_HPP
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace zaitsev
{
  template<typename T>
  struct safe_plus
  {
    static_assert(std::is_integral<T>::value == true, "Type not integer");
    T operator()(const T& a, const T& b) const
    {
      if (a >= 0 && std::numeric_limits<T>::max() - a < b)
      {
        throw std::runtime_error("Sum overflow");
      }
      if (a < 0 && std::numeric_limits<T>::lowest() - a < b)
      {
        throw std::runtime_error("Sum underflow");
      }
      return a + b;
    }
  };

  template<typename T>
  struct safe_minus
  {
    static_assert(std::is_integral<T>::value == true, "Type not integer");
    T operator()(const T& a, const T& b) const
    {
      if (b < 0 && std::numeric_limits<T>::max() + b < a)
      {
        throw std::runtime_error("Difference overflow");
      }
      if (b >= 0 && std::numeric_limits<T>::lowest() + b > a)
      {
        throw std::runtime_error("Difference underflow");
      }
      return a - b;
    }
  };

  template<typename T>
  struct safe_division
  {
    static_assert(std::is_integral<T>::value == true, "Type not integer");
    T operator()(const T& a, const T& b) const
    {
      if (b == 0)
      {
        throw std::runtime_error("Zero division");
      }
      if (b < 0 && a < 0 && a == std::numeric_limits<T>::lowest() && b == -1)
      {
        throw std::runtime_error("Division overflow");
      }
      return a / b;
    }
  };

  template<typename T>
  struct safe_multiplies
  {
    static_assert(std::is_integral<T>::value == true, "Type not integer");
    T operator()(const T& a, const T& b) const
    {
      if (a == 0 || b == 0)
        return 0;
      //когда-нибудь тут что-то будет
      if (a > 0 && b > 0 && std::numeric_limits<T>::max() / b <= a && std::numeric_limits<T>::max() % b > 0)
      {

      }
      if (a < 0 && b < 0 && std::numeric_limits<T>::max() / b <= a && std::numeric_limits<T>::max() % b > 0)
      {

      }
      return a * b;
    }
  };
}
#endif
