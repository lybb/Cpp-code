#include "Sort.h"

#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>


//��topKˮ������
//�������������˼·���ǣ���ͳ�Ƹ���ˮ��������ֵĴ�����Ȼ�󰴴���������������ٴ�ӡ��ǰK���
//ͳ�ƴ���ʱ����Ҫѡȡ����K/V�ṹ��K��ˮ�����ƣ�V�Ǵ���-----ʹ��map
//����ʱ���ȿ���ʹ��STL�㷨�е�sort��������Ҳ���Խ��н�����ȡǰK��

//ʹ�����ȼ�����/��ʱ����Ҫ��С��
struct Less 
{
	bool operator()(const map<string,int>::iterator& lp,const map<string,int>::iterator& rp)
	{
		return (lp->second) < (rp->second);
	}
};
//ʹ��sort��������ʱ����Ҫ��������
struct Greater 
{
	bool operator()(const map<string,int>::iterator& lp,const map<string,int>::iterator& rp)
	{
		return (lp->second) > (rp->second);
	}
};

//�ⷨһ����ˮ������������vector�У�ʹ�ö���������ȡǰK��
void GetFavoriteFruitH(const vector<string>& fruits,size_t k)
{
	if(fruits.empty())
		return ;
	map<string,int> countMap;
	//1����ˮ��������ֵĴ���ͳ�Ƴ���---ʹ��������������find��insert��operator[]

	////1-1ʹ��find���������find����false���򽫸���ˮ���²���һ�Σ����򣬾ͽ��������1	
	//for (size_t i=0; i<fruits.size(); i++)
	//{
	//	map<string,int>::iterator it = countMap.find(fruits[i]);
	//	if (it != countMap.end())
	//		it->second++;
	//		//(*it).second++;
	//	else
	//		countMap.insert(make_pair(fruits[i],1));
	//}

	////1-2ʹ��operator[]
	//for (size_t i=0; i<fruits.size(); i++)
	//{
	//	countMap[fruits[i]]++;	
	//	//map��operator[]��ʵ�֣�(*((this->insert(make_pair(x,T()))).first)).second
	//	//insert���ص���һ��pair<itrator,bool>�ṹ�壬ȡfirst��ȡ����ָ��k���ĵ��������ٶԵ�����
	//	//�����ã�����K����ȡsecond�Ϳ��Զ���value++
	//}

	//1-3����insert����ֵ��pair<>�ṹ��ķ�ʽ
	for (size_t i=0; i<fruits.size(); i++)
	{
		pair<map<string,int>::iterator,bool> ret = countMap.insert(make_pair(fruits[i],1));
		if(ret.second == false)
			ret.first->second++;
	}

	//2����map�е����ݲ��뵽vector��
	vector<map<string,int>::iterator> v;
	map<string,int>::iterator it = countMap.begin();
	while (it != countMap.end())
	{
		v.push_back(it);
		it++;
	}

	//3������---��С�ѣ�ÿ�ζѶ���ֵ������С�ģ�����´ν�����ֵ�ȶѶ���С����ô�Ͳ����ѣ������
	//���Ѷ�ֵ������������ǰֵ����
	it = countMap.begin();
	make_heap(v.begin(),v.end(),Less());
	v.push_back(it);
	it++;
	while (it != countMap.end())
	{
		if(it->second > v.front()->second)
		{
			pop_heap(v.begin(),v.end(),Less());
			v.pop_back();
			v.push_back(it);
			push_heap(v.begin(),v.end(),Less());
		}
		it++;
	}
	

	//3����ӡˮ��������
	size_t index = 0;
	while (k--)
	{
		map<string,int>::iterator tmp = v[index++];
		cout<<tmp->first<<":"<<tmp->second<<endl;
	}
	cout<<endl;
}

//�ⷨ������ˮ������������vector�У�ʹ��sort�㷨��������
void GetFavoriteFruitV(const vector<string>& fruits,size_t k)
{
	if(fruits.empty())
		return ;
	map<string,int> countMap;
	//1����ˮ��������ֵĴ���ͳ�Ƴ���
	for (size_t i=0; i<fruits.size(); i++)
	{
		countMap[fruits[i]]++;
	}

	//2����countMap�е�ˮ������������vector�У��ٽ�������
	vector<map<string,int>::iterator> v;
	map<string,int>::iterator it = countMap.begin();
	while (it != countMap.end())
	{
		v.push_back(it);
		it++;
	}
	sort(v.begin(),v.end(),Greater());

	//3����ӡˮ��������
	size_t index = 0;
	while (k--)
	{
		map<string,int>::iterator tmp = v[index++];
		cout<<tmp->first<<":"<<tmp->second<<endl;
	}
	cout<<endl;
}

//�ⷨ�����������ȼ����н�����ȡǰK��ˮ���Ĳ���
void GetFavoriteFruitP(const vector<string>& fruits,size_t k)
{
	if(fruits.empty())
		return ;
	//1���Ƚ�ÿ��ˮ���Լ����ֵĴ���ͳ����һ��map��
	map<string,int> countMap;
	for (size_t i=0; i<fruits.size(); i++)
	{
		countMap[fruits[i]]++;	
	}
	//2����ˮ���Լ���Ӧ�����������ȼ����У���ÿ��top()ȡ���Ķ��Ǵ�������ˮ��
	priority_queue<map<string,int>::iterator,vector<map<string,int>::iterator>,Less> pq;
	map<string,int>::iterator it = countMap.begin();
	while (it != countMap.end())
	{
		pq.push(it);
		it++;
	}	

	//3����ӡǰK��ˮ���������
	while (k--)
	{
		cout<<pq.top()->first<<":"<<pq.top()->second<<endl;
		pq.pop();
	}
	cout<<endl;
}



int main()
{
	vector<string> fruits;
	fruits.push_back("����");
	fruits.push_back("ˮ����");
	fruits.push_back("����");
	fruits.push_back("����");
	fruits.push_back("�㽶");
	fruits.push_back("����");
	fruits.push_back("�㽶");
	fruits.push_back("ƻ��");
	fruits.push_back("ˮ����");
	fruits.push_back("����");
	fruits.push_back("ƻ��");
	fruits.push_back("�㽶");
	cout<<"GetFavoriteFruitH----->"<<endl;
	GetFavoriteFruitH(fruits,2);
	cout<<"GetFavoriteFruitP----->"<<endl;
	GetFavoriteFruitP(fruits,2);
	cout<<"GetFavoriteFruitV----->"<<endl;
	GetFavoriteFruitV(fruits,2);
	//Test();


	system("pause");
	return 0;
}