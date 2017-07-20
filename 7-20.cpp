#include <stack>
#include <iostream>
using namespace std;

//�ж�ջ��ѹ�뵯��˳�򣺽�������ջ��������ջ˳������齫������ջ��û��һ�Σ����ж�ջ��Ԫ���Ƿ�ͳ�ջ����ĵ�ǰԪ���Ƿ���ͬ�����
//��ͬ���ͽ�����ջ��Ԫ��pop������ʹ��ջ������±�+1�����ջ��Ϊ�գ���ջ��Ԫ�����ջ����ĵ�ǰԪ�ز���ȣ��򷵻�false
bool  IsPopOrder(int* In, int sz1, int* Out, int sz2)
{
	if(In==NULL || Out==NULL)
		return false;
	int i=0;
	int j=0;
	stack<int> s;
	s.push(In[i++]);
	while(!s.empty() && i<sz1)
	{
		s.push(In[i++]);
		while (!s.empty() && s.top() == Out[j] && j<sz2)
		{
			s.pop();
			j++;
		}
	}
	if (s.empty() || j>=sz2)
		return true;
	else
		return false;
}

//��������������1�ĸ���
int GetNumCount1(int num)
{
	int count = 0;
	if (num < 0)
	{
		count = 1;
		num = num*-1;
	}
	while (num)
	{
		if((num&1) == 1)
			count++;
		num >>= 1;
	}
	return count;
}

int GetNumCount2(int num)
{
	int count=0;
	while (num)
	{
		if(num & (num-1))
			count++;
		num >>= 1;
	}
	return count;
}


int main()
{
	int ret = GetNumCount1(10);
	//int ret = GetNumCount1(-10);
	int In[] = {1,2,3,4,5};
	//int Out[] = {4,5,3,2,1};
	//int Out[] = {4,5,2,3,1};
	int Out[] = {4,5,1};
	int sz1 = sizeof(In)/sizeof(In[0]);
	int sz2 = sizeof(Out)/sizeof(Out[0]);
	cout<<IsPopOrder(In,sz1,Out,sz2)<<endl;
	system("pause");
	return 0;
}