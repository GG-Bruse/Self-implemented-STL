#pragma once
#include<iostream>
#include<cassert>
using std::pair;
using std::make_pair;
using std::cout;
using std::cout;
using std::endl;

enum Color { RED, BLACK };
template<class T>
struct RedBlackTreeNode {
	RedBlackTreeNode(const T& data) :_parent(nullptr), _left(nullptr), _right(nullptr), _data(data), _color(RED) {}

	RedBlackTreeNode<T>* _parent;
	RedBlackTreeNode<T>* _left;
	RedBlackTreeNode<T>* _right;
	T _data;
	Color _color;
};

template<class T, class Ref, class Ptr>
struct __redblacktree_iterator {
	typedef RedBlackTreeNode<T> TreeNode;
	typedef __redblacktree_iterator<T, Ref, Ptr> self;
public:
	__redblacktree_iterator(TreeNode* node):_node(node) {}
	Ref operator*() {
		return _node->_data;
	}
	Ptr operator->() {
		return &_node->_data;
	}
	bool operator!=(const self& s)const {
		return _node != s._node;
	}
	bool operator==(const self& s)const {
		return _node == s._node;
	}
	self& operator++() {
		if (_node->_right != nullptr) {
			//��������������
			TreeNode* cur = _node->_right;
			while (cur->_left != nullptr) {
				cur = cur->_left;
			}
			_node = cur;
		}
		else {
			//�ҵ������к��Ӳ������Һ��ӵĽ��
			TreeNode* parent = _node->_parent;
			TreeNode* cur = _node;
			while (parent && cur == parent->_right) {
				cur = cur->_parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}
	self& operator--() {
		if (_node->_left != nullptr) {
			//�����������ҽ��
			TreeNode* cur = _node->_left;
			while (cur->_right != nullptr) {
				cur = cur->_right;
			}
			_node = cur;
		}
		else {
			//�ҵ������к��Ӳ��������ӵĽ��
			TreeNode* parent = _node->_parent;
			TreeNode* cur = _node;
			while (parent && cur == parent->_left) {
				cur = cur->_parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}
private:
	TreeNode* _node;
};

template<class Key, class T, class KeyofT>
class RedBlackTree
{
	typedef RedBlackTreeNode<T> TreeNode;
public:
	typedef __redblacktree_iterator<T, T&, T*> iterator;
	iterator begin() {
		TreeNode* cur = _root;
		while (cur != nullptr && cur->_left != nullptr) {
			cur = cur->_left;
		}
		return iterator(cur);
	}
	iterator end() {
		return iterator(nullptr);
	}

	pair<iterator,bool> insert(const T& data) {
		KeyofT kot;

		if (_root == nullptr) {
			_root = new TreeNode(data);
			_root->_color = BLACK;
			return make_pair(iterator(_root),true);
		}

		TreeNode* parent = nullptr;
		TreeNode* cur = _root;
		while (cur != nullptr) {
			if (kot(data) > kot(cur->_data)) {
				parent = cur;
				cur = cur->_right;
			}
			else if (kot(data) < kot(cur->_data)) {
				parent = cur;
				cur = cur->_left;
			}
			else return make_pair(iterator(cur),false);
		}
		cur = new TreeNode(data);
		cur->_color = RED;
		if (kot(data) > kot(parent->_data)) {
			parent->_right = cur;
		}
		else {
			parent->_left = cur;
		}
		cur->_parent = parent;
		TreeNode* remain = cur;

		while (parent && parent->_color == RED)
		{
			TreeNode* grandfather = parent->_parent;
			assert(grandfather != nullptr);//��parent���Ϊ��ʱ��grandfather���ز�Ϊ��(�����Ϊ��)
			assert(grandfather->_color == BLACK);//��parent���Ϊ��ʱ��grandfather����Ϊ��ɫ(����Υ�����ʣ����������ĺ�ɫ���)

			if (parent == grandfather->_left) {
				TreeNode* uncle = grandfather->_right;
				if (uncle != nullptr && uncle->_color == RED) {
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else {//uncle�����ڻ���Ϊ��
					//�ҵ��� + ��ɫ
					if (cur == parent->_left) {
						rotate_right(grandfather);
						grandfather->_color = RED;
						parent->_color = BLACK;
					}
					//����˫�� + ��ɫ
					else {//cur == parent->_right
						rotate_left(parent);
						rotate_right(grandfather);
						cur->_color = BLACK;
						grandfather->_color = RED;
					}
					break;
				}
			}
			else {//parent == grandfather->_right
				TreeNode* uncle = grandfather->_left;
				if (uncle != nullptr && uncle->_color == RED) {
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else {//uncle�����ڻ���Ϊ��
					//���� + ��ɫ
					if (cur == parent->_right) {
						rotate_left(grandfather);
						grandfather->_color = RED;
						parent->_color = BLACK;
					}
					//����˫�� + ��ɫ
					else {//cur == parent->_left
						rotate_right(parent);
						rotate_left(grandfather);
						cur->_color = BLACK;
						grandfather->_color = RED;
					}
					break;
				}
			}
		}
		_root->_color = BLACK;
		return make_pair(iterator(remain),true);
	}

	void inorder() {
		_inorder(_root);
	}

	bool IsBalance() {
		//����Ҳ�Ǻ����
		if (_root == nullptr) return true;

		//������Ǻ�ɫ��
		if (_root->_color != BLACK) return false;

		int benchmark = 0;//��׼ֵ
		return _IsBalance(_root, 0, benchmark);
	}
private:
	void _inorder(TreeNode* root) {
		if (root == nullptr) {
			return;
		}
		_inorder(root->_left);
		cout << root->_data.first << ":" << root->_data.second << " ";
		_inorder(root->_right);
	}

	bool _IsBalance(TreeNode* root, int blackNum, int& benchmark) {
		if (root == nullptr) {
			if (benchmark == 0) {
				benchmark = blackNum;
				return true;
			}
			else {
				return blackNum == benchmark;
			}
		}
		if (root->_color == BLACK) ++blackNum;

		if (root->_color == RED && root->_parent->_color == RED) return false;//�߼���·����root���Ϊ��ɫ����Ͳ�����Ϊ����㣬һ����parent���

		return _IsBalance(root->_left, blackNum, benchmark) && _IsBalance(root->_right, blackNum, benchmark);
	}

	void rotate_left(TreeNode* parent) {
		TreeNode* subR = parent->_right;
		TreeNode* subRL = subR->_left;
		TreeNode* pparent = parent->_parent;

		parent->_right = subRL;
		if (subRL != nullptr) subRL->_parent = parent;
		subR->_left = parent;
		parent->_parent = subR;

		//��������任����������
		if (_root == parent) {
			_root = subR;
			subR->_parent = nullptr;
		}
		else {
			if (pparent->_left == parent) pparent->_left = subR;
			else pparent->_right = subR;
			subR->_parent = pparent;
		}
	}
	void rotate_right(TreeNode* parent) {
		TreeNode* subL = parent->_left;
		TreeNode* subLR = subL->_right;
		TreeNode* pparent = parent->_parent;

		parent->_left = subLR;
		if (subLR != nullptr) subLR->_parent = parent;
		subL->_right = parent;
		parent->_parent = subL;

		if (_root == parent) {
			_root = subL;
			subL->_parent = nullptr;
		}
		else {
			if (pparent->_left == parent) pparent->_left = subL;
			else pparent->_right = subL;
			subL->_parent = pparent;
		}
	}

private:
	TreeNode* _root = nullptr;
};