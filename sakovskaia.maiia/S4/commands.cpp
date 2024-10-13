#include <string>
#include <iostream>
#include "commands.hpp"

namespace sakovskaia
{
  void print(const Tree< std::string, Tree< size_t, std::string > > & dictionaries, std::istream & input, std::ostream & output)
  {
    std::string dataset = "";
    input >> dataset;
    Tree< size_t, std::string > data_ = dictionaries.at(dataset);
    if (data_.empty())
    {
      throw std::logic_error("<EMPTY>");
    }
    output << dataset;
    for (auto it = data_.cbegin(); it != data_.cend(); ++it)
    {
      output << " " << it->first << " " << it->second;
    }
    output << "\n";
  }

  void complement(Tree< std::string, Tree< size_t, std::string > > & dictionaries, std::istream & input)
  {
    std::string newDataset = "", dataset1 = "", dataset2 = "";
    input >> newDataset >> dataset1 >> dataset2;
    Tree< size_t, std::string > data1 = dictionaries.at(dataset1);
    Tree< size_t, std::string > data2 = dictionaries.at(dataset2);
    Tree< size_t, std::string > result;
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
    dictionaries.push(newDataset, result);
  }

  void intersect(Tree< std::string, Tree< size_t, std::string > > & dictionaries, std::istream & input)
  {
    std::string newDataset = "", dataset1 = "", dataset2 = "";
    input >> newDataset >> dataset1 >> dataset2;
    Tree< size_t, std::string > data1 = dictionaries.at(dataset1);
    Tree< size_t, std::string > data2 = dictionaries.at(dataset2);
    Tree< size_t, std::string > result;
    for (auto it = data1.cbegin(); it != data1.cend(); ++it)
    {
      if (data2.contains(it->first))
      {
        result.push(it->first, it->second);
      }
    }

    dictionaries.push(newDataset, result);
  }

  void unionCMD(Tree<std::string, Tree< size_t, std::string > > & dictionaries, std::istream & input)
  {
    std::string newDataset, dataset1, dataset2;
    input >> newDataset >> dataset1 >> dataset2;
    Tree< size_t, std::string > data1 = dictionaries.at(dataset1);
    Tree< size_t, std::string > data2 = dictionaries.at(dataset2);
    Tree< size_t, std::string > result;
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
    dictionaries.push(newDataset, result);
  }
}
