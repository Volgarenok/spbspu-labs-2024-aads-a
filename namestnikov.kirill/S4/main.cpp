#include <iostream>
#include <string>
#include <map>

int main()
{
  std::map< char, int > letters{{'a', 27}, {'b', 3}, {'c', 1}};
  letters['b'] = 57;
  letters['c'] = 24;
  for (const auto & pair : letters)
  {
    std::cout << "{" << pair.first << ";" << pair.second << "}";
  }
}
