#include <iostream>
#include <fstream>
#include <string>

#include "postfix.hpp"

int main(int argv, char ** argc)
{
  std::istream * inPointer = &std::cin;
  if (argv == 2)
  {
    std::ifstream inFile(argc[2]);
    if (!inFile.is_open())
    {
      return 0;
    }
    inPointer = &inFile;
  }
  std::istream & in = *inPointer;

  bool firstOutput = true;
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
      if (!firstOutput)
      {
        std::cout << ' ';
      }
      std::cout << rebdev::postFixToResult(postFix);
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
    firstOutput = false;
  }

  std::cout << '\n';
  return 0;
}
