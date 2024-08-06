#ifndef DATASETSUMMARIZER_HPP
#define DATASETSUMMARIZER_HPP

#include <string>

namespace isaychev
{
  class DatasetSummarizer
  {
   public:
    DatasetSummarizer();
    void operator()(const std::pair< int, std::string > & elem);
    int get_keysum();
    const std::string & get_valsum();

   private:
    int key_sum;
    std::string value_sum;
  };
}

#endif
