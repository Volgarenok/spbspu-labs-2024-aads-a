#include <iostream>
#include "list.hpp"

void pr(size_t sth)
{
  std::cout << sth << " ";
}

bool ch(size_t sth)
{
  if (sth % 2 == 0)
  {
    return true;
  }
  return false;
}

int main()
{
  using namespace grechishnikov;

  List< size_t > testListErase;
  testListErase.assign({ 1, 2, 4, 6, 7, 9 });

//  testListErase.erase(testListErase.begin()[3]);

  std::for_each(testListErase.begin(), testListErase.end(), pr);
  std::cout << '\n';

  std::cout << testListErase[3];
  std::cout << '\n';

  List< size_t > testListRemove;
  testListRemove.assign({ 1, 2, 1, 4, 1, 1, 7, 9, 1 });
  testListRemove.remove_if(ch);

  std::for_each(testListRemove.begin(), testListRemove.end(), pr);
  std::cout << '\n';

}
