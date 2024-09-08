#ifndef HUFFMAN_TREENODE_HPP
#define HUFFMAN_TREENODE_HPP

#include <cstddef>
#include <string>
#include "UBST.hpp"

namespace skuratov
{
  struct HuffmanTreeNode
  {
    char data;
    size_t freq;
    HuffmanTreeNode* left;
    HuffmanTreeNode* right;

    HuffmanTreeNode(char data, size_t freq):
      data(data),
      freq(freq),
      left(nullptr),
      right(nullptr)
    {}
  };

  struct Compare
  {
    bool operator()(HuffmanTreeNode* l, HuffmanTreeNode* r)
    {
      return (l->freq > r->freq);
    }
  };

  struct Context
  {
    UBST< std::string, std::string > context;
  };

  struct CodeContext
  {
    UBST< std::string, UBST< char, std::string > > codeContext;
  };
}

#endif
