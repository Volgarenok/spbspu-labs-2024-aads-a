#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <utility>
#include <list/binList.hpp>

namespace arakelyan
{
  template < class T >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue &otherQ);
    Queue(Queue &&otherQ) noexcept;
    ~Queue() = default;

    Queue &operator=(const Queue &otherQ);
    Queue &operator=(Queue &&otherQ) noexcept;

    bool empty() const;
    size_t size() const;

    T &front();
    const T &front() const;

    T &back();
    const T &back() const;

    void push(const T &val);
    void push(T &&val);

    void pop();

    void swap(Queue &otherQ) noexcept;
  private:
    BinList< T > data_;
  };

  template < class T >
  Queue< T >::Queue():
    data_()
  {}

  template < class T >
  Queue< T >::Queue(const Queue &otherQ):
    data_(otherQ.data_)
  {}

  template < class T >
  Queue< T >::Queue(Queue &&otherQ) noexcept:
    data_(std::move(otherQ.data_))
  {}

  template < class T >
  Queue< T > &Queue< T >::operator=(const Queue &otherQ)
  {
    data_ = otherQ.data_;
    return *this;
  }

  template < class T >
  Queue< T > &Queue< T >::operator=(Queue &&otherQ) noexcept
  {
    data_ = otherQ.data_;
    return *this;
  }

  template < class T >
  bool Queue< T >::empty() const
  {
    return data_.empty();
  }

  template < class T >
  size_t Queue< T >::size() const
  {
    return data_.get_size();
  }

  template < class T >
  T &Queue< T >::front()
  {
    return data_.front();
  }

  template < class T >
  const T &Queue< T >::front() const
  {
    return data_.front();
  }

  template < class T >
  T &Queue< T >::back()
  {
    return data_.back();
  }

  template < class T >
  const T &Queue< T >::back() const
  {
    return data_.back();
  }

  template < class T >
  void Queue< T >::push(const T &val)
  {
    data_.push_back(val);
  }

  template < class T >
  void Queue< T >::push(T &&val)
  {
    data_.push_back(std::move(val));
  }

  template < class T >
  void Queue< T >::pop()
  {
    data_.pop_front();
  }

  template < class T >
  void Queue< T >::swap(Queue &otherQ) noexcept
  {
    std::swap(data_, otherQ.data_);
  }
}
#endif
