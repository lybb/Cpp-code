#include <iostream>
//求数组中出现次数超过了数组的一半的字符。如：int a[]={2,3,2,2,2,2,2,5,4,1,2,3}，求出的数字是2。

int MoreThanHalfNum(int* a,int sz)
{
	assert(a && sz>0);
	int count = 1;
	int ret = a[0];
	for (int i=1; i<sz; i++)
	{
		if(count == 0)
		{
			ret = a[i];
			count = 1;
		}
		else if(a[i] == ret)
			count++;
		else
			count--;
	}

	count = 0;	//这里一定要将count清零后再统计
	for (int i=0; i<sz; i++)//求出出现次数最多的数的个数
	{
		if(a[i] == ret)
			count++;
	}
	if(count*2 <= sz)	//不满足次数超过一半2
		return 0;
	return ret;
}

#include <vector>

int MoreThanHalfNum_Solution(vector<int> numbers) {
	if(numbers.empty())
		return 0;
	int tmp = numbers[0];
	size_t count = 1;
	for(size_t index=0; index<numbers.size(); index++){
		if(count == 0){
			tmp = numbers[index];
			count = 1;
		}
		else if(numbers[index] == tmp)
			count++;
		else
			count--;
	}

	count = 0;
	for(size_t index=0; index<numbers.size(); index++){
		if(numbers[index] == tmp)
			count++;
	}
	if(count*2 <= numbers.size())
		return 0;
	return tmp;
}

void Test()
{
	//int a[]={2,3,2,2,2,2,2,5,4,1,2,3};
	//int a[]={1,2,3,2,2,2,5,4,2};
	//int a[]={1,2,3,2,4,2,5,2,3};
	//int a[]={1,0,2,1,1};
	int a[] = {4,2,1,4,2,4};
	int ret = MoreThanHalfNum(a,sizeof(a)/sizeof(a[0]));
	cout<<ret<<endl;
	vector<int> v;
	for (int i=0; i<sizeof(a)/sizeof(a[0]); i++)
	{
		v.push_back(a[i]);
	}
	int tmp = MoreThanHalfNum_Solution(v);
	cout<<tmp<<endl;
}
int main()
{
	//TestBinaryTree();
	Test();
	system("pause");
	return 0;
}