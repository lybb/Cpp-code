#include "BitMap.h"
#include <string>

struct _HashFunc1
{
	size_t BKDRHash(const char *str)  
	{  
		register size_t hash = 0;  
		while (size_t ch = (size_t)*str++)  
		{         
			hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..  
			// 有人说将乘法分解为位运算及加减法可以提高效率，如将上式表达为：hash = hash << 7 + hash << 1 + hash + ch;  
			// 但其实在Intel平台上，CPU内部对二者的处理效率都是差不多的，  
			// 我分别进行了100亿次的上述两种运算，发现二者时间差距基本为0（如果是Debug版，分解成位运算后的耗时还要高1/3）；  
			// 在ARM这类RISC系统上没有测试过，由于ARM内部使用Booth's Algorithm来模拟32位整数乘法运算，它的效率与乘数有关：  
			// 当乘数8-31位都为1或0时，需要1个时钟周期  
			// 当乘数16-31位都为1或0时，需要2个时钟周期  
			// 当乘数24-31位都为1或0时，需要3个时钟周期  
			// 否则，需要4个时钟周期  
			// 因此，虽然我没有实际测试，但是我依然认为二者效率上差别不大          
		}  
		return hash;  
	} 
	size_t operator()(const string& s)
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

template<class K = string,
	class HashFunc1 = _HashFunc1,
	class HashFunc2 = _HashFunc2,
	class HashFunc3 = _HashFunc3,
	class HashFunc4 = _HashFunc4, 
	class HashFunc5 = _HashFunc5>
class BloomFilter
{
public:
	BloomFilter(const size_t range)
		:_range(range)
		,_bm(range)
	{}

	void Set(const K& s)	//同时设置5个位
	{
		size_t index1 = HashFunc1()(s.c_str())%_range;//映射在range的范围之内的第index个整型数上
		size_t index2 = HashFunc2()(s.c_str())%_range;
		size_t index3 = HashFunc3()(s.c_str())%_range;
		size_t index4 = HashFunc4()(s.c_str())%_range;
		size_t index5 = HashFunc5()(s.c_str())%_range;

		_bm.Set(index1);	//设置这个整型数的位
		_bm.Set(index2);
		_bm.Set(index3);
		_bm.Set(index4);
		_bm.Set(index5);	
	}

	bool Test(const K& val)
	{
		size_t hash1 = HashFunc1()(val);
		size_t hash2 = HashFunc2()(val);
		size_t hash3 = HashFunc3()(val);
		size_t hash4 = HashFunc4()(val);
		size_t hash5 = HashFunc5()(val);

		cout<<hash1<<","<<hash2<<","<<hash3<<","<<hash4<<","<<hash5<<endl;

		if (_bm.Test(hash1) == 0)
			return false;

		if (_bm.Test(hash2) == 0)
			return false;

		if (_bm.Test(hash3) == 0)
			return false;

		if (_bm.Test(hash4) == 0)
			return false;

		if (_bm.Test(hash5) == 0)
			return false;

		return true;	//5个位同时为1才能表示存在
	}
private:
	BitMap _bm;
	size_t _range;
};

void TestBloomFilter()
{
	BloomFilter<> bm(-1);
	bm.Set("sort1");
	bm.Set("sort3");
	bm.Set("sort5");
	bm.Set("abcdefg");
	bm.Set("bitmap");
	bm.Set("http://blog.csdn.net/qq_26768741/article/details/53083775");
	bm.Set("http://blog.csdn.net/qq_26768741/article/details");
	bm.Set("http://blog.csdn.net/qq_26768741/article/details/53083775121212");


	cout<<bm.Test("sort1")<<endl;
	cout<<bm.Test("bbbbbbbbb")<<endl;
	cout<<bm.Test("http://blog.csdn.net/qq_26768741/article/details/53083775121212")<<endl;
	cout<<bm.Test("http://blog.csdn.net/qq_26768741/article/details/")<<endl;
	cout<<bm.Test("http://blog.csdn.net/qq_26768741/article/details/530837")<<endl;
}