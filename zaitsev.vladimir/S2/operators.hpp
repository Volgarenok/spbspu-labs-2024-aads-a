#ifndef OPERATORS_HPP
#define OPERATORS_HPP
#include <iostream>
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace zaitsev
{
  template<typename T>
  struct BinaryOperator
  {
    virtual size_t priority() const = 0;
    virtual T operator()(const T& a, const T& b) const = 0;
    virtual BinaryOperator<T>* clone() const = 0;
    virtual std::ostream& operator<<(std::ostream& output) = 0;
    friend std::ostream& operator<<(std::ostream& output, const BinaryOperator<T>& object)
    {
      object.operator<<(output);
      return output;
    }
  };

  template<typename T>
  struct SafePlus: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value == true, "Type not integer");
    virtual size_t priority() const
    {
      return 1;
    }
    virtual T operator()(const T& a, const T& b) const
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
    virtual BinaryOperator<T>* clone() const
    {
      return new SafePlus<T>();
    }
    virtual std::ostream& operator<<(std::ostream& output)
    {
      output << '+';
      return output;
    }
  };

  template<typename T>
  struct SafeMinus: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value == true, "Type not integer");
    virtual size_t priority() const
    {
      return 1;
    }
    virtual T operator()(const T& a, const T& b) const
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
    virtual BinaryOperator<T>* clone() const
    {
      return new SafeMinus<T>();
    }
    virtual std::ostream&  operator<<(std::ostream& output)
    {
      output << '-';
      return output;
    }
  };

  template<typename T>
  struct SafeDivision: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value == true, "Type not integer");
    virtual size_t priority() const
    {
      return 2;
    }
    virtual T operator()(const T& a, const T& b) const
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
    virtual BinaryOperator<T>* clone() const
    {
      return new SafeDivision<T>();
    }
    virtual std::ostream& operator<<(std::ostream& output)
    {
      output << '/';
      return output;
    }
  };

  template<typename T>
  struct SafeMod: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value == true, "Type not integer");
    virtual size_t priority() const
    {
      return 2;
    }
    virtual T operator()(const T& a, const T& b) const
    {
      if (b == 0 || a == std::numeric_limits<T>::lowest() && b == -1)
      {
        throw std::runtime_error("Mod overflow");
      }
      return a % b;
    }
    virtual BinaryOperator<T>* clone() const
    {
      return new SafeMod<T>;
    }
    virtual std::ostream& operator<<(std::ostream& output)
    {
      output << '%';
      return output;
    }
  };

  template<typename T>
  struct SafeMultiplication: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value == true, "Type not integer");
    virtual size_t priority() const
    {
      return 2;
    }
    virtual T operator()(const T& a, const T& b) const
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
    virtual BinaryOperator<T>* clone() const
    {
      return new SafeMultiplication<T>();
    }
    virtual std::ostream& operator<<(std::ostream& output)
    {
      output << '*';
      return output;
    }
  };
}
#endif
