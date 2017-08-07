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

//ʵ�ֲ�¡������
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
	void Set(const K& s)	//ͬʱ����5��λ
	{
 		//�ȷֱ�õ�ʹ�������ϣ�㷨ʱ�õ���λ��
		size_t index1 = HashFun1()(s) % _range;
		size_t index2 = HashFun2()(s) % _range;
		size_t index3 = HashFun3()(s) % _range;
		size_t index4 = HashFun4()(s) % _range;
		size_t index5 = HashFun5()(s) % _range;

		//����5��λȫ�����ý�λͼ��
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

		//ֻҪ��һ��λ���ϲ����ڣ����ʾ�����ַ�����������
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

		return true;	//5��λͬʱ����ʱ��ʾ�ַ�������
	}
private:
	BitMap _bm;	//�ڲ��ṹ��Ҫһ��λͼ
	size_t _range;	//��Χ
};

//��¡����������չ 
//1����¡������������׼ȷ�Ļ��ǲ�������׼ȷ�ģ� 
//����һ��Ԫ�ر�ӳ����5��λ����ͬ��Ԫ���п��ܱ�ӳ�䵽��ͬ��λ���ϣ���ˣ����ڲ�¡��������˵����
//�Ĳ�������׼ȷ�ģ������ǲ�׼ȷ�ģ���Ϊĳһ��λ�п���������Ԫ��ӳ�䵽��


//2����¡��������ȱ�㣿 
//�ŵ㣺��1������ڽ�����Ԫ�ش���һ����������ȥ���ҵİ취����¡����ʡ�ռ��ʱ�䣻��2������Ͳ�ѯ
//���¼����Ӷȶ���O(1)����3�����ڲ���ֱ�Ӵ洢Ԫ�ر�����˶�һЩ������Ҫ��ߵ����ݺ������ƣ�
//ȱ�㣺��1�����У���Ԫ��Խ��Խ��ʱ���������ʻ�Խ��Խ�ߣ���2����֧��ɾ����������Ϊͬһ��λ�п���
//�����Ԫ��ӳ�䣬ɾ��һ��Ԫ��ʱ�ͻ�Ӱ������Ԫ��


//3�������չBloomFilterʹ����֧��ɾ��Ԫ�صĲ����������ʵ��һ��֧��ɾ���Ĳ�¡������.
//�������ü����ķ�ʽʵ�֣�ԭ��ʱһ��λ���洢һ��Ԫ�ص�״̬�����ڸ�Ϊһ��size_t����ֵ����ÿ��Ԫ��
//���ղ�ͬ�Ĺ�ϣ�㷨ӳ�䵽��ͬ��λ�ã�ÿ��λ�õ�ֵ��ʾ�ж��ٸ�Ԫ�ر�ӳ�䵽���λ�ã����Ҫɾ��һ
//��Ԫ�أ��������Ӧ�ļ���λ���Ͻ���ֵ��1

//ʵ�ֲ�¡������
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
	void Set(const K& s)	//ͬʱ����5��λ
	{
		//�ȷֱ�õ�ʹ�������ϣ�㷨ʱ�õ���λ��
		size_t index1 = HashFun1()(s) % _bm.size();
		size_t index2 = HashFun2()(s) % _bm.size();
		size_t index3 = HashFun3()(s) % _bm.size();
		size_t index4 = HashFun4()(s) % _bm.size();
		size_t index5 = HashFun5()(s) % _bm.size();

		cout<<index1<<"  "<<index2<<"  "<<index3<<"  "<<index4<<"  "<<index5<<endl;
		//���ĳһ��λ�ñ�ӳ���ˣ��򽫸�λ�õļ�����++
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

		//ֻҪ��һ��λ���ϲ����ڣ����ʾ�����ַ�����������
		if(_bm[index1] != 0 && _bm[index2] != 0 && _bm[index3] != 0 &&
			_bm[index4] != 0 && _bm[index5] != 0)
			return true;
		return false;//5��λͬʱ����ʱ��ʾ�ַ�������
	}
private:
	vector<size_t> _bm;//��һ��λ��λͼ��չ��һ��size_t��vector
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

	cout<<bfp.ReSet("sort")<<endl;	//����---1
	cout<<bfp.ReSet("bfp")<<endl;	//������---0
// 	cout<<bfp.Test("Find")<<endl;	//0
// 	cout<<bfp.Test("abcdeabcde")<<endl;	//1
// 	cout<<bfp.Test("sort1")<<endl;	//1
// 	cout<<bfp.Test("http://blog.csdn.net/fengasdfgh/article/details/53110")<<endl;	//0
}