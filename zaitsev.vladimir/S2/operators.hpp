#ifndef OPERATORS_HPP
#define OPERATORS_HPP
#include <ostream>
#include <limits>
#include <cmath>
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
    virtual std::ostream& operator<<(std::ostream& output) const = 0;
    virtual ~BinaryOperator() = default;
    friend std::ostream& operator<<(std::ostream& output, const BinaryOperator<T>& object)
    {
      object.operator<<(output);
      return output;
    }
  };

  template<typename T>
  struct SafePlus: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value, "Type not integer");
    virtual ~SafePlus() = default;
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
    virtual std::ostream& operator<<(std::ostream& output) const
    {
      output << '+';
      return output;
    }
  };

  template<typename T>
  struct SafeMinus: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value, "Type not integer");
    virtual ~SafeMinus() = default;
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
    virtual std::ostream&  operator<<(std::ostream& output) const
    {
      output << '-';
      return output;
    }
  };

  template<typename T>
  struct SafeDivision: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value, "Type not integer");
    virtual ~SafeDivision() = default;
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
    virtual std::ostream& operator<<(std::ostream& output) const
    {
      output << '/';
      return output;
    }
  };

  template<typename T>
  struct SafeMod: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value, "Type not integer");
    virtual ~SafeMod() = default;
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
      return (a % b >= 0) ? a % b : a % b + b;
    }
    virtual BinaryOperator<T>* clone() const
    {
      return new SafeMod<T>;
    }
    virtual std::ostream& operator<<(std::ostream& output) const
    {
      output << '%';
      return output;
    }
  };

  template<typename T>
  struct SafeMultiplication: public BinaryOperator<T>
  {
    static_assert(std::is_integral<T>::value, "Type not integer");
    virtual ~SafeMultiplication() = default;
    virtual size_t priority() const
    {
      return 2;
    }
    virtual T operator()(const T& a, const T& b) const
    {
      T max_val = std::numeric_limits<T>::max();
      T min_val = std::numeric_limits<T>::lowest();
      if ((a < 0 && b == min_val) || (a == min_val && b < 0))
      {
        throw std::runtime_error("Multiplication overflow");
      }

      if ((a > 0 && b > 0 || a < 0 && b < 0)
          && (max_val / std::abs(b) < std::abs(a)
          || (max_val / std::abs(b) == std::abs(a) && max_val / std::abs(b) != 0)))
      {
        throw std::runtime_error("Multiplication overflow");
      }
      T min_mult = std::min(a, b);
      T max_mult = std::max(a, b);
      if ((a < 0 && b > 0 || a > 0 && b < 0)
          && (min_val / max_mult != min_mult
          || (min_val / max_mult == min_mult && min_val / max_mult != 0)))
      {
        throw std::runtime_error("Multiplication overflow");
      }
      return a * b;
    }
    virtual BinaryOperator<T>* clone() const
    {
      return new SafeMultiplication<T>();
    }
    virtual std::ostream& operator<<(std::ostream& output) const
    {
      output << '*';
      return output;
    }
  };
}
#endif
