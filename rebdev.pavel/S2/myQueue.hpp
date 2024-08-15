#ifndef MYQUEUE_HPP
#define MYQUEUE_HPP

#include <cstddef>
#include <stdexcept>

#include "../common/list.hpp"

namespace rebdev
{
  template < class T >
  class Queue
  {
    public:
      Queue() = default;
      Queue(const Queue & queue) = default;
      Queue(Queue && queue) = default;

      ~Queue() = default;

      Queue & operator=(const Queue & queue) = default;
      Queue & operator=(Queue && rhQueue) = default;

      void push(T data)
      {
        dataBase_.push_back(data);
      }
      T drop()
      {
        if (dataBase_.size() == 0)
        {
          throw std::logic_error("Try to take and delete element from empty queue!");
        }

        T backData = dataBase_.front();
        dataBase_.pop_front();

        return backData;
      }
      size_t size() const noexcept
      {
        return dataBase_.size();
      }
      bool empty() const noexcept
      {
        return dataBase_.empty();
      }

    private:
      BiList< T > dataBase_;
  };
}

#endif
