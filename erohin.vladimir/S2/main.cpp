#include <iostream>

int main()
{
  long long operand = 0;
  char operation = 0;
  while (!std::cin.eof())
  {
    std::cin >> operand;
    std::cin.clear();
    std::cin >> operation;
  }
  std::cout << operation << " " << operand << "\n";
}
