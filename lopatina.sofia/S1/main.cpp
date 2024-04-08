#include <iostream>
#include <cstddef>
#include <iterator>
#include <forward_list>
#include <string>
#include <utility>
#include <assert.h>

template<typename T>
struct Node
{
  T data;
  Node<T> * next;

  Node(T _data):
    data(_data),
    next(nullptr)
  {}
};

template <typename T>
struct ListIterator: public std::iterator<std::forward_iterator_tag,T>
{
public:
  using this_t = ListIterator<T>;
  ListIterator():
    node(nullptr)
  {}
  ListIterator(Node<T> * node):
    node(node)
  {}
  ~ListIterator() = default;

  ListIterator(const this_t &) = default;
  this_t & operator=(const this_t &) = default;
  this_t & operator++()
  {
    assert(node != nullptr);
    node = node->next;
    return *this;
  }
  this_t operator++(int)
  {
    assert(node != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }
  T & operator*()
  {
    assert(node != nullptr);
    return node->data;
  }
  T * operator->()
  {
    assert(node != nullptr);
    return std::addressof(node->data);
  }

  bool operator!=(const this_t & rhs) const
  {
    return node == rhs.node;
  }
  bool operator==(const this_t & rhs) const
  {
    return !(rhs == *this);
  }

private:
  Node<T> * node;
};

template <typename T>
struct List
{
  Node<T> * head;
  Node<T> * tail;

  List():
    head(nullptr),
    tail(nullptr)
  {}

  explicit List(size_t n, const T & val):
    head(nullptr),
    tail(nullptr)
  {
    for (size_t i = 0; i < n; ++i)
    {
      push_back(val);
    }
  }

//1
  T & front()
  {
    return head->data;
  }
  bool empty() const noexcept
  {
    return head == nullptr;
  }
  void push_front(T value)
  {
    Node<T> * newptr = new Node<T>(value);
    newptr->next = head;
    head = newptr;
    if (tail == nullptr)
    {
      tail = newptr;
    }
  }
  void push_back(T value)
  {
    Node<T> * newptr = new Node<T>(value);
    if (empty())
    {
      head = newptr;
      tail = newptr;
      return;
    }
    tail->next = newptr;
    tail = newptr;
  }
  void pop_front()
  {
    if (head == nullptr)
    {
      return;
    }
    if (head == tail)
    {
      delete tail;
      head = nullptr;
      tail = nullptr;
      return;
    }
    Node<T> * newhead = head->next;
    delete head;
    head = newhead;
  }
  void pop_back()
  {
    if (tail == nullptr)
    {
      return;
    }
    if (head == tail)
    {
      delete tail;
      head = nullptr;
      head = nullptr;
      return;
    }
    Node<T> * newptr = head;
    while (newptr->next != tail)
    {
      newptr = newptr->next;
    }
    newptr->next = nullptr;
    delete tail;
    tail = newptr;
  }
  void clear() noexcept
  {
    Node<T> * newhead = head;
    while (newhead)
    {
      newhead = head->next;
      delete head;
      head = newhead;
    }
  }
  void swap(List & list2)
  {
    Node<T> * subhead = head;
    Node<T> * subtail = tail;
    head = list2.head;
    tail = list2.tail;
    list2.head = subhead;
    list2.tail = subtail;
  }

//2
  void remove(const T & val)
  {
    if (head == nullptr)
    {
      return;
    }
    if (head == tail)
    {
      if (head->data == val)
      {
        pop_back();
      }
      return;
    }
    Node<T> * subhead = head;
    Node<T> * todelete = head;
    while (subhead)
    {
      if ((subhead == head) && (subhead->data == val))
      {
        subhead = subhead->next;
        pop_front();
      }
      else
      {
        if (subhead->next)
        {
          todelete = subhead->next;
          if (todelete->data == val)
          {
            subhead->next = todelete->next;
            delete todelete;
          }
          else
          {
            subhead = subhead->next;
          }
        }
        else
        {
          subhead = subhead->next;
        }
      }
    }
  }

  void assign(size_t n, const T & val)
  {
  }

//
  void print()
  {
    std::cout << "PRINT LIST: ";
    Node<T> * subhead = head;
    while (subhead)
    {
      std::cout << subhead->data << ' ';
      subhead = subhead->next;
    }
    std::cout << '\n';
  }

  ListIterator<T> begin()
  {
    return ListIterator<T>(head);
  }
  ListIterator<T> end()
  {
    return ListIterator<T>();
  }
};


int main()
{
  List<int> list;
  std::cout << list.empty() << '\n';
  list.push_back(60);
  list.print();
  list.push_back(89);
  list.push_back(3);
  std::cout << list.empty() << '\n';
  std::cout << list.head->data << '\n';
  list.pop_front();
  std::cout << list.head->data << '\n';
  list.clear();
  std::cout << list.empty() << '\n';
  list.push_front(-1);
  list.print();
  list.push_back(1);
  list.push_front(-2);
  list.print();
  std::cout << "FRONT: " << list.front() << '\n';
  list.clear();
  //std::cout << "Empty FRONT: " << list.front() << '\n';
  list.push_front(1);
  list.pop_front();
  list.push_front(11);
  list.push_front(111);
  list.print();
  list.pop_back();
  list.print();
  std::cout << "LIST EMPTY: " << list.empty() << '\n';

  List<int> first;
  first.push_back(1);
  first.push_back(2);
  //first.push_back(3);
  List<int> second;
  second.push_back(11);
  second.push_back(22);
  second.push_back(33);
  first.print();
  first.swap(second);
  first.print();
  second.print();
  std::cout << "O: " << first.empty() << ' ' << second.empty() << '\n';
  ListIterator<int> ptr = first.begin();
  std::cout << *ptr << '\n';
  std::cout << *(second.begin()) << '\n';
  std::cout << *(++(second.begin())) << '\n';
  std::cout << "TEST FOR ITER: \n";
  for (ListIterator<int> it = second.begin(); it != nullptr; ++it)
  {
    std::cout << *it << '\n';
  }
  ListIterator<int> iter = second.begin();
  std::cout << *(++iter) << '\n';
  while (iter != nullptr)
  {
    std::cout << *iter << '\n';
    ++iter;
  }
//------
  List<int> fill_list(3, 77);
  fill_list.print();
  fill_list.push_front(78);
  fill_list.print();
  fill_list.remove(77);
  fill_list.print();
  List<int> list2(2, 55);
  list2.print();
  list2.remove(55);
  list2.print();
  list2.push_back(1);
  list2.print();
  list2.remove(1);
  list2.print();
  list2.push_back(3);
  list2.push_front(2);
  list2.push_back(1);
  list2.push_back(2);
  list2.print();
  list2.remove(2);
  list2.print();
  list2.remove(1);
  list2.remove(9999);
  list2.print();
  list2.remove(3);
  list2.print();
  list2.remove(1);
  list2.print();
}
