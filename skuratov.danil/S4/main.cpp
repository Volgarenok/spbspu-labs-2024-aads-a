#include <iostream>

namespace skuratov
{
  namespace detail
  {
    template < typename Key, typename Value >
    struct TreeNode
    {
      TreeNode(const Key key, const Value value):
        parent_(nullptr),
        left_(nullptr),
        right_(nullptr),
        data_(std::pair< Key, Value >(key, value))
      {}
      ~TreeNode() = default;
      TreeNode* parent_;
      TreeNode* left_;
      TreeNode* right_;
      std::pair< Key, Value > data;
    };
  }

  template < typename Key, typename Value, typename Compare >
  class AVLTree
  {
  public:
    AVLTree():
      root_(nullptr),
      cmp_(Compare()),
      size_(0)
    {}

    ~AVLTree()
    {
      clear();
    }

    AVLTree(const AVLTree& diff):
      root_(nullptr),
      cmp_(diff.cmp_),
      size_(0)
    {
      try
      {
        for (auto it = diff.cbegin(); it != diff.cend(); it++)
        {
          push(it->first, it->second)
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    AVLTree(const AVLTree&& diff):
      root_(diff.root_),
      cmp_(diff.cmp_),
      size_(diff.size_)
    {
      diff.root_ = nullptr;
      diff.size_ = 0;
    }

    size_t size() const;
    bool empty() const noexcept;
    void clear() noexcept;
    void swap();

    void push(Key k, Value v);
    Value get(Key k);
    Value drop(Key k);
  private:
    detail::TreeNode< Key, Value >* root_;
    Compare* cmp_;
    size_t size_;
  };

  int main()
  {
    std::cout << "Hello!";
    return 0;
  }
}
