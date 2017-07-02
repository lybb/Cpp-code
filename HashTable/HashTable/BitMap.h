#include <vector>
#include <iostream>
using namespace std;

class BitMap
{
public:
	BitMap(size_t range)
	{
		_bitmap.resize((range>>5)+1);
	}

	void Set(size_t val)
	{
		size_t index = val/32;
		size_t num = val%32;
		_bitmap[index] |= (1<<num);
	}

	void Reset(size_t val)
	{
		size_t index = val/32;
		size_t num = val%32;
		_bitmap[index] &= (~(1<<num));
	}

	bool Test(size_t val)
	{
		size_t index = val/32;	//确定在第几个整型数据上
		size_t num = val%32;	//确定在这个数据的哪个bit位上
		if (_bitmap[index] & (1<<num))
			return true;
		else
			return false;
	}
protected:
	vector<size_t> _bitmap;
}; 

void TestBitMap()
{
	BitMap b(1000);
	b.Set(10);
	b.Set(20);
	b.Set(94);

	cout<<b.Test(10)<<endl;//1
	cout<<b.Test(11)<<endl;//0
	cout<<b.Test(13)<<endl;//0
}