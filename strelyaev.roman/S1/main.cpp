#include <iostream>
#include <utility>
#include "list.hpp"
#include "iterator.hpp"
#include "inputList.hpp"

int main()
{
  strelyaev::List < std::pair < std::string, strelyaev::List< int > > > list_of_lists;
  strelyaev::makeSequence(std::cin, list_of_lists);
  std::cout << "А все\n";
}
