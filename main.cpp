#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"string.h"
#include"vector.hpp"
#include"queue.hpp"
#include"stack.hpp"
#include"list.hpp"
#include"map.hpp"
#include"set.hpp"
using namespace bjy;
using std::cout;
using std::endl;
int main_vector()
{
	vector<int> v;
	for (int i = 0; i < 10; ++i) { v.push_back(i + 1); }
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	for (vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend(); ++rit) {
		cout << *rit << " ";
	}
	cout << endl;
	return 0;
}
int main_priority_queue()
{
	priority_queue<int> heap;
	heap.push(5);
	heap.push(3);
	heap.push(2);
	heap.push(0);
	heap.push(4);
	heap.push(1);
	while (!heap.empty()) {
		cout << heap.top() << " ";
		heap.pop();
	}
	cout << endl;

	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	priority_queue<int, vector<int>, greater<int>> heap2(arr, arr + sizeof(arr) / sizeof(arr[0]));
	while (!heap2.empty()) {
		cout << heap2.top() << " ";
		heap2.pop();
	}
	cout << endl;

	return 0;
}
int main_test()
{
	stack<int> sk;
	for (size_t i = 0; i < 10; ++i) { sk.push(i + 1); }
	while (!sk.empty()) {
		cout << sk.top() << " ";
		sk.pop();
	}
	cout << endl;

	queue<int> qe;
	for (size_t i = 0; i < 10; ++i) { qe.push(i+1); }
	while (!qe.empty()) {
		cout << qe.front() << " ";
		qe.pop();
	}
	cout << endl;

	return 0;
}
int main_list()
{
	vector<int>v;
	for (size_t i = 0; i < 10; ++i) { v.push_back(i + 1); }
	const list<int> lt(v.begin(),v.end());
	for (list<int>::const_iterator it = lt.begin(); it != lt.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	return 0;
}
int main_map1() {
	size_t N = 10;
	srand((unsigned)time(NULL));
	map<int, int> t;
	for (size_t i = 0; i < N; ++i) {
		int x = rand();
		//cout << "insert:" << x << ":" << i << endl;
		t.insert(make_pair(x, i));
	}
	for (map<int, int>::iterator it = t.begin(); it != t.end(); ++it) {
		cout << (*it).first << " " << (*it).second << endl;
	}
	return 0;
}
int main/*_map2*/()
{
	string arr[] = { "ƻ��", "����", "ƻ��", "����", "ƻ��", "ƻ��", "����", "ƻ��", "�㽶", "ƻ��", "�㽶" };

	map<string, int> countMap;
	for (auto& str : arr)
	{
		// 1��str����countMap�У�����pair(str, int()),Ȼ���ڶԷ��ش���++
		// 2��str��countMap�У�����value(����)�����ã�����++;
		countMap[str]++;
	}

	map<string, int>::iterator it = countMap.begin();
	while (it != countMap.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}

	for (auto& kv : countMap)
	{
		cout << kv.first << ":" << kv.second << endl;
	}
}
int main_set()
{
	set<int> s;
	s.insert(5);
	s.insert(3);
	s.insert(1);
	s.insert(2);
	s.insert(4);
	for (set<int>::iterator it = s.begin(); it != s.end(); ++it) {
		cout << *it << endl;
	}
	return 0;
}