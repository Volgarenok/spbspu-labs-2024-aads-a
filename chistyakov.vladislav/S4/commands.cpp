#include "commands.hpp"

chistyakov::printImpl(AVLTree * dataset)
{
  if (dataset.left != nullptr)
  {
    printImpl(dataset->left);
  }

  std::cout << dataset.value.first << " " << dataset.value.second << " ";

  if (dataset.right != nullptr)
  {
    printImpl(dataset->right);
  }
}

chistyakov::print(AVLTree * dataset)
{
  if (dataset == nullptr)
  {
    std::cout << "<EMPTY>";
  }
  else
  {
    printImpl(dataset);
  }
}
