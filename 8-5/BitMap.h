#include <vector>

#include <iostream>
using namespace std;

//实现一个位图
class BitMap
{
public:
	BitMap(size_t range)
	{
		_bm.resize((range>>5) + 1);
	}
	void Set(const size_t& x)
	{
		size_t index = x>>5;
		size_t num = x%32;

		_bm[index] |= (1<<num);
	}
	void Reset(const size_t& x)
	{
		size_t index = x>>5;
		size_t num = x%32;
		_bm[index] &= (~(1<<num));
	}
	bool Test(size_t x)
	{
		size_t index = x>>5;
		size_t num = x%32;
		if(_bm[index] & (1<<num))
			return true;
		else
			return false;
	}
private:
	vector<size_t> _bm;
};

//以下三个问题都是位图相关类似题目，请给出解决方案： 
//42亿九千万个整数如果全部存在内存中，则所需要的内存是2^32 * 4Bytes = 4*4*2^30 = 16G，那么100亿个整
//数差不多需要的内存是40G，如果全部存到内存中再排序是不现实的。

//1）给定100亿个整数，设计算法找到只出现一次的整数 
//哈希切分+位图：将这100亿个整数使用哈希切分映射到1000个小文件中，在每个小文件中使用两个bit位的位
//图表示一个整数的状态，其中00表示出现0次，01表示出现1次，10表示出现多次，11丢弃，然后在每个小文
//件中找状态是01的整数，最后将所有结果进行合并。
//46亿九千万的整数使用位图占用的内存是：(2^32 * 2)/8 = 2^30Bytes = 1G


//2）给两个文件，分别有100亿个整数，我们只有1G内存，如何找到两个文件交集 
//解法一：哈希切分：将两个文件按照相同的哈希算法分别映射到100个小文件中，并对其进行编号：a1,a2...a100
//b1,b2...b100，则对于两个大文件来说，使用相同的哈希算法后会将相同的数据分到每组编号相同的文件中，
//那么只需要比较两组小文件下标相同的文件即可找到两个大文件的交集。
//解法二：位图：将两个文件映射到两个位图中，最后将两个位图相与，求得的结果就是两个文件的交集。

//3）1个文件有100亿个int，1G内存，设计算法找到出现次数不超过2次的所有整数 
//这里采用两个位的位图来表示一个整数的状态，00表示不存在，01表示出现了1次，10表示出现了2次，11表示
//出现了多次，100亿的整数采用2位位图存储则所需内存在1G左右，因此这里只需要在位图中查找状态是01和10
//的整数，就可以得到结果。


void TestBitMap()
{
	BitMap b(1);
	b.Set(4);
	b.Set(6);
	cout<<b.Test(4)<<endl;
	cout<<b.Test(5)<<endl;
	b.Reset(4);
	cout<<b.Test(4)<<endl;
}