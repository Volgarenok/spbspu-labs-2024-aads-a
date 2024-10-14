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
    if (dataBase_.size() == 1)
    {
      dataBase_.clear();
    }
    else
    {
      typename List< T >::Node* newTail = dataBase_.head_;
      while (newTail->next_->next_ != nullptr)
      {
        newTail = newTail->next_;
      }
      delete newTail->next_;
      newTail->next_ = nullptr;
    }
    --dataBase_.size_;
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
