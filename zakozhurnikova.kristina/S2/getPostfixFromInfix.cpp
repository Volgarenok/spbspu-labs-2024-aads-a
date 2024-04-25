#include "getPostfixFromInfix.hpp"
#include <cctype>
#include <iostream>
#include "stack.hpp"
#include "queue.hpp"
#include "readWord.hpp"

bool isBinaryOperator(const std::string& op)
{
  return op == "+" || op == "-" || op == "/" || op == "*" || op == "%";
}

bool hasMorePriority(const std::string& stack, const std::string& current)
{
  return (stack != "(") && (((current == "*" || current == "/") && (stack == "*" || stack == "/")) || (current == "+" || current == "-"));
}

void handleBinaryOperations(zakozhurnikova::Stack<std::string> &stack, const std::string &src, std::string &dest)
{
  if (isBinaryOperator(src))
  {
    while (!stack.empty() && hasMorePriority(stack.top(), src))
    {
      dest += stack.top() + " ";
      stack.drop();
    }
    stack.push(src);
  }
  else if (src == "(")
  {
    stack.push(src);
  }
  else if (src == ")")
  {
    while (stack.top() != "(")
    {
      dest += stack.top() + " ";
      stack.drop();
    }
    stack.drop();
  }
}

void getRemainsFromStack(zakozhurnikova::Stack<std::string> &stack, std::string &dest)
{
  while (!stack.empty())
  {
    if (stack.top() == "(")
    {
      throw std::runtime_error("incorrect brackets");
    }
    dest += stack.top() + " ";
    stack.drop();
  }
}

std::string& getPostfixFromInfixPart(std::istream& in, std::string& result)
{
  zakozhurnikova::Stack<std::string> stack;
  std::string buff;
  std::getline(in, buff, '\n');
  c_iterator_t it = buff.cbegin();
  while (it != buff.cend())
  {
    std::string sub;
    it = zakozhurnikova::readWord(it, buff.cend(), sub);
    try
    {
      std::stoll(sub);
      result += sub + " ";
    }
    catch (const std::invalid_argument &)
    {
      handleBinaryOperations(stack, sub, result);
    }
  }
  getRemainsFromStack(stack, result);
  return result;
}

void zakozhurnikova::getPostfixFromInfix(std::istream &in, Queue< std::string >& queue)
{
  std::string buffer;
  while (!in.eof())
  {
    std::string postfix = getPostfixFromInfixPart(in, buffer);
    if (!postfix.empty())
    {
      queue.push(postfix);
    }
    buffer.clear();
  }
}
