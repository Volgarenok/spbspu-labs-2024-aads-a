#include "getPostfixFromInfix.hpp"
#include <cctype>
#include "stack.hpp"
#include "queue.hpp"

bool isBinaryOperator(char ch)
{
  return ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '%';
}

bool hasMorePriority(char stack, char current)
{
  return (stack != '(') && (((current == '*' || current == '/') && (stack == '*' || stack == '/')) || (current == '+' || current == '-'));
}

std::string& getPostfixFromInfix(std::istream &in, std::string& result)
{
  const char WHITE_SPACE = ' ';
  zakozhurnikova::Stack< char > stack;
  std::string buff;
  std::getline(in, buff, '\n');
  for (auto it = buff.cbegin(); it != buff.cend(); ++it)
  {
    if (std::isdigit(*it))
    {
      auto cpy = it;
      while (std::isdigit(*cpy))
      {
        result.push_back(*cpy);
        ++cpy;
      }
      it = --cpy;
      result.push_back(WHITE_SPACE);
    }
    else if (isBinaryOperator(*it))
    {
      while (!stack.empty() && hasMorePriority(stack.top(), *it))
      {
        result.push_back(stack.top());
        result.push_back(WHITE_SPACE);
        stack.drop();
      }
      stack.push(*it);
    }
    else if (*it == '(')
    {
      stack.push(*it);
    }
    else if (*it == ')')
    {
      while (stack.top() != '(')
      {
        result.push_back(stack.top());
        result.push_back(WHITE_SPACE);
        stack.drop();
      }
      stack.drop();
    }
  }
  while (!stack.empty())
  {
    if (stack.top() == '(')
    {
      throw std::runtime_error("incorrect brackets");
    }
    result.push_back(stack.top());
    result.push_back(WHITE_SPACE);
    stack.drop();
  }
  return result;
}

void getPostfixFromInfix(std::istream &in, zakozhurnikova::Queue< std::string >& queue)
{
  std::string buffer;
  while(!in.eof())
  {
    std::string postfix = getPostfixFromInfix(in, buffer);
    if (!postfix.empty())
    {
      queue.push(postfix);
    }
    buffer.clear();
  }
}
