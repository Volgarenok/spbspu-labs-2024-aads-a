#ifndef DATAARRAY_HPP
#define DATAARRAY_HPP

namespace isaychev
{
  template < class T >
  class DataArray
  {
   public:
    DataArray();
    ~DataArray();
    DataArray(const DataArray & rhs);
    DataArray(const DataArray && rhs);
    DataArray & operator=(const DataArray & rhs);
    DataArray & operator=(const DataArray && rhs);

    void push_front(T & rhs);
    void pop_front();
    void push_back(T & rhs);
    void pop_back();
    void resize();

   private:
    T * data;
  }
}

#endif
