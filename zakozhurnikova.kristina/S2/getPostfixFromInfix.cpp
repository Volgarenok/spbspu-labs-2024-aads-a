#include "getPostfixFromInfix.hpp"
#include "stack.hpp"
#include "queue.hpp"

bool isBinaryOperator(char ch)
{
  return ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '%';
}

bool hasMorePriority(char stack, char current)
{
  return ((current == '*' || current == '/') && (stack == '*' || stack == '/')) || (current == '+' || current == '-');
}

void getPostfixFromInfix(std::istream &in, zakozhurnikova::Queue< std::string >& queue)
{
  std::string buffer;
  while(in)
  {
    queue.push(getPostfixFromInfix(in, buffer));
    buffer.clear();
  }
}

std::string& getPostfixFromInfix(std::istream &in, std::string& result)
{
  zakozhurnikova::Stack< char > stack;
  char ch = 0;
  in >> std::noskipws;
  while (in.peek() != '\n')
  {
    in >> ch;
    if (std::isdigit(ch))
    {
      std::string value;
      value.push_back(ch);
      while (std::isdigit(in.peek()))
      {
        value.push_back(in.get());
      }
      result.push(value);
    }
    else if (isBinaryOperator(ch))
    {
      while (!stack.empty() && hasMorePriority(stack.top(), ch))
      {
        std::string value;
        value.push_back(stack.top());
        result.push(value);
        stack.drop();
      }
      stack.push(ch);
    }
    else if (ch == '(')
    {
      stack.push(ch);
    }
    else if (ch == ')')
    {
      while (stack.top() != '(')
      {
        std::string value;
        value.push_back(stack.top());
        result.push(value);
        stack.drop();
      }
      stack.drop();
    }
  }
  while (!stack.empty())
  {
    if (stack.top() == '(')
    {
      throw std::runtime_error("malo closing brackets");
    }
    std::string value;
    result.push(value);
    stack.drop();
  }
}
