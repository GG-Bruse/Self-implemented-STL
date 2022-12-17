#pragma once
#include "hash_table.h"
using namespace OpenHash;
namespace bjy {
	template <class K, class V, class Hash = hash<K>>
	class unordered_map 
	{
		struct MapKeyOfT {
			const K& operator()(const pair<K, V>& kv) {
				return kv.first;
			}
		};
	public:
		typedef typename HashTable<K, pair<K, V>, Hash, MapKeyOfT>::iterator iterator;
		iterator begin() { return _hash_table.begin(); }
		iterator end() { return _hash_table.end(); }

		pair<iterator, bool> insert(const pair<K, V>& kv) {
			return _hash_table.insert(kv);
		}
		bool erase(const K& key) {
			return _hash_table.erase(key);
		}

		V& operator[](const K& key) {
			pair<iterator, bool> ret = _hash_table.insert(make_pair(key, V()));
			return ret.first->second;
		}

	private:
		HashTable<K, pair<K, V>, Hash, MapKeyOfT> _hash_table;
	};
}