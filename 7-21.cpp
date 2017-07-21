#include <iostream>
//【附加题】--给定一个整数N，那么N的阶乘N！末尾有多少个0呢？例如：N＝10，N！＝3 628 800，
//N！的末尾有两个0。
//思路分析：①如果是先求出N的阶乘，再将其转换成字符串来找0的话，需要考虑到N的阶乘有可能很大，一般
//类型存放不下；②由于末尾是0，思路转换成求10的倍数，求10的倍数时思路又转换成求能被2或者5整除的数
size_t CountTail0(int num)
{
	int i=1;
	int count = 0;
	for (; i<=num; i++)
	{
		if (i%5 == 0)
			count++;
	}
	return count;
}

int main()
{
	int ret = CountTail0(5);
	cout<<ret<<endl;
	system("pause");
	return 0;
}