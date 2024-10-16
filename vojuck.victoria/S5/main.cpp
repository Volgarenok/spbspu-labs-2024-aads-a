#include <utility>
#include <iterator>
#include <string>
#include <limits>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <functional>
#include <cstdlib>
#include "tree.hpp"

using namespace vojuck;


struct TraversalResult
{
  long long sum;
  std::string values;

  TraversalResult() : sum(0), values("") {}

  void operator()(const std::pair<const int, std::string>& key_value)
  {
      // Проверка на переполнение при добавлении
    if ((key_value.first > 0 && sum > std::numeric_limits<long long>::max() - key_value.first) ||
        (key_value.first < 0 && sum < std::numeric_limits<long long>::min() - key_value.first))
    {
      throw std::overflow_error("overflow sum.");
    }
    sum += key_value.first;

    if (!values.empty())
    {
      values += " ";
    }
      values += key_value.second;
  }
};

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cerr << "Using: ./lab [ascending|descending|breadth] filename" << '\n';
    return EXIT_FAILURE;
  }

  std::string mode = argv[1];
  std::string filename = argv[2];

  bool ascending = false, descending = false, breadth = false;
  if (mode == "ascending")
  {
    ascending = true;
  }
  else if (mode == "descending")
  {
    descending = true;
  }
    else if (mode == "breadth")
  {
    breadth = true;
  }
  else
  {
    std::cerr << "Not ascending, descending or breadth." << '\n';
    return EXIT_FAILURE;
  }

  std::ifstream infile(filename);
  if (!infile)
  {
    std::cerr << "very bad file:(: " << filename << '\n';
    return EXIT_FAILURE;
  }


  BinarySearchTree<int, std::string> bst;

  int key;
  std::string value;
  while (infile >> key >> value)
  {
    bst.insertNew(key, value);
  }

  infile.close();

  if (bst.isEmpty())
  {
    std::cout << "<EMPTY>" << '\n';
    return EXIT_SUCCESS;
  }

  TraversalResult result;

  try
  {
    if (ascending)
    {
      bst.traverse_lnr([&result](const std::pair<const int, std::string>& kv)
      {
        result(kv);
      });
    }
    else if (descending)
    {
      bst.traverse_rnl([&result](const std::pair<const int, std::string>& kv)
      {
        result(kv);
      });
    }
    else if (breadth)
    {
      bst.traverse_breadth([&result](const std::pair<const int, std::string>& kv)
      {
        result(kv);
      });
    }
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << "error: " << e.what() << '\n';
    return EXIT_FAILURE;
  }

  if (result.sum > std::numeric_limits<int>::max() || result.sum < std::numeric_limits<int>::min())
  {
    std::cerr << "error: overflow." << '\n';
    return EXIT_FAILURE;
  }

  std::cout << result.sum << " " << result.values << '\n';

  return EXIT_SUCCESS;
}
