#include "commands_processing.hpp"
#include <fstream>
#include <limits>

  void zaitsev::readDs(std::istream& in, library& dest)
  {
    std::string name;
    in >> name;
    if (!in)
    {
      return;
    }
    dictionary new_dict;
    std::string value;
    int key;
    while (in.peek() != '\n' && in)
    {
      in >> key >> value;
      new_dict[key] = value;
    }
    dest[name] = std::move(new_dict);
  }

  void zaitsev::initLib(int argc, char** argv, library& dest)
  {
    if (argc < 2)
    {
      throw std::runtime_error("No file with datasets");
    }
    std::fstream input(argv[1]);
    if (!input)
    {
      throw std::runtime_error("File opening failed");
    }
    while (input)
    {
      readDs(input, dest);
    }
  }

  void zaitsev::printDs(std::istream& in, library& lib)
  {
    std::string ds_name;
    in >> ds_name;
    if (!lib.count(ds_name))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    if (lib.at(ds_name).empty())
    {
      std::cout << "<EMPTY>\n";
      return;
    }
    std::cout << ds_name;
    for (auto i : lib.at(ds_name))
    {
      std::cout << " " << i.first << " " << i.second;
    }
    std::cout << '\n';
  }

  void zaitsev::complementDs(std::istream& in, library& lib)
  {
    std::string new_ds_name, ds1_name, ds2_name;
    in >> new_ds_name >> ds1_name >> ds2_name;
    if (!lib.count(ds1_name) || !lib.count(ds2_name))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    ds_it ds1_beg = lib[ds1_name].cbegin();
    ds_it ds2_beg = lib[ds2_name].cbegin();
    ds_it ds1_end = lib[ds1_name].cend();
    ds_it ds2_end = lib[ds2_name].cend();
    dictionary new_dict;
    while (ds1_beg != ds1_end && ds2_beg != ds2_end)
    {
      if ((*ds1_beg).first == (*ds2_beg).first)
      {
        ++ds1_beg;
        ++ds2_beg;
      }
      else if ((*ds1_beg).first < (*ds2_beg).first)
      {
        new_dict.insert(*ds1_beg);
        ++ds1_beg;
      }
      else
      {
        ++ds2_beg;
      }
    }
    while (ds1_beg != ds1_end)
    {
      new_dict.insert(*ds1_beg);
      ++ds1_beg;
    }
    lib[new_ds_name] = std::move(new_dict);
  }

  void zaitsev::intersectDs(std::istream& in, library& lib)
  {
    std::string new_ds_name, ds1_name, ds2_name;
    in >> new_ds_name >> ds1_name >> ds2_name;
    if (!lib.count(ds1_name) || !lib.count(ds2_name))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    ds_it ds1_beg = lib[ds1_name].cbegin();
    ds_it ds2_beg = lib[ds2_name].cbegin();
    ds_it ds1_end = lib[ds1_name].end();
    ds_it ds2_end = lib[ds2_name].end();
    dictionary new_dict;
    while (ds1_beg != ds1_end && ds2_beg != ds2_end)
    {
      if ((*ds1_beg).first == (*ds2_beg).first)
      {
        new_dict.insert(*ds1_beg);
        ++ds1_beg;
        ++ds2_beg;
      }
      else
      {
        (*ds1_beg).first < (*ds2_beg).first ? ++ds1_beg : ++ds2_beg;
      }
    }
    lib[new_ds_name] = std::move(new_dict);
  }

  void zaitsev::uniteDs(std::istream& in, library& lib)
  {
    std::string new_ds_name, ds1_name, ds2_name;
    in >> new_ds_name >> ds1_name >> ds2_name;
    if (!lib.count(ds1_name) || !lib.count(ds2_name))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    ds_it ds1_beg = lib[ds1_name].cbegin();
    ds_it ds2_beg = lib[ds2_name].cbegin();
    ds_it ds1_end = lib[ds1_name].end();
    ds_it ds2_end = lib[ds2_name].end();
    dictionary new_dict;
    while (ds1_beg != ds1_end && ds2_beg != ds2_end)
    {
      if ((*ds1_beg).first == (*ds2_beg).first)
      {
        new_dict.insert(*ds1_beg);
        ++ds1_beg;
        ++ds2_beg;
      }
      else if ((*ds1_beg).first < (*ds2_beg).first)
      {
        new_dict.insert(*ds1_beg);
        ++ds1_beg;
      }
      else
      {
        new_dict.insert(*ds2_beg);
        ++ds2_beg;
      }
    }
    while (ds1_beg != ds1_end)
    {
      new_dict.insert(*ds1_beg);
      ++ds1_beg;
    }
    while (ds2_beg != ds2_end)
    {
      new_dict.insert(*ds2_beg);
      ++ds2_beg;
    }
    lib[new_ds_name] = std::move(new_dict);
  }
