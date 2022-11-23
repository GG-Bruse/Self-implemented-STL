#pragma once
#include"RedBlackTree.hpp"
namespace bjy
{
	template<class Key, class Value>
	class map
	{
		struct MapKeyofT {
			const Key& operator()(const pair<Key,Value>& kv) {
				return kv.first;
			}
		};
	public:
		typedef typename RedBlackTree<Key, pair<Key, Value>, MapKeyofT>::iterator iterator;
		iterator begin() { return _tree.begin(); }
		iterator end() { return _tree.end(); }


		bool insert(const pair<Key,Value>& kv) {
			return _tree.insert(kv);
		}
	private:
		RedBlackTree<Key, pair<Key, Value>, MapKeyofT> _tree;
	};
}