#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include <stdexcept>
#include "node.hpp"
#include "iterator.hpp"
#include <list>

namespace spiridonov
{
  template <typename T>
  class List
  {
  private:
    Node<T>* head;
    Node<T>* tail;
    size_t size = 0;

  public:
    List();
    List(const List<T>& other);
    List(const T& value, size_t count);
    List(std::initializer_list<T> ilist);
    List(iterator<T> first, iterator<T> last);

    Node<T>* get_head() const;
    void push_back(const T& value);
    void clear();
    void swap(int pos1, int pos2);
    void swap(List<T>& other);
    void fill(const T& value, size_t count);
    void remove(const T& value);
    template <typename UnaryPredicate>
    void remove_if(UnaryPredicate p);
    void assign(const T& value, size_t count);
    void insert(iterator<T> position, const T& value);
    void erase(iterator<T> position);
    void assign(std::initializer_list<T> ilist);
    void assign(iterator<T> first, iterator<T> last);
    void splice(iterator<T> position, List<T>& other);
    void reverse();

    bool is_empty() const;
    size_t get_size() const;
    iterator<T> begin() const;
    iterator<T> end() const;
    T pop_back();
    T pop_front();

    T& operator[](size_t index);
    bool operator==(const List& other) const;
    bool operator!=(const List& other) const;
    bool operator<(const List& other) const;
    bool operator>(const List& other) const;
    bool operator<=(const List& other) const;
    bool operator>=(const List& other) const;
  };

  template <typename T>
  List<T>::List() : head(nullptr), tail(nullptr), size(0) {}

  template <typename T>
  List<T>::List(const List& other) : head(nullptr), tail(nullptr), size(0)
  {
    Node<T>* current = other.head;

    while (current != nullptr)
    {
      push_back(current->data);
      current = current->next;
    }
  }

  Node<T>* get_head() const
  {
    return head;
  }

  /*void push_back(const T& value)
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
*/

  bool is_empty() const
  {
    return size == 0;
  }

  int get_size() const
  {
    return size;
  }
  template<typename T>
  T& List<T>::operator[](size_t index)
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

  template <typename T>
  bool List<T>::operator==(const List& other) const
  {
    if (size != other.size)
    {
      return false;
    }

    Node<T>* current = head;
    Node<T>* otherCurrent = other.head;

    while (current != nullptr)
    {
      if (current->data != otherCurrent->data)
      {
        return false;
      }

      current = current->next;
      otherCurrent = otherCurrent->next;
    }

    return true;
  }

  template <typename T>
  bool List<T>::operator!=(const List& other) const
  {
    return !(*this == other);
  }

  template <typename T>
  bool List<T>::operator<(const List& other) const
  {
    Node<T>* current = head;
    Node<T>* otherCurrent = other.head;

    while (current != nullptr && otherCurrent != nullptr)
    {
      if (current->data < otherCurrent->data)
      {
        return true;
      }
      else if (current->data > otherCurrent->data)
      {
        return false;
      }

      current = current->next;
      otherCurrent = otherCurrent->next;
    }

    return size < other.size;
  }

  template <typename T>
  bool List<T>::operator>(const List& other) const
  {
    return (other < *this);
  }

  template <typename T>
  bool List<T>::operator<=(const List& other) const
  {
    return !(other < *this);
  }

  template <typename T>
  bool List<T>::operator>=(const List& other) const
  {
    return !(*this < other);
  }

  template <typename T>
  void List<T>::fill(const T& value, size_t count)
  {
    *this = List<T>(value, count);
  }

  /*  T pop_back()
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

};
*/
}

#endif
