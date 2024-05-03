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
