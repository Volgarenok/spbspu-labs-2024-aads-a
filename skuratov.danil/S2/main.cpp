#include <fstream>
#include <iostream>
#include "processExpressions.hpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;
  Queue< Queue< std::string > > exp;
  Queue< std::string > lineQueue;
  std::string line;
  if (argc > 1)
  {
    std::ifstream infile(argv[1]);
    if (!infile)
    {
      std::cerr << "Error reading file" << '\n';
      return 1;
    }
    while (infile)
    {
      char symb;
      while (infile >> symb && symb != '\n')
      {
        if (symb == ' ')
        {
          lineQueue.push(line);
          line = "";
        }
        else
        {
          line += symb;
        }
      }
      exp.push(lineQueue);
    }
  }
  else
  {
    while (std::cin)
    {
      char symb;
      while (std::cin >> symb && symb != '\n')
      {
        if (symb == ' ')
        {
          lineQueue.push(line);
          line = "";
        }
        else
        {
          line += symb;
        }
      }
      exp.push(lineQueue);
    }
  }
  try
  {
    processExpressions(exp);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  return 0;
}
