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
#include "output_sum_sequence_values.hpp"
#include "empty_list.hpp"

int main()
{
  try
  {
    using namespace stepanov;
    List<std::pair<std::string, List<size_t>>> sequences;

    read_sequences(sequences);
    if (sequences.empty())
    {
      std::cout << 0 << '\n';
      return 0;
    }

    if (isEmptyList(sequences))
    {
      print_sequence_names(sequences);
      std::cout << "0\n" <<std::endl;
      return 0;
    }

    auto sums = sum_sequence_values(sequences);
    print_sequence_names(sequences);
    print_sequence_values(sequences);
    output_sum_sequence_values(sums);

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
