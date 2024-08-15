#ifndef MYSTACK_HPP
#define MYSTACH_HPP

#include <cstddef>
#include <stdexcept>

#include "../common/list.hpp"

namespace rebdev
{
  template < class T >
  class Stack
  {
    public:
      Stack() = default;
      Stack(const Stack & stack) = default;
      Stack(Stack && stack) = default;

      ~Stack() = default;

      Stack & operator=(const Stack & stack) = default;
      Stack & operator=(Stack && rhStack) = default;

      void push(T data)
      {
        dataBase_.push_back(data);
      }
      T drop()
      {
        if (dataBase_.size() == 0)
        {
          throw std::logic_error("Try to take and delete element from empty stack!");
        }

        T backData = dataBase_.back();
        dataBase_.pop_back();

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
