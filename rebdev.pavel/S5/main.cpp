#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <limits>

#include <tree.hpp>

struct Key_summ
{
  void operator()(const std::pair< const int, std::string > & key_value)
  {
    if ((result_ > 0) && (key_value.first > 0))
    {
      if (result_ > (std::numeric_limits< int >::max() - key_value.first))
      {
        throw std::overflow_error("int overflow");
      }
    }
    else if ((result_ < 0) && (key_value.first < 0))
    {
      if (result_ < (std::numeric_limits< int >::min() - key_value.first))
      {
        throw std::overflow_error("int overflow");
      }
    }
    result_ += key_value.first;
    strQueue.push(key_value.second);
  }
  int result_ = 0;
  std::queue< std::string > strQueue;
};

int main(int argc, char ** argv)
{
  if (argc != 3)
  {
    std::cerr << "Bad number of input arguments!\n";
    return 1;
  }
  std::ifstream inFile(argv[2]);
  if (inFile.eof())
  {
    std::cout << "<EMPTY>\n";
    return 0;
  }
  if (!inFile.is_open())
  {
    std::cerr << "Can't open tree file!\n";
    return 1;
  }
  rebdev::AVLTree< int, std::string > tree;
  while (!inFile.eof())
  {
    int key;
    inFile >> key;
    if (!inFile && !inFile.eof())
    {
      std::cerr << "Uncorrect key!\n";
      return 1;
    }
    std::string value;
    inFile >> value;
    if (!inFile.eof())
    {
      tree[key] = value;
    }
  }
  Key_summ key;
  try
  {
    std::string inParam(argv[1]);
    if (inParam == "ascending")
    {
      tree.traverse_lnr(key);
    }
    else if (inParam == "descending")
    {
      tree.traverse_rnl(key);
    }
    else if (inParam == "breadth")
    {
      tree.traverse_breadth(key);
    }
    else
    {
      std::cerr << "Bad argument input!\n";
      return 1;
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  std::cout << key.result_;
  while (!key.strQueue.empty())
  {
    std::cout << ' ' << (key.strQueue.front());
    key.strQueue.pop();
  }
  return 0;
}
