#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <functional>
#include <stdexcept>
#include <operators.hpp>
#include "map.hpp"

namespace zaitsev
{
  struct summator
  {
    void operator()(const std::pair< const long long, std::string >& key_value) {
      key_sum_ = safePlus(key_sum_, key_value.first);
      val_sum_ += (val_sum_.empty() ? key_value.second : " " + key_value.second);
    }
    long long key_sum_ = 0;
    std::string val_sum_ = "";
  };
}

int main(int argc, char** argv)
{
  if (argc < 3)
  {
    std::cerr << "Not enough arguments\n";
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
        std::cerr << "Invalid agrument\n";
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
