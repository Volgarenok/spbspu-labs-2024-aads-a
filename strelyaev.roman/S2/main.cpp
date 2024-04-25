#include <iostream>
#include <fstream>
#include "queue.hpp"
#include "stack.hpp"
#include "calculations.hpp"
#include "conversion.hpp"

int main(int argc, char** argv)
{
  using namespace strelyaev;
  Stack< long long > results;
  std::istream* stream_pointer = std::addressof(std::cin);
  std::fstream file;
  if (argc > 1)
  {
    file.open(argv[1]);
    stream_pointer = std::addressof(file);
  }
  std::istream& in = *stream_pointer;
  if (in.eof() || !in)
  {
    std::cout << "\n";
    return 0;
  }
  while (!in.eof())
  {
    Queue< ExpressionUnit > infix_queue = parseString(in);
    Queue< ExpressionUnit > post_fix = makePostfix(infix_queue);
    long long result = 0;
    try
    {
      result = calculatePostfix(post_fix);
    }
    catch (const std::out_of_range& e)
    {
      continue;
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
    results.push(result);
  }
  if (results.empty())
  {
    std::cout << "\n";
    return 0;
  }
  std::cout << results.back();
  results.pop_back();
  while (!results.empty())
  {
    std::cout << " " << results.back();
    results.pop_back();
  }
  std::cout << "\n";
}

