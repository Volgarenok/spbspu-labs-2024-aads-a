#include <iostream>
#include <sstream>

template <typename T>
class Node
{
public:
  T data;
  Node* prev;
  Node* next;

  Node(const T& value):
    data(value),
    prev(nullptr),
    next(nullptr)
  {}
  ~Node() {}
};

template <typename T>
class LinkedList
{
private:
  Node<T>* head;
  Node<T>* tail;
  size_t size;
public:
  LinkedList():
    head(nullptr),
    tail(nullptr),
    size(0)
  {}
  ~LinkedList()
  {
    clear();
  }

  LinkedList& operator=(const LinkedList& other)
  {
    if (this == &other)
    {
      return *this;
    }
    clear();
    Node<T>* curr = other.head;
    while (curr)
    {
      push_back(curr->data);
      curr = curr->next;
    }
    return *this;
  }

  class Iterator
  {
  private:
    Node<T>* ptr;

  public:
    Iterator(Node<T>* node):
      ptr(node)
    {}

    Iterator& operator++()
    {
      ptr = ptr->next;
      return *this;
    }

    bool operator!=(const Iterator& other) const
    {
      return ptr != other.ptr;
    }

    T& operator*() const
    {
      return ptr->data;
    }

  };

  class ConstIterator
  {
  private:
    Node<T>* ptr;

  public:
    ConstIterator(Node<T>* node):
      ptr(node)
    {}

    ConstIterator& operator++()
    {
      ptr = ptr->next;
      return *this;
    }

    bool operator!=(const ConstIterator& other) const
    {
      return ptr != other.ptr;
    }

    const T& operator*() const
    {
      return ptr->data;
    }
  };

  Iterator begin() const
  {
    return Iterator(head);
  }

  Iterator end() const
  {
    return Iterator(nullptr);
  }

  ConstIterator cbegin() const
  {
    return ConstIterator(head);
  }

  ConstIterator cend() const
  {
    return ConstIterator(nullptr);
  }

  bool empty() const
  {
    return size == 0;
  }

  T& front() const
  {
    //if (empty()) throw std::out_of_range("List is empty");
    return head->data;
  }

  T& back() const
  {
    //if (empty()) throw std::out_of_range("List is empty");
    return tail->data;
  }

  void assign(size_t count, const T& value)
  {
    clear();
    for (size_t i = 0; i < count; ++i)
    {
      push_back(value);
    }
  }

