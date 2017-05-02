#include<iostream>
#include<windows.h>
using namespace std;

typedef int DataType;
class SeqList
{
	friend ostream& operator<<(ostream& os,SeqList& list);
public:
	SeqList()
		:_sz(0)
		,_capacity(0)
		,_pdata(NULL)
	{	}
	SeqList(const SeqList& list)
	{
		_pdata = new DataType[_capacity];
		memcpy(_pdata,list._pdata,list._sz*sizeof(DataType));
		_sz = list._sz;
		_capacity = list._capacity;
	}
	~SeqList()
	{
		if(_pdata != NULL)
		{
			delete[] _pdata;
			_pdata = NULL;
		}
		_sz = 0;
		_capacity = 0;
	}
public:
	void PushBack(const DataType& x);
	void PushFront(const DataType& x);
	void PopBack();
	void PopFront();
	void insert(int pos,const DataType& x);
	void Remove(const DataType& x);
	void RemoveAll(const DataType& x);
	void BubbleSort1();
	void BubbleSort();
	void SelectSort();
	void InsertSort();
public:
	void ChechCapacity()
	{
		if(_sz == _capacity)
		{
			int newCapacity = _capacity+2;
			DataType* tmp = new DataType[newCapacity];
			memcpy(tmp,_pdata,_sz*sizeof(DataType));
			_pdata = tmp;
			_capacity = newCapacity;
		}
	}
private:
	int Find(int pos)
	{
		if((pos > 0)&&(pos <= _sz))
		{
			for(int i=0; i<_sz; i++)
			{
				if(i == pos-1)
					return i;
			}
		}
		cout<<"pos is not a right position!"<<endl;
	}
private:
	int _sz;
	int _capacity;
	DataType* _pdata;
};
ostream& operator<<(ostream& os,SeqList& list)
{
	for(int i=0; i<list._sz; i++)
	{
		os<<list._pdata[i]<<" ";
	}
	return os;
}

void SeqList::PushBack(const DataType& x)	//尾插
{
	ChechCapacity();
	_pdata[_sz] = x;
	_sz++;
}
void SeqList::PushFront(const DataType& x)	//头插
{
	ChechCapacity();
	int i = _sz;
	while(i != 0)
	{
		_pdata[i] = _pdata[i-1];
		i--;
	}
	_pdata[0] = x;
	_sz++;
}
void SeqList::PopBack()		//尾删
{
	if(_sz == 0)
	{
		cout<<"SeqList is empty!"<<endl;
	}
	else
	{
		_pdata[_sz] = 0;
		_sz--;
	}
}
void SeqList::PopFront()		//头删
{
	if(_sz == 0)
	{
		cout<<"SeqList is empty!"<<endl;
	}
	else
	{
		for(int i=0; i<_sz; i++)
		{
			_pdata[i] = _pdata[i+1];
		}
		_sz--;
	}
}
void SeqList::insert(int pos,const DataType& x)		//指定位置插入
{
	ChechCapacity();
	int ret = Find(pos);
	for(int i=_sz; i>ret; i--)
	{
		_pdata[i] = _pdata[i-1];
	}
	_pdata[ret] = x;
	_sz++;
}
void SeqList::Remove(const DataType& x)
{
	int flag = 1;
	for(int i=0; i<_sz; i++)
	{
		if(_pdata[i] == x)
		{
			while(i != _sz)
			{
				_pdata[i] = _pdata[i+1];
				i++;
			}
			_sz--;
		}
	}
}
void SeqList::RemoveAll(const DataType& x)
{
	for(int i=0; i<_sz; i++)
	{
		Remove(x);
	}
}
void SeqList::BubbleSort()
{
	int flag = 0;
	int m = 0;
	for(int i=0; i<_sz; i++)
	{
		flag = 1;
		for(int j=0; j<_sz-i-1; j++)
		{
			if(_pdata[j] > _pdata[j+1])
			{
				DataType tmp = _pdata[j];
				_pdata[j] = _pdata[j+1];
				_pdata[j+1] = tmp;
				flag = 0;
			}
		}
		if(flag)
			return ;
	}
}
void SeqList::InsertSort()
{
	int i = 0;
	int j = 0;
	for(i=1; i<_sz; i++)
	{
		DataType temp = _pdata[i];
		for(j=i-1; j>=0; j--)
		{
			if(_pdata[j] > temp)
			{
				_pdata[j+1] = _pdata[j];
			}
			else 
				break;
		}
		_pdata[j+1] = temp;
	}
}
void SeqList::SelectSort()
{
	int i = 0;
	int j = 0;
	DataType m = 0;
	for(i=0; i<_sz; i++)
	{
		m = i;
		for(j=i+1; j<_sz;j++)
		{
			if(_pdata[m] > _pdata[j])
			{
				m = j;
			}
			if (m != i)
			{
				DataType tmp = _pdata[i];
				_pdata[i] = _pdata[m];
				_pdata[m] = tmp;
			}
		}
	}
}

void test1()
{
	SeqList mylist;
	mylist.PushBack(1);
	mylist.PushBack(2);
	mylist.PushBack(3);
	mylist.PushBack(7);
	mylist.PushBack(5);
	mylist.PushBack(4);
	mylist.PushBack(6);
	mylist.PushBack(8);
	mylist.PushBack(9);
	mylist.PushBack(10);
	//mylist.PushFront(9);
	//mylist.PopBack();
	//mylist.PopFront();
	//mylist.insert(6,10);
	//mylist.Remove(3);
	//mylist.RemoveAll(3);
	//mylist.BubbleSort();
	//mylist.InsertSort();
	mylist.SelectSort();
	cout<<mylist<<endl;
}

int main()
{
	test1();
	system("pause");
	return 0;
}