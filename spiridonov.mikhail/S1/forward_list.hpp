#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include <stdexcept>
#include <list>
#include "node.hpp"
#include "iterator.hpp"

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
    ~List();
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
    List<T>& operator=(const List<T>& other);
    bool operator!=(const List& other) const;
    bool operator<(const List& other) const;
    bool operator>(const List& other) const;
    bool operator<=(const List& other) const;
    bool operator>=(const List& other) const;
  };

  template <typename T>
  List<T>::List() : head(nullptr), tail(nullptr), size(0)
  {}

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

  template <typename T>
  List<T>::~List()
  {
    Node<T>* current = head;
    while (current != nullptr)
    {
      Node<T>* temp = current;
      current = current->next;
      delete temp;
    }
  }

  template<typename T>
  List<T>::List(const T& value, size_t count) : head(nullptr), tail(nullptr), size(0)
  {
    for (size_t i = 0; i < count; ++i)
    {
      push_back(value);
    }
  }

  template <typename T>
  List<T>::List(std::initializer_list<T> ilist) : head(nullptr), tail(nullptr), size(0)
  {
    for (const auto& value : ilist)
    {
      push_back(value);
    }
  }

  template <typename T>
  List<T>::List(iterator<T> first, iterator<T> last) : head(nullptr), tail(nullptr), size(0)
  {
    for (auto it = first; it != last; ++it)
    {
      push_back(*it);
    }
  }

  template <typename T>
  Node<T>* List<T>::get_head() const
  {
    return head;
  }

  template <typename T>
  void List<T>::push_back(const T& value)
  {
    Node<T>* newNode = new Node<T>(value, nullptr);
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

  template <typename T>
  bool List<T>::is_empty() const
  {
    return size == 0;
  }

  template <typename T>
  size_t List<T>::get_size() const
  {
    return size;
  }

  template <typename T>
  iterator<T> List<T>::begin() const
  {
    return iterator<T>(head);
  }

  template <typename T>
  iterator<T> List<T>::end() const
  {
    return iterator<T>(nullptr);
  }

  template <typename T>
  T List<T>::pop_back()
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

  template <typename T>
  T List<T>::pop_front()
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

  template <typename T>
  void List<T>::clear()
  {
    while (head)
    {
      Node<T>* nextNode = head->next;
      delete head;
      head = nextNode;
    }
    tail = nullptr;
    size = 0;
  }

  template <typename T>
  void List<T>::swap(int pos1, int pos2)
  {
    if (pos1 < 0 || pos1 >= size || pos2 < 0 || pos2 >= size)
    {
      throw std::out_of_range("Index out of bounds");
    }

    T& data1 = (*this)[pos1];
    T& data2 = (*this)[pos2];

    T temp = data1;
    data1 = data2;
    data2 = temp;
  }

  template< typename T >
  void List< T >::swap(List< T >& other)
  {
    std::swap(size, other.size);
    std::swap(head, other.head);
    std::swap(tail, other.tail);
  }

  template <typename T>
  void List<T>::insert(iterator<T> position, const T& value)
  {
    Node<T>* newNode = new Node<T>(value);

    if (position == end())
    {
      push_back(value);
    }
    else
    {
      Node<T>* current = position.current;
      newNode->next = current->next;
      current->next = newNode;
      size++;
    }
  }

  template <typename T>
  void List<T>::erase(iterator<T> position)
  {
    if (position == end())
    {
      throw std::out_of_range("Cannot erase end iterator");
    }

    Node<T>* current = position.current;

    if (current == head)
    {
      pop_front();
    }
    else
    {
      Node<T>* prev = head;
      while (prev->next != current)
      {
        prev = prev->next;
      }

      prev->next = current->next;
      delete current;
      size--;
    }
  }

  template <typename T>
  void List<T>::assign(std::initializer_list<T> ilist)
  {
    clear();

    for (const auto& value : ilist)
    {
      push_back(value);
    }
  }

  template<typename T>
  inline void List<T>::assign(iterator<T> first, iterator<T> last)
  {
    clear();

    for (iterator<T> it = first; it != last; ++it)
    {
      push_back(*it);
    }
  }

  template <typename T>
  void List<T>::splice(iterator<T> position, List<T>& other)
  {
    if (!other.is_empty())
    {
      if (position == end())
      {
        tail->next = other.head;
        tail = other.tail;
        size += other.size;

        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
      }
      else
      {
        Node<T>* current = position.current;

        other.tail->next = current->next;
        current->next = other.head;

        if (current == tail)
        {
          tail = other.tail;
        }

        size += other.size;

        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
      }
    }
  }

  template <typename T>
  void List<T>::reverse()
  {
    Node<T>* prevNode = nullptr;
    Node<T>* currentNode = head;

    while (currentNode != nullptr)
    {
      Node<T>* nextNode = currentNode->next;

      currentNode->next = prevNode;

      prevNode = currentNode;
      currentNode = nextNode;
    }

    tail = head;
    head = prevNode;
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
  List<T>& List<T>::operator=(const List& other)
  {
    if (this == &other)
    {
      return *this;
    }

    clear();

    Node<T>* temp = other.head;
    while (temp != nullptr)
    {
      push_back(temp->data);
      temp = temp->next;
    }

    return *this;
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

  template <typename T>
  void List<T>::remove(const T& value)
  {
    Node<T>* current = head;
    Node<T>* prev = nullptr;

    while (current != nullptr)
    {
      if (current->data == value)
      {
        if (prev == nullptr)
        {
          pop_front();
          current = head;
        }
        else
        {
          prev->next = current->next;
          delete current;
          current = prev->next;
          size--;
        }
      }
      else
      {
        prev = current;
        current = current->next;
      }
    }
  }

  template <typename T>
  template <typename UnaryPredicate>
  void List<T>::remove_if(UnaryPredicate p)
  {
    Node<T>* current = head;
    Node<T>* prev = nullptr;

    while (current != nullptr)
    {
      if (p(current->data))
      {
        if (prev == nullptr)
        {
          pop_front();
          current = head;
        }
        else
        {
          prev->next = current->next;
          delete current;
          current = prev->next;
          size--;
        }
      }
      else
      {
        prev = current;
        current = current->next;
      }
    }
  }

  template <typename T>
  void List<T>::assign(const T& value, size_t count)
  {
    clear();

    for (size_t i = 0; i < count; ++i)
    {
      push_back(value);
    }
  }

}

#endif
