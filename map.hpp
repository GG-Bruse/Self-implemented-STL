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

		pair<iterator,bool> insert(const pair<Key,Value>& kv) {
			return _tree.insert(kv);
		}

		Value& operator[](const Key& key)
		{
			pair<iterator, bool> ret = insert(make_pair(key, Value()));
			return ret.first->second;
		}
	private:
		RedBlackTree<Key, pair<Key, Value>, MapKeyofT> _tree;
	};
}