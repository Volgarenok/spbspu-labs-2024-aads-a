#ifndef LIST_HPP
#define LIST_HPP

#include "iterator.hpp"
#include "constIterator.hpp"
#include "biList.hpp"

namespace chistyakov
{
  template< typename T >
  class List
  {
    public:
      List():
        head_(nullptr),
        tail_(nullptr)
      {}

      List(biList < T > * head, biList < T > * tail)
        head_(head),
        tail_(tail)
      {}

      Iterator < T > begin()
      {
        return Iterator < T >(head_);
      }

      Iterator < T > end()
      {
        return Iterator < T >(nullptr);
      }

      constIterator < T > cbegin()
      {
        return constIterator < T >(head_);
      }

      constIterator < T > cend()
      {
        return constIterator < T >(nullptr);
      }

    private:
      biList < T > * head_;
      biList < T > * tail_;
  };
}
