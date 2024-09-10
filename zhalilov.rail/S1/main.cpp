#include <iostream>
#include <fstream>

#include <list/list.hpp>

#include "getSeqFromStream.hpp"
#include "outputSeqs.hpp"

int main()
{
  using namespace zhalilov;
  List< strListPair > sequences;
  getSeqFromStream(sequences, std::cin);
  if (sequences.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  try
  {
    outputSeqs(sequences, std::cout);
    std::cout << "\n";
  }
  catch (const std::overflow_error &e)
  {
    std::cerr << "Error has occured: " << e.what();
    return 1;
  }
}
