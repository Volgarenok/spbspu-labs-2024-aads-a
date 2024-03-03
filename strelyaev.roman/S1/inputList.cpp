#include "inputList.hpp"
#include <utility>
#include <string>
#include <istream>
#include "list.hpp"

std::pair< std::string, strelyaev::List< double > > strelyaev::makeSequence(std::istream& in)
{
  List< double > list_of_double;
  std::string name = "";
  while (in)
  {
    double a = 0;
    in >> a;
    list_of_double.push_back(a);
  }
  std::pair< std::string, List< double > > pairs = {name, list_of_double};
  return pairs;
}
