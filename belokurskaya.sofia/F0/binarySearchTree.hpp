#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <functional>
#include <stdexcept>

#include "MyVector.hpp"

namespace belokurskaya
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class BinarySearchTree
  {
    struct Node
    {
      Key key;
      Value value;
      Node* left;
      Node* right;
      Node(Key k, Value v):
        key(k),
        value(v),
        left(nullptr),
        right(nullptr)
      {}
    };

    Node* root;
    Compare compare;
    size_t tree_size;

    void clear(Node* node)
    {
      if (node)
      {
        clear(node->left);
        clear(node->right);
        delete node;
        tree_size--;
      }
    }

    Node* copy(Node* node)
    {
      if (!node) return nullptr;
      Node* newNode = new Node(node->key, node->value);
      newNode->left = copy(node->left);
      newNode->right = copy(node->right);
      return newNode;
    }

    Node* find(Node* node, Key key) const 
    {
      if (!node)
      {
        return nullptr;
      }
      if (compare(key, node->key))
      {
        return find(node->left, key);
      }
      else if (compare(node->key, key))
      {
        return find(node->right, key);
      }
      else
      {
        return node;
      }
    }

    Node* insert(Node* node, Key key, Value value)
    {
      if (!node)
      {
        tree_size++;
        return new Node(key, value);
      }
      if (compare(key, node->key))
      {
        node->left = insert(node->left, key, value);
      }
      else if (compare(node->key, key))
      {
        node->right = insert(node->right, key, value);
      }
      return node;
    }

    bool containsRecursive(Node* node, const Key& key) const
    {
      if (node == nullptr)
      {
        return false;
      }
      if (key < node->key)
      {
        return containsRecursive(node->left, key);
      }
      else if (key > node->key)
      {
        return containsRecursive(node->right, key);
      }
      return true;
    }

    Node* eraseRecursive(Node* node, Key key)
    {
      if (!node)
      {
        return nullptr;
      }

      if (compare(key, node->key))
      {
        node->left = eraseRecursive(node->left, key);
      }
      else if (compare(node->key, key))
      {
        node->right = eraseRecursive(node->right, key);
      }
      else
      {
        if (!node->left && !node->right)
        {
          delete node;
          return nullptr;
        }
        else if (!node->left)
        {
          Node* temp = node->right;
          delete node;
          return temp;
        }
        else if (!node->right)
        {
          Node* temp = node->left;
          delete node;
          return temp;
        }
        else
        {
          Node* temp = node->left ? node->left : node->right;
          delete node;
          return temp;
        }
      }
      return node;
    }

    Node* search(Node* node, const Key& key) const
    {
      if (node == nullptr)
      {
        throw std::invalid_argument("No element found with the given key");
      }
      if (key < node->key)
      {
        return search(node->left, key);
      }
      else if (key > node->key)
      {
        return search(node->right, key);
      }
      return node;
    }

    void getAllKeysRecursive(const Node* node, MyVector< Key >& keys) const
    {
      if (node != nullptr)
      {
        getAllKeysRecursive(node->left, keys);
        keys.push_back(node->key);
        getAllKeysRecursive(node->right, keys);
      }
    }

    void displayRecursive(const Node* node, std::ostream& out, const std::string& separator) const
    {
      if (node != nullptr)
      {
        displayRecursive(node->left, out, separator);
        if (node->left != nullptr)
        {
          out << separator;
        }
        out << node->key << ": " << node->value;
        if (node->right != nullptr)
        {
          out << separator;
        }
        displayRecursive(node->right, out, separator);
      }
    }

    Node* insertRecursive(Node* node, const Key& key, const Value& value)
    {
      if (node == nullptr)
        return new Node(key, value);
      if (key < node->key)
      {
        node->left = insertRecursive(node->left, key, value);
      }
      else if (key > node->key)
      {
        node->right = insertRecursive(node->right, key, value);
      }
      else
      {
          return node;
      }
      return node;
    }

    void deleteElementsRecursive(Node* node)
    {
      if (node != nullptr)
      {
        DELETE(node->key);
        deleteElementsRecursive(node->left);
        deleteElementsRecursive(node->right);
      }
    }

    Node* deleteRecursive(Node* node, const Key& key)
    {
      if (node == nullptr)
      {
        return node;
      }
      if (key < node->key)
      {
        node->left = deleteRecursive(node->left, key);
      }
      else if (key > node->key)
      {
        node->right = deleteRecursive(node->right, key);
      }
      else
      {
        if (node->left == nullptr || node->right == nullptr)
        {
          Node* temp = node->left ? node->left : node->right;
          if (temp == nullptr)
          {
            temp = node;
            node = nullptr;
          }
          else
          {
            *node = *temp;
          }
          delete temp;
        }
        else
        {
          Node* temp = getMinValueNode(node->right);
          node->key = temp->key;
          node->value = temp->value;
          node->right = deleteRecursive(node->right, temp->key);
        }
      }
      return node;
    }

    Node* getMinValueNode(Node* node) const
    {
      Node* current = node;
      while (current && current->left != nullptr)
      {
        current = current->left;
      }
      return current;
    }

  public:
    BinarySearchTree():
      root(nullptr),
      tree_size(0)
    {}

    ~BinarySearchTree()
    {
      clear(root);
    }

    BinarySearchTree(const BinarySearchTree& other)
    {
      root = copy(other.root);
      tree_size = other.tree_size;
    }

    BinarySearchTree& operator=(const BinarySearchTree& other)
    {
      if (this != &other)
      {
        clear(root);
        root = copy(other.root);
        tree_size = other.tree_size;
      }
      return *this;
    }

    void swap(BinarySearchTree& other)
    {
      std::swap(root, other.root);
      std::swap(tree_size, other.tree_size);
      std::swap(compare, other.compare);
    }

    void push(Key key, Value value)
    {
      root = insert(root, key, value);
    }

    Value get(Key key) const
    {
      Node* node = find(root, key);
      if (node) return node->value;
      {
        throw std::runtime_error("Key not found");
      }
    }

    Value at(const Key& key)
    {
      Node* node = find(root, key);
      if (!node)
      {
        throw std::out_of_range("Key not found");
      }
      return node->value;
    }

    bool exists(Key key) const
    {
      return find(root, key) != nullptr;
    }

    void clear()
    {
      clear(root);
      root = nullptr;
      tree_size = 0;
    }

    size_t size() const
    {
      return tree_size;
    }

    bool empty() const
    {
      return tree_size == 0;
    }

    bool contains(const Key& key) const
    {
      return containsRecursive(root, key);
    }

    Value& SEARCH(const Key& key) const
    {
      return search(root, key)->value;
    }

    void INSERT(const Key& key, const Value& value)
    {
      root = insertRecursive(root, key, value);
    }

    MyVector< Key > getAllKeys() const
    {
      MyVector< Key > keys;
      getAllKeysRecursive(root, keys);
      return keys;
    }

    void DELETE(const Key& key)
    {
      root = deleteRecursive(root, key);
    }

    void display(std::ostream& out, const std::string separator = ", ") const
    {
      displayRecursive(root, out, separator);
    }

    void erase(Key key)
    {
      root = eraseRecursive(root, key);
      if (root)
      {
        tree_size--;
      }
    }

    void deleteElements(const BinarySearchTree< Key, Value >& other)
    {
      deleteElementsRecursive(other.root);
    }

    Node* find(Key key) const
    {
      return find(root, key);
    }

    class Iterator
    {
      Node* current;
      Node* node_;
      const Node* root;
      bool finished = false;
      std::function< Node*(Node*) > nextFunc;
      Compare compare;

      Node* leftMost(Node* node)
      {
        while (node && node->left)
        {
          node = node->left;
        }
        return node;
      }

      Node* inOrderSuccessor(Node* node)
      {
        if (node->right)
        {
          return leftMost(node->right);
        }

        Node* successor = nullptr;
        Node* ancestor = const_cast< Node* >(root);
        while (ancestor != node)
        {
          if (compare(node->key, ancestor->key))
          {
            successor = ancestor;
            ancestor = ancestor->left;
          }
          else
          {
            ancestor = ancestor->right;
          }
        }
        return successor;
      }

      public:
      Iterator():
        current(nullptr),
        node_(nullptr),
        root(nullptr),
        finished(true)
      {}

      Iterator(Node* node):
        node_(node)
      {
        if (node_ == nullptr)
        {
          *this = Iterator();
        }
      }

      Iterator(Node* rootNode, Compare comp):
        current(leftMost(rootNode)),
        root(rootNode),
        compare(comp)
      {
        nextFunc = std::bind(&Iterator::inOrderSuccessor, this, std::placeholders::_1);
      }

      std::pair< Key, Value > operator*() const
      {
        return std::make_pair(current->key, current->value);
      }

      Iterator& operator++()
      {
        if (current)
        {
          current = nextFunc(current);
        }
        return *this;
      }

      bool operator==(const Iterator& other) const
      {
        return current == other.current;
      }

      friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
      {
        return lhs.current != rhs.current;
      }
    };

    Iterator begin() const
    {
      return Iterator(root, compare);
    }

    Iterator end() const
    {
      return Iterator(nullptr, compare);
    }
  };
}

#endif
