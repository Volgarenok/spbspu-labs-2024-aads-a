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
      bool isEmpty() const;
      void pop();
      void push(const T& value);
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
}

#endif
