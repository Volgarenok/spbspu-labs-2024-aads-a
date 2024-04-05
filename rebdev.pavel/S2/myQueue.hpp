#ifndef MYQUEUE_HPP
#define MYQUEUE_HPP

#include <list>

namespace rebdev
{
  template < class T >
  class Queue
  {
    public:
      void push(T data)
      {
        dataBase_.push_back(data);
      }
      T drop()
      {
        T backData = dataBase_.front();
        dataBase_.pop_front();
        return backData;
      }
      size_t size() const noexcept
      {
        return dataBase_.size();
      }

    private:
      std::list< T > dataBase_;
  };
}

#endif
