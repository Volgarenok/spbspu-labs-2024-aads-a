#include "cmd.hpp"

namespace sivkov
{
  void print(const AVLTree< std::string, AVLTree< size_t, std::string > >& treeOfdic, std::istream& in, std::ostream& out)
  {
    std::string dataset = "";
    in >> dataset;
    AVLTree< size_t, std::string > data = treeOfdic.at(dataset);
    if (data.empty())
    {
      throw std::logic_error("<EMPTY>");
    }
    out << dataset;
    for (auto it = data.cbegin(); it != data.cend(); ++it)
    {
      out << " " << it->first << " " << it->second;
    }
    out << "\n";
  }

  void complement(AVLTree< std::string, AVLTree< size_t, std::string > >& treeOfdic, std::istream& in)
  {
    std::string newDataset = "", dataset1 = "", dataset2 = "";
    in >> newDataset >> dataset1 >> dataset2;
    AVLTree< size_t, std::string > data1 = treeOfdic.at(dataset1);
    AVLTree< size_t, std::string > data2 = treeOfdic.at(dataset2);
    AVLTree< size_t, std::string > result;

    for (auto it = data1.cbegin(); it != data1.cend(); ++it)
    {
      try
      {
        data2.at(it->first);
      }
      catch (...)
      {
        result.push(it->first, it->second);
      }
    }
    treeOfdic.push(newDataset, result);
  }

  void intersect(AVLTree< std::string, AVLTree< size_t, std::string > >& treeOfdic, std::istream& in)
  {
    std::string newDataset = "", dataset1 = "", dataset2 = "";
    in >> newDataset >> dataset1 >> dataset2;
    AVLTree< size_t, std::string > data1 = treeOfdic.at(dataset1);
    AVLTree< size_t, std::string > data2 = treeOfdic.at(dataset2);
    AVLTree< size_t, std::string > result;
    for (auto it = data1.cbegin(); it != data1.cend(); ++it)
    {
      if (data2.contains(it->first))
      {
        result.push(it->first, it->second);
      }
    }

    treeOfdic.push(newDataset, result);
  }

  void unionCMD(AVLTree<std::string, AVLTree< size_t, std::string > >& treeOfdic, std::istream& in)
  {
    std::string newDataset, dataset1, dataset2;
    in >> newDataset >> dataset1 >> dataset2;

    AVLTree< size_t, std::string > data1 = treeOfdic.at(dataset1);
    AVLTree< size_t, std::string > data2 = treeOfdic.at(dataset2);
    AVLTree< size_t, std::string > result;
    for (auto it = data1.cbegin(); it != data1.cend(); ++it)
    {
      result.push(it->first, it->second);
    }
    for (auto it = data2.cbegin(); it != data2.cend(); ++it)
    {
      if (!result.contains(it->first))
      {
        result.push(it->first, it->second);
      }
    }
    treeOfdic.push(newDataset, result);
  }
}
