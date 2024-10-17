#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace agarkov
{
  template< typename T >
  class Queue
  {
    public:
      Queue();
      bool isEmpty() const;
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
  bool Queue< T >::isEmpty() const
  {
    return (begin_ == nullptr);
  }
}

#endif
