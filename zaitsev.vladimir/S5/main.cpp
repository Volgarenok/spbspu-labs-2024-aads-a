#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <stdexcept>
#include <operators.hpp>
#include <map.hpp>
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
      Map< std::string, std::function< summator()> > commands;
      using ll = long long;
      commands["ascending"] = std::bind(&Map< ll, std::string >::traverse_lnr< summator >, &key_vals, summator{});
      commands["descending"] = std::bind(&Map< ll, std::string >::traverse_rnl< summator >, &key_vals, summator{});
      commands["breadth"] = std::bind(&Map< ll, std::string >::traverse_breadth< summator >, &key_vals, summator{});
      summator res = commands.at(argv[1])();
      std::cout << res.key_sum << " " << res.val_sum << '\n';
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
