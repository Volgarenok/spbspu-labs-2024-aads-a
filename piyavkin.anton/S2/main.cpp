#include <iostream>
#include <fstream>
#include "stack.hpp"
#include "queue.hpp"
#include "input.hpp"
#include "partexpression.hpp"

int main(int argc, char* argv[])
{
  using namespace piyavkin;
  std::cout << argc << argv[1];
  // List< Queue< char > > queues;
  // if (argc == 1)
  // {
  //   input(std::cin, queues);
  // }
  // else if (argc == 2)
  // {
  //   std::ifstream in(argv[1]);
  //   input(in, queues);
  // }
  // else
  // {
  //   std::cerr << "The file is not specified correctly\n";
  //   return 1;
  // }
  // while (!queues.begin()->empty())
  // {
  //   std::cout << queues.begin()->drop() << ' ';
  // }
  // std::cout << '\n';
  Queue< int > q;
  q.push(5);
  Queue< int > q3;
  q3 = std::move(q);
  std::cout << q3.drop();
}