  void emplace_front(const T& value)
  {
    Node<T>* newNode = new Node<T>(value);
    if (empty())
    {
      head = tail = newNode;
    }
    else
    {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
    ++size;
  }

  void push_front(const T& value)
  {
    emplace_front(value);
  }

  void pop_front()
  {
    if (empty())
    {
      return;
    }
    Node<T>* temp = head;
    head = head->next;
    if (head)
    {
      head->prev = nullptr;
    }
    delete temp;
    --size;
    if (size == 0)
    {
      tail = nullptr;
    }
  }

  void emplace_back(const T& value)
  {
    Node<T>* newNode = new Node<T>(value);
    if (empty())
    {
      head = tail = newNode;
    }
    else
    {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
    ++size;
  }

  void push_back(const T& value)
  {
    emplace_back(value);
  }

  void pop_back()
  {
    if (empty())
    {
      return;
    }
    Node<T>* temp = tail;
    tail = tail->prev;
    if (tail)
    {
      tail->next = nullptr;
    }
    delete temp;
    --size;
    if (size == 0)
    {
      head = nullptr;
    }
  }

  void emplace(const Iterator& pos, const T& value)
  {
    if (pos.ptr == nullptr)
    {
      emplace_back(value);
      return;
    }

    Node<T>* newNode = new Node<T>(value);
    newNode->next = pos.ptr;
    newNode->prev = pos.ptr->prev;
    if (pos.ptr->prev)
    {
      pos.ptr->prev->next = newNode;
    }
    else
    {
      head = newNode;
    }
    pos.ptr->prev = newNode;
    ++size;
  }

  void insert(const Iterator& pos, size_t count, const T& value)
  {
    for (size_t i = 0; i < count; ++i)
    {
      emplace(pos, value);
    }
  }

  Iterator erase(const Iterator& pos)
  {
    if (pos.ptr == nullptr)
    {
      return end();
    }

    Node<T>* toDelete = pos.ptr;
    Iterator nextIter(toDelete->next);
    if (toDelete->prev)
    {
      toDelete->prev->next = toDelete->next;
    }
    else
    {
      head = toDelete->next;
    }
    if (toDelete->next)
    {
      toDelete->next->prev = toDelete->prev;
    }
    else
    {
      tail = toDelete->prev;
    }
    delete toDelete;
    --size;
    return nextIter;
  }

  void swap(LinkedList& other)
  {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
  }

  void clear()
  {
    while (!empty())
    {
      pop_back();
    }
  }

  void splice(const Iterator& pos, LinkedList& other)
  {
    if (other.empty())
    {
      return;
    }

    if (pos.ptr == nullptr)
    {
      tail->next = other.head;
      other.head->prev = tail;
      tail = other.tail;
    }
    else
    {
      Node<T>* posNode = pos.ptr;
      Node<T>* beforePos = posNode->prev;

      if (beforePos)
      {
        beforePos->next = other.head;
      }
      other.head->prev = beforePos;

      posNode->prev = other.tail;
      other.tail->next = posNode;

      if (pos.ptr == head)
      {
        head = other.head;
      }
    }

    size += other.size;
    other.head = other.tail = nullptr;
    other.size = 0;
  }

  void remove(const T& value)
  {
    Node<T>* curr = head;
    while (curr)
    {
      if (curr->data == value)
      {
        Node<T>* toDelete = curr;
        curr = curr->next;
        erase(Iterator(toDelete));
      }
      else
      {
        curr = curr->next;
      }
    }
  }

  template <typename Predicate>
  void remove_if(Predicate pred)
  {
    Node<T>* curr = head;
    while (curr)
    {
      if (pred(curr->data))
      {
        Node<T>* toDelete = curr;
        curr = curr->next;
        erase(Iterator(toDelete));
      }
      else
      {
        curr = curr->next;
      }
    }
  }

  void unique()
  {
    Node<T>* curr = head;
    while (curr && curr->next)
    {
      if (curr->data == curr->next->data)
      {
        Node<T>* toDelete = curr->next;
        curr->next = curr->next->next;
        if (curr->next)
        {
          curr->next->prev = curr;
        }
        delete toDelete;
        --size;
      }
      else
      {
        curr = curr->next;
      }
    }
  }

  void merge(LinkedList& other)
  {
    if (this == &other)
    {
      return;
    }

    Node<T>* thisCurr = head;
    Node<T>* otherCurr = other.head;

    while (thisCurr && otherCurr)
    {
      if (thisCurr->data > otherCurr->data)
      {
        Node<T>* temp = otherCurr;
        otherCurr = otherCurr->next;
        temp->next = thisCurr;
        temp->prev = thisCurr->prev;
        if (thisCurr->prev)
        {
          thisCurr->prev->next = temp;
        }
        thisCurr->prev = temp;
        if (thisCurr == head)
        {
          head = temp;
        }
        ++size;
      }
      else
      {
        thisCurr = thisCurr->next;
      }
    }

    if (otherCurr)
    {
      if (!head)
      {
        head = other.head;
      }
      if (tail)
      {
        tail->next = other.head;
      }
      other.head->prev = tail;
      tail = other.tail;
      size += other.size;
    }

    other.head = other.tail = nullptr;
    other.size = 0;
  }

  void sort()
  {
    if (size < 2)
    {
      return;
    }

    bool swapped = true;
    while (swapped)
    {
      swapped = false;
      Node<T>* curr = head;
      while (curr->next)
      {
        if (curr->data > curr->next->data)
        {
          std::swap(curr->data, curr->next->data);
          swapped = true;
        }
        curr = curr->next;
      }
    }
  }

  void reverse()
  {
    Node<T>* curr = head;
    while (curr)
    {
      std::swap(curr->prev, curr->next);
      curr = curr->prev;
      if (curr && curr->prev == nullptr)
      {
        head = curr;
      }
    }
    std::swap(head, tail);
  }
};

int main()
{
  constexpr size_t maxvalue = std::numeric_limits<size_t>::max();

  LinkedList<std::pair<std::string, LinkedList<size_t>>> pairs;
  std::string str;
  std::istream& input = std::cin;
  input >> str;
  while (input)
  {
    pairs.push_back({ str, LinkedList<size_t>() });
    input >> str;
    while (input && std::isdigit(str[0]))
    {
      pairs.back().second.push_back(std::stoull(str));
      input >> str;
    }
  }
  auto iter = pairs.begin();
  auto end = pairs.end();

  while (iter != end)
  {
    std::cout << (*iter).first;
    if (++iter != end)
    {
      std::cout << " ";
    }
  }

  if (!pairs.empty())
  {
    std::cout << "\n";
  }

  LinkedList<size_t> lst;
  while (!pairs.empty())
  {
    size_t sum = 0;
    bool anyNonEmptyList = false;

    for (auto& pair : pairs)
    {
      if (!pair.second.empty())
      {
        if (anyNonEmptyList)
        {
          std::cout << " ";
        }
        anyNonEmptyList = true;
        std::cout << pair.second.front();
        size_t size_n = pair.second.front();
        if (sum + pair.second.front() <= maxvalue)
        {
          sum += pair.second.front();
          pair.second.pop_front();
        }
        else
        {
          lst.push_back(sum);
          sum = 0;
          std::cerr << "Overflow!\n";
          return 1;
        }
      }
    }

    if (!anyNonEmptyList)
    {
      break;
    }

    lst.push_back(sum);
    std::cout << "\n";
  }

  for (auto& sum : lst)
  {
    std::cout << sum << " ";
  }
  std::cout << "\n";

  if (lst.empty())
  {
    std::cout << "0\n";
  }
}
