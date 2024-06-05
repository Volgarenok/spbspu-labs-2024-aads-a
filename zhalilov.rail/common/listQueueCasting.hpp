#ifndef LISTQUEUECASTING_HPP
#define LISTQUEUECASTING_HPP

#include <queue.hpp>
#include <list/list.hpp>

namespace zhalilov
{
  template < class T >
  void listToQueue(const List< T > &list, Queue< T > &queue)
  {
    auto it = list.cbegin();
    auto end = list.cend();
    while (it != end)
    {
      queue.push(*it);
      ++it;
    }
  }

  template < class T >
  void queueToList(Queue< T > queue, List< T > &list)
  {
    while (!queue.empty())
    {
      list.push_back(queue.front());
      queue.pop();
    }
  }
}

#endif
