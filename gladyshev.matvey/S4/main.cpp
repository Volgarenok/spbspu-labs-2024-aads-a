#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <limits>
using dic = std::map<int, std::string>;
using bigdic = std::map<std::string, std::map<int, std::string>>;
void read_dictionaries(std::ifstream& in, bigdic& dictionaries)
{
  std::string dataset = "";
  std::string value = "";
  int key = 0;
  while (in >> dataset)
  {
    std::map<int, std::string> dict;
    while (in >> key >> value)
    {
      dict.insert(std::make_pair(key, value));
      if (in.get() == '\n')
      {
        break;
      }
    }
    dictionaries.insert(std::make_pair(dataset, dict));
  }
}
void print_dictionary(const dic& dictionary)
{
  for (const auto& dataset : dictionary)
  {
    std::cout << " " << dataset.first << " " << dataset.second;
  }
  std::cout << "\n";
}

void print_dictionaries(const std::string& s, const bigdic& dictionaries)
{
  for (const auto& dataset : dictionaries)
  {
    if (s == dataset.first)
    {
      if (dataset.second.empty())
      {
        throw std::overflow_error("<EMPTY>");
      }
      std::cout << dataset.first;
      print_dictionary(dataset.second);
    }
  }
}
bigdic intersect(const std::string& s, const dic& dict1, const dic& dict2)
{
  dic result;
  bigdic finres;
  for (const auto& pair1 : dict1)
  {
    for (const auto& pair2: dict2)
    {
      if (pair1.first == pair2.first)
      {
        result.insert(std::make_pair(pair1.first, pair1.second));
      }
    }
  }
  finres.insert(std::make_pair(s, result));
  return finres;
}

bigdic complement(const std::string& s, const dic& dict1, const dic& dict2)
{
  dic result;
  bigdic finres;
  bool check = true;
  for (const auto& pair1 : dict1)
  {
    check = true;
    for (const auto& pair2 : dict2)
    {
      if (pair1.first == pair2.first)
      {
        check = false;
      }
    }
    if (check)
    {
      result.insert(std::make_pair(pair1.first, pair1.second));
    }
  }
  finres.insert(std::make_pair(s, result));
  return finres;
}

bigdic union_dictionaries(const std::string& s, const dic& dict1, const dic& dict2)
{
  dic result = dict1;
  bigdic finres;
  for (const auto& pair1: dict1)
  {
    for (const auto& pair2: dict2)
    {
      if ((pair1.first != pair2.first) && (pair1.second != pair2.second))
      {
        result.insert(std::make_pair(pair2.first, pair2.second));
      }
    }
  }
  finres.insert(std::make_pair(s, result));
  return finres;
}

dic findName(const bigdic& dictionaries, const std::string& name)
{
   auto it = dictionaries.find(name);
  if (it != dictionaries.end()) {
    return it->second;
  } else {
    return dic();
  }
}
void clearDictionary(bigdic& dictionaries, const std::string& name) {
  auto it = dictionaries.find(name);
  if (it != dictionaries.end()) {
    dictionaries.erase(it);
  }
}
std::ostream& process_commands(std::istream& in, std::ostream& out, bigdic& maindic)
{
  std::map < std::string, std::function < bigdic(const std::string&, const dic&, const dic&) > > cmds;
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
        clearDictionary(maindic, name1);
        bigdic temp = cmds.at(command)(name1, supdic1, supdic2);
        for (const auto& pair : temp)
        {
          maindic.insert(pair);
        }
      }
      //catch (const std::overflow_error& e)
      //{
       // std::cerr << "Error: " << e.what() << "\n";
      //}
      catch (const std::out_of_range &)
      {
        std::cerr << "<INVALID COMMAND>\n";
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
  }
}

int main(int argc, char* argv[])
{
  bigdic dictionaries;
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    read_dictionaries(file,dictionaries);

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
