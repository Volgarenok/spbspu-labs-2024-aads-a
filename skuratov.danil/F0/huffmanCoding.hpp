#ifndef HUFFMAN_CODING_HPP
#define HUFFMAN_CODING_HPP

#include <vector>
#include "huffmanTreeNode.hpp"
#include "queue.hpp"

namespace skuratov
{
  void storeCodes(HuffmanTreeNode* root, const std::string& str, UBST< char, std::string >& huffmanCodes);
  void createHuffmanCodes(const std::string& text, UBST< char, std::string >& huffmanCodes);
  bool compressText(const std::string& text, const UBST< char, std::string >& huffmanCodes, std::string& encodedText);
  bool decompressText(const std::string& encodedText, const UBST< char, std::string >& huffmanCodes, std::string& decodedText);
  double calculateEfficiency(const std::string& text, const UBST< char, std::string >& huffmanCodes);
  bool compareByLength(const std::string& a, const std::string& b);
  bool sortByDescendingFreq(HuffmanTreeNode* a, HuffmanTreeNode* b);
}

#endif
