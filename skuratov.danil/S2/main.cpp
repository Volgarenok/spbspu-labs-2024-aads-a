#include <fstream>
#include "processExpressions.hpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;
  List< std::string > exp;
  std::string line;

  if (argc > 1)
  {
    std::ifstream infile(argv[1]);
    if (!infile)
    {
      std::cerr << "Error reading file" << '\n';
      return 1;
    }
    while (std::getline(infile, line))
    {
      if (!line.empty())
      {
        exp.pushBack(line);
      }
    }
  }
  else
  {
    while (std::getline(std::cin, line))
    {
      if (!line.empty())
      {
        exp.pushBack(line);
      }
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
