#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <set>
#include <iostream>
#include <AVLtree.hpp>

namespace novokhatskiy
{
  class Dictionary
  {
  public:
    using val_t = std::pair< std::string, std::set< std::string > >;
    Dictionary() = default;
    ~Dictionary() = default;
    void addValue(Dictionary&& other);
    val_t& getValue(const std::string& name);
    const val_t& getValue(const std::string& name) const;
    void remove(const std::string& word);
    void find(const std::string& word, std::ostream& out) const;
    size_t size() const noexcept;
    Tree< std::string, val_t >& getDict();
    Tree< std::string, val_t > getDict() const;
  private:
   Tree< std::string, val_t > dict_;
  };
  std::istream& operator>>(std::istream& in, Dictionary& dict);
  std::ostream& operator<<(std::ostream& out, const Dictionary& dict);
}

#endif
