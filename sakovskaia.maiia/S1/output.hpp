#ifndef OUTPUT_HPP
#define OUTPUT_HPP
#include <string>
#include <iostream>
#include "list.hpp"
namespace sakovskaia
{
  void outputSequences(const List< std::pair< std::string, List< unsigned long long int > > > & sequences);
  void outputProcessedData(const List< List< unsigned long long int > > & processedData);
  void outputSums(const List< unsigned long long int > & sums);
}
#endif
