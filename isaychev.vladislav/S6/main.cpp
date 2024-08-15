#include "do_cmd.hpp"

int main(int argc, char * argv[])
{
  if (argc != 4)
  {
    return 1;
  }

  size_t amount = strtoull(argv[3], nullptr, 10);
  if (amount == 0)
  {
    return 2;
  }
}
