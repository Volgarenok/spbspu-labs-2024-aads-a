#ifndef TREE_HPP
#define TREE_HPP

#include <utility>
#include <functional>
#include "stack.hpp"
#include "queue.hpp"
namespace vojuck
{
  template <typename Key, typename Value>
  class BinarySearchTree
  {
  private:
    struct Node
    {
      std::pair<const Key, Value> key_value;
      Node* left;
      Node* right;

      Node(const Key& key, const Value& value) :
      key_value(std::make_pair(key, value)),
      left(nullptr),
      right(nullptr)
      {}
     };

  Node* root_;

  public:
    BinarySearchTree() : root_(nullptr)
    {}


    BinarySearchTree(const std::function<bool(const Key&, const Key&)>& comp) :
      root_(nullptr), comparator_(comp)
      {}

      ~BinarySearchTree()
      {
        clear(root_);
      }

      BinarySearchTree(const BinarySearchTree&) = delete;
      BinarySearchTree& operator=(const BinarySearchTree&) = delete;
      BinarySearchTree(BinarySearchTree&&) = delete;
      BinarySearchTree& operator=(BinarySearchTree&&) = delete;


      void insertNew(const Key& key, const Value& value)
      {
        if (root_ == nullptr)
        {
          root_ = new Node(key, value);
          return;
        }

        Node* current = root_;
        Node* parent = nullptr;

        while (current != nullptr)
        {
          parent = current;
          if (comparator_(key, current->key_value.first))
          {
            current = current->left;
          }
          else if (comparator_(current->key_value.first, key))
          {
            current = current->right;
          }
          else
          {
            current->key_value.second = value;
            return;
          }
        }

        if (comparator_(key, parent->key_value.first))
        {
          parent->left = new Node(key, value);
        }
        else
        {
          parent->right = new Node(key, value);
        }
      }

      class InOrderIterator
      {
      public:
        InOrderIterator(Node* root)
        {
          pushLeft(root);
        }

        bool hasNext() const
        {
          return !stack_.isEmpty();
        }

        std::pair<const Key, Value>& next()
        {
          Node* node = stack_.pop();
          current_ = &node->key_value;
          pushLeft(node->right);
          return *current_;
        }

      private:
        vojuck::Stack<Node*> stack_;
        std::pair<const Key, Value>* current_;

        void pushLeft(Node* node)
        {
          while (node != nullptr)
          {
            stack_.push(node);
            node = node->left;
          }
        }
      };

      class ConstInOrderIterator
      {
      public:
        ConstInOrderIterator(const Node* root)
        {
          pushLeft(root);
        }

        bool hasNext() const
        {
          return !stack_.isEmpty();
        }

        const std::pair<const Key, Value>& next()
        {
          const Node* node = stack_.pop();
          current_ = &node->key_value;
          pushLeft(node->right);
          return *current_;
        }

      private:
        vojuck::Stack<const Node*> stack_;
        const std::pair<const Key, Value>* current_;

        void pushLeft(const Node* node)
        {
          while (node != nullptr)
          {
            stack_.push(node);
            node = node->left;
          }
        }
      };

      class BreadthFirstIterator
      {
      public:
        BreadthFirstIterator(Node* root)
        {
          if (root != nullptr)
          {
            queue_.push(root);
          }
        }

        bool hasNext() const
        {
          return !queue_.isEmpty();
        }

        std::pair<const Key, Value>& next()
        {
          Node* node = queue_.drop();
          current_ = &node->key_value;

          if (node->left != nullptr)
            queue_.push(node->left);
          if (node->right != nullptr)
            queue_.push(node->right);

          return *current_;
        }

      private:
        vojuck::Queue<Node*> queue_;
        std::pair<const Key, Value>* current_;
      };


      InOrderIterator getInOrderIterator()
      {
        return InOrderIterator(root_);
      }

      ConstInOrderIterator getConstInOrderIterator() const
      {
        return ConstInOrderIterator(root_);
      }

      BreadthFirstIterator getBreadthFirstIterator()
      {
        return BreadthFirstIterator(root_);
      }


      template< typename F >
      F traverse_lnr(F f) const
      {
        vojuck::Stack<Node*> stack;
        const Node* current = root_;

        while (current != nullptr || !stack.isEmpty())
        {
          while (current != nullptr)
          {
            stack.push(const_cast<Node*>(current));
            current = current->left;
          }

          current = stack.pop();
          f(current->key_value);
          current = current->right;
        }

        return f;
      }

      template< typename F >
      F traverse_rnl(F f) const
      {
        vojuck::Stack<Node*> stack;
        const Node* current = root_;

        while (current != nullptr || !stack.isEmpty())
        {
          while (current != nullptr)
          {
            stack.push(const_cast<Node*>(current));
            current = current->right;
          }

          current = stack.pop();
          f(current->key_value);
          current = current->left;
        }

        return f;
      }

      template< typename F >
      F traverse_breadth(F f) const
      {
        if (root_ == nullptr)
          return f;

        vojuck::Queue<Node*> queue;
        queue.push(const_cast<Node*>(root_));

        while (!queue.isEmpty())
        {
          Node* current = queue.drop();
          f(current->key_value);

          if (current->left != nullptr)
            queue.push(current->left);
            if (current->right != nullptr)
              queue.push(current->right);
        }

          return f;
      }
      bool isEmpty() const
      {
        return root_ == nullptr;
      }

    private:
      std::function<bool(const Key&, const Key&)> comparator_ =
        [](const Key& a, const Key& b) -> bool { return a < b; };

      void clear(Node* node)
      {
        if (node == nullptr)
          return;
          clear(node->left);
          clear(node->right);
          delete node;
      }
  };
}

#endif
