#include <iostream>
#include <iterator>
#include <random>
#include <deque>
#include <list>
#include <string>
#include <iomanip>
#include <list.hpp>
#include "sorts.hpp"
#include "outputinput.hpp"

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "error arg in commadn line\n";
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
    std::cerr << "error\n";
    return 1;
  }

  using namespace sivkov;
  List< int > fwdList;
  std::list< int > biList;
  std::deque< int > deq;

  try
  {
    generateRandom(n, "floats", deq, fwdList, biList);
    print(std::cout, deq);
    enterTypeOfSort(direction, deq, fwdList, biList, std::cout);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
