#include <assert.h>
#include <string.h>
#include <iostream>
using namespace std;

//将N个字符的数组，循环右移K位。时间复杂度O(N)-----三步翻转法
//先翻转前k个字符，再翻转k之后的字符，最后再整体翻转。需要注意的是，测试时的字符串不能是char*类型，
//该类型的字符串是不能被改变的
void Reverse(char*& s,int left, int right)
{
	while (left < right)
	{
		swap(s[left],s[right]);
		left++;
		right--;
	}
}
char* RotatleRight(char* str,int length,int k)
{
	assert(str && length>=0);
	Reverse(str,0,k-1);
	Reverse(str,k,length-1);
	Reverse(str,0,length-1);
	return str;
}

//删除小写字母字符串中重复字符。如果可以，优先删除重复字符中排在比他小字符前面的字符。 
//比如，输入：bbcacdww；输出：bacdw 
//提示：暴力求解效率太低，考虑哈希思想。
//思路分析：由于都是小写字符，那么可以确定一个大小是26的数组count，这个数组存放对应字符出现的次数，
//①遍历字符串s，将每个字符转换成count数组的下标，出现几次，count数组对应位置就是几；
//②统计出重复字符的个数sum，重新申请一块大小为len-sum的数组；
//③由于是优先删除出现在前边的字符，则选择从后向前拷贝，将原字符串的每个字符拷贝到数组tmp中

void  DropRepeateChar(char*& s,int len)
{
	assert(s && len>0);
	//在arr中统计a-z之间出现字符的对应次数
	char count[26] = {0};
	for (int i=0; i<len; i++)
	{
		if(s[i] >= 'a' && s[i] <= 'z')
		{
			int index = s[i] - 'a';
			count[index]++;
		}
	}

	//统计重复出现的字符次数
	int sum = 0;
	for (int i=0; i<26; i++)
	{
		if(count[i] >= 2)
			sum++;
	}

	//从后向前拷贝字符
	int size = len - sum;
	int sz = size;
	char* tmp = new char[size+1];	//这里需要多开辟出一个字符空间，用来存放结尾标识符
	int j=0;
	for (int i=len-1; i>=0; i--)
	{
		int index = s[i]-'a';
		if(count[index] > 0)
		{
			tmp[--size] = s[i];
			count[s[i]-'a'] = 0;
		}
	}
	tmp[sz] = 0;
	swap(s,tmp);
}


int main()
{
	//char str[] = {'a','b','c','d','e','f','\0'};
	//int len = sizeof(str)/sizeof(str[0]);
	//RotatleRight(str,len,2);
	char* str = "bbcacdww";
	int len = strlen(str);
	DropRepeateChar(str,len);
	cout<<str<<endl;
	system("pause");
	return 0;
}