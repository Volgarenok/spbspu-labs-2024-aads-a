#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <functional>
#include <stdexcept>
#include <operators.hpp>
#include "map.hpp"
#include "summator.hpp"

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }
  using namespace zaitsev;
  std::fstream input(argv[2]);
  Map< long long, std::string > key_vals;
  try
  {
    while (!input.eof())
    {
      std::string val;
      long long key = 0;
      input >> key >> val;
      if (input)
      {
        key_vals[key] = val;
      }
    }
    if (key_vals.empty())
    {
      std::cout << "<EMPTY>\n";
    }
    else
    {
      if (strcmp(argv[1], "ascending") == 0)
      {
        summator res = key_vals.traverse_lnr(summator{});
        std::cout << res.key_sum_ << " " << res.val_sum_ << '\n';
      }
      else if (strcmp(argv[1], "descending") == 0)
      {
        summator res = key_vals.traverse_rnl(summator{});
        std::cout << res.key_sum_ << " " << res.val_sum_ << '\n';
      }
      else if (strcmp(argv[1], "breadth") == 0)
      {
        summator res = key_vals.traverse_breadth(summator{});
        std::cout << res.key_sum_ << " " << res.val_sum_ << '\n';
      }
      else
      {
        throw std::invalid_argument("Invalid agrument");
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
