#include <iostream>
#include <fstream>
#include <string>

#include "manageData.h"

using namespace stepanov;

int main(int argc, char* argv[])
{
  std::string strInput = "";
  manageExpression expression;
  Stack< long long > stackResult;

  if (argc == 1)
  {
    char ch;
    while (true)
    {
      strInput = "";
      while (std::cin.get(ch) && ch != '\n')
      {
        strInput += ch;
      }
      if (std::cin.eof())
      {
        break;
      }
      if (strInput.empty())
      {
        continue;
      }

      try
      {
        expression.convertToPolish(strInput);
        expression.calculatePolish(stackResult);
      }
      catch (std::runtime_error &e)
      {
        std::cerr << e.what() << "\n";
        return 1;
      }
    }
    expression.printResult(stackResult);
  }
  else if (argc == 2)
  {
    std::ifstream fileName;
    fileName.open(argv[1]);
    if (!fileName.is_open())
    {
      std::cerr << "No such file in directory" << "\n";
      return 1;
    }
    char ch;
    while (true)
    {
      strInput = "";
      while (fileName.get(ch) && ch != '\n')
      {
        strInput += ch;
      }
      if (fileName.eof())
      {
        break;
      }
      if (strInput.empty())
      {
        continue;
      }

      try
      {
        expression.convertToPolish(strInput);
        expression.calculatePolish(stackResult);
      }
      catch (std::runtime_error &e)
      {
        std::cerr << e.what() << "\n";
        return 1;
      }
    }
    expression.printResult(stackResult);
    fileName.close();
  }

  if (stackResult.isEmpty())
  {
    std::cout << '\n';
  }
  return 0;
}
