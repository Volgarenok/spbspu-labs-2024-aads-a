#ifndef STACK_HPP
#define STACK_HPP
#include <list>

namespace strelyaev
{
  template< typename T >
  class stack
  {
    public:
      stack() = default;
      stack(const stack< T >&) = default;
      stack(stack< T >&&);
      ~stack() = default;

      void push(const T&);
      T& back();
      const T& back() const;
      T& front();
      const T& front() const;
      bool empty();
      T drop();

      stack< T >& operator=(const stack< T >&) = default;
      stack< T >& operator=(const stack< T >&&);
    private:
      std::list< T > data;
  };

  template< typename T >
  stack< T >::stack(stack< T >&& other):
    data(std::move(other.data))
  {}

  template< typename T >
  stack< T >& stack< T >::operator=(const stack< T >&& other)
  {
    if (std::addressof(other) != this)
    {
      std::swap(data, other.data);
      other.data.clear();
    }
    return *this;
  }

  template< typename T >
  void stack< T >::push(const T& value)
  {
    data.push_back(value);
  }

  template< typename T >
  T& stack< T >::back()
  {
    return data.back();
  }

  template< typename T >
  const T& stack< T >::back() const
  {
    return data.back();
  }

  template< typename T >
  T& stack< T >::front()
  {
    return data.front();
  }

  template< typename T >
  const T& stack< T >::front() const
  {
    return data.front();
  }

  template< typename T >
  bool stack< T >::empty()
  {
    return data.empty();
  }

  template< typename T >
  T stack< T >::drop()
  {
    T value = data.back();
    data.pop_back();
    return value;
  }

}
#endif
