#pragma once

#include<iostream>
using namespace std;
#include <vector>
#include <assert.h>

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

//��
template<class T,class Compare = Greater<T>>	//Ĭ��Ϊ���
class Heap
{
public:
	Heap()
	{}
	Heap(T* a,int size)
	{
		assert(a);
		_heap.reserve(size);
		for(int i=0; i<size; ++i)
		{
			_heap.push_back(a[i]);
		}
		//����
		for (int j=(size-2)/2; j>=0; --j)	//�������ϣ��ҵ���һ����Ҷ�ӽ��
		{
			AdjustDown(j);
		}
	}
	void Push(const T& x)
	{
		_heap.push_back(x);			//��������һ������
		AdjustUp(_heap.size()-1);	//�����������ֵ�λ�����ϵ���
	}
	void Pop()
	{
		assert(!_heap.empty());
		swap(_heap[0],_heap[_heap.size()-1]);	//�����Ѷ������һ��Ԫ��
		_heap.pop_back();	//ɾ�����һ��Ԫ��(ɾ���˶Ѷ���Ԫ��)
		AdjustDown(0);		//�ӵ�һ�������µ���
	}
	bool Empty()
	{
		return _heap.empty();
	}
	size_t Size()
	{
		size_t sz = _heap.size();
		return _heap.size();
	}
	const T& Top()
	{
		return _heap[0];
	}
	void Display()
	{
		for (size_t i=0; i<Size(); ++i)
		{
			cout<<_heap[i]<<" ";
		}
		cout<<endl;
	}
protected:
	void AdjustDown(int root)	//���µ���
	{
		int parent = root;
		size_t child = parent * 2 + 1;
		while (child < _heap.size())
		{
			Compare com;
			//ѡ���Һ����нϴ��һ��
			/*if ((child+1) < _heap.size()
				&& _heap[child+1] > _heap[child])*/
			if ((child+1) < _heap.size()
				&& com(_heap[child+1],_heap[child]))
			{
				++child;
			}
			//ѡ���ڵ��뺢�ӽڵ��нϴ��һ��
			/*if (_heap[child] > _heap[parent])*/
			if (com(_heap[child],_heap[parent]))
			{
				swap(_heap[parent],_heap[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}
	void AdjustUp(int child)		//���ϵ���
	{
		int parent = (child-1)/2;
		while(child > 0)
		{
			Compare com;
			//if (_heap[child] > _heap[parent])	//���ӽ����ڸ��ڵ�ͽ���
			if(com(_heap[child],_heap[parent]))
			{
				swap(_heap[child],_heap[parent]);
				child = parent;
				parent = (child-1)/2;
			}
			else
				break;
		}
	}
protected:
	vector<T> _heap;
};



void HeapSort(int* a,size_t size)
{
	//����
	for (int i=(size-1)/2; i>=0; --i)
	{
		_AdjustDown(a,i,size);
	}
	
	//����
	int index = size-1;
	for (int i=0; i<size; ++i)
	{
		swap(a[0],a[index]);	//�����Ѷ������һ����-------�����С���������ŵ����
		_AdjustDown(a,0,index);	//�ӶѶ���ʼ�������µ���
		--index;
	}
	for (size_t j=0; j<size; ++j)
	{
		cout<<a[j]<<" ";
	}
	cout<<endl;
}
void _AdjustDown(int* a,int root,int size)	//���µ���
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < size)
	{
		if ((child+1) < size
			&& a[child+1] > a[child])	//�����������ڲ�������������������
		{
			++child;
		}
		if (a[child] > a[parent])
		{
			swap(a[child],a[parent]);
			parent = child;
			child = 2*parent +1;
		}
		else
			break;
	}
}


//���ȼ�����
template<class T,class Compare = Greater<T>>
class PriorityQueue
{
public:
	PriorityQueue(T* a,int size)
		:_pq(a,size)
	{}
	void Push(const T& x)
	{
		_pq.Push(x);
	}
	void Pop()
	{
		_pq.Pop();
	}
	const T& Top()
	{
		return _pq.Top();
	}
	void Display()
	{
		_pq.Display();
	}
protected:
	Heap<T,Compare> _pq;
};
void TestPriorityQueue()
{
	int a[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 }; 
	int sz = sizeof(a)/sizeof(a[0]);
	PriorityQueue<int,Greater<int>> pq1(a,sz);
	cout<<"��ѣ� ";
	pq1.Display();
	cout<<"Top: "<<pq1.Top()<<endl;

	pq1.Push(30);
	cout<<"Push(30)�� ";
	pq1.Display();

	pq1.Pop();
	cout<<"Pop()�� ";
	pq1.Display();
}


void TestHeap()
{
	int a[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 }; 
	int sz = sizeof(a)/sizeof(a[0]);
	Heap<int,Greater<int>> hp1(a,sz);
	cout<<"��ѣ� ";
	hp1.Display();
	//HeapSort(a,sz);
	

	//cout<<"Empty: "<<hp1.Empty()<<endl;
	//cout<<"Size: "<<hp1.Size()<<endl;
	//cout<<"Top: "<<hp1.Top()<<endl;

	//hp1.Push(30);
	//cout<<"Push(30)�� ";
	//hp1.Display();

	//hp1.Pop();
	//cout<<"Pop()�� ";
	//hp1.Display();

	//Heap<int,Less<int>> hp2(a,sz);
	//cout<<"С�ѣ� ";
	//hp2.Display();

	cout<<endl;
}
void TestPriorityQueue()
{
	int a[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 }; 
	int sz = sizeof(a)/sizeof(a[0]);
	PriorityQueue<int,Greater<int>> pq1(a,sz);
	cout<<"��ѣ� ";
	pq1.Display();
	cout<<"Top: "<<pq1.Top()<<endl;

	pq1.Push(30);
	cout<<"Push(30)�� ";
	pq1.Display();

	pq1.Pop();
	cout<<"Pop()�� ";
	pq1.Display();

	Heap<int,Less<int>> pq2(a,sz);
	cout<<"С�ѣ� ";
	pq2.Display();
}