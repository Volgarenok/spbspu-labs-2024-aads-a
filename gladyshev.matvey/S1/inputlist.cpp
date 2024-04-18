#include "inputlist.hpp"

void gladyshev::readSequence(std::istream& in, List< std::pair< std::string, List< size_t > > >& list)
{
  std::string line = "";
  in >> line;
  while (in)
  {
    list.push_front({line, List< size_t >{}});
    while (in >> line)
    {
      try
      {
        size_t number = std::stoull(line);
        list.front().second.push_front(number);
      }
      catch (const std::invalid_argument&)
      {
        break;
      }
    }
  }
}
