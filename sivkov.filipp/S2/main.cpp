#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <string>
<<<<<<< HEAD
#include "infixToPostfix.hpp"
#include "utilities.hpp"
#include "calcultPostfix.hpp"

int main(int argc, char* argv[])
{
  std::queue<char> numb;
  std::stack<int> infix;

  if (argc == 2)
  {
    std::ifstream inputFile(argv[1]);
    infixToPostFix(inputFile, numb);
  }
  else
  {
    infixToPostFix(std::cin, numb);
  }

  int rez = 0;
  rez = calcult(numb);

  std::cout << rez;
  return 0;
=======

bool isNum(char c)
{
  return (c >= '0' && c <= '9');
>>>>>>> 052a79f6868177c78b86b1d4addcfc061dce2f0c
}

bool isOperator(char c)
{
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

int getPriority(char op)
{
  if (op == '*' || op == '/')
  {
    return 2;
  }
  else if (op == '+' || op == '-')
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int main(int argc, char* argv[])
{
  if (argc == 2)
  {
    std::ifstream inputFile(argv[1]);
  }

  std::stack<char> oper;
  std::queue<char> numb;
  std::stack<int> infix;

  std::ifstream inputFile(argv[1]);
  char token;

  while (inputFile >> token)
  {
    if (isNum(token))
    {
      numb.push(token);
    }
    else if (isOperator(token))
    {
      while (!oper.empty() && oper.top() != '(' && getPriority(oper.top()) >= getPriority(token))
      {
        numb.push(oper.top());
        oper.pop();
      }
      oper.push(token);
    }
    else if (token == '(')
    {
      oper.push(token);
    }
    else if (token == ')')
    {
      while (!oper.empty() && oper.top() != '(')
      {
        numb.push(oper.top());
        oper.pop();
      }
      oper.pop();
    }
  }

  while (!oper.empty())
  {
    numb.push(oper.top());
    oper.pop();
  }

  while (!numb.empty())
  {
    if (numb.front() == '+')
    {
      int a = infix.top();
      infix.pop();
      int b = infix.top();
      infix.pop();
      int c = b + a;
      infix.push(c);
      numb.pop();
    }
    else if (numb.front() == '-')
    {
      int a = infix.top();
      infix.pop();
      int b = infix.top();
      infix.pop();
      int c = b - a;
      infix.push(c);
      numb.pop();
    }
    else if (numb.front() == '/')
    {
      int a = infix.top();
      infix.pop();
      int b = infix.top();
      infix.pop();
      int c = b / a;
      infix.push(c);
      numb.pop();
    }
    else if (numb.front() == '*')
    {
      int a = infix.top();
      infix.pop();
      int b = infix.top();
      infix.pop();
      int c = b * a;
      infix.push(c);
      numb.pop();
    }
    else
    {
      char num = numb.front();
      int a = num - '0';
      infix.push(a);
      numb.pop();
    }
  }
  std::cout << infix.top();
  return 0;
}

