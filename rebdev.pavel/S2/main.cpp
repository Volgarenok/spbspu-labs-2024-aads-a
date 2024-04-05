#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "myQueue.hpp"
#include "node.hpp"
#include "postfixToNum.hpp"
#include "inputToPostfix.hpp"

int main(int argc, char ** argv)
{
  std::istream * inputPointer = &std::cin;
  std::ifstream file;
  if (argc > 1)
  {
    file.open(argv[1]);
    inputPointer = &file;
  }
  std::istream & inputLink = *inputPointer;

  rebdev::Stack< long long > resultStack;
  while (!inputLink.eof())
  {
    rebdev::queue< rebdev::node > postfixQueue;

    std::string nextLine;
    std::getline(inputLink, nextLine);

    if (!nextLine.empty())
    {
      std::istringstream inputStr(nextLine);

      try
      {
        rebdev::makePostfixQueue(postfixQueue, inputStr);
        resultStack.push(rebdev::convertPostfixToNum(postfixQueue));
      }
      catch (const std::exception & e)
      {
        std::cerr << e.what() << '\n';
        return 1;
      }
    }
  }

  if (resultStack.size() > 0)
  {
    while (resultStack.size() > 1)
    {
      std::cout << resultStack.drop() << ' ';
    }
    std::cout << resultStack.drop();
  }
  std::cout << '\n';
  return 0;
}
