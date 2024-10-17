#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdexcept>
#include <list.hpp>

namespace agarkov
{
  template< typename T >
  class Queue
  {
    public:
      Queue();
      ~Queue();
      Queue(const Queue< T >& other);
      Queue< T >& operator=(const Queue< T >& other);
      bool isEmpty() const;
      void pop();
      void clear();
      void push(const T& value);
      T get() const;
    private:
      details::List< T >* begin_;
      details::List< T >* end_;
  };

  template< typename T >
  Queue< T >::Queue():
    begin_(nullptr),
    end_(nullptr)
  {}

  template< typename T >
  Queue< T >::~Queue()
  {
    clear();
  }

  template< typename T >
  Queue< T >::Queue(const Queue< T >& other):
    begin_(nullptr),
    end_(nullptr)
  {
    try
    {
      details::List< T >* curent = other.begin_;
      while (curent != nullptr)
      {
        push(curent->data_);
        curent = curent->next_;
      }
    }
    catch (...)
    {
      clear();
      throw;
    }
  }

  template< typename T >
  Queue< T >& Queue< T >::operator=(const Queue< T >& other)
  {
    if (this != std::addressof(other))
    {
      Queue< T > temp(other);
      std::swap(begin_, temp.begin_);
      std::swap(end_, temp,end_);
    }
    return *this;
  }

  template< typename T >
  bool Queue< T >::isEmpty() const
  {
    return (begin_ == nullptr);
  }

  template< typename T >
  void Queue< T >::pop()
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty queue");
    }
    if (begin_ == end_)
    {
      delete begin_;
      begin_ = nullptr;
      end_ = nullptr;
    }
    else
    {
      details::List< T >* temp = begin_->next_;
      delete begin_;
      begin_ = temp;
    }
  }

  template < typename T >
  void Queue< T >::clear()
  {
    while (!isEmpty())
    {
      pop();
    }
  }

  template< typename T >
  void Queue< T >::push(const T& value)
  {
    details::List< T >* temp = new details::List< T >{value, nullptr};
    if (isEmpty())
    {
      begin_ = temp;
    }
    else
    {
      end_->next_ = temp;
    }
    end_ = temp;
  }

  template< typename T >
  T Queue< T >::get() const
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty queue");
    }
    return begin_->data_;
  }

}

#endif
