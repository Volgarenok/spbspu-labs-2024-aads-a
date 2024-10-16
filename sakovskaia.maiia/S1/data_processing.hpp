#ifndef DATA_PROCESSING_HPP
#define DATA_PROCESSING_HPP
#include <string>
#include <stdexcept>
#include <iostream>
#include <limits>
#include <list.hpp>
namespace sakovskaia
{
  using ullList = List< unsigned long long int >;
  List< ullList > processData(const List< std::pair< std::string, ullList > > & sequences);
  ullList calculateSums(const List< ullList > & data);
  bool isEmpty(List< std::pair< std::string, ullList > >& sequences);
}
#endif
