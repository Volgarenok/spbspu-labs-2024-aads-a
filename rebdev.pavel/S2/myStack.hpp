#ifndef MYSTACK_HPP
#define MYSTACH_HPP

#include <list>
#include <cstddef>

namespace rebdev
{
  template < class T >
  class Stack
  {
    public:
      void push(T data)
      {
        dataBase_.push_back(data);
      }
      T drop()
      {
        T backData = dataBase_.back();
        dataBase_.pop_back();
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
