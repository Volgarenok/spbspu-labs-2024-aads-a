#include "huffmanCoding.hpp"

void skuratov::storeCodes(HuffmanTreeNode* root, const std::string& str, UBST< char, std::string >& huffmanCodes)
{
  if (root == nullptr)
  {
    return;
  }
  if (root->data != '$')
  {
    huffmanCodes[root->data] = str;
  }
  storeCodes(root->left, str + "0", huffmanCodes);
  storeCodes(root->right, str + "1", huffmanCodes);
}

void skuratov::createHuffmanCodes(const std::string& text, UBST< char, std::string >& huffmanCodes)
{
  UBST< char, int > freq;
  for (char c : text)
  {
    freq[c]++;
  }

  Queue< HuffmanTreeNode* > minHeap;
 
  for (const auto& pair : freq)
  {
    minHeap.push(new HuffmanTreeNode(pair.first, pair.second));
  }

  while (minHeap.size() > 1)
  {
    HuffmanTreeNode* left = nullptr;
    HuffmanTreeNode* right = nullptr;

    if (!minHeap.empty())
    {
      left = minHeap.front();
      minHeap.drop();
    }

    if (!minHeap.empty())
    {
      right = minHeap.front();
      minHeap.drop();
    }

    HuffmanTreeNode* top = new HuffmanTreeNode('$', left->freq + right->freq);
    top->left = left;
    top->right = right;

    minHeap.push(top);

    std::vector< HuffmanTreeNode* > temp;
    while (!minHeap.empty())
    {
      temp.push_back(minHeap.front());
      minHeap.drop();
    }

    std::sort(temp.begin(), temp.end(), sortByDescendingFreq);

    for (HuffmanTreeNode* node : temp)
    {
      minHeap.push(node);
    }
  }

  storeCodes(minHeap.front(), "", huffmanCodes);
}

bool skuratov::compressText(const std::string& text, const UBST< char, std::string >& huffmanCodes, std::string& encodedText)
{
  for (char c : text)
  {
    if (huffmanCodes.find(c) == huffmanCodes.end())
    {
      return false;
    }
    encodedText += huffmanCodes.at(c);
  }
  return true;
}

bool skuratov::decompressText(const std::string& encodedText, const UBST< char, std::string >& huffmanCodes, std::string& decodedText)
{
  UBST< std::string, char > reverseCodes;
  for (const auto& pair : huffmanCodes)
  {
    reverseCodes[pair.second] = pair.first;
  }

  std::string currentCode = "";
  for (char bit : encodedText)
  {
    currentCode += bit;
    auto it = reverseCodes.find(currentCode);
    if (it != reverseCodes.end())
    {
      decodedText += it->second;
      currentCode.clear();
    }
  }
  return currentCode.empty();
}

double skuratov::calculateEfficiency(const std::string& text, const UBST< char, std::string >& huffmanCodes)
{
  double originalSize = text.size() * 8;
  double compressedSize = 0;

  for (char c : text)
  {
    compressedSize += huffmanCodes.at(c).size();
  }
  return (originalSize - compressedSize) / originalSize * 100;
}

bool skuratov::compareByLength(const std::string& a, const std::string& b)
{
  return a.length() < b.length();
}

bool skuratov::sortByDescendingFreq(HuffmanTreeNode* a, HuffmanTreeNode* b)
{
  return a->freq > b->freq;
}
