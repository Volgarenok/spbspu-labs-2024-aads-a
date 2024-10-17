#ifndef TREE_HPP
#define TREE_HPP

#include <utility>
#include "stack.hpp"
namespace vojuck
{
  template <typename Key, typename Value>
  class BinarySearchTree
  {
  private:
    struct Node
    {
      Key key;
      Value value;
      Node* left;
      Node* right;
      Node(const Key& k, const Value& v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const Key& key, const Value& value)
    {
      if (!node)
      {
        node = new Node(key, value);
      }
      else if (key < node->key)
      {
        insert(node->left, key, value);
      }
      else if (key > node->key)
      {
        insert(node->right, key, value);
      }
    }

  public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree()
    {
      clear(root);
    }

    void push(const Key& key, const Value& value)
    {
      insert(root, key, value);
    }

    Value* get(const Key& key) const
    {
      Node* current = root;
      while (current)
      {
        if (key < current->key)
        {
          current = current->left;
        }
        else if (key > current->key)
        {
          current = current->right;
        }
        else
        {
          return &current->value;
        }
      }
        return nullptr;
    }

    class TreeIterator //:// public std::iterator< std::bidirectional_iterator_tag, Value >
    {
    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = std::pair<Key, Value>;
      using difference_type = std::ptrdiff_t;
      using pointer = value_type*;
      using reference = value_type&;
      TreeIterator() = default;

      explicit TreeIterator(Node* node)
      {
        pushLeft(node);
      }

      reference operator*()
      {
        return current;
      }

      pointer operator->()
      {
        return &current;
      }

      TreeIterator& operator++()
      {
        if (!nodes.isEmpty())
        {
          Node* node = nodes.pop();
          current = {node->key, node->value};
          pushLeft(node->right);
        }
        return *this;
      }

      bool operator==(const TreeIterator& other) const
      {
        return nodes == other.nodes;
      }

      bool operator!=(const TreeIterator& other) const
      {
        return !(*this == other);
      }

    private:
      Stack<Node*> nodes;
      value_type current;

      void pushLeft(Node* node)
      {
        while (node)
        {
          nodes.push(node);
          node = node->left;
        }
        if (!nodes.isEmpty())
        {
          current = {nodes.top()->key, nodes.top()->value};
        }
      }
    };

    class ConstTreeIterator//: public std::iterator< std::bidirectional_iterator_tag, Value >
    {
    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = const std::pair<Key, Value>;
      using difference_type = std::ptrdiff_t;
      using pointer = const value_type*;
      using reference = const value_type&;
      ConstTreeIterator() = default;

      explicit ConstTreeIterator(const Node* node)
      {
        pushLeft(node);
      }

      reference operator*() const
      {
        return current;
      }

      pointer operator->() const
      {
        return &current;
      }

      ConstTreeIterator& operator++()
      {
        if (!nodes.isEmpty())
        {
          const Node* node = nodes.pop();
          current = {node->key, node->value};
          pushLeft(node->right);
        }
        return *this;
      }

      bool operator==(const ConstTreeIterator& other) const
      {
        return nodes == other.nodes;
      }

      bool operator!=(const ConstTreeIterator& other) const
      {
        return !(*this == other);
      }

    private:
      Stack<const Node*> nodes;
      value_type current;

      void pushLeft(const Node* node)
      {
        while (node)
        {
          nodes.push(node);
          node = node->left;
        }
        if (!nodes.isEmpty())
        {
          current = {nodes.top()->key, nodes.top()->value};
        }
      }
    };


    TreeIterator begin()
    {
      return TreeIterator(root);
    }

    TreeIterator end()
    {
      return TreeIterator();
    }

    ConstTreeIterator cbegin() const
    {
      return ConstTreeIterator(root);
    }

    ConstTreeIterator cend() const
    {
      return ConstTreeIterator();
    }

  private:
    void clear(Node* node)
    {
      if (node)
      {
        clear(node->left);
        clear(node->right);
        delete node;
      }
    }
  };
}
#endif
