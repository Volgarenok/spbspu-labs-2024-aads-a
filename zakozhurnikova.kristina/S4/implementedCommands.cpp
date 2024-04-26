#include "implementedCommands.hpp"
#include <iostream>

namespace zak = zakozhurnikova;
using map = BinarySearchTree< int, std::string >;
void zak::ImplementedCommands::executeCommand(std::istream& in, std::string& result)
{
	in >> result;
}

void zak::ImplementedCommands::print(zak::List< std::string >& args, std::string& result)
{
	result += args.front();
}

void zak::ImplementedCommands::complement(zak::List< std::string >& args, std::string& result)
{
result += args.front();
}

void zak::ImplementedCommands::intersect(zak::List<std::string >& args, std::string& result)
{
 result += args.front();
}

void zak::ImplementedCommands::doUnion(zak::List< std::string >& args, std::string& result)
{
 result += args.front();
}

void zak::ImplementedCommands::addMap(std::string& mapName, map& toAdd)
{
	std::pair< std::string, map > insertedPair = std::make_pair(mapName, toAdd);
	//maps_.push(insertedPair);
}
