#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <vector>

#include <iostream>
using namespace std;

template<class T>
struct Less
{
	bool operator()(const T& left,const T& right)
	{
		return left < right;
	}
};

template<class T>
struct Greater
{
	bool operator()(const T& left,const T& right)
	{
		return left > right;
	}
};

template<class T,class Compare=Greater<T>>
class Heap
{
public:
	Heap()
	{}
	Heap(T* a,int sz)
	{
		assert(a);
		//_hp.reserve(sz);

		//2.将所有数插入vector中
		for (int idx=0; idx<sz; idx++)
		{
			_hp.push_back(a[idx]);
		}

		//3.向下调整
		for (int idx=(sz-1)/2; idx>=0; --idx)
		{
			AdjustDown(idx);
		}
	}
	void Push(const T& x)	//插入一个数后需要从该节点开始向上调整
	{
		_hp.push_back(x);
		AdjustUp(_hp.size()-1);
	}
	void Pop()
	{
		//第一个与最后一个交换，删除最后一个，并从下标为0的位置开始向下调整
		if(_hp.empty())
			return ;
		swap(_hp[0],_hp[_hp.size()-1]);
		_hp.pop_back();
		AdjustDown(0);
	}
	T& Top()
	{
		return _hp[0];
	}
	size_t Size()
	{
		return _hp.size();
	}
	void Clear()
	{
		_hp.clear();
	}
	void Show()
	{
		for (size_t i=0; i<_hp.size(); ++i)
		{
			cout<<_hp[i]<<" ";
		}
		cout<<endl;
	}
protected:
	void AdjustDown(int root)
	{
		int parent = root;
		size_t child = parent*2+1;
		while(child < _hp.size())
		{
			Compare com;
			//a[child+1] > a[child]
			if((child+1)<_hp.size() && com(_hp[child+1],_hp[child]))
				child++;
			if(com(_hp[child],_hp[parent]))	//a[child] > a[parent]
			{
				swap(_hp[child],_hp[parent]);
				parent = child;
				child = parent*2+1;
			}
			else
				break;
		}
	}
	void AdjustUp(int child)
	{
		int parent = (child-1)/2;
		while (child > 0)
		{
			Compare com;
			if(com(_hp[child],_hp[parent]))
			{
				swap(_hp[child],_hp[parent]);
				child = parent;
				parent = (child-1)/2;
			}
			else
				break;
		}
	}
private:
	vector<T> _hp;
};

//void TestHeap()
//{
//	int a[] = {10,16,18,12,11,13,15,17,14,19};
//	int len = sizeof(a)/sizeof(a[0]);
//	vector<int> v;
//	for (int i=0; i<len; i++)
//	{
//		v.push_back(a[i]);
//	}
//	Heap<int> hp(a,len);
//	hp.Pop();
//	hp.Show();
//}