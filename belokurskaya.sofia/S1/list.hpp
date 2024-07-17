#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <stdexcept>

namespace belokurskaya
{
  template< class T >
  class List
  {
    struct Node
    {
      T value;
      Node* next;
      Node(const T& value):
        value(value),
        next(nullptr)
      {}
    };
    Node* head;
    size_t list_size;

    public:
      List():
        head(nullptr), list_size(0)
      {}

      List(size_t count, const T& value):
        head(nullptr),
        list_size(0)
      {
        try
        {
          for (size_t i = 0; i < count; ++i)
          {
            push_back(value);
          }
        }
        catch (...)
        {
          clear();
          throw;
        }
      }

      List(const List< T >& other):
        head(nullptr),
        list_size(0)
      {
        try
        {
          Node* current = other.head;
          while (current)
          {
            push_back(current->value);
            current = current->next;
          }
        }
        catch (...)
        {
          clear();
          throw;
        }
      }

      List(List< T >&& other) noexcept:
        head(other.head),
        list_size(other.list_size)
      {
        other.head = nullptr;
        other.list_size = 0;
      }

      List(const std::initializer_list< T >& ilist):
        head(nullptr),
        list_size(0)
      {
        try
        {
          for (const T& value : ilist)
          {
            push_back(value);
          }
        }
        catch (...)
        {
          clear();
          throw;
        }
      }

      ~List()
      {
        clear();
      }

      class Iterator: public std::iterator< std::forward_iterator_tag, T >
      {
        private:
          Node* current;

        public:
          using pointer = T*;
          using reference = T&;

          Iterator():
            current(nullptr)
          {}

          reference operator*() const
          {
            return current->value;
          }

          pointer operator->() const
          {
            return std::addressof(current->value);
          }

          Iterator& operator++()
          {
            current = current->next;
            return *this;
          }

          Iterator operator++(int)
          {
            Iterator result = *this;
            ++(*this);
            return result;
          }

          bool operator!=(const Iterator& other) const
          {
            return current != other.current;
          }

          bool operator==(const Iterator& other) const
          {
            return current == other.current;
          }

        private:
          friend class List;
          explicit Iterator(Node* node):
            current(node)
          {}
      };

      Iterator begin()
      {
        return Iterator(head);
      }

      Iterator end()
      {
        return Iterator(nullptr);
      }

      class ConstIterator: public std::iterator< std::forward_iterator_tag, const T >
      {
        private:
          const Node* current;
          friend class List;
          explicit ConstIterator(const Node* node):
            current(node)
          {}

        public:
          using pointer = const T*;
          using reference = const T&;

          ConstIterator():
            current(nullptr)
          {}

          reference operator*() const
          {
            return current->value;
          }

          pointer operator->() const
          {
            return std::addressof(current->value);
          }

          ConstIterator& operator++()
          {
            current = current->next;
            return *this;
          }

          ConstIterator operator++(int)
          {
            ConstIterator result = *this;
            ++(*this);
            return result;
          }

          bool operator!=(const ConstIterator& other) const
          {
            return current != other.current;
          }

          bool operator==(const ConstIterator& other) const
          {
            return current == other.current;
          }
      };

      ConstIterator begin() const
      {
        return ConstIterator(head);
      }

      ConstIterator end() const
      {
        return ConstIterator(nullptr);
      }

      void clear()
      {
        while (head)
        {
          Node* temp = head;
          head = head->next;
          delete temp;
        }
        list_size = 0;
      }

      bool empty() const noexcept
      {
        return head == nullptr;
      }

      void push_back(const T& value)
      {
        Node* newNode = new Node(value);
        if (!head)
        {
          head = newNode;
        }
        else
        {
          Node* current = head;
          while (current->next)
          {
            current = current->next;
          }
          current->next = newNode;
        }
        ++list_size;
      }

      void push_front(const T& value)
      {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        ++list_size;
      }

      void pop_back()
      {
        if (!head)
        {
          throw std::out_of_range("List is empty");
        }
        if (!head->next)
        {
          delete head;
          head = nullptr;
        }
        else
        {
          Node* current = head;
          while (current->next->next)
          {
            current = current->next;
          }
          delete current->next;
          current->next = nullptr;
        }
        --list_size;
      }

      void pop_front()
      {
        if (!head)
        {
          throw std::out_of_range("List is empty");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        --list_size;
      }

      void erase(Iterator pos)
      {
        if (pos == end())
        {
          throw std::out_of_range("Iterator is out of range");
        }

        if (pos == begin())
        {
          pop_front();
        }
        else
        {
          Node* current = head;
          while (current && current->next != pos.current)
          {
            current = current->next;
          }
          if (!current)
          {
            throw std::out_of_range("Index out of range");
          }
          Node* temp = current->next;
          current->next = current->next->next;
          delete temp;
          --list_size;
        }
      }

      void remove(const T& value)
      {
        Node* current = head;
        Node* prev = nullptr;
        while (current)
        {
          if (current->value == value)
          {
            if (current == head)
            {
              pop_front();
              current = head;
            }
            else
            {
              prev->next = current->next;
              delete current;
              current = prev->next;
            }
          }
          else
          {
            prev = current;
            current = current->next;
          }
        }
      }

      size_t size() const noexcept
      {
        return list_size;
      }

      List& operator=(List other) noexcept
      {
        swap(*this, other);
        return *this;
      }

      friend void swap(List& first, List& second) noexcept
      {
        std::swap(first.head, second.head);
        std::swap(first.list_size, second.list_size);
      }

      bool operator==(const List< T >& other) const noexcept
      {
        Node* current1 = head;
        Node* current2 = other.head;
        while (current1 && current2)
        {
          if (current1->value != current2->value)
          {
            return false;
          }
          current1 = current1->next;
          current2 = current2->next;
        }
        return !current1 && !current2;
      }

      bool operator!=(const List< T >& other) const noexcept
      {
        return !(*this == other);
      }

      bool operator<(const List< T >& other) const noexcept
      {
        Node* current1 = head;
        Node* current2 = other.head;
        while (current1 && current2)
        {
          if (current1->value != current2->value)
          {
            return current1->value < current2->value;
          }
          current1 = current1->next;
          current2 = current2->next;
        }
        return current2 != nullptr;
      }

      bool operator<=(const List< T >& other) const noexcept
      {
        return *this < other || *this == other;
      }

      bool operator>(const List< T >& other) const noexcept
      {
        return !(*this <= other);
      }

      bool operator>=(const List< T >& other) const noexcept
      {
        return *this > other || *this == other;
      }
  };
}

#endif
