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
      if (!node)
      {
        return nullptr;
      }
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

    Node* findNode(const Key& key) const
    {
      Node* current = root;
      while (current != nullptr)
      {
        if (compare(key, current->key) < 0)
        {
          current = current->left;
        }
        else if (compare(key, current->key) > 0)
        {
          current = current->right;
        }
        else
        {
          return current;
        }
      }
      return nullptr;
    }

    Value& at(const Key& key)
    {
      Node* node = findNode(key);
      if (node == nullptr)
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

    size_t size() const noexcept
    {
      return tree_size;
    }

    bool empty() const noexcept
    {
      return tree_size == 0;
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
        Node* newNode = new Node(key, Value());
        root = insert(root, key, Value());
        return newNode->value;
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

      public:
        Iterator(Node* rootNode, const Compare& comp):
          current(leftMost(rootNode)),
          root(rootNode),
          compare(comp)
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
            Node* ancestor = const_cast< Node* >(root);
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
      return Iterator(root, compare);
    }

    Iterator end() const
    {
      return Iterator(nullptr, compare);
    }

    private:
      Node* erase(Node* node, Key key)
      {
        if (!node)
        {
          return nullptr;
        }

        if (compare(key, node->key))
        {
          node->left = erase(node->left, key);
        }
        else if (compare(node->key, key))
        {
          node->right = erase(node->right, key);
        }
        else
        {
          if (!node->left)
          {
            Node* rightChild = node->right;
            delete node;
            tree_size--;
            return rightChild;
          }
          else if (!node->right)
          {
            Node* leftChild = node->left;
            delete node;
            tree_size--;
            return leftChild;
          }
          else
          {
            Node* successor = leftMost(node->right);
            node->key = successor->key;
            node->value = successor->value;
            node->right = erase(node->right, successor->key);
          }
        }
        return node;
      }
  };
}

#endif
