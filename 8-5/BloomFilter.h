#include "BitMap.h"
#include <string>

struct _HashFunc1
{
	size_t BKDRHash(const char *str)  
	{  
		register size_t hash = 0;  
		while (size_t ch = (size_t)*str++)  
		{         
			hash = hash * 131 + ch;        
		}  
		return hash;  
	} 
	size_t operator ()(const string& s)
	{
		return BKDRHash(s.c_str());
	}
};
struct _HashFunc2
{
	size_t SDBMHash(const char *str)  
	{  
		register size_t hash = 0;  
		while (size_t ch = (size_t)*str++)  
		{  
			hash = 65599 * hash + ch;         
			//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
		}  
		return hash;  
	}  
	size_t operator()(const string& s)
	{
		return SDBMHash(s.c_str());
	}
};
struct _HashFunc3
{
	size_t RSHash(const char *str)  
	{  
		register size_t hash = 0;  
		size_t magic = 63689;     
		while (size_t ch = (size_t)*str++)  
		{  
			hash = hash * magic + ch;  
			magic *= 378551;  
		}  
		return hash;  
	}
	size_t operator()(const string& s)
	{
		return RSHash(s.c_str());
	}
};
struct _HashFunc4
{
	size_t APHash(const char *str)  
	{  
		register size_t hash = 0;  
		size_t ch;  
		for (long i = 0; ch = (size_t)*str++; i++)  
		{  
			if ((i & 1) == 0)  
			{  
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));  
			}  
			else  
			{  
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));  
			}  
		}  
		return hash;  
	}  
	size_t operator()(const string& s)
	{
		return APHash(s.c_str());
	}
};
struct _HashFunc5
{
	size_t JSHash(const char *str)  
	{  
		if(!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;  
		register size_t hash = 1315423911;  
		while (size_t ch = (size_t)*str++)  
		{  
			hash ^= ((hash << 5) + ch + (hash >> 2));  
		}  
		return hash;  
	}  
	size_t operator()(const string& s)
	{
		return JSHash(s.c_str());
	}
};

//实现布隆过滤器
template<class K=string,
	class HashFun1 = _HashFunc1,
	class HashFun2 = _HashFunc2,
	class HashFun3 = _HashFunc3,
	class HashFun4 = _HashFunc4,
	class HashFun5 = _HashFunc5>
class BloomFilter
{
public:
	BloomFilter(const size_t range)
		:_range(range)
		,_bm(range)
	{}
	void Set(const K& s)	//同时设置5个位
	{
 		//先分别得到使用五个哈希算法时得到的位置
		size_t index1 = HashFun1()(s) % _range;
		size_t index2 = HashFun2()(s) % _range;
		size_t index3 = HashFun3()(s) % _range;
		size_t index4 = HashFun4()(s) % _range;
		size_t index5 = HashFun5()(s) % _range;

		//将这5个位全部设置进位图中
		_bm.Set(index1);
		_bm.Set(index2);
		_bm.Set(index3);
		_bm.Set(index4);
		_bm.Set(index5);
	}
	bool Test(const K& s)
	{
		size_t index1 = HashFun1()(s) % _range;
		size_t index2 = HashFun2()(s) % _range;
		size_t index3 = HashFun3()(s) % _range;
		size_t index4 = HashFun4()(s) % _range;
		size_t index5 = HashFun5()(s) % _range;

		//只要有一个位置上不存在，则表示整个字符串都不存在
		if(_bm.Test(index1) == false)
			return false;
		if(_bm.Test(index2) == false)
			return false;
		if(_bm.Test(index3) == false)
			return false;
		if(_bm.Test(index4) == false)
			return false;
		if(_bm.Test(index5) == false)
			return false;

		return true;	//5个位同时存在时表示字符串存在
	}
private:
	BitMap _bm;	//内部结构需要一个位图
	size_t _range;	//范围
};

//布隆过滤器的扩展 
//1：布隆过滤器存在是准确的还是不存在是准确的？ 
//由于一个元素被映射了5个位，不同的元素有可能被映射到相同的位置上，因此，对于布隆过滤器来说，它
//的不存在是准确的，存在是不准确的，因为某一个位有可能是其他元素映射到的


//2：布隆过滤器优缺点？ 
//优点：（1）相对于将所有元素存在一个数组中再去查找的办法，布隆更节省空间和时间；（2）插入和查询
//的事件复杂度都是O(1)；（3）由于不是直接存储元素本身，因此对一些保密性要求高的数据很有优势；
//缺点：（1）误判：当元素越来越多时，其误判率会越来越高；（2）不支持删除操作：因为同一个位有可能
//被多个元素映射，删除一个元素时就会影响其他元素


//3：如何扩展BloomFilter使得它支持删除元素的操作？请设计实现一个支持删除的布隆过滤器.
//采用引用计数的方式实现：原来时一个位来存储一个元素的状态，现在改为一个size_t的数值，将每个元素
//按照不同的哈希算法映射到不同的位置，每个位置的值表示有多少个元素被映射到这个位置，如果要删除一
//个元素，则在其对应的几个位置上将数值减1

//实现布隆过滤器
template<class K=string,
	class HashFun1 = _HashFunc1,
	class HashFun2 = _HashFunc2,
	class HashFun3 = _HashFunc3,
	class HashFun4 = _HashFunc4,
	class HashFun5 = _HashFunc5>
class BloomFilterR
{
public:
	BloomFilterR(const size_t range)
	{
		_bm.resize(range);
	}
	void Set(const K& s)	//同时设置5个位
	{
		//先分别得到使用五个哈希算法时得到的位置
		size_t index1 = HashFun1()(s) % _bm.size();
		size_t index2 = HashFun2()(s) % _bm.size();
		size_t index3 = HashFun3()(s) % _bm.size();
		size_t index4 = HashFun4()(s) % _bm.size();
		size_t index5 = HashFun5()(s) % _bm.size();

		cout<<index1<<"  "<<index2<<"  "<<index3<<"  "<<index4<<"  "<<index5<<endl;
		//如果某一个位置被映射了，则将该位置的计数器++
		_bm[index1]++;	
		_bm[index2]++;
		_bm[index3]++;
		_bm[index4]++;
		_bm[index5]++;
	}
	bool ReSet(const K& s)
	{
		size_t index1 = HashFun1()(s) % _bm.size();
		size_t index2 = HashFun2()(s) % _bm.size();
		size_t index3 = HashFun3()(s) % _bm.size();
		size_t index4 = HashFun4()(s) % _bm.size();
		size_t index5 = HashFun5()(s) % _bm.size();
		if (Test(s))
		{
			_bm[index1]--;
			_bm[index2]--;
			_bm[index3]--;
			_bm[index4]--;
			_bm[index5]--;
			return true;
		}
		return false;
	}
	bool Test(const K& s)
	{
		size_t index1 = HashFun1()(s) % _bm.size();
		size_t index2 = HashFun2()(s) % _bm.size();
		size_t index3 = HashFun3()(s) % _bm.size();
		size_t index4 = HashFun4()(s) % _bm.size();
		size_t index5 = HashFun5()(s) % _bm.size();

		//只要有一个位置上不存在，则表示整个字符串都不存在
		if(_bm[index1] != 0 && _bm[index2] != 0 && _bm[index3] != 0 &&
			_bm[index4] != 0 && _bm[index5] != 0)
			return true;
		return false;//5个位同时存在时表示字符串存在
	}
private:
	vector<size_t> _bm;//将一个位的位图扩展成一个size_t的vector
};

void TestBloomFilter()
{
	BloomFilter<> bf(-1);
	bf.Set("sort");
	bf.Set("abcdeabcde");
	bf.Set("find2");
	bf.Set("sort1");
	bf.Set("http://blog.csdn.net/fengasdfgh/article/details/53110957");
	bf.Set("http://blog.csdn.net/fengasdfgh/article/53110957");
	bf.Set("http://blog.csdn.net/fengasdfgh/article/details/531109");

	cout<<bf.Test("Find")<<endl;	//0
	cout<<bf.Test("abcdeabcde")<<endl;	//1
	cout<<bf.Test("sort1")<<endl;	//1
	cout<<bf.Test("http://blog.csdn.net/fengasdfgh/article/details/53110")<<endl;	//0

}

void TestBloomFilterR()
{
	BloomFilterR<> bfp(30);
	bfp.Set("sort");
	bfp.Set("abcdeabcde");
	bfp.Set("find2");
	bfp.Set("sort1");
	bfp.Set("http://blog.csdn.net/fengasdfgh/article/details/53110");
	bfp.Set("http://blog.csdn.net/fengasdfgh/article/details/5*212123110");

	cout<<bfp.Test("http://blog.csdn.net/fengasdfgh/article/details/53110")<<endl;//1
	cout<<bfp.Test("http://blog.csdn.net/fengasdfgh/article/details/5*212123")<<endl;//0

	cout<<bfp.ReSet("sort")<<endl;	//存在---1
	cout<<bfp.ReSet("bfp")<<endl;	//不存在---0
// 	cout<<bfp.Test("Find")<<endl;	//0
// 	cout<<bfp.Test("abcdeabcde")<<endl;	//1
// 	cout<<bfp.Test("sort1")<<endl;	//1
// 	cout<<bfp.Test("http://blog.csdn.net/fengasdfgh/article/details/53110")<<endl;	//0
}