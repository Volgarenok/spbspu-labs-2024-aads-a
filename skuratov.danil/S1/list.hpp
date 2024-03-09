#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "cstddef"

namespace skuratov
{
  template <typename T>
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
        pop_front();
      }
    }

    Node<T>* push_front(T value)
    {
      Node<T>* ptr = new Node<T>(value);
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

    Node<T>* push_back(T value)
    {
      Node<T>* ptr = new Node<T>(value);
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

    void pop_front()
    {
      if (head == nullptr)
      {
        return;
      }
      Node<T>* ptr = head->next;
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

    void pop_back()
    {
      if (tail == nullptr)
      {
        return;
      }
      Node<T>* ptr = tail->prev;
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

    Node<T>* getAt(size_t index)
    {
      Node<T>* ptr = head;
      for (size_t j = 0; j != index; j++)
      {
        if (ptr == nullptr)
        {
          return ptr;
        }
        ptr = ptr->next;
      }
      return ptr;
    }

    Node<T>* operator [] (int index)
    {
      return getAt(index);
    }

    Node<T>* insert(int index, double value)
    {
      Node<T>* right = getAt(index);
      if (right == nullptr)
      {
        return push_back(value);
      }
      Node<T>* left = right->prev;
      if (left == nullptr)
      {
        return push_front(value);
      }
      Node<T>* ptr = new Node<T>(value);
      ptr->prev = left;
      ptr->next = right;
      left->prev = ptr;
      right->next = ptr;
      ++size;
      return ptr;
    }

    void erase(int index)
    {
      Node<T>* ptr = getAt(index);
      if (ptr == nullptr)
      {
        return;
      }
      if (ptr->prev == nullptr)
      {
        pop_front();
        return;
      }
      if (ptr->next == nullptr)
      {
        pop_back();
        return;
      }
      Node<T>* left = ptr->prev;
      Node<T>* right = ptr->next;
      left->next = right;
      right->prev = left;
      delete ptr;
      --size;
    }

    size_t getSize() const
    {
      return size;
    }

  private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;
  };
}

#endif
