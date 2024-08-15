#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <limits>
#include <list>

template < typename T >
class Queue
{
public:
  Queue()
  {
    queue_list;
  }
  ~Queue() = default;
  bool empty() const
  {
    return queue_list.empty();
  }
  size_t size() const
  {
    return queue_list.size();
  }
  T & front()
  {
    return queue_list.front();
  }
  const T & front() const
  {
    return queue_list.front();
  }
  T & back()
  {
    return queue_list.back();
  }
  const T & back() const
  {
    return queue_list.back();
  }
  void push(const T & rhs)
  {
    queue_list.push_back(rhs);
  }
  void pop()
  {
    queue_list.pop_front();
  }
private:
  std::list<T> queue_list;
};

template < typename T >
class Stack
{
public:
  Stack()
  {
    stack_list;
  }
  ~Stack() = default;
  bool empty() const
  {
    return stack_list.empty();
  }
  size_t size() const
  {
    return stack_list.size();
  }
  T & top()
  {
    return stack_list.back();
  }
  const T & top() const
  {
    return stack_list.back();
  }
  void push(const T & rhs)
  {
    stack_list.push_back(rhs);
  }
  void pop()
  {
    stack_list.pop_back();
  }
private:
  std::list<T> stack_list;
};

//--------------------

void inputExpression(std::istream & in, Queue<char> & queue_source)
{
  char c = 0;
  while (in >> c)
  {
    if (c == '\n')
    {
      return;
    }
    queue_source.push(c);
  }
}

int main(int argc, char ** argv)
{
  Queue<char> queue_source;
  Queue<char> queue_result;
  Stack<char> stack_process;

  if (argc == 1)
  {
    while (!std::cin.eof())
    {
      inputExpression(std::cin, queue_source);
    }
  }

/*
  if (argc == 1)
  {
    std::copy(
        std::istream_iterator<int>{std::cin},
        std::istream_iterator<int>{},
        std::back_inserter(ints)
      );
      if (!std::cin && !std::cin.eof())
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
  }
  else if (argc == 2)
  {
    std::ifstream input(argv[1]);
    while (!input.eof())
    {
      std::copy(
        std::istream_iterator<int>{input},
        std::istream_iterator<int>{},
        std::back_inserter(ints)
      );
      if (!input && !input.eof())
      {
        input.clear();
        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
  }
*/

  while (!queue_source.empty())
  {
    std::cout << queue_source.front() << ' ';
    queue_source.pop();
  }
  std::cout << '\n';
}
