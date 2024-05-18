#include "getPostfixForm.hpp"
#include <cctype>
#include <iostream>
#include "stack.hpp"
#include "queue.hpp"
#include "input.hpp"

bool binary(const std::string& p)
{
  return (p == "+") || (p == "-") || (p == "/") || (p == "*") || (p == "%");
}

bool priority(const std::string& stack, const std::string& current)
{
  return (stack != "(") && (((current == "*" || current == "/") && (stack == "*" || stack == "/")) || (current == "+" || current == "-"));
}

void operations(marishin::Stack< std::string > &stack, const std::string &str, std::string &value)
{
  if (binary(str))
  {
    while (!stack.empty() && priority(stack.top(), str))
    {
      value += stack.top() + " ";
      stack.drop();
    }
    stack.push(str);
  }
  else if (str == "(")
  {
    stack.push(str);
  }
  else if (str == ")")
  {
    while (stack.top() != "(")
    {
      value += stack.top() + " ";
      stack.drop();
    }
    stack.drop();
  }
}

void getFromStack(marishin::Stack< std::string > &stack, std::string &value)
{
  while (!stack.empty())
  {
    if (stack.top() == "(")
    {
      throw std::runtime_error("incorrect characters");
    }
    value += stack.top() + " ";
    stack.drop();
  }
}

std::string& getPostfixFormIn(std::istream& in, std::string& result)
{
  marishin::Stack<std::string> stack;
  std::string name;
  std::getline(in, name, '\n');
  input_it_t it = name.cbegin();
  while (it != name.cend())
  {
    std::string str;
    it = marishin::input(it, name.cend(), str);
    try
    {
      std::stoll(str);
      result += str + " ";
    }
    catch (const std::invalid_argument &)
    {
      operations(stack, str, result);
    }
  }
  getFromStack(stack, result);
  return result;
}

void marishin::getPostfixForm(std::istream& in, Queue< std::string >& queue)
{
  std::string name = "";
  while (!in.eof())
  {
    std::string postfix = getPostfixFormIn(in, name);
    if (!postfix.empty())
    {
      queue.push(postfix);
    }
    name.clear();
  }
}
