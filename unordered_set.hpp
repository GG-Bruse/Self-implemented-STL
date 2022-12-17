#pragma once
#include "hash_table.h"
using namespace OpenHash;
namespace bjy {
	template <class K, class Hash = hash<K>>
	class unordered_set 
	{
		struct SetKeyOfT {
			const K& operator()(const K& key) {
				return key;
			}
		};
	public:
		typedef typename HashTable<K, K, Hash, SetKeyOfT>::iterator iterator;
		iterator begin() { return _hash_table.begin(); }
		iterator end() { return _hash_table.end(); }

		pair<iterator, bool> insert(const K& key) {
			return _hash_table.insert(key);
		}
		bool erase(const K& key) {
			return _hash_table.erase(key);
		}
	private:
		HashTable<K, K, Hash, SetKeyOfT> _hash_table;
	};
}
