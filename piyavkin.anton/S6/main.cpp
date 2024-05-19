#include <iostream>
#include <string>
#include "timsort.hpp"
#include "createcontainer.hpp"
#include "printsortcontainers.hpp"

template< class T >
void choose_function(const std::string& str, std::deque< T >& deque, piyavkin::List< T >& bi_list, std::forward_list< T >& list)
{
  if (str == "ascending")
  {
    print_sorted_containers(std::cout, deque, bi_list, list, std::less< T >());
  }
  else if (str == "descending")
  {
    print_sorted_containers(std::cout, deque, bi_list, list, std::greater< T >());
  }
  else
  {
    throw std::logic_error("Invalid traversal order");
  }
}

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
    if (size == 0)
    {
      throw std::logic_error("Zero size");
    }
    using namespace piyavkin;
    if (std::string(argv[2]) == "ints")
    {
      std::forward_list< int > list;
      List< int > bi_list;
      std::deque< int > deque;
      create_containers(deque, bi_list, list, size);
      print_containers(std::cout, deque);
      choose_function(std::string(argv[1]), deque, bi_list, list);
    }
    else if (std::string(argv[2]) == "floats")
    {
      std::forward_list< float > list;
      List< float > bi_list;
      std::deque< float > deque;
      create_containers(deque, bi_list, list, size);
      print_containers(std::cout, deque);
      choose_function(std::string(argv[1]), deque, bi_list, list);
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
