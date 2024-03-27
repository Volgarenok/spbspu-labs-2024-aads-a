#include <iostream>
#include <stack>
#include <queue>

int main()
{
  std::queue<int> temp;
  int number = 0;
  while (true)
  {
    std::cin >> number;
    if (number == 0)
    {
      break;
    }
    temp.push(number);
  }
  std::cout << temp.size();
  while (!temp.empty())
  {
    //int ans = temp.front();
    //std::cin << ans;
    temp.pop();
  }
}
