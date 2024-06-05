#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../common/list/list.hpp"
#include "chooseSort.hpp"
#include "generate.hpp"
#include "print.hpp"
#include "sorts.hpp"

int main(int argc, char* argv[])
{
  size_t size = 15;
  std::default_random_engine generator;
  strelyaev::fillContainer< int, std::less< int > >(std::cout, size, generator);
}