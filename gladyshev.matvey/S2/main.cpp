#include <iostream>
#include <fstream>

#include "queue.hpp"
#include "stack.hpp"
#include "checkdata.hpp"
#include "topostfix.hpp"
#include "solvedata.hpp"

int main(int argc, char* argv[])
{
  using namespace gladyshev;
  std::istream* input;
  std::ifstream file;
  if (argc == 2)
  {
    file.open(argv[1]);
    input = &file;
  }
  else
  {
    input = &std::cin;
  }
  Queue< long long int > results;
  std::string in = "";
  std::string token = "";
  try
  {
    while (std::getline(*input, in))
    {
      Queue< std::string > queuecheck;
      size_t i = 0;
      while (i < in.length())
      {
        token = "";
        while (i < in.length() && !std::isspace(in[i]))
        {
          token += in[i];
          ++i;
        }
        if (!token.empty())
        {
          queuecheck.push(token);
        }
        ++i;
      }
      Queue< std::string > postfix = infixToPostfix(queuecheck);
      long long int result = evaluatePostfix(postfix);
      results.push(result);
    }
  }
  catch (const std::logic_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  results.reverse();
  if (!results.empty())
  {
    std::cout << results.drop();
  }
  while (!results.empty())
  {
    std::cout << " " << results.drop();
  }
  std::cout << "\n";
}
