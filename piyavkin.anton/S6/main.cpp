#include <iostream>
#include <string>
#include "timsort.hpp"
#include "createcontainer.hpp"
#include "printsortcontainers.hpp"

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "File entered incorrectly\n";
    return 1;
  }
  try
  {
    size_t size = std::stoull(argv[3]);
    using namespace piyavkin;
    if (std::string(argv[2]) == "ints")
    {
      std::forward_list< int > list;
      List< int > bi_list;
      std::deque< int > deque;
      create_containers(deque, bi_list, list, size);
      print_containers(std::cout, deque);
      if (std::string(argv[1]) == "ascending")
      {
        print_sorted_containers(std::cout, deque, bi_list, list, std::less< int >());
      }
      else if (std::string(argv[1]) == "descending")
      {
        print_sorted_containers(std::cout, deque, bi_list, list, std::greater< int >());
      }
      else
      {
        throw std::logic_error("Invalid traversal order");
      }
    }
    else if (std::string(argv[2]) == "float")
    {
      std::forward_list< float > list;
      List< float > bi_list;
      std::deque< float > deque;
      create_containers(deque, bi_list, list, size);
      if (std::string(argv[1]) == "ascending")
      {
        print_sorted_containers(std::cout, deque, bi_list, list, std::less< float >());
      }
      else if (std::string(argv[1]) == "descending")
      {
        print_sorted_containers(std::cout, deque, bi_list, list, std::greater< float >());
      }
      else
      {
        throw std::logic_error("Invalid traversal order");
      }
    }
    else
    {
      std::cerr << "Bad type\n";
      return 1;
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
}
