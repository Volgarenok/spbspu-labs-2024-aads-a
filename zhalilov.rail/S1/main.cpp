#include <iostream>
#include <fstream>

#include "list.hpp"
#include "getSeqFromStream.hpp"
#include "outputSeqs.hpp"
#include "countSum.hpp"

int main()
{
  using namespace zhalilov;
  List< pair > sequences;
  std::ifstream file("test");
  getSeqFromStream(sequences, file);
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
