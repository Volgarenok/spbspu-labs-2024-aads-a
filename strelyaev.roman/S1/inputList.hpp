#ifndef INPUTLIST_HPP
#define INPUTLIST_HPP
#include <istream>
#include <list/list.hpp>
namespace strelyaev
{
void makeSequence(std::istream&, List < std::pair < std::string, List< size_t > > >&);
}
#endif
