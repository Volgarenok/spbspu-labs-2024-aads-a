#ifndef GENERATE_HPP
#define GENERATE_HPP
#include <cstdlib>

int RandomNumberInt()
{
  return (std::rand() % 100);
}

int RandomNumberFloat()
{
  return static_cast < float > (rand()) / 1.2;
}

#endif
