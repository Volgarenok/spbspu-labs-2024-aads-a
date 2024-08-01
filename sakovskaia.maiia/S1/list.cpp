 #include "list.hpp"

template < typename T >
typename std::forward_list < T >::iterator List < T >::begin()
{
  return data.begin();
}

template < typename T >
typename std::forward_list < T >::const_iterator List < T >::begin() const
{
  return data.begin();
}

template < typename T >
typename std::forward_list < T >::const_iterator List < T >::cbegin() const
{
  return data.cbegin();
}

template < typename T >
typename std::forward_list < T >::iterator List < T >::end()
{
  return data.end();
}

template < typename T >
typename std::forward_list < T >::const_iterator List < T >::end() const
{
  return data.end();
}

template < typename T >
typename std::forward_list < T >::const_iterator List < T >::cend() const
{
  return data.cend();
}

template < typename T >
T & List < T >::front()
{
  return data.front();
}

template < typename T >
const T & List < T >::front() const
{
  return data.front();
}

template < typename T >
bool List < T >::empty() const
{
  return data.empty();
}

template < typename T >
void List < T >::push_back(const T & value)
{
  data.insert_after(before_end(), value);
}

template < typename T >
void List < T >::pop_front()
{
  data.pop_front();
}

template < typename T >
void List < T >::clear()
{
  data.clear();
}

template < typename T >
void List < T >::swap(List < T > & other)
{
  data.swap(other.data);
}

template < typename T >
typename std::forward_list < T >::iterator List < T >::before_end()
{
  auto i = data.before_begin();
  auto prev = i;
  for (i = data.begin(); i != data.end(); ++i)
  {
      prev = i;
  }
  return prev;
}
