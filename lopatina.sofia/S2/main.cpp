#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
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

bool isDigit(char c)
{
  return (c >= '0' && c <= '9');
}

bool isArithmetic(char c)
{
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

enum TypeName
{
  OPERAND,
  OPERATION,
  OPEN_BRACKET,
  CLOSE_BRACKET
};

struct InfixType
{
public:
  InfixType() = default;
  InfixType(long long val, TypeName name);
  InfixType(char val, TypeName name);
  ~InfixType() = default;
  TypeName getType() const;
  long long getNumber() const;
  char getSymbol() const;
private:
  long long number_;
  char symbol_;
  TypeName type_;
};

InfixType::InfixType(long long val, TypeName name):
  number_(val),
  symbol_(0),
  type_(name)
{}
InfixType::InfixType(char val, TypeName name):
  number_(0),
  symbol_(val),
  type_(name)
{}

TypeName InfixType::getType() const
{
  return type_;
}
long long InfixType::getNumber() const
{
  return number_;
}
char InfixType::getSymbol() const
{
  return symbol_;
}

struct PostfixType
{
public:
  PostfixType() = default;
  explicit PostfixType(long long val);
  explicit PostfixType(char val);
  ~PostfixType() = default;
private:
  long long number_;
  char symbol_;
  TypeName type_;
};
PostfixType::PostfixType(long long val):
  number_(val),
  symbol_(0),
  type_(TypeName::OPERAND)
{}
PostfixType::PostfixType(char val):
  number_(0),
  symbol_(val),
  type_(TypeName::OPERATION)
{}

void inputExpression(std::istream & in, Queue<InfixType> & queue_source)
{
  char c = 0;
  std::string num_str = "";
  in >> std::noskipws;
  while (in >> c)
  {
    if (c == '\n')
    {
      if (!num_str.empty())
      {
        long long num = std::stoll(num_str);
        InfixType elem{num, TypeName::OPERAND};
        queue_source.push(elem);
      }
      in >> std::skipws;
      return;
    }
    if (isDigit(c))
    {
      num_str += c;
    }
    else if (c == ' ')
    {
      if (!num_str.empty())
      {
        long long num = std::stoll(num_str);
        InfixType elem{num, TypeName::OPERAND};
        queue_source.push(elem);
        num_str = "";
      }
    }
    else if (c == '(')
    {
      InfixType elem{c, TypeName::OPEN_BRACKET};
      queue_source.push(elem);
    }
    else if (c == ')')
    {
      InfixType elem{c, TypeName::CLOSE_BRACKET};
      queue_source.push(elem);
    }
    else if (isArithmetic(c))
    {
      InfixType elem{c, TypeName::OPERATION};
      queue_source.push(elem);
    }
    else
    {
      in >> std::skipws;
      throw std::invalid_argument("Invalid expression element");
    }
  }
}

bool isLowerPriority(const InfixType & lhs, const InfixType & rhs)
{
  int priority_lhs = 1, priority_rhs = 1;
  char symbol_lhs = lhs.getSymbol();
  char symbol_rhs = rhs.getSymbol();
  if (symbol_lhs == '+' || symbol_lhs == '-')
  {
    priority_lhs = 0;
  }
  if (symbol_rhs == '+' || symbol_rhs == '-')
  {
    priority_rhs = 0;
  }
  return priority_lhs < priority_rhs;
}

Queue<PostfixType> convertToPostfix(Queue<InfixType> & queue_source)
{
  Queue<PostfixType> queue_result;
  Stack<InfixType> stack_process;

  while (!queue_source.empty())
  {
    InfixType infix_elem = queue_source.front();
    if (infix_elem.getType() == OPEN_BRACKET)
    {
      stack_process.push(infix_elem);
    }
    else if (infix_elem.getType() == OPERAND)
    {
      PostfixType postfix_elem{infix_elem.getNumber()};
      queue_result.push(postfix_elem);
    }
    else if (infix_elem.getType() == CLOSE_BRACKET)
    {
      if (stack_process.empty())
      {
        throw std::logic_error("Wrong math expression");
      }
      InfixType elem_stack = stack_process.top();
      while (elem_stack.getType() != OPEN_BRACKET)
      {
        if (stack_process.empty())
        {
          throw std::logic_error("Wrong math expression");
        }
        PostfixType postfix_elem{elem_stack.getSymbol()};
        queue_result.push(postfix_elem);
        stack_process.pop();
        elem_stack = stack_process.top();
      }
      stack_process.pop();
    }
    else if (infix_elem.getType() == OPERATION)
    {
      while (!stack_process.empty())
      {
        InfixType elem_stack = stack_process.top();
        if (elem_stack.getType() == OPERATION && !isLowerPriority(elem_stack, infix_elem))
        {
          PostfixType postfix_elem{elem_stack.getSymbol()};
          queue_result.push(postfix_elem);
          stack_process.pop();
        }
        else
        {
          break;
        }
      }
      stack_process.push(infix_elem);
    }
    queue_source.pop();
  }
  while (!stack_process.empty())
  {
    InfixType elem_stack = stack_process.top();
    if (elem_stack.getType() == OPERATION)
    {
      PostfixType postfix_elem{elem_stack.getSymbol()};
      queue_result.push(postfix_elem);
      stack_process.pop();
    }
    else
    {
      throw std::logic_error("Wrong math expression");
    }
  }
  return queue_result;
}

int main(int argc, char ** argv)
{
  Queue<InfixType> queue_source;
  Queue<char> queue_result;
  Stack<char> stack_process;
  try
  {
    if (argc == 1)
    {
      while (!std::cin.eof())
      {
        inputExpression(std::cin, queue_source);
      }
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
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
/*
  std::cout << queue_source.empty() << '\n';

  while (!queue_source.empty())
  {
    std::cout << queue_source.front() << ' ';
    queue_source.pop();
  }
  std::cout << '\n';
*/
}
