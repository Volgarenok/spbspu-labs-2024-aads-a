#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list/binList.hpp>
#include <queue>
#include <utility>
#include <iosfwd>

namespace arakelyan
{
  template < class T, class Container = BinList< T > >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue &otherQ);
    Queue(Queue &&otherQ) noexcept;

    ~Queue() = default;

    //operators?

    bool empty() const;
    size_t size() const;

    T &front();
    const T &front() const;

    T &back();
    const T &back() const;

    void push(const T &val);
    void push(T &&val);

    // template < class... Args >
    // void emplase(Args&&... args); // надо реализовать emplace для своего списка:(

    void pop();

    void swap(Queue &otherQ) noexcept;
  private:
    Container data_;
  };

  template < class T, class Container >
  Queue< T, Container >::Queue():
    data_()
  {}

  template < class T, class Container >
  Queue< T, Container >::Queue(const Queue &otherQ):
    data_(otherQ.data_)
  {}

  template < class T, class Container >
  Queue< T, Container>::Queue(Queue &&otherQ) noexcept:
    data_(std::move(otherQ.data_))
  {}

  template < class T, class Container >
  bool Queue< T, Container>::empty() const
  {
    return data_.empty();
  }

  template < class T, class Container >
  size_t Queue< T, Container >::size() const
  {
    return data_.get_size();
  }

  template < class T, class Container >
  T &Queue< T, Container >::front()
  {
    return data_.front();
  }

  template < class T, class Container >
  const T &Queue< T, Container >::front() const
  {
    return data_.front();
  }

  template < class T, class Container >
  T &Queue< T, Container >::back()
  {
    return data_.back();
  }

  template < class T, class Container >
  const T &Queue< T, Container >::back() const
  {
    return data_.back();
  }

  template < class T, class Container >
  void Queue< T, Container >::push(const T &val)
  {
    data_.push_back(val);
  }

  template < class T, class Container >
  void Queue< T, Container >::push(T &&val)
  {
    data_.push_back(std::move(val));
  }

  template < class T, class Container >
  void Queue< T, Container >::pop()
  {
    data_.pop_front();
  }

  template < class T, class Container >
  void Queue< T, Container >::swap(Queue &otherQ) noexcept
  {
    std::swap(data_, otherQ.data_);
  }
}
#endif
