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
  TypeName getType() const;
  long long getOperand() const;
  char getOperation() const;
private:
  long long operand_;
  char operation_;
  TypeName type_;
};
PostfixType::PostfixType(long long val):
  operand_(val),
  operation_(0),
  type_(TypeName::OPERAND)
{}
PostfixType::PostfixType(char val):
  operand_(0),
  operation_(val),
  type_(TypeName::OPERATION)
{}
TypeName PostfixType::getType() const
{
  return type_;
}
long long PostfixType::getOperand() const
{
  return operand_;
}
char PostfixType::getOperation() const
{
  return operation_;
}

void inputExpression(std::istream & in, Queue<InfixType> & queue_source)
{
  char c = 0;
  std::string num_str = "";
  in >> std::noskipws;
  while (in >> c)
  {
    if (c == '\n')
    {
      if (queue_source.empty())
      {
        return;
      }
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

//--------

bool isAdditionOverflow(long long num1, long long num2)
{
  const long long max = std::numeric_limits<long long>::max();
  const long long min = std::numeric_limits<long long>::min();
  if (num1 > 0 && num2 > 0 && (max - num1 < num2))
  {
    return true;
  }
  if (num1 < 0 && num2 < 0 && (min - num1 > num2))
  {
    return true;
  }
  return false;
}

bool isSubtractionOverflow(long long num1, long long num2)
{
  return isAdditionOverflow(num1, - num2);
}

bool isMultiplicationOverflow(long long num1, long long num2)
{
  if (num1 == 0 || num2 == 0)
  {
    return false;
  }
  const long long max = std::numeric_limits<long long>::max();
  if (std::abs(num1) > max / std::abs(num2))
  {
    return true;
  }
  return false;
}

long long calculatePostfix(Queue<PostfixType> & queue_postfix)
{
  Stack<long long> stack_process;

  while (!queue_postfix.empty())
  {
    PostfixType elem = queue_postfix.front();
    if (elem.getType() == OPERAND)
    {
      stack_process.push(elem.getOperand());
    }
    else if (elem.getType() == OPERATION)
    {
      if (stack_process.empty())
      {
        throw std::logic_error("Wrong math expression");
      }
      long long num2 = stack_process.top();
      stack_process.pop();
      if (stack_process.empty())
      {
        throw std::logic_error("Wrong math expression");
      }
      long long num1 = stack_process.top();
      stack_process.pop();
      char operation = elem.getOperation();
      if (operation == '+')
      {
        if (isAdditionOverflow(num1, num2))
        {
          throw std::logic_error("Overflow during addition");
        }
        stack_process.push(num1 + num2);
      }
      else if (operation == '-')
      {
        if (isSubtractionOverflow(num1, num2))
        {
          throw std::logic_error("Overflow during substraction");
        }
        stack_process.push(num1 - num2);
      }
      else if (operation == '*')
      {
        if (isMultiplicationOverflow(num1, num2))
        {
          throw std::logic_error("Overflow during multiplication");
        }
        stack_process.push(num1 * num2);
      }
      else if (operation == '/')
      {
        if (num2 == 0)
        {
          throw std::logic_error("Division by zero");
        }
        stack_process.push(num1 / num2);
      }
      else if (operation == '%')
      {
        if (num2 == 0)
        {
          throw std::logic_error("Division by zero");
        }
        stack_process.push(num1 % num2);
      }
    }
    queue_postfix.pop();
  }
  return stack_process.top();
}

int main(int argc, char ** argv)
{
  Stack<long long> stack_result;
  Queue< Queue< InfixType > > queue_input;
  try
  {
    if (argc == 1)
    {
      while (!std::cin.eof())
      {
        Queue<InfixType> queue_infix;
        inputExpression(std::cin, queue_infix);
        queue_input.push(queue_infix);
      }
    }
    else
    {
      std::ifstream input(argv[1]);
      if (!input)
      {
        std::cerr << "No such file\n";
        return 1;
      }
      while (!input.eof())
      {
        Queue<InfixType> queue_infix;
        inputExpression(input, queue_infix);
        queue_input.push(queue_infix);
      }
    }
    while (!queue_input.empty())
    {
      Queue<InfixType> queue_infix = queue_input.front();
      if (!queue_infix.empty())
      {
        Queue<PostfixType> queue_postfix = convertToPostfix(queue_infix);
        stack_result.push(calculatePostfix(queue_postfix));
      }
      queue_input.pop();
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  std::cout << stack_result.top();
  stack_result.pop();
  while (!stack_result.empty())
  {
    std::cout << ' ' << stack_result.top();
    stack_result.pop();
  }
  std::cout << '\n';
  return 0;
}
