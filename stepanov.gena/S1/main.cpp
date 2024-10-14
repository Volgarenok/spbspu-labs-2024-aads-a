#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <limits>
#include "list.hpp"
#include "node.hpp"
#include "iterator.hpp"
#include "constiterator.hpp"
#include "read_sequencess.hpp"
#include "print_sequence_names.hpp"
#include "print_sequence_values.hpp"
#include "sum_sequence_values.hpp"

int main() 
{
  try
  {
    using namespace stepanov;

    auto sequences = read_sequences();
    print_sequence_names(sequences);

    if (sequences.empty()) {
      std::cout << "0\n";  
      return 0;
    }

    bool allEmpty = true;
    for (const auto& seq : sequences)
    {
      if (!seq.second.empty())
      {
        allEmpty = false;
        break; 
      }
    }

    if (allEmpty) {
      std::cout << "0\n"; 
      return 0;
    }

    print_sequence_values(sequences);
    sum_sequence_values(sequences);
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
