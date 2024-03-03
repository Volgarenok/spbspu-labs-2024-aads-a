#ifndef INPUTLIST_HPP
#define INPUTLIST_HPP
#include "list.hpp"
#include <istream>
namespace strelyaev
{
  std::pair< std::string, strelyaev::List< double > > makeSequence(std::istream&);
}
#endif
