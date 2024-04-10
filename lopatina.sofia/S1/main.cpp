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

  bool operator==(const this_t & rhs) const
  {
    return node == rhs.node;
  }
  bool operator!=(const this_t & rhs) const
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
  T & back()
  {
    return tail->data;
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
/*
  template <class Predicate>
  void remove_if (Predicate pred)
  {
    Node<T> * newptr = head;
    while (newptr)
    {
      Node<T> *
    }
  }
*/
  void assign(size_t n, const T & val)
  {
    clear();
    for (size_t i = 0; i < n; ++i)
    {
      push_back(val);
    }
  }

//
  void print()
  {
    Node<T> * subhead = head;
    while (subhead)
    {
      std::cout << subhead->data << ' ';
      subhead = subhead->next;
    }
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
  List<std::pair<std::string,List<size_t>>> list;
  std::string name = "";
  std::string num_str = "";
  size_t number = 0;
  size_t max_size = 0;
  while (std::cin >> name)
  {
    size_t loc_size = 0;
    List<size_t> list_num;
    std::getline(std::cin,num_str);
    size_t sz = 0;
    while (!num_str.empty())
    {
      number = 0;
      number = std::stoull(num_str,&sz);
      num_str = num_str.substr(sz);
      list_num.push_back(number);
      loc_size += 1;
    }
    list.push_back(std::make_pair(name, list_num));
    if (loc_size > max_size)
    {
      max_size = loc_size;
    }
  }

  for (auto iter = list.begin(); iter != list.end(); ++iter)
  {
    std::cout << (*iter).first << ' ';
  }
  std::cout << '\n';

  List<size_t> list_sum;
  for (size_t i = 0; i < max_size; ++i)
  {
    size_t sum = 0;
    for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
      List<size_t> sub_list = (*iter).second;
      size_t size = 0;
      for (auto sub_iter = sub_list.begin(); sub_iter != sub_list.end(); ++sub_iter)
      {
        if (size == i)
        {
          sum += *sub_iter;
          std::cout << *sub_iter << ' ';
        }
        ++size;
      }
    }
    std::cout << '\n';
    list_sum.push_back(sum);
  }
  list_sum.print();
  std::cout << '\n';
}
