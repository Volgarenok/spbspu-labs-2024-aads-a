#ifndef FUNC_OBJECT_HPP
#define FUNC_OBJECT_HPP

#include <utility>
#include "treeTraversalCmds.hpp"

namespace skuratov
{
	struct KeySumm
	{
		KeySumm();
		void operator()(const std::pair< const int, std::string >& keyValue);
		int getKeyValue() const;
		std::string getNameString() const;
	private:
		int keyValue_;
		std::string nameStr_;
	};
}

#endif