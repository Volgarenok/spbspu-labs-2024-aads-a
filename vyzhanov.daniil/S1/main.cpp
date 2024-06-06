#include "List.hpp"

int main()
{
  vyzhanov::List<int> test;
  for (int i = 0; i < 20; i++)
  {
    test.Add(i);
  }
  test.Show();
  test.~List();
  test.Show();
}
