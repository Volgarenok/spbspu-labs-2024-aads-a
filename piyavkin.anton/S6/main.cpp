#include <iostream>
#include <string>
#include <functional>
#include <tree.hpp>
#include "createcontainer.hpp"
#include "printsortcontainers.hpp"

template< class T, class Cmp >
void choose_type(std::ostream& out, size_t size, std::default_random_engine& gen)
{
  using namespace piyavkin;
  std::deque< T > deque;
  for (size_t i = 0; i < size; ++i)
  {
    T value = detail::get_value(gen, T());
    deque.push_front(value);
  }
  print_container(out, deque.cbegin(), deque.cend());
  out << '\n';
  print_sorted_containers(out, deque, Cmp());
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
    std::default_random_engine generator;
    using namespace piyavkin;
    Tree< std::pair< std::string, std::string >, std::function< void(std::ostream&, size_t, std::default_random_engine&) > > container;
    container[std::make_pair< std::string, std::string >("ints", "ascending")] = choose_type< int, std::less< int > >;
    container[std::make_pair< std::string, std::string >("ints", "descending")] = choose_type< int, std::greater< int > >;
    container[std::make_pair< std::string, std::string >("floats", "ascending")] = choose_type< float, std::less< float > >;
    container[std::make_pair< std::string, std::string >("floats", "descending")] = choose_type< float, std::greater< float > >;
    container.at(std::make_pair(std::string(argv[2]), std::string(argv[1])))(std::cout, size, generator);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
}
