#ifndef CMD_HPP
#define CMD_HPP

#include <string>
#include <iostream>
#include <AVLTree.hpp>

namespace sivkov
{
  void add_word(AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in);
  void add_translation(AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in);
  void create_dictionary(AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in);
  void remove_word(AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in);
  void list_words(const AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in, std::ostream& out);
  void count_words(const AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in, std::ostream& out);
  void search_words(const AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in, std::ostream& out);
  void delete_dictionary(AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in);
  void rename_dictionary(AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in);
  void merge_dictionaries(AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in);
  void repeating_words(const AVLTree<std::string, AVLTree<std::string, std::string>>& treeOfdic, std::istream& in, std::ostream& out);
  void save(const AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, const std::string& filename);
  void help(std::ostream& out);
}

#endif

