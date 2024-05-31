#include <iostream>

namespace skuratov
{
	namespace detail
	{
		template < typename Key, typename Value >
		struct TreeNode
		{
			TreeNode* parent;
			TreeNode* left;
			TreeNode* right;
			std::pair< Key, Value > data;

			TreeNode(const Key key, const Value value):
			  parent(nullptr),
				left(nullptr),
				right(nullptr),
				data(std::pair< Key, Value >(key, value))
			{}
		};
	}

	template < typename Key, typename Value, typename Compare >
	class BinarySearchTree
	{
	public:
		void push(Key k, Value v);
		Value get(Key k);
		Value drop(Key k);
		//...
	};

	int main()
	{
		std::cout << "Hello!";
		return 0;
	}
}
