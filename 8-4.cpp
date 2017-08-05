#include <assert.h>
#include <string.h>
#include <iostream>
using namespace std;

//��N���ַ������飬ѭ������Kλ��ʱ�临�Ӷ�O(N)-----������ת��
//�ȷ�תǰk���ַ����ٷ�תk֮����ַ�����������巭ת����Ҫע����ǣ�����ʱ���ַ���������char*���ͣ�
//�����͵��ַ����ǲ��ܱ��ı��
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

//ɾ��Сд��ĸ�ַ������ظ��ַ���������ԣ�����ɾ���ظ��ַ������ڱ���С�ַ�ǰ����ַ��� 
//���磬���룺bbcacdww�������bacdw 
//��ʾ���������Ч��̫�ͣ����ǹ�ϣ˼�롣
//˼·���������ڶ���Сд�ַ�����ô����ȷ��һ����С��26������count����������Ŷ�Ӧ�ַ����ֵĴ�����
//�ٱ����ַ���s����ÿ���ַ�ת����count������±꣬���ּ��Σ�count�����Ӧλ�þ��Ǽ���
//��ͳ�Ƴ��ظ��ַ��ĸ���sum����������һ���СΪlen-sum�����飻
//������������ɾ��������ǰ�ߵ��ַ�����ѡ��Ӻ���ǰ��������ԭ�ַ�����ÿ���ַ�����������tmp��

void  DropRepeateChar(char*& s,int len)
{
	assert(s && len>0);
	//��arr��ͳ��a-z֮������ַ��Ķ�Ӧ����
	char count[26] = {0};
	for (int i=0; i<len; i++)
	{
		if(s[i] >= 'a' && s[i] <= 'z')
		{
			int index = s[i] - 'a';
			count[index]++;
		}
	}

	//ͳ���ظ����ֵ��ַ�����
	int sum = 0;
	for (int i=0; i<26; i++)
	{
		if(count[i] >= 2)
			sum++;
	}

	//�Ӻ���ǰ�����ַ�
	int size = len - sum;
	int sz = size;
	char* tmp = new char[size+1];	//������Ҫ�࿪�ٳ�һ���ַ��ռ䣬������Ž�β��ʶ��
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