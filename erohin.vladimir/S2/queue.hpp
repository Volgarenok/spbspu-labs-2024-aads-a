#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include <list>

namespace
{
  template< class T, class Container = std::list< T > >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue & stack);
    Queue(Queue && stack);
    template< class InputIt >
    Queue(InputIt first, InputIt last);
    explicit Queue(const Container & cont);
    explicit Queue(Container && cont);
    ~Queue();
    Queue & operator=(const Queue & other);
    Queue & operator=(Queue && other);
    T & front();
    const T & front() const;
    T & back();
    const T & back() const;
    bool empty();
    size_t size();
    void push(const T & value);
    void push(T && value);
    template< class... Args >
    void emplace(Args&&... args);
    void pop();
    void swap(Queue & other) noexcept;
  private:
    Container container_;
  };

  template< class T, class Container >
  Queue< T, Container >::Queue(const Queue & stack):
    container_(stack.container_)
  {}

  template< class T, class Container >
  Queue< T, Container >::Queue(Queue && stack):
    container_(stack.container_)
  {}

  template< class T, class Container >
  template< class InputIt >
  Queue< T, Container >::Queue(InputIt first, InputIt last):
    container_(Container(first, last))
  {}

  template< class T, class Container >
  Queue< T, Container >::Queue(const Container & cont):
    container_(cont)
  {}

  template< class T, class Container >
  Queue< T, Container >::Queue(Container && cont):
    container_(std::move(cont))
  {}

  template< class T, class Container >
  Queue< T, Container >::~Queue() = default;

  template< class T, class Container >
  Queue< T, Container > & Queue< T, Container >::operator=(const Queue & other)
  {
    if (*this != &other)
    {
      Queue< T, Container > temp(other);
      swap(temp);
    }
    return *this;
  }

  template< class T, class Container >
  Queue< T, Container > & Queue< T, Container >::operator=(Queue && other)
  {
    if (*this != &other)
    {
      Queue< T, Container > temp(std::move(other));
      swap(temp);
    }
    return *this;
  }

  template< class T, class Container >
  T & Queue< T, Container >::front()
  {
    return container_.front();
  }

  template< class T, class Container >
  const T & Queue< T, Container >::front() const
  {
    return container_.front();
  }

  template< class T, class Container >
  T & Queue< T, Container >::back()
  {
    return container_.back();
  }

  template< class T, class Container >
  const T & Queue< T, Container >::back() const
  {
    return container_.back();
  }

  template< class T, class Container >
  bool Queue< T, Container >::empty()
  {
    return container_.empty();
  }

  template< class T, class Container >
  size_t Queue< T, Container >::size()
  {
    return container_.size();
  }

  template< class T, class Container >
  void Queue< T, Container >::push(const T & value)
  {
    container_.push_back(value);
  }

  template< class T, class Container >
  void Queue< T, Container >::push(T && value)
  {
    container_.push_back(std::move(value));
  }

  template< class T, class Container >
  template< class... Args >
  void Queue< T, Container >::emplace(Args &&... args)
  {
    container_.emplace_back(std::forward< Args... >(args...));
  }

  template< class T, class Container >
  void Queue<T, Container>::pop()
  {
    container_.pop_back();
  }

  template< class T, class Container >
  void Queue<T, Container>::swap(Queue<T, Container> & rhs) noexcept
  {
    container_.swap(rhs);
  }

  template< class T, class Container >
  void swap(Queue<T, Container> & lhs, Queue<T, Container> & rhs) noexcept
  {
    lhs.swap(rhs);
  }

  template< class T, class Container >
  bool operator==(const Queue<T, Container> & lhs, const Queue<T, Container> & rhs)
  {
    return (lhs.container_ == rhs.container_);
  }

  template< class T, class Container >
  bool operator!=(const Queue<T, Container> & lhs, const Queue<T, Container> & rhs)
  {
    return (lhs.container_ != rhs.container_);
  }

  template< class T, class Container >
  bool operator<(const Queue<T, Container> & lhs, const Queue<T, Container> & rhs)
  {
    return (lhs.container_ < rhs.container_);
  }

  template< class T, class Container >
  bool operator<=(const Queue<T, Container> & lhs, const Queue<T, Container> & rhs)
  {
    return (lhs.container_ <= rhs.container_);
  }

  template< class T, class Container >
  bool operator>(const Queue<T, Container> & lhs, const Queue<T, Container> & rhs)
  {
    return (lhs.container_ > rhs.container_);
  }

  template< class T, class Container >
  bool operator>=(const Queue<T, Container> & lhs, const Queue<T, Container> & rhs)
  {
    return (lhs.container_ >= rhs.container_);
  }
}

#endif
