#include <vector>
#include <iostream>
using namespace std;



//开链法/拉链法（哈希桶）
template<class K,class V>
struct HashNode
{
	K _key;
	V _value;
	HashNode<K,V>* _next;

	HashNode(const K key, V val)
		:_key(key)
		,_value(val)
		,_next(NULL)
	{}
};

template<class K,class V>
class HashTable
{
	typedef HashNode<K,V> Node;
public:
	HashTable()
		:_size(0)
	{}

	void Insert(const K key,V val)
	{
		_CheckCapacity();
		size_t size = _tables.size();
		size_t index = _HashFun(key,size);
		Node* cur = new Node(key,val);
		cur->_next = _tables[index];
		_tables[index] = cur;
		_size++;
	}
	bool Remove(const K key)
	{
		size_t size = _tables.size();
		size_t index = _HashFun(key,size);
		Node* cur = _tables[index];
		Node* prev = NULL;
		while(cur)
		{
			while (cur->_key == key)
			{
				if (prev == NULL)	//头部删除
				{
					_tables[index] = cur->_next;
				}
				else
				{
					prev->_next = cur->_next;
				}
				delete cur;
				_size--;
				return true;
			}

			prev = cur;
			cur = cur->_next;
		}
		return false;
	}

	void Find(const K key)
	{
		Node* ret = _Find(key);
		if (ret)
			cout<<"find key is :"<<ret->_key<<endl;
		else
			cout<<"key is not exist!"<<endl;
	}
protected:
	Node* _Find(const K key)
	{
		size_t index = _HashFun(key,_tables.size());
		Node* cur = _tables[index];
		while (cur)
		{
			if (cur->_key == key)
				return cur;

			cur = cur->_next;
		}
		return NULL;
	}
	void _CheckCapacity()
	{
		if (_size == 0 || _size == _tables.size())	//表为空或者负载为1
		{
			vector<Node*> newTable;
			size_t size = _tables.size();
			newTable.resize(_GetPrime(size));
			for (size_t i=0; i<size; i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;

					size_t index = _HashFun(cur->_key,newTable.size());
					cur->_next = newTable[index];
					newTable[index] = cur;

					cur = next;
				}
			}
			_tables.swap(newTable);
		}
	}
	size_t _GetPrime(size_t size)
	{//采用素数----能减少冲突
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul,
			786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul,
			25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul,
			805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		for (int i=0; i<_PrimeSize; i++)
		{
			if(_PrimeList[i] > size)
				return _PrimeList[i];
		}
	}
	size_t _HashFun(const K key, int size)
	{
		return key % size;
	}
private:
	vector<Node*> _tables;
	size_t _size;	//有效数据的个数
};

void TestHashTable()
{
	int a[54] = {51, 105, 52, 3, 55, 2, 106, 53, 0};
	HashTable<int,int> table;
	for (size_t i=0; i<sizeof(a)/sizeof(a[0]); ++i)
	{
		table.Insert(a[i],i);
	}
	table.Remove(2);
	table.Remove(53);

	table.Find(55);
	table.Find(120);

	//ht.Display();
}