#include "BitMap.h"
#include <string>

struct _HashFunc1
{
	size_t BKDRHash(const char *str)  
	{  
		register size_t hash = 0;  
		while (size_t ch = (size_t)*str++)  
		{         
			hash = hash * 131 + ch;   // Ҳ���Գ���31��131��1313��13131��131313..  
			// ����˵���˷��ֽ�Ϊλ���㼰�Ӽ����������Ч�ʣ��罫��ʽ���Ϊ��hash = hash << 7 + hash << 1 + hash + ch;  
			// ����ʵ��Intelƽ̨�ϣ�CPU�ڲ��Զ��ߵĴ���Ч�ʶ��ǲ��ģ�  
			// �ҷֱ������100�ڴε������������㣬���ֶ���ʱ�������Ϊ0�������Debug�棬�ֽ��λ�����ĺ�ʱ��Ҫ��1/3����  
			// ��ARM����RISCϵͳ��û�в��Թ�������ARM�ڲ�ʹ��Booth's Algorithm��ģ��32λ�����˷����㣬����Ч��������йأ�  
			// ������8-31λ��Ϊ1��0ʱ����Ҫ1��ʱ������  
			// ������16-31λ��Ϊ1��0ʱ����Ҫ2��ʱ������  
			// ������24-31λ��Ϊ1��0ʱ����Ҫ3��ʱ������  
			// ������Ҫ4��ʱ������  
			// ��ˣ���Ȼ��û��ʵ�ʲ��ԣ���������Ȼ��Ϊ����Ч���ϲ�𲻴�          
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
		if(!*str)        // �����ɱ�����ӣ��Ա�֤���ַ������ع�ϣֵ0  
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

	void Set(const K& s)	//ͬʱ����5��λ
	{
		size_t index1 = HashFunc1()(s.c_str())%_range;//ӳ����range�ķ�Χ֮�ڵĵ�index����������
		size_t index2 = HashFunc2()(s.c_str())%_range;
		size_t index3 = HashFunc3()(s.c_str())%_range;
		size_t index4 = HashFunc4()(s.c_str())%_range;
		size_t index5 = HashFunc5()(s.c_str())%_range;

		_bm.Set(index1);	//���������������λ
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

		return true;	//5��λͬʱΪ1���ܱ�ʾ����
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