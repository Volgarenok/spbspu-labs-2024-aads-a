#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <limits>

#include "avltree.hpp"
using namespace gladyshev;
using dic = Tree< int, std::string >;
using bigdic = Tree< std::string, Tree< int, std::string > >;
void read_dictionaries(std::ifstream& in, bigdic& dictionaries)
{
  std::string dataset = "";
  std::string value = "";
  int key = 0;
  while (in >> dataset)
  {
    Tree< int, std::string > dict;
    if (in.get() == '\n')
    {
       dictionaries.insert(dataset, dict);
       continue;
    }
    while (in >> key >> value)
    {
      dict.insert(key, value);
      if (in.get() == '\n')
      {
        break;
      }
    }
    dictionaries.insert(dataset, dict);
  }
}
void print_dictionary(const dic& dictionary)
{
  for (auto it = dictionary.cbegin(); it != dictionary.cend(); ++it)
  {
    std::cout << " " << it->first << " " << it->second;
  }
  std::cout << "\n";
}

void print_dictionaries(const std::string& s, const bigdic& dictionaries)
{
  bool hasDic = false;
  for (auto it = dictionaries.cbegin(); it != dictionaries.cend(); ++it)
  {
    if (s == it->first)
    {
      if (it->second.empty())
      {
        throw std::overflow_error("<EMPTY>");
      }
      hasDic = true;
      std::cout << it->first;
      print_dictionary(it->second);
    }
    if (it->first.empty())
    {
       throw std::overflow_error("<INVALID COMMAND>");
    }
  }
  if (!hasDic)
  {
    throw std::overflow_error("<INVALID COMMAND>");
  }
}
bigdic intersect(const std::string& s, const dic& dict1, const dic& dict2)
{
  dic result;
  bigdic finres;
  for (auto it1 = dict1.cbegin(); it1 != dict1.cend(); ++it1)
  {
    for (auto it2 = dict2.cbegin(); it2 != dict2.cend(); ++it2)
    {
      if (it1->first == it2->first)
      {
        result.insert(it1->first, it1->second);
      }
    }
  }
  finres.insert(s, result);
  return finres;
}

bigdic complement(const std::string& s, const dic& dict1, const dic& dict2)
{
  dic result;
  bigdic finres;
  bool check = true;
  auto it = dict1.cbegin();
  for (auto it1 = dict1.cbegin(); it1 != dict1.cend(); ++it1)
  {
    check = true;
    for (auto it2 = dict2.cbegin(); it2 != dict2.cend(); ++it2)
    {
      if (it1->first == it2->first)
      {
        check = false;
      }
    }
    if (check)
    {
      result.insert(it1->first, it1->second);
    }
  }
  finres.insert(s, result);
  return finres;
}

bigdic union_dictionaries(const std::string& s, const dic& dict1, const dic& dict2)
{
  dic result = dict2;
  bigdic finres;
  for (auto it1 = dict1.cbegin(); it1 != dict1.cend(); ++it1)
  {
    for (auto it2 = dict2.cbegin(); it2 != dict2.cend(); ++it2)
    {
      if ((it1->first != it2->first) && (it1->second != it2->second))
      {
        result.insert(it1->first, it1->second);
      }
    }
  }
  finres.insert(s, result);
  return finres;
}

dic findName(const bigdic& dictionaries, const std::string& name)
{
  auto it = dictionaries.find(name);
  if (it != dictionaries.cend())
  {
    return it->second;
  }
  else
  {
    throw std::out_of_range("bad");
  }
}
std::ostream& process_commands(std::istream& in, std::ostream& out, bigdic& maindic)
{
  Tree < std::string, std::function < bigdic(const std::string&, const dic&, const dic&) > > cmds;
  cmds["complement"] = complement;
  cmds["intersect"] = intersect;
  cmds["union"] = union_dictionaries;
  std::string command = "";
  std::string dataset = "";
  std::string name1 = "";
  std::string name2 = "";
  std::string name3 = "";
  while (in >> command)
  {
    if (command == "print")
    {
      in >> dataset;
      try
      {
        print_dictionaries(dataset, maindic);
      }
      catch (const std::overflow_error& e)
      {
        std::cerr << e.what() << "\n";
      }
    }
    else
    {
      try
      {
        in >> name1 >> name2 >> name3;
        dic supdic1 = findName(maindic, name2);
        dic supdic2 = findName(maindic, name3);
        bigdic temp = cmds.at(command)(name1, supdic1, supdic2);
        for (const auto& pair: temp)
        {
          maindic.insert(pair.first, pair.second);
        }
      }
      //catch (const std::overflow_error& e)
      //{
       // std::cerr << "Error: " << e.what() << "\n";
      //}
      catch (const std::out_of_range&)
      {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
  }
  return out;
}

int main(int argc, char* argv[])
{
  bigdic dictionaries;
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    read_dictionaries(file, dictionaries);

  }
  else
  {
    std::cerr << "No such file\n";
    return 1;
  }
  // try
  // {
  process_commands(std::cin, std::cout, dictionaries);
  // }
  // catch (const std::overflow_error& e)
  // {
   //  std::cerr << "Error: " << e.what() << "\n";
  // }
  return 0;
}
