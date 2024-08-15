#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

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
      if (!node) return nullptr;
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

    class Iterator
    {
      Node* current;
      const Node* root;
      bool finished = false;

      Node* leftMost(Node* node)
      {
        if (node == nullptr)
        {
          return nullptr;
        }
        while (node->left != nullptr)
        {
          node = node->left;
        }
        return node;
      }

      public:
        Iterator(Node* rootNode):
          current(leftMost(rootNode)),
          root(rootNode)
        {}

        std::pair< Key, Value > operator*() const
        {
          return std::make_pair(current->key, current->value);
        }

        Iterator& operator++()
        {
          if (current == nullptr)
          {
            finished = true;
            return *this;
          }

          if (current->right != nullptr)
          {
            current = leftMost(current->right);
          }
          else
          {
            Node* successor = nullptr;
            Node* ancestor = root;
            while (ancestor != current)
            {
              if (compare(current->key, ancestor->key))
              {
                successor = ancestor;
                ancestor = ancestor->left;
              }
              else
              {
                ancestor = ancestor->right;
              }
            }
            current = successor;
          }

          return *this;
        }

        bool operator!=(const Iterator& other) const
        {
          return current != other.current || finished != other.finished;
        }

        bool operator==(const Iterator& other) const
        {
          return !(*this != other);
        }
    };

    Iterator begin() const
    {
      return Iterator(root);
    }

    Iterator end() const
    {
      return Iterator(nullptr);
    }
  };
}

#endif
