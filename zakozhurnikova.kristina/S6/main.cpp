#include <iostream>
#include <forward_list>
#include <list.hpp>
#include <deque>
#include <string>
#include <algorithm>
#include "generate.hpp"

int main(int argc, char* argv[])
{
  using namespace zakozhurnikova;
  if (argc != 4)
  {
    std::cerr << "No right argument";
    return 1;
  }

  std::string type = argv[3];
  if (type == "ints")
  {
    int array[10];
    std::generate_n(array, 10, RandomNumberInt);
    List< int > countOne;
    std::deque< int > countTwo;
    std::forward_list< int > countThree;
    for (int i = 0; i < 10; ++i)
    {
      int number = array[i];
      countOne.push_back(number);
      countTwo.push_front(number);
      countThree.push_front(number);
      countThree.sort(std::less< int >());
    }
  }
  else if (type == "floats")
  {}
  else
  {
    std::cerr << "No right argument";
    return 1;
  }


}
