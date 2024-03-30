#include "getPostfixFromInfix.hpp"
#include "stack.hpp"
#include "queue.hpp"

bool isOpeningBracket(char ch)
{
  return ch == '(';
}
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
  zakozhurnikova::Stack< char > stack;
  char ch = 0;
  in >> std::noskipws;
  while (std::cin.peek() != '\n')
  {
    std::cin >> ch;
    if (std::isdigit(ch))
    {
      std::string value;
      value.push_back(ch);
      while (std::isdigit(std::cin.peek()))
      {
        value.push_back(std::cin.get());
      }
      queue.push(value);
    }
    else if (isBinaryOperator(ch))
    {
      while (!stack.empty() && hasMorePriority(stack.top(), ch))
      {
        std::string value;
        value.push_back(stack.top());
        queue.push(value);
        //res.push_back(stack.top());
        //res.push_back(' ');
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
        queue.push(value);
        //res.push_back(stack.top());
        //res.push_back(' ');
        stack.drop();
      }
      stack.drop();
    }
  }

  while (!stack.empty())
  {
    if (isOpeningBracket(stack.top()))
    {
      throw std::logic_error("malo closing brackets");
    }
    std::string value;
    queue.push(value);
    //res.push_back(stack.top());
    //res.push_back(' ');
    stack.drop();
  }
}
