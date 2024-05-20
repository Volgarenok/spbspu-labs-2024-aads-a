#include <fstream>
#include "processExpressions.hpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;
  Queue< Queue< std::string > > exp;
  std::string line;

  if (argc > 1)
  {
    std::ifstream infile(argv[1]);
    if (!infile)
    {
      std::cerr << "Error reading file" << '\n';
      return 1;
    }
    while (infile >> line)
    {
      Queue< std::string > lineQueue;
      for (char& ch : line)
      {
        lineQueue.push(std::string(1, ch));
      }
      exp.push(lineQueue);
    }
  }
  else
  {
    while (std::cin >> line)
    {
      Queue< std::string > lineQueue;
      for (char& ch : line)
      {
        lineQueue.push(std::string(1, ch));
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
