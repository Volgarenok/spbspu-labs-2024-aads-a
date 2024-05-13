#include <iostream>
#include <string>
#include <limits>
#include "list.hpp"
#include "readinput.hpp"

int main() {
  petuhov::List< std::pair< std::string, petuhov::List< int > > > sequences;
  try {
    petuhov::readInput(sequences, std::cin);
  } catch (const std::overflow_error &e) {
    std::cerr << e.what() << "\n";
    return 1;
  }

  if (sequences.empty()) {
    std::cout << "0\n";
    return 0;
  }

  petuhov::List< std::string > names;
  for (petuhov::ConstIterator< std::pair< std::string, petuhov::List< int > > > it = sequences.cbegin(); it != sequences.cend(); ++it) {
    names.push_front(it->first);
  }
  names.reverse();

  for (petuhov::ConstIterator< std::string > it = names.cbegin(); it != names.cend(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << "\n";

  int max_length = 0;
  for (petuhov::ConstIterator< std::pair< std::string, petuhov::List< int > > > it = sequences.cbegin(); it != sequences.cend(); ++it) {
    int length = 0;
    for (petuhov::ConstIterator< int > num_it = it->second.cbegin(); num_it != it->second.cend(); ++num_it) {
      ++length;
    }
    if (length > max_length) {
      max_length = length;
    }
  }

  petuhov::List< petuhov::List< int > > columns;
  for (int i = 0; i < max_length; ++i) {
    petuhov::List< int > column;
    for (petuhov::ConstIterator< std::pair< std::string, petuhov::List< int > > > it = sequences.cbegin(); it != sequences.cend(); ++it) {
      petuhov::ConstIterator< int > num_it = it->second.cbegin();
      int index = 0;
      while (num_it != it->second.cend() && index < i) {
        ++num_it;
        ++index;
      }
      if (num_it != it->second.cend() && index == i) {
        column.push_front(*num_it);
      } else {
        column.push_front(-1);
      }
    }
    column.reverse();
    columns.push_front(column);
  }
  columns.reverse();

  petuhov::List< int > sums;
  for (petuhov::ConstIterator< petuhov::List< int > > col_it = columns.cbegin(); col_it != columns.cend(); ++col_it) {
    int sum = 0;
    bool has_numbers = false;
    for (petuhov::ConstIterator< int > num_it = col_it->cbegin(); num_it != col_it->cend(); ++num_it) {
      if (*num_it != -1) {
        std::cout << *num_it << " ";
        sum += *num_it;
        has_numbers = true;
      }
    }
    if (has_numbers) {
      sums.push_front(sum);
    }
    std::cout << "\n";
  }
  sums.reverse();

  for (petuhov::ConstIterator< int > sum_it = sums.cbegin(); sum_it != sums.cend(); ++sum_it) {
    std::cout << *sum_it << " ";
  }
  std::cout << "\n";

  return 0;
}
