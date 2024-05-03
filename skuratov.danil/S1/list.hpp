#ifndef LIST_HPP
#define LIST_HPP

#
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

      List(const T& value, size_t n):
        head(nullptr),
        tail(nullptr),
        size(0)
      {
        for (size_t i = 0; i < n; ++i)
        {
          pushBack(value);
        }
      }

      List(const List& diff):
        head(nullptr),
        tail(nullptr),
        size(0)
      {
        try
        {
          detail::Node<T>* current = diff.head;
          while (current)
          {
            pushBack(current->value_);
            current = current->next;
          }
        }
        catch (...)
        {
          clear();
          throw;
        }
      }

      List& operator=(const List& diff)
      {
        if (this == &diff)
        {
          return *this;
        }
        clear();
      }

      List(List&& diff) noexcept:
        head(diff.head),
        tail(diff.tail),
        size(diff.size)
      {
        diff.head = nullptr;
        diff.tail = nullptr;
        diff.size = 0;
      }

      List& operator=(List&& diff)
      {
        if (this != &diff)
        {
          clear();
          swap(diff);
        }
        return *this;
      }

      ConstIterator< T > cbegin() const noexcept
      {
        return ConstIterator< T >(head);
      }

      ConstIterator< T > cend() const noexcept
      {
        return ConstIterator< T >(nullptr);
      }

      T & front()
      {
        return head->value_;
      }

      T & back()
      {
        return tail->value_;
      }

      bool empty() const noexcept
      {
        return !size;
      }

      void pushFront(const T& value)
      {
        detail::Node< T >* ptr = new detail::Node< T >(value);
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

      void pushBack(const T& value)
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

      void assign(size_t n, const T& value)
      {
        clear();
        for (size_t i = 0; i < n; ++i)
        {
          push_back(value);
        }
      }

      void swap(List& diff) noexcept
      {
        std::swap(head, diff.head);
        std::swap(tail, diff.tail);
        std::swap(size, diff.size);
      }

      void remove(const T& value)
      {
        detail::Node< T > dummyNode(0);
        dummyNode.next = head;
        detail::Node< T >* prev = &dummyNode;
        detail::Node< T >* current = head;

        while (current)
        {
          if (current->data == value)
          {
            prev->next = current->next;
            delete current;
            current = prev->next;
          }
          else
          {
            prev = current;
            current = current->next;
          }
        }
        head = dummyNode.next;
      }

      template< typename UnaryPredicate >
      void removeIf(UnaryPredicate predicate)
      {
        detail::Node< T > dummyNode(0);
        dummyNode.next = head;
        detail::Node< T >* prev = &dummyNode;
        detail::Node< T >* current = head;

        while (current)
        {
          if (predicate(current->value_))
          {
            prev->next = current->next;
            delete current;
            current = prev->next;
          }
          else
          {
            prev = current;
            current = current->next;
          }
        }
        head = dummyNode.next;
      }

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
