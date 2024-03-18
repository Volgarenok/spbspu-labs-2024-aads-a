#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace chistyakov
{
  template< typename T >
  class Iterator
  {
    public:
      Iterator():
        biList_(nullptr)
      {}

      Iterator(const Iterator & val):
        biList_(val)
      {}

      ~Iterator() = default;

    private:
      BiList< T > * biList_;
  };
}

#endif
