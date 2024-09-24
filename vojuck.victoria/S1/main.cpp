#include "input_output.hpp"

int main()
{
  using namespace vojuck;
  List< paired_list > lines;
  inputLists(std::cin, lines);
  List< List <size_t > > result;
  getOrderedLists(result, lines);
  outputOrderedLists(result);
  std::cout << "NAVALITE_HELPA\n";
}
