#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <functional>
#include <stdexcept>

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
      throw std::runtime_error("Key not found");
    }

    Value& at(const Key& key) const
    {
      Node* node = find(root, key);
      if (node)
      {
        return node->value;
      }
      throw std::out_of_range("Key not found");
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

    void erase(Key key)
    {
      root = eraseRecursive(root, key);
      if (root)
      {
        tree_size--;
      }
    }

    Value& operator[](const Key& key)
    {
      Node* node = find(root, key);
      if (node)
      {
        return node->value;
      }
      else
      {
        throw std::out_of_range("Key not found");
      }
    }

    class Iterator
    {
      Node* current;
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

      bool operator!=(const Iterator& other) const
      {
        return current != other.current;
      }

      bool operator==(const Iterator& other) const
      {
        return current == other.current;
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

    const Iterator cbegin() const
    {
      return Iterator(root, compare);
    }

    const Iterator cend() const
    {
      return Iterator(nullptr, compare);
    }
  };
}

#endif
