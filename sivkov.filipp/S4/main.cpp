#include <utility>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <stdexcept>
#include <functional>
#include <limits>

namespace sivkov
{
  void inputDictionary(std::map < std::string, std::map< size_t, std::string > >& treeOfdic, std::istream& in)
  {
    while (!in.eof())
    {
      in.clear();
      std::string name = "";
      std::map< size_t, std::string > dictionary;
      size_t key = 0;
      in >> name;
      while (in >> key)
      {
        std::string word = "";
        in >> word;
        dictionary[key] = word;
      }
      treeOfdic[name] = dictionary;
    }
  }
}


namespace sivkov
{

  void print(std::map < std::string, std::map< size_t, std::string > >& treeOfdic, std::istream& in, std::ostream& out)
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

int main(int argc, char* argv[])
{
  std::map< std::string, std::map< size_t, std::string > > treeOfdic;
  if (argc != 2)
  {
    std::cerr << "Error CMD line\n";
    return 1;
  }
  else
  {
    std::ifstream file(argv[1]);
    sivkov::inputDictionary(treeOfdic, file);
  }
  std::map< std::string, std::function< void(std::map< std::string, std::map< size_t, std::string > >&, std::istream&) > > cmd;
  cmd["print"] = std::bind(sivkov::print, std::placeholders::_1, std::placeholders::_2, std::ref(std::cout));
  cmd["complement"] = sivkov::complement;
  cmd["intersect"] = sivkov::intersect;
  cmd["union"] = sivkov::uni;

  std::string inputCommand = "";

  while (std::cin >> inputCommand)
  {
    auto it = cmd.find(inputCommand);
    if (it != cmd.end())
    {
      try
      {
        it->second(treeOfdic, std::cin);
      }
      catch (const std::logic_error& e)
      {
        std::cerr << e.what() << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    else
    {
      std::cerr << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
