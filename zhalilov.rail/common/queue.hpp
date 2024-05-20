#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list/list.hpp>

namespace zhalilov
{
  template < typename T, typename Container = List< T > >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue &);
    Queue(Queue &&) noexcept;

    ~Queue() = default;

    Queue &operator=(const Queue &);
    Queue &operator=(Queue &&) noexcept;

    T &front() noexcept;
    const T &front() const noexcept;
    T &back() noexcept;
    const T &back() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    void push(const T &);
    void push(T &&);

    template < typename... Args >
    void emplace(Args &&...);

    void pop();
    void swap(Queue &) noexcept;

  private:
    Container container_;
  };

  template < typename T, typename Container >
  Queue< T, Container >::Queue():
    container_()
  {}

  template < typename T, typename Container >
  Queue< T, Container >::Queue(const Queue &other):
    container_(other.container_)
  {}

  template < typename T, typename Container >
  Queue< T, Container >::Queue(Queue &&other) noexcept:
    container_(std::move(other.container_))
  {
    other.container_ = Container();
  }

  template < typename T, typename Container >
  Queue< T, Container > &Queue< T, Container >::operator=(const Queue &other)
  {
    container_ = other.container_;
    return *this;
  }

  template < typename T, typename Container >
  Queue< T, Container > &Queue< T, Container >::operator=(Queue &&other) noexcept
  {
    container_ = std::move(other.container_);
    other.container_ = Container();
    return *this;
  }

  template < typename T, typename Container >
  T &Queue< T, Container >::front() noexcept
  {
    return container_.front();
  }

  template < typename T, typename Container >
  const T &Queue< T, Container >::front() const noexcept
  {
    return container_.front();
  }

  template < typename T, typename Container >
  T &Queue< T, Container >::back() noexcept
  {
    return container_.back();
  }

  template < typename T, typename Container >
  const T &Queue< T, Container >::back() const noexcept
  {
    return container_.back();
  }

  template < typename T, typename Container >
  bool Queue< T, Container >::empty() const noexcept
  {
    return container_.empty();
  }

  template < typename T, typename Container >
  size_t Queue< T, Container >::size() const noexcept
  {
    return container_.capacity();
  }

  template < typename T, typename Container >
  void Queue< T, Container >::push(const T &value)
  {
    container_.push_back(value);
  }

  template < typename T, typename Container >
  void Queue< T, Container >::push(T &&value)
  {
    container_.push_back(std::move(value));
  }

  template < typename T, typename Container >
  template < typename... Args >
  void Queue< T, Container >::emplace(Args &&... args)
  {
    container_.emplace(std::forward< Args >(args)...);
  }

  template < typename T, typename Container >
  void Queue< T, Container >::pop()
  {
    container_.pop_front();
  }

  template < typename T, typename Container >
  void Queue< T, Container >::swap(Queue &other) noexcept
  {
    std::swap(container_, other.container_);
  }
}

#endif
