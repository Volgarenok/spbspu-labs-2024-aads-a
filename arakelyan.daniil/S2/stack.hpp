#ifndef STACK_HPP
#define STACK_HPP

#include <utility>
#include <list/binList.hpp>

namespace arakelyan
{
  template < class T >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack &otherS);
    Stack(Stack &&otherS) noexcept;
    ~Stack() = default;

    Stack &operator=(const Stack &otherS);
    Stack &operator=(Stack &&otherS) noexcept;

    bool empty() const;
    size_t size() const;

    T &top();
    const T &top() const;

    void push(const T &val);
    void push(T &&val);

    void pop();

    void swap(Stack &otherS) noexcept;
  private:
    BinList< T > data_;
  };

  template < class T >
  Stack< T >::Stack():
    data_()
  {}

  template < class T >
  Stack< T >::Stack(const Stack &otherS):
    data_(otherS.data_)
  {}

  template < class T >
  Stack< T >::Stack(Stack &&otherS) noexcept:
    data_(std::move(otherS.data_))
  {}

  template < class T >
  Stack< T > &Stack< T >::operator=(const Stack &otherS)
  {
    data_ = otherS.data_;
    return *this;
  }

  template < class T >
  Stack< T > &Stack< T >::operator=(Stack &&otherS) noexcept
  {
    data_ = std::move(otherS.data_);
    return *this;
  }

  template < class T >
  bool Stack< T >::empty() const
  {
    return data_.empty();
  }

  template < class T >
  size_t Stack< T >::size() const
  {
    return data_.get_size();
  }

  template < class T >
  T &Stack< T >::top()
  {
    return data_.front();
  }

  template < class T >
  const T &Stack< T >::top() const
  {
    return data_.front();
  }

  template < class T >
  void Stack< T >::push(const T &val)
  {
    data_.push_front(val);
  }

  template < class T >
  void Stack< T >::push(T &&val)
  {
    data_.push_front(std::move(val));
  }

  template < class T >
  void Stack< T >::pop()
  {
    data_.pop_front();
  }

  template < class T >
  void Stack< T >::swap(Stack &otherS) noexcept
  {
    std::swap(data_, otherS.data_);
  }
}
#endif
