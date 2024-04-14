#include <iostream>
#include <fstream>
#include <map>
#include <limits>
#include <string>

using namespace std;

class Supervisor
{
public:
  Supervisor(int argc, char** argv):
    lib()
  {
    if (argc < 2)
    {
      throw std::runtime_error("No file with datasets");
    }
    fstream input(argv[1]);
    if (!input)
    {
      throw std::runtime_error("File opening failed");
    }
    while (input)
    {
      read_ds(input);
    }
  }
  void execute(istream& in, ostream& out)
  {
    while (in)
    {
      string command;
      in >> command;
      if (!in)
      {
        break;
      }
      try
      {
        if (commands.count(command))
        {
          string arg1, arg2, arg3;
          switch (commands[command])
          {
          case com_nmb::print_c:
            in >> arg1;
            if (!lib.count(arg1) || in.peek() != '\n')
            {
              throw std::invalid_argument("");
            }
            else
            {
              print_ds(arg1, out) << '\n';
            }
            break;
          case com_nmb::intersect_c:
            in >> arg1 >> arg2 >> arg3;
            if (!lib.count(arg2) || !lib.count(arg3))
            {
              throw std::invalid_argument("");
            }
            else
            {
              intersect_ds(arg1, arg2, arg3);
            }
            break;
          case com_nmb::complement_c:
            in >> arg1 >> arg2 >> arg3;
            if (!lib.count(arg2) || !lib.count(arg3))
            {
              throw std::invalid_argument("");
            }
            else
            {
              complement_ds(arg1, arg2, arg3);
            }
            break;
          case com_nmb::union_c:
            in >> arg1 >> arg2 >> arg3;
            if (!lib.count(arg2) || !lib.count(arg3))
            {
              throw std::invalid_argument("");
            }
            else
            {
              union_ds(arg1, arg2, arg3);
            }
          }
        }
        else
        {
          throw std::invalid_argument("<INVALID COMMAND>");
        }
      }
      catch (const std::invalid_argument& e)
      {
        out << e.what() << '\n';
      }
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
private:
  using dictionary = map<int, string>;
  using ds_it = map<int, string>::const_iterator;
  using library = map< string, dictionary>;
  library lib;

  enum struct com_nmb { print_c, complement_c, intersect_c, union_c };
  map<string, com_nmb> commands = {
    {"print",com_nmb::print_c},
    {"intersect", com_nmb::intersect_c },
    {"complement", com_nmb::complement_c},
    { "union", com_nmb::union_c } };

  bool check_args(const string& arg1, const string& arg2, const string& arg3)
  {
    return arg1 == arg2 || arg2 == arg3 || arg3 == arg1;
  }
  void read_ds(istream& in)
  {
    string name;
    dictionary new_dict;
    in >> name;
    string value;
    int key;
    while (in.peek() != '\n' && in)
    {
      in >> key >> value;
      new_dict[key] = std::move(value);
    }
    lib[std::move(name)] = std::move(new_dict);
  }
  ostream& print_ds(string ds_name, ostream& out)
  {
    if (lib[ds_name].empty())
    {
      out << "<EMPTY>";
      return out;
    }
    out << ds_name;
    for (auto i : lib[ds_name])
    {
      out << " " << i.first << " " << i.second;
    }
    return out;
  }
  void complement_ds(string new_ds_name, string ds1_name, string ds2_name)
  {
    ds_it ds1_beg = lib[ds1_name].cbegin();
    ds_it ds2_beg = lib[ds2_name].cbegin();
    ds_it ds1_end = lib[ds1_name].end();
    ds_it ds2_end = lib[ds2_name].end();
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
    lib[std::move(new_ds_name)] = std::move(new_dict);
  }
  void intersect_ds(string new_ds_name, string ds1_name, string ds2_name)
  {
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
    lib[std::move(new_ds_name)] = std::move(new_dict);
  }
  void union_ds(string new_ds_name, string ds1_name, string ds2_name)
  {
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
    lib[std::move(new_ds_name)] = std::move(new_dict);
  }
};

int main(int argc, char** argv)
{
  try
  {
    Supervisor supervisor(argc, argv);
    supervisor.execute(std::cin, std::cout);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
