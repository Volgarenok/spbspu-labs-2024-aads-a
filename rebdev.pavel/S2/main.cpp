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
    inPointer = &inFile;
  }
  std::istream & in = *inPointer;

  while (!in.eof())
  {
    std::string inStr;
    std::getline(in, inStr);

    rebdev::postFixQueue postFix;
    try
    {
      rebdev::makePostFix(inStr, postFix);
      std::cout << rebdev::postFixToResult(postFix) << ' ';
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }

  std::cout << '\n';
  return 0;
}
