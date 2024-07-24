#include <iostream>
#include <fstream>
#include <string>
#include <stack>

#include "postfix.hpp"

int main(int argv, char ** argc)
{
  std::istream * inPointer = &std::cin;
  if (argv == 2)
  {
    std::ifstream inFile(argc[1]);
    if (inFile.peek() == EOF)
    {
      std::cout << '\n';
      return 0;
    }
    inPointer = &inFile;
  }
  std::istream & in = *inPointer;

  std::stack< long long > resStack;

  while (!in.eof())
  {
    std::string inStr;
    std::getline(in, inStr);
    if (inStr.empty())
    {
      continue;
    }
    rebdev::postFixQueue postFix;

    try
    {
      rebdev::makePostFix(inStr, postFix);
      if (postFix.empty())
      {
        break;
      }
      long long num = rebdev::postFixToResult(postFix);
      resStack.push(num);
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }

  for (size_t i = 0; i < (resStack.size() - 1); ++i)
  {
    std::cout << resStack.top() << ' ';
    resStack.pop();
  }

  std::cout << resStack.top() << '\n';
  return 0;
}
