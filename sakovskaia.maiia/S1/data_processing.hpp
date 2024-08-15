#ifndef DATA_PROCESSING_HPP
#define DATA_PROCESSING_HPP
#include <string>
#include <stdexcept>
#include "list.hpp"
namespace sakovskaia
{
  using ullList = List< unsigned long long int >;
  List< ullList > processData(const List< std::pair< std::string, ullList > > & sequences);
  List< unsigned long long int > calculateSums(const List< ullList > & processedData);
}
#endif
