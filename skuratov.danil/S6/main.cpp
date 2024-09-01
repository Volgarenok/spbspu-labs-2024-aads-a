#include <iostream>  
#include <cstdlib>  
#include <ctime>  

int main(/*int argc, char* argv[]*/)
{
  /*if (argc != 4)
  {
    std::cerr << "Not enough arguments" << '\n';
    return 1;
  }*/

  srand(static_cast< unsigned int >(time(0)));

  for (int i = 0; i < 10; ++i)
  {
    int randomNumber = rand() % 100;
    std::cout << randomNumber << " " << '\n';
  }
  return 0;
}
