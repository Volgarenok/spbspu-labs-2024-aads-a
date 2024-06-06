#include <iostream>
#include <iterator>
#include <random>
#include <deque>
#include <list>
#include <string>
#include <iomanip>
#include <list.hpp>
#include "sorts.hpp"
#include "outputInput.hpp"

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
  try
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    if (type == "floats")
    {
      List< float > fwdList;
      std::list< float > biList;
      std::deque< float > deq;
      filRandom(n, deq, fwdList, biList, gen);
      print(std::cout, deq);
      enterTypeOfSort(direction, deq, fwdList, biList, std::cout);
    }
    else if (type == "ints")
    {
      List< int > fwdList;
      std::list< int > biList;
      std::deque< int > deq;
      filRandom(n, deq, fwdList, biList, gen);
      print(std::cout, deq);
      enterTypeOfSort(direction, deq, fwdList, biList, std::cout);
    }
    else
    {
      throw std::invalid_argument("Invalid type");
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}

