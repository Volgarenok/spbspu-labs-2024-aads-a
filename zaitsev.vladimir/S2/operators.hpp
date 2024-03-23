#ifndef OPERATORS_HPP
#define OPERATORS_HPP
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace zaitsev
{
  template<typename T>
  struct BinaryOperator
  {
    constexpr size_t priority() const = 0;
    T operator()(const T& a, const T& b) const = 0;
  };

  template<typename T>
  struct SafePlus: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value == true, "Type not integer");
    constexpr size_t priority()
    {
      return 1;
    }
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
  struct SafeMinus: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value == true, "Type not integer");
    constexpr size_t priority()
    {
      return 1;
    }
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
  struct SafeDivision: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value == true, "Type not integer");
    constexpr size_t priority()
    {
      return 2;
    }
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
  struct SafeMod: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value == true, "Type not integer");
    constexpr size_t priority()
    {
      return 2;
    }
    T operator()(const T& a, const T& b) const
    {
      if (b == 0 || a == std::numeric_limits<T>::lowest() && b == -1) 
      {
        throw std::runtime_error("Mod overflow");
      }
      return a % b;
    }
  };

  template<typename T>
  struct SafeMultiplication: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value == true, "Type not integer");
    constexpr size_t priority()
    {
      return 2;
    }
    T operator()(const T& a, const T& b) const
    {
      if (a == 0 || b == 0)
        return 0;
      //когда-нибудь тут что-то будет
      if (a > 0 && b > 0 && std::numeric_limits<T>::max() / b < a )
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
