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

#endif
