#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

namespace chistyakov
{
  template< typename T, typename Comparator = std::less< T > >
  class Tree
  {
    public:
      Tree():
        root(nullptr),
        size(0)
      {}

      void printTree(TreeNode< T > * curr)
      {
        if (curr)
        {
          printPrint(curr->left);
          std::cout << curr->value;
          printPrint(curr->right);
        }
      }

  };
}
