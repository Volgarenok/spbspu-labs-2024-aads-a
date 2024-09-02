#ifndef STACK_HPP
#define STACK_HPP

#include <list/list.hpp>

namespace zhalilov
{
  template < typename T, typename Container = List< T > >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack &);
    Stack(Stack &&) noexcept;

    ~Stack() = default;

    Stack &operator=(const Stack &);
    Stack &operator=(Stack &&) noexcept;

    T &top() noexcept;
    const T &top() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    void push(const T &);
    void push(T &&);

    template < typename... Args >
    void emplace(Args &&...);

    void pop();
    void swap(Stack &) noexcept;

  private:
    Container container_;
  };

  template < typename T, typename Container >
  Stack< T, Container >::Stack():
    container_()
  {}

  template < typename T, typename Container >
  Stack< T, Container >::Stack(const Stack &other):
    container_(other.container_)
  {}

  template < typename T, typename Container >
  Stack< T, Container >::Stack(Stack &&other) noexcept:
    container_(std::move(other.container_))
  {
    other.container_ = Container();
  }

  template < typename T, typename Container >
  Stack< T, Container > &Stack< T, Container >::operator=(const Stack &other)
  {
    container_ = other.container_;
    return *this;
  }

  template < typename T, typename Container >
  Stack< T, Container > &Stack< T, Container >::operator=(Stack &&other) noexcept
  {
    container_ = std::move(other.container_);
    other.container_ = Container();
    return *this;
  }

  template < typename T, typename Container >
  T &Stack< T, Container >::top() noexcept
  {
    return container_.back();
  }

  template < typename T, typename Container >
  const T &Stack< T, Container >::top() const noexcept
  {
    return container_.back();
  }

  template < typename T, typename Container >
  bool Stack< T, Container >::empty() const noexcept
  {
    return container_.empty();
  }

  template < typename T, typename Container >
  size_t Stack< T, Container >::size() const noexcept
  {
    return container_.capacity();
  }

  template < typename T, typename Container >
  void Stack< T, Container >::push(const T &value)
  {
    container_.push_back(value);
  }

  template < typename T, typename Container >
  void Stack< T, Container >::push(T &&value)
  {
    container_.push_back(std::move(value));
  }

  template < typename T, typename Container >
  template < typename... Args >
  void Stack< T, Container >::emplace(Args &&... args)
  {
    container_.emplace(std::forward< Args >(args)...);
  }

  template < typename T, typename Container >
  void Stack< T, Container >::pop()
  {
    container_.pop_back();
  }

  template < typename T, typename Container >
  void Stack< T, Container >::swap(Stack &other) noexcept
  {
    std::swap(container_, other.container_);
  }
}

#endif
