#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <map>

int main()
{
  std::map< int, std::string > myMap;
  while (!std::cin.eof())
  {
    std::cin.clear();
    int keyNumber = 0;
    std::string value = "";
    while (std::cin >> keyNumber >> value)
    {
      myMap.insert(std::make_pair(keyNumber, value));
    }
  }
  std::cout << "|||" << myMap[10];
}
