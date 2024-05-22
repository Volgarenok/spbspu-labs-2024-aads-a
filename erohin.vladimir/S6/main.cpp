#include <iostream>
#include <stdexcept>
#include <deque>
#include <forward_list>
#include <list>
#include <algorithm>

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Wrong CLA's number\n";
    return 1;
  }
  try
  {
    size_t size = std::stoull(argv[3]);
    if (size == 0)
    {
      throw std::invalid_argument("Invalid sequence size");
    }
    std::deque< int > random_seq;
    for (size_t i = 0; i < size; ++i)
    {
      random_seq.push_back(rand());
      std::cout << random_seq.back() << std::endl;
    }
    std::sort(random_seq.begin(), random_seq.end());
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  return 0;
}
