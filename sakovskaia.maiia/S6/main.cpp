#include <iostream>
#include <list>
#include <deque>
#include <string>
#include <random>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include "list.hpp"
#include "input_output.hpp"
#include "sort.hpp"

int main(int argc, char * argv[])
{
  using namespace sakovskaia;
  if (argc != 4)
  {
    std::cerr << "error cmd line\n";
    return 1;
  }
  std::string direction = "";
  std::string type = "";
  size_t n = 0;
  try
  {
    direction = argv[1];
    type = argv[2];
    n = std::stoull(argv[3]);
  }
  catch (...)
  {
    std::cerr << "error data\n";
    return 1;
  }
  try
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    if (type == "floats")
    {
      List< float > fwdList;
      std::list< float > biList;
      std::deque< float > deq;
      fill(deq, fwdList, biList, gen, n, type);
      print(std::cout, deq);
      sorting(direction, deq, fwdList, biList, std::cout);
    }
    else if (type == "ints")
    {
      List< int > fwdList;
      std::list< int > biList;
      std::deque< int > deq;
      fill(deq, fwdList, biList, gen, n, type);
      print(std::cout, deq);
      sorting(direction, deq, fwdList, biList, std::cout);
    }
    else
    {
      throw std::invalid_argument("Error type");
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
