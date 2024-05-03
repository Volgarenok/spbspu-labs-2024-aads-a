#ifndef AVLTREE_HPP
#define AVLTREE_HPP

namespace chistyakov
{
  template< typename T, typename Comp = std::less< T > >
  class AVLTree
  {
    public:
      AVLTree():
        size_(0),
        root_(nullptr),
        comp_(Comp)
      {}

      AVLTree(AVLTree && tmp)
        size_(tmp.size_),
        root_(tmp.root_),
        comp_(tmp.comp_)
      {
        tmp.size_ = 0;
        tmp.root_ = nullptr;
      }

      AVLTree & operator=(const AVLTree & tmp)
      {
        swap(tmp);
        return *this;
      }

      AVLTree & operator=(const AVLTree && tmp)
      {
        swap(tmp);
        return *this;
      }

      ~AVLTree() = default;

      bool empty() const
      {
        return size_ == 0;
      }

      void swap(AVLTree tmp)
      {
        std::swap(tmp.size_, size_);
        std::swap(tmp.root_, root_);
        std::swap(tmp.comp_, comp_);
      }

      size_t size() const
      {
        return size_;
      }

    private:
      size_t size_;
      Node * root_;
      Comp comp_;
  };
}

#endif
