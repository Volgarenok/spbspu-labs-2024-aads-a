#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include "node.hpp"

namespace vyzhanov
{
	template< class T >
	class List;

	template < typename T >
	class Iterator : public std::iterator< std::bidirectional_iterator_tag, T >
	{
	  friend List< T >;
	  using node = Node< T >;
	  using iterator = Iterator< T >;
	public:
	  Iterator() = default;
	  Iterator(const iterator& it) = default;
	  Iterator(iterator&& it) = default;
	  ~Iterator() = default;
	};

}
#endif
