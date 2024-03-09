#include <iostream>
#include <sstream>
#include <vector>
#include <numeric>
#include "sequence.hpp"
#include "list.hpp"

int main()
{
  using namespace skuratov;
  std::vector<Sequence> sequences;
  std::string line;

  while (std::getline(std::cin, line))
  {
    if (!line.empty())
    {
      std::istringstream iss(line);
      std::string name;
      iss >> name;
      Sequence sequence(name);
      int num = {};
      while (iss >> num)
      {
        sequence.numbers().push_back(num);
      }
      sequences.push_back(sequence);
    }
  }

  for (const auto& seq : sequences)
  {
    std::cout << seq.name() << " ";
  }
  std::cout << '\n';
}
