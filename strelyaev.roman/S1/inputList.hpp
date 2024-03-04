#ifndef INPUTLIST_HPP
#define INPUTLIST_HPP
#include "list.hpp"
#include <istream>
namespace strelyaev
{
void makeSequence(std::istream&, List < std::pair < std::string, List< size_t > > >&);
}
#endif
