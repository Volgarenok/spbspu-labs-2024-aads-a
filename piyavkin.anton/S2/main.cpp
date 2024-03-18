#include <iostream>
#include <fstream>
#include "stack.hpp"
#include "queue.hpp"

int main(int argc, char* argv[])
{
  using namespace piyavkin;
  Queue< char > queue;
  if (argc != 2)
  {
    std::cerr << "The file is not specified correctly\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  char a = 0;
  input >> a;
  queue.push(a);
  std::cout << queue.drop();
}
