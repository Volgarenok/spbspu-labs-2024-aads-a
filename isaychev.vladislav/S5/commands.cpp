#include "commands.hpp"

void isaychev::trav_asc(const map_t & data, functor_t & f)
{
  f = data.traverse_lnr(f);
}

void isaychev::trav_des(const map_t & data, functor_t & f)
{
  f = data.traverse_rnl(f);
}

void isaychev::trav_brd(const map_t & data, functor_t & f)
{
  f = data.traverse_breadth(f);
}
