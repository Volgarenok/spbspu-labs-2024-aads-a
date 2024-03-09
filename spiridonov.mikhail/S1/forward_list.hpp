#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include "node.hpp"
#include <stdexcept>

namespace spiridonov
{
  template <typename T>
  class List
  {
  public:
    class iterator;

  private:
    Node<T>* head;
    Node<T>* tail;
    size_t size = 0;

  public:
    List() : head(nullptr), tail(nullptr), size(0)
    {}

    ~List()
    {
      while (head != nullptr)
      {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
      }
    }

    Node<T>* get_head() const
    {
      return head;
    }

    void push_back(const T& value)
    {
      Node<T>* newNode = new Node<T>(value);
      if (head == nullptr)
      {
        head = newNode;
        tail = newNode;
      }
      else
      {
        tail->next = newNode;
        tail = newNode;
      }
      size++;
    }

    bool is_empty() const
    {
      return size == 0;
    }

    int get_size() const
    {
      return size;
    }

    class iterator
    {
    private:
      Node<T>* current;

    public:
      iterator(Node<T>* node) : current(node)
      {}

      iterator& operator++()
      {
        if (current) current = current->next;
        return *this;
      }

      bool operator==(const iterator& other) const
      {
        return current == other.current;
      }

      bool operator!=(const iterator& other) const
      {
        return current != other.current;
      }

      T& operator*() const
      {
        return current->data;
      }

      T* operator->() const
      {
        return &(current->data);
      }
    };

    iterator begin() const
    {
      return iterator(head);
    }

    iterator end() const
    {
      return iterator(nullptr);
    }

    T pop_back()
    {
      if (is_empty())
        throw std::out_of_range("Trying to pop from an empty sequence");

      T value;
      if (head == tail)
      {
        value = tail->data;
        delete tail;
        head = nullptr;
        tail = nullptr;
      }
      else
      {
        Node<T>* temp = head;
        while (temp->next != tail)
        {
          temp = temp->next;
        }
        value = tail->data;
        delete tail;
        tail = temp;
        tail->next = nullptr;
      }
      size--;
      return value;
    }

    T pop_front()
    {
      if (is_empty())
        throw std::out_of_range("Trying to pop from an empty sequence");

      T value = head->data;
      Node<T>* temp = head;
      head = head->next;
      delete temp;
      size--;

      if (head == nullptr)
        tail = nullptr;

      return value;
    }
    T& operator[](int index)
    {
      if (index < 0 || index >= size)
      {
        throw std::out_of_range("Index out of bounds");
      }

      Node<T>* current = head;
      for (int i = 0; i < index; i++)
      {
        current = current->next;
      }

      return current->data;
    }
  };

  struct NamedList
  {
    std::string name;
    List<int> list;
  };
}

#endif
