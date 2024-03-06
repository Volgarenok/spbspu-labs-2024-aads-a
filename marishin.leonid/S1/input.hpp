#ifndef INPUT_HPP
#define INPUT_HPP

#include "linkedList.hpp"

void readInput(LinkedList< std::pair< std::string, LinkedList< size_t >>>& pairs);
void printPairs(const LinkedList< std::pair< std::string, LinkedList< size_t >>>& pairs);
void calculateSums(const LinkedList< std::pair< std::string, LinkedList< size_t >>>& pairs, bool& overflow, LinkedList< size_t >& lst);
void printResults(const LinkedList< size_t >& lst, bool overflow);

#endif
