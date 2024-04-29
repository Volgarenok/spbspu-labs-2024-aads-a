#include <iostream>
#include "queue.hpp"
#include "calculatePostfix.hpp"
int main()
{
  using namespace grechishnikov;

  Queue< std::string > b;
  b.push("23");
  b.push("10");
  b.push("+");
  b.push("-140");
  b.push("-");
  try
  {
    std::cout << calculatePostfix(b) << '\n';
  }
  catch(std::exception &e)
  {
    std::cout << e.what() << '\n';
  }
}
