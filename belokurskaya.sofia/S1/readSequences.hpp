#ifndef READ_SEQUENCES_HPP
#define READ_SEQUENCES_HPP

#include <iostream>

#include "list.hpp"
#include "SequencePair.hpp"

namespace belokurskaya
{
  List< SequencePair > readSequences(std::istream& in);
}

#endif
