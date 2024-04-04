#include <iostream>
#include "queue.hpp"
#include "token.hpp" // TO_DEL
#include <sstream> // TO_DEL
#include <string> // TO_DEL
#include "stack.hpp" // TO_DEL

bool isOperator(std::string& c)
{
  return ((c == "+") || (c == "-") || (c == "/") || (c == "*") || (c == "%"));
}


strelyaev::Queue< strelyaev::Token > makeQueue(std::istream& in)
{
  strelyaev::Queue< strelyaev::Token > token_queue;
  std::string str = "";
  while (in >> str)
  {
    if (isOperator(str))
    {
      char ch = str[0];
      token_queue.push(strelyaev::Token(ch));
      std::cout << "{" << ch << "}\n";
      continue;
    }
    long long operand = 0;
    try
    {
      operand = std::stoll(str);
    }
    catch (const std::exception& e)
    {
      continue;
    }
    token_queue.push(strelyaev::Token(operand));
    std::cout << "{" << operand << "}\n";
  }
  return token_queue;
}

int main()
{
  using namespace strelyaev;
  std::string infix = "12 + 4";
  std::stringstream ss(infix);
  Queue< Token > a = makeQueue(ss);
  //splitTokens(a);
}
