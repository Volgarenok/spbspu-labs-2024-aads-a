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
      Node * next;
      Node(T value):
        value(value),
        next(nullptr) {}
    };
    Node * head;

    public:
      List():
        head(nullptr) {}

      List(size_t count, const T & value):
        head(nullptr)
      {
        for (size_t i = 0; i < count; ++i)
        {
          push_back(value);
        }
      }

      List(const List< T > & other):
        head(nullptr)
      {
        Node * current = other.head;
        while (current)
        {
          push_back(current->value);
          current = current->next;
        }
      }

      List(const std::initializer_list< T > & ilist):
        head(nullptr)
      {
        for (const T & value: ilist)
        {
          push_back(value);
        }
      }

      ~List()
      {
        while (head)
        {
          Node * temp = head;
          head = head->next;
          delete temp;
        }
      }

      bool empty() const
      {
        return head == nullptr;
      }

      void push_back(T value)
      {
        Node * newNode = new Node(value);
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
      }

      void push_front(T value)
      {
        Node * newNode = new Node(value);
        newNode->next = head;
        head = newNode;
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
          return;
        }
        Node * current = head;
        while (current->next->next)
        {
          current = current->next;
        }
        delete current->next;
        current->next = nullptr;
      }

      void pop_front()
      {
        if (!head)
        {
          throw std::out_of_range("List is empty");
        }
        else
        {
          Node * temp = head;
          head = head->next;
          delete temp;
        }
      }

      void insert(size_t index, T value)
      {
        if (index == 0)
        {
          push_front(value);
        }
        Node * newNode = new Node(value);
        Node * current = head;
        for (size_t i = 0; i < index - 1 && current; ++i)
        {
          current = current->next;
        }
        if (!current)
        {
          throw std::out_of_range("Index out of range");
        }
        newNode->next = current->next;
        current->next = newNode;
      }

      void erase(size_t index)
      {
        if (index == 0)
        {
          pop_front();
        }
        Node * current = head;
        for (size_t i = 0; i < index - 1 && current; ++i)
        {
          current = current->next;
        }
        if (!current || !current->next)
        {
          throw std::out_of_range("Index out of range");
        }
        Node * temp = current->next;
        current->next = current->next->next;
        delete temp;
      }

      void remove(T value)
      {
        Node * current = head;
        Node * prev = nullptr;
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

      T & at(size_t index) const
      {
        Node * current = head;
        for (size_t i = 0; i < index && current; ++i)
        {
          current = current->next;
        }
        if (!current)
        {
          throw std::out_of_range("Index out of range");
        }
        return current->value;
      }

      size_t size() const
      {
        size_t count = 0;
        Node * current = head;
        while (current)
        {
          ++count;
          current = current->next;
        }
        return count;
      }

      bool operator==(const List< T > & other) const
      {
        Node * current1 = head;
        Node * current2 = other.head;
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

      bool operator!=(const List< T > & other) const
      {
        return !(* this == other);
      }

      bool operator<(const List< T > & other) const
      {
        Node * current1 = head;
        Node * current2 = other.head;
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

      bool operator<=(const List< T > & other) const
      {
        return * this < other || * this == other;
      }

      bool operator>(const List< T > & other) const
      {
        return !(* this <= other);
      }


      bool operator>=(const List< T > & other) const
      {
        return * this > other || * this == other;
      }
  };
}

#endif
