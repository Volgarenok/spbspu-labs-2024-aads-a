#include <iostream>
#include <string>
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

template< class T >
void choose_type(const T&, const std::string& type_trav, size_t size)
{
  using namespace piyavkin;
  std::forward_list< T > list;
  List< T > bi_list;
  std::deque< T > deque;
  create_containers(deque, bi_list, list, size);
  print_container(std::cout, deque);
  choose_function(type_trav, deque, bi_list, list);
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
      choose_type(0, std::string(argv[1]), size);
    }
    else if (std::string(argv[2]) == "floats")
    {
      choose_type(0.0f, std::string(argv[1]), size);
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
