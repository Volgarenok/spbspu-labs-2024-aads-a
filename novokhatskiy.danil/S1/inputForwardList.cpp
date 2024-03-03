#include "inputForwardList.hpp"

void novokhatskiy::inputForwardList(novokhatskiy::ForwardList<std::pair<std::string, novokhatskiy::ForwardList< unsigned long long > > >& pairsOfList, std::istream& input)
{
  using pair = std::pair<std::string, novokhatskiy::ForwardList<unsigned long long> >;
  std::string line = "";
  input >> line;
  while (input)
  {
    if (!input)
    {
      throw std::invalid_argument("Can not read the line");
    }
    if (line == "third")
    {
      std::cerr << "The end of input\n";
      break;
    }
    pairsOfList.push_front({ line, novokhatskiy::ForwardList< unsigned long long > ()});
    while (input >> line && !std::isalpha(line[0]))
    {
      pairsOfList.front().second.push_front(std::stoull(line));
    }
  }
}
