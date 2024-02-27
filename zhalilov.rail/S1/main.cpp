#include <iostream>

#include "list.hpp"
#include "getSeqFromStream.hpp"

int main()
{
  using namespace zhalilov;
  List< pair > sequences;
  getSeqFromStream(sequences, std::cin);
}