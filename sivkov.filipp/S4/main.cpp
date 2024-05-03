#include <utility>
#include <iostream>
#include <string>

template <typename Key, typename Value>
struct Node
{
  Node* left;
  Node* right;
  Node* parent;
  std::pair<Key, Value> data;

  Node():
    left(nullptr),
    right(nullptr),
    parent(nullptr)
  {}

  Node(const Key& key, const Value& value):
    left(nullptr),
    right(nullptr),
    parent(nullptr),
    data(std::make_pair(key, value)) {}

  ~Node() = default;
};

template < typename Key, typename Value, typename Comp = std::less< Key > >
struct AVLTree
{
  using node = Node< Key, Value >;
  AVLTree():
    size_(0),
    root_(nullptr),
    comp_(Comp())
  {}

  AVLTree(const AVLTree& other):
    size_(0),
    root_(nullptr),
    comp_(other.comp_)
  {
    root_ = deep_copy(other.root_);
  }

  AVLTree(const AVLTree&& other):
    size_(other.size_),
    root_(other.root_),
    comp_(other.comp_)
  {
    other.root_ = nullptr;
    other.size_ = 0;
  }

  ~AVLTree()
  {
    clear();
  }

  AVLTree& operator=(const AVLTree& other)
  {
    if (this != std::addressof(other))
    {
      AVLTree< Key, Value, Comp > temp(other);
      swap(temp);
    }
    return *this;
  }

  AVLTree& operator=(const AVLTree&& other)
  {
    if (this != std::addressof(other))
    {
      swap(other);
    }
    return *this;
  }
};
