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
        std::cout << rebdev::convertPostfixToNum(postfixQueue) << '\n';
      }
      catch (const std::exception & e)
      {
        std::cerr << e.what() << '\n';
        return 1;
      }
    }
  }
  return 0;
}
