#include "cmd.hpp"
#include <map>
#include <iostream>

namespace sivkov
{
  void print(std::map< std::string, std::map< size_t, std::string > >& treeOfdic, std::istream& in, std::ostream& out)
  {
    std::string dataset = "";
    in >> dataset;
    auto found = treeOfdic.find(dataset);
    if (found != treeOfdic.end())
    {
      out << dataset;
      for (auto it = found->second.begin(); it != found->second.end(); ++it)
      {
        out << " " << it->first << " " << it->second;
      }
    }
    else
    {
      throw std::logic_error("<EMPTY>");
    }
  }

  void complement(std::map<std::string, std::map<size_t, std::string>>& treeOfdic, std::istream& in)
  {
    std::string newDataset, dataset1, dataset2;
    in >> newDataset >> dataset1 >> dataset2;

    auto found1 = treeOfdic.find(dataset1);
    auto found2 = treeOfdic.find(dataset2);

    if (found1 != treeOfdic.end() && found2 != treeOfdic.end())
    {
      std::map<size_t, std::string> complementDict;
      for (auto it = found1->second.begin(); it != found1->second.end(); ++it)
      {
        complementDict[it->first] = it->second;
      }
      for (auto it = found2->second.begin(); it != found2->second.end(); ++it)
      {
        auto iter = complementDict.find(it->first);
        if (iter != complementDict.end())
        {
          complementDict.erase(iter);
        }
      }
      treeOfdic[newDataset] = complementDict;
    }
  }

  void intersect(std::map<std::string, std::map<size_t, std::string>>& treeOfdic, std::istream& in)
  {
    std::string newDataset, dataset1, dataset2;
    in >> newDataset >> dataset1 >> dataset2;

    auto found1 = treeOfdic.find(dataset1);
    auto found2 = treeOfdic.find(dataset2);

    if (found1 != treeOfdic.end() && found2 != treeOfdic.end())
    {
      std::map<size_t, std::string> intersectDict;
      for (auto it = found1->second.begin(); it != found1->second.end(); ++it)
      {
        auto it2 = found2->second.find(it->first);
        if (it2 != found2->second.end())
        {
          intersectDict[it->first] = it->second;
        }
      }
      treeOfdic[newDataset] = intersectDict;
    }
  }

  void uni(std::map<std::string, std::map<size_t, std::string>>& treeOfdic, std::istream& in)
  {
    std::string newDataset, dataset1, dataset2;
    in >> newDataset >> dataset1 >> dataset2;

    auto found1 = treeOfdic.find(dataset1);
    auto found2 = treeOfdic.find(dataset2);

    if (found1 != treeOfdic.end() && found2 != treeOfdic.end())
    {
      std::map<size_t, std::string> unionDict;
      for (auto it = found1->second.begin(); it != found1->second.end(); ++it)
      {
        unionDict[it->first] = it->second;
      }
      for (auto it = found2->second.begin(); it != found2->second.end(); ++it)
      {
        unionDict[it->first] = it->second;
      }
      treeOfdic[newDataset] = unionDict;
    }
  }
}
