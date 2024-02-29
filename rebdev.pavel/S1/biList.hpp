#ifndef BILIST
#define BILIST

namespace rebdev
{
  template < typename T >
  class BiList
  {
    public:
    BiList();
    BiList(const BiList & OldList);
    BiList(const Bilist && rList);
    BiList(T firstElement);

    ~BiList();

    BiList & operator = (const BiList & OldList);
    BiList & operator = (const BiList && OldList);

    T element(size_t numOfElement);
    BiList & push(T newElement);
    T pop();
    void clear();
    void swap(Bilist * secondList);

    iterator begin();
    iteretor end();

    int capacity();
    private:
    T data;
    BiList * last;
    BiList * next;
  };
}
#endif
