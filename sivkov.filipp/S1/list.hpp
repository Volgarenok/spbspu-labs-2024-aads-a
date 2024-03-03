template< class T >
class Node
{
public:
  T data_;
  Node* next_;
  Node(const T& value, Node* const next);
  Node(T&& value, Node* const next);
  ~Node() = default;
};

template< class T >
Node< T >::Node(const T& value, Node* const next) :
  data_(value),
  next_(next)
{}

template< class T >
Node< T >::Node(T&& value, Node* const next) :
  data_(value),
  next_(next)
{}


template <class T>
class List
{
public:
	List();
	~List();

  bool empty() const;
  void push_front(const T& value);
  void pop_front();
  void del();
  void swap(List< T >& list);


private:
  Node< T >* head_;
};



template<class T>
List<T>::List()
{
  head_(nullptr);
}

template<class T>
List<T>::~List()
{
  del();
}

template<class T>
bool List<T>::empty() const
{
  return !head_;
}

template<class T>
void List<T>::push_front(const T& value)
{
  Node< T >* data = new Node< T >(value, head_);
  head_ = data;
}

template<class T>
void List<T>::pop_front()
{
  Node< T >* new_head = head_->next_;
  delete head_;
  head_ = new_head;
}

template<class T>
void List<T>::del()
{
  while (head_)
  {
    pop_front();
  }
}

template<class T>
void List<T>::swap(List<T>& list)
{
  std::swap(head_, list.head_);
}
