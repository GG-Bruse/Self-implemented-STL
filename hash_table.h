#pragma once
#include "string.h"
#include "vector.hpp"
using std::pair;
using std::make_pair;
using namespace bjy;
namespace OpenHash {
	template<class K>//默认仿函数
	struct hash {
		size_t operator()(const K& key) {
			return (size_t)key;
		}
	};
	template<>//特化
	struct hash<string> {
		//BKDR算法
		size_t operator()(const string& key) {
			size_t sum = 0;
			for (auto& e : key) {
				sum = sum * 131 + e;
			}
			return sum;
		}
	};

	template<class T>
	struct HashNode {
		HashNode() = default;
		HashNode(const T& data) :_data(data), _next(nullptr) {}
		T _data;
		HashNode<T>* _next;
	};



	template<class K, class T, class Hash, class KeyOfT>
	class HashTable;//前置声明

	template<class K, class T, class Hash, class KeyOfT>
	struct __hash_table_iterator {
		typedef HashNode<T> Node;
		typedef HashTable<K, T, Hash, KeyOfT> HashTable;
		typedef __hash_table_iterator<K, T, Hash, KeyOfT> self;
	public:
		__hash_table_iterator(Node* node, HashTable* pht) :_node(node), _pht(pht) {}

		T& operator*() { return _node->_data; }
		T* operator->() { return &(_node->_data); }
		bool operator!=(const self& it)const { return _node != it._node; }
		bool operator==(const self& it)const { return _node == it._node; }
		
		self& operator++() {
			if (_node->_next != nullptr) {
				_node = _node->_next;
			}
			else {//_node->_next == nullptr
				Hash hash;
				KeyOfT kot;
				size_t hashi = hash(kot(_node->_data)) % _pht->table_size();
				++hashi;
				for (; hashi < _pht->table_size(); ++hashi) {
					if (_pht->_table[hashi] != nullptr) {
						_node = _pht->_table[hashi];
						break;
					}
				}
				if (hashi == _pht->table_size()) {
					_node = nullptr;
				}
			}
			return *this;
		}

	private:
		Node* _node;
		HashTable* _pht;
	};



	template<class K, class T, class Hash, class KeyOfT>
	class HashTable
	{
		typedef HashNode<T> Node;

		//声明模板类为友元，需模板参数
		template<class K, class T, class Hash, class KeyOfT>
		friend struct __hash_table_iterator;

		inline size_t __stl_next_prime(unsigned long n)
		{
			static const size_t __stl_num_primes = 28;
			static const size_t __stl_prime_list[__stl_num_primes] =
			{
			  53,         97,         193,       389,       769,
			  1543,       3079,       6151,      12289,     24593,
			  49157,      98317,      196613,    393241,    786433,
			  1572869,    3145739,    6291469,   12582917,  25165843,
			  50331653,   100663319,  201326611, 402653189, 805306457,
			  1610612741, 3221225473, 4294967291
			};
			for (size_t i = 0; i < __stl_num_primes; ++i) {
				if (__stl_prime_list[i] > n) return __stl_prime_list[i];
			}
			return -1;
		}
	public:
		typedef __hash_table_iterator<K, T, Hash, KeyOfT> iterator;
		iterator begin() {
			for (size_t i = 0; i < _table.size(); ++i) {
				if (_table[i] != nullptr) return iterator(_table[i],this);
			}
			return end();
		}
		iterator end() {
			return iterator(nullptr, this);
		}

		pair<iterator,bool> insert(const T& data) {
			Hash hash;
			KeyOfT kot;
			iterator ret = find(kot(data));
			if (ret != end()) return make_pair(ret, false);//不允许键值冗余

			//负载因子到达1进行扩容
			if (_table.size() == 0 || _size == _table.size()) {
				vector<Node*> new_table;
				new_table.resize(__stl_next_prime(_table.size()), nullptr);
				for (size_t i = 0; i < _table.size(); ++i) {
					Node* cur = _table[i];
					while (cur != nullptr) {
						Node* next = cur->_next;
						size_t hashi = hash(kot(cur->_data)) % new_table.size();
						//头插
						cur->_next = new_table[hashi];
						new_table[hashi] = cur;
						cur = next;
					}
					_table[i] = nullptr;
				}
				_table.swap(new_table);
			}

			size_t hashi = hash(kot(data)) % _table.size();
			//头插
			Node* newNode = new Node(data);
			newNode->_next = _table[hashi];
			_table[hashi] = newNode;
			++_size;
			return make_pair(iterator(newNode, this), true);
		}

		bool erase(const K& key) {
			Hash hash;
			KeyOfT kot;
			if (_table.size() == 0) return false;
			size_t hashi = hash(key) % _table.size();
			Node* cur = _table[hashi];
			Node* prev = nullptr;
			while (cur != nullptr) {
				if (kot(cur->_data) == key) {
					if (prev == nullptr) {//头删
						_table[hashi] = cur->_next;
					}
					else {
						prev->_next = cur->_next;
					}
					delete cur;
					--_size;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}

		iterator find(const K& key) {
			Hash hash;
			KeyOfT kot;
			if (_table.size() == 0) return end();
			size_t hashi = hash(key) % _table.size();
			Node* cur = _table[hashi];
			while (cur != nullptr) {
				if (kot(cur->_data) == key) {
					return iterator(cur, this);
				}
				cur = cur->_next;
			}
			return end();
		}

		~HashTable() {
			for (size_t i = 0; i < _table.size(); ++i) {
				Node* cur = _table[i];
				while (cur != nullptr) {
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_table[i] = nullptr;
			}
		}

		//存储的元素个数
		size_t size() { return _size; }

		// 表的长度
		size_t table_size() { return _table.size(); }

		// 桶的个数
		size_t bucket_num() {
			size_t num = 0;
			for (size_t i = 0; i < _table.size(); ++i) {
				if (_table[i]) {
					++num;
				}
			}
			return num;
		}

		size_t max_bucket_length() {
			size_t maxLen = 0;
			for (size_t i = 0; i < _table.size(); ++i) {
				size_t len = 0;
				Node* cur = _table[i];
				while (cur) {
					++len;
					cur = cur->_next;
				}
				if (len > maxLen) maxLen = len;
			}
			return maxLen;
		}

	private:
		vector<Node*> _table;
		size_t _size = 0;
	};
}