#include "inputForwardList.hpp"

void novokhatskiy::inputForwardList(ForwardList<std::pair<std::string, ForwardList< unsigned long long > > >& pairsOfList, std::istream& input)
{
  std::string line = "";
  input >> line;
  while (input)
  {
    if (!input)
    {
      throw std::invalid_argument("Can not read the line");
    }
    pairsOfList.push_front({ line, ForwardList< unsigned long long > ()});
    while (input >> line && !std::isalpha(line[0]))
    {
      pairsOfList.front().second.push_front(std::stoull(line));
    }
    pairsOfList.front().second.reverse();
  }
  pairsOfList.reverse();
}
