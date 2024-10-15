#include <iostream>
#include <string>
#include "tree.hpp"

int main()
{
  vojuck::BinarySearchTree<int, std::string> bst;
  int choice;

  std::cout << "Binary Search Tree - Manual Input\n";
  std::cout << "Enter 1 to insert a key-value pair, 2 to display tree, 3 to exit.\n";

  do
  {
    std::cout << '\n' << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 1)
    {
      int key;
      std::string value;

      std::cout << "Enter key (integer): ";
      std::cin >> key;
      std::cin.ignore();

      std::cout << "Enter value (string): ";
      std::getline(std::cin, value);

      bst.push(key, value);
      std::cout << "Inserted (" << key << ", " << value << ") into the tree.\n";
    }
    else if (choice == 2)
    {
      std::cout << "Current tree (in-order traversal):\n";
      for (auto it = bst.begin(); it != bst.end(); ++it)
      {
        std::cout << it->first << ": " << it->second << std::endl;
      }
    }
    else if (choice != 3)
    {
      std::cout << "Invalid choice. Please try again.\n";
    }

  }
  while (choice != 3);

  std::cout << "Exiting program.\n";
  return 0;
}
