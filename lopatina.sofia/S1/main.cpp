#include <iostream>
#include <iterator>
#include <forward_list>
#include <string>
#include <utility>


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
struct List
{
  Node<T> * head;
  Node<T> * tail;

  List():
    head(nullptr),
    tail(nullptr)
    {}

  bool empty()
  {
    return head == nullptr;
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
    Node<T> * newhead = head->next;
    delete head;
    head = newhead;
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

 // std::iterator< std::forward_iterator_tag, T> begin() noexcept
//	{
//		return head;
//	}
};


//template <typename T>
//struct ListIterator:
//	public std::iterator<
//	std::forward_iterator_tag,
//	int
//	>
//{
//public:
//	ListIterator() :
//		node(nullptr)
//	{}
//	~ListIterator() = default;
//	ListIterator(const this_t &) = default;
//	this_t & operator=(const this_t &) = default;
//
//	this_t & operator++()
//	{
//		assert(node != nullptr);
//		node = node->next;
//		return *this;
//	}
//	this_t operator++(int)
//	{
//		assert(node != nullptr);
//		this_t result(*this);
//		++(*this);
//		return result;
//	}
//	T & operator*()
//	{
//		assert(node != nullptr);
//		return node->data;
//	}
//	T * operator->()
//	{
//		assert(node != nullptr);
//		return std::addressof(node->data);
//	}
//
//	T & operator*()
//	{
//		assert(node != nullptr);
//		return node->data;
//	}
//	T * operator->()
//	{
//		assert(node != nullptr);
//		return std::addressof(node->data);
//	}
//
//	bool operator!=(const this_t & rhs) const
//	{
//		return node == rhs.node;
//	}
//	bool operator==(const this_t & rhs) const
//	{
//		return !(rhs == *this);
//	}
//
//private:
//	List<T> * node;
//	using this_t = ListIterator<T>;
//};


int main()
{
	List<int> list;
	std::cout << list.empty() << '\n';
	list.push_back(60);
	list.push_back(89);
	list.push_back(3);
	std::cout << list.empty() << '\n';
	std::cout << list.head->data << '\n';
	list.pop_front();
	std::cout << list.head->data << '\n';
	list.clear();
	std::cout << list.empty() << '\n';
	list.push_back(1);

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
//	std::cout << *(first.begin()) << '\n';
}
