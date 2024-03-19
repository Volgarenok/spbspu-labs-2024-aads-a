#include "inputForwardList.hpp"

void novokhatskiy::inputForwardList(ForwardList< std::pair< std::string, ForwardList< size_t > > >& pairsOfList, std::istream& input)
{
  std::string line = "";
  input >> line;
  while (input)
  {
    if (!input)
    {
      throw std::invalid_argument("Can not read the line");
      return;
    }
    pairsOfList.push_front({ line, ForwardList< size_t > ()});
    while (input >> line && !std::isalpha(line[0]))
    {
      pairsOfList.front().second.push_front(std::stoull(line));
    }
    pairsOfList.front().second.reverse();
  }
  pairsOfList.reverse();
}
