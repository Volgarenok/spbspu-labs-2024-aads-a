#ifndef QUEUE_H
#define QUEUE_h

#include <list.hpp>

namespace stepanov
{
  template < typename T >
  class Queue
  {
  public:
    Queue() = default;
    ~Queue() = default;
    Queue(const Queue & queue) = default;
    Queue(Queue && queue) = default;
    Queue & operator=(const Queue & queue) = default;
    Queue & operator=(Queue && rhQueue) = default;

    void pushFront(const T& newHead);
    void popBack();
    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    const T& getHead() const ;
    const T& getTail() const;
  private:
    List< T > dataBase_;
  };
}

template < typename T >
void stepanov::Queue< T >::pushFront(const T& newHead)
{
  dataBase_.push_front(newHead);
}

template < typename T >
void stepanov::Queue< T >::popBack()
{
  if (!isEmpty())
  {
    dataBase_.pop_back();
  }
}

template < typename T >
bool stepanov::Queue< T >::isEmpty() const noexcept
{
  return dataBase_.empty();
}

template < typename T >
size_t stepanov::Queue< T >::getSize() const noexcept
{
  return dataBase_.size();
}

template < typename T >
const T& stepanov::Queue< T >::getHead() const
{
  return dataBase_.front();
}

template < typename T >
const T& stepanov::Queue< T >::getTail() const
{
  return dataBase_.getBack();
}

#endif
