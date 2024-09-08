#include "non_interactive_cmd.hpp"
#include <ostream>
#include <fstream>

void isaychev::print_help(std::ostream & out)
{
  out << "Command Line Options:\n  --saved start with loading previously saved data from the <saved> file\n";
  out << "  --help output help\n\nCommands:\n";
  out << "1.  make <file name> <new list name>\n    Create a frequency list based on a text file.\n";
  out << "2.  delete <list name>\n    Delete a frequency list.\n";
  out << "3.  merge <new list> <list name 1> <list name 2>\n";
  out << "    Create a new frequency list by merging contents of the following lists\n";
  out << "4.  print <list name>\n    Output the contents of the list.\n";
  out << "5.  printlast <list name> <number of words>\n    Output n positions of the frequency list, ";
  out << "starting from the end.\n";
  out << "6.  printfirst <list name> <number of words>\n";
  out << "    Output the first n words of the frequency list to the console, starting from begining.\n";
  out << "7.  intersect <new list> <list name 1> <list name 2>\n";
  out << "    Create a new frequency list containing words that are in both lists at the same time.\n";
  out << "8.  getcount <word> <list name>\n";
  out << "    Output how many times a word occurs in the text, based on the frequency list.\n";
  out << "9.  total <list name>\n";
  out << "    Output the number of words in the text based on the list.\n";
  out << "10. unique <list name>\n";
  out << "    Print the number of unique words that are in the list.\n";
  out << "11. clear\n    Clear data of current session.\n12. ls\n    Print names of all lists.\n";
  out << "13. execludemore <new list> <list name> <total>\n";
  out << "    Create a frequency list based on words of <list name> which amount is greater than <total>\n";
  out << "14. execludeless <new list> <list name> <total>\n";
  out << "    Create a frequency list based on words of <list name> which amount is lesser than <total>\n";
}

void read_list(std::istream & in, isaychev::BSTree< std::string, isaychev::FreqList > & col)
{
  std::string name, str;
  size_t elem_count = 0, n = 0;
  in >> name >> elem_count;
  isaychev::FreqList temp;
  for (size_t i = 0; i < elem_count; ++i)
  {
    in >> n >> str;
    temp.add_element({{str}, n});
  }
  col.insert({name, temp});
}

void isaychev::load_saved(BSTree< std::string, FreqList > & col)
{
  std::fstream in("saved");
  if (!in.is_open())
  {
    throw std::runtime_error("bad file");
  }
  size_t count = 0;
  in >> count;
  for (size_t i = 0; i < count; ++i)
  {
    read_list(in, col);
  }
}

void output_name_and_content(std::ostream & out, const std::pair< std::string, isaychev::FreqList> & rhs)
{
  out << rhs.first << ' ' << rhs.second.size() << '\n';
  out << rhs.second;
}

void isaychev::save(const collection_t & col)
{
  std::ofstream file("saved");
  file << col.size() << "\n";
  for (auto i = col.begin(); i != col.end(); ++i)
  {
    output_name_and_content(file, *i);
  }
}
