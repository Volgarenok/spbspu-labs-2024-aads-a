#include <iostream>

int main()
{
  long long operand = 0ll;
  char operation = 0;
  while (!std::cin.eof())
  {
    if (std::cin)
    {
      std::cin.clear();
      std::cin >> operation;
    }
    std::cin >> operand;
  }
  std::cout << operation << " " << operand << "\n";
}
