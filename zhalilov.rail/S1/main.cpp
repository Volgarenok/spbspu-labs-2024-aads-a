#include <iostream>
#include <fstream>

#include "list.hpp"
#include "getSeqFromStream.hpp"
#include "outputSeqs.hpp"

int main()
{
  using namespace zhalilov;
  List< pair > sequences;
  getSeqFromStream(sequences, std::cin);
  if (sequences.empty())
  {
    return 0;
  }

  try
  {
    outputSeqs(sequences, std::cout);
  }
  catch (const std::overflow_error &e)
  {
    std::cerr << "Error has occured: " << e.what();
    return 1;
  }
}
