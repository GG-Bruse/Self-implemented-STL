#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"string.h"
#include"vector.hpp"
#include"queue.hpp"
#include"stack.hpp"
#include"list.hpp"
#include"map.hpp"
#include"set.hpp"
#include "unordered_map.hpp"
#include "unordered_set.hpp"
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
int main_map2()
{
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };

	map<string, int> countMap;
	for (auto& str : arr)
	{
		// 1、str不在countMap中，插入pair(str, int()),然后在对返回次数++
		// 2、str在countMap中，返回value(次数)的引用，次数++;
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
	return 0;
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



/*************         unordered_set     unordered_map           ***/
void test_map()
{
	unordered_map<string, string> dict;
	dict.insert(make_pair("sort", "排序"));
	dict.insert(make_pair("string", "字符串"));
	dict.insert(make_pair("left", "左边"));

	for (unordered_map<string, string>::iterator it = dict.begin(); it != dict.end(); ++it){
		cout << it->first << ":" << it->second << endl;
	}
	cout << endl;

	unordered_map<string, int> countMap;
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
	for (auto e : arr){
		countMap[e]++;
	}

	for (auto& kv : countMap){
		cout << kv.first << ":" << kv.second << endl;
	}
	countMap.erase("西瓜");
	cout << endl;
	for (auto& kv : countMap) {
		cout << kv.first << ":" << kv.second << endl;
	}
}
void test_set()
{
	unordered_set<int> s;
	s.insert(2);
	s.insert(3);
	s.insert(1);
	s.insert(2);
	s.insert(5);

	for (unordered_set<int>::iterator it = s.begin(); it != s.end(); ++it){
		cout << *it << " ";
	}
	cout << endl;

	s.erase(2);

	for (unordered_set<int>::iterator it = s.begin(); it != s.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
}
int main()
{
	test_map();
	test_set();
	return 0;
}