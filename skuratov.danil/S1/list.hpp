#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include "node.hpp"
#include "constIterators.hpp"

namespace skuratov
{
  template< typename T >
  class List
  {
    public:
      List():
        head(nullptr),
        tail(nullptr),
        size(0)
      {}

      ~List()
      {
        while (head != nullptr)
        {
          popFront();
        }
      }

      List(size_t n, const T & value_):
        head(nullptr),
        tail(nullptr),
        size(0)
      {
        for (size_t i = 0; i < n; ++i)
        {
          pushBack(value_);
        }
      }

      List< T > cbegin() noexcept
      {
        return ConstIterator< T >(head);
      }

      List< T > cend() noexcept
      {
        return ConstIterator< T >(nullptr);
      }

      T & front()
      {
        return head->value;
      }

      T & back()
      {
        return tail->value;
      }

      bool empty() const
      {
        return !size;
      }

      detail::Node< T >* pushFront(T value_)
      {
        detail::Node< T >* ptr = new detail::Node< T >(value_);
        ptr->next = head;
        if (head != nullptr)
        {
          head->prev = ptr;
        }
        if (tail == nullptr)
        {
          tail = ptr;
        }
        head = ptr;
        ++size;
        return ptr;
      }

      detail::Node< T >* pushBack(T value)
      {
        detail::Node< T >* ptr = new detail::Node< T >(value);
        ptr->prev = tail;
        if (tail != nullptr)
        {
          tail->next = ptr;
        }
        if (head == nullptr)
        {
          head = ptr;
        }
        tail = ptr;
        ++size;
        return ptr;
      }

      void popFront()
      {
        if (head == nullptr)
        {
          return;
        }
        detail::Node< T >* ptr = head->next;
        if (ptr != nullptr)
        {
          ptr->prev = nullptr;
        }
        else
        {
          tail = nullptr;
        }
        delete head;
        head = ptr;
        --size;
      }

      void popBack()
      {
        if (tail == nullptr)
        {
          return;
        }
        detail::Node< T >* ptr = tail->prev;
        if (ptr != nullptr)
        {
          ptr->next = nullptr;
        }
        else
        {
          head = nullptr;
        }
        delete tail;
        tail = ptr;
        --size;
      }

      void clear() noexcept
      {
        while (!empty())
        {
          popBack();
        }
        size = 0;
      }

      void assign(sizet n, const T& value)
      {
        clear();
        for (sizet i = 0; i < n; ++i)
        {
          push_back(value);
        }
      }

      void swap() noexcept
      {}

      void remove(const T& value)
      {}

      void remove_if()
      {}

      size_t getSize() const
      {
        return size;
      }

    private:
      detail::Node< T >* head;
      detail::Node< T >* tail;
      size_t size;
  };
}

#endif
