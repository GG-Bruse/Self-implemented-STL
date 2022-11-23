#pragma once
#include"RedBlackTree.hpp"
namespace bjy
{
	template<class Key>
	class set
	{
		struct SetKeyofT {
			const Key& operator()(const Key& key) {
				return key;
			}
		};
	public:
		typedef typename RedBlackTree<Key, Key, SetKeyofT>::iterator iterator;
		iterator begin() { return _tree.begin(); }
		iterator end() { return _tree.end(); }

		bool insert(const Key& key) {
			return _tree.insert(key);
		}
	private:
		RedBlackTree<Key, Key, SetKeyofT> _tree;
	};
}


