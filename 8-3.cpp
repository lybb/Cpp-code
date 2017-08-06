#include "Sort.h"

#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>


//求topK水果问题
//求解这个题的整体思路就是：先统计各种水果及其出现的次数，然后按次数进行排序，最后再打印出前K大的
//统计次数时，需要选取的是K/V结构，K是水果名称，V是次数-----使用map
//排序时，既可以使用STL算法中的sort进行排序，也可以进行建堆求取前K大

//使用优先级队列/堆时，需要建小堆
struct Less 
{
	bool operator()(const map<string,int>::iterator& lp,const map<string,int>::iterator& rp)
	{
		return (lp->second) < (rp->second);
	}
};
//使用sort进行排序时，需要降序排序
struct Greater 
{
	bool operator()(const map<string,int>::iterator& lp,const map<string,int>::iterator& rp)
	{
		return (lp->second) > (rp->second);
	}
};

//解法一：将水果及其次数存进vector中，使用堆来进行求取前K大
void GetFavoriteFruitH(const vector<string>& fruits,size_t k)
{
	if(fruits.empty())
		return ;
	map<string,int> countMap;
	//1、将水果及其出现的次数统计出来---使用了三种做法：find，insert，operator[]

	////1-1使用find函数，如果find返回false，则将该种水果新插入一次，否则，就将其次数加1	
	//for (size_t i=0; i<fruits.size(); i++)
	//{
	//	map<string,int>::iterator it = countMap.find(fruits[i]);
	//	if (it != countMap.end())
	//		it->second++;
	//		//(*it).second++;
	//	else
	//		countMap.insert(make_pair(fruits[i],1));
	//}

	////1-2使用operator[]
	//for (size_t i=0; i<fruits.size(); i++)
	//{
	//	countMap[fruits[i]]++;	
	//	//map中operator[]的实现：(*((this->insert(make_pair(x,T()))).first)).second
	//	//insert返回的是一个pair<itrator,bool>结构体，取first就取到了指向k出的迭代器，再对迭代器
	//	//解引用，就是K，再取second就可以对其value++
	//}

	//1-3采用insert返回值是pair<>结构体的方式
	for (size_t i=0; i<fruits.size(); i++)
	{
		pair<map<string,int>::iterator,bool> ret = countMap.insert(make_pair(fruits[i],1));
		if(ret.second == false)
			ret.first->second++;
	}

	//2、将map中的数据插入到vector中
	vector<map<string,int>::iterator> v;
	map<string,int>::iterator it = countMap.begin();
	while (it != countMap.end())
	{
		v.push_back(it);
		it++;
	}

	//3、建堆---建小堆，每次堆顶的值都是最小的，如果下次进来的值比堆顶还小，那么就不进堆，否则就
	//将堆顶值丢弃，并将当前值插入
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
	

	//3、打印水果及次数
	size_t index = 0;
	while (k--)
	{
		map<string,int>::iterator tmp = v[index++];
		cout<<tmp->first<<":"<<tmp->second<<endl;
	}
	cout<<endl;
}

//解法二：将水果及其次数存进vector中，使用sort算法进行排序
void GetFavoriteFruitV(const vector<string>& fruits,size_t k)
{
	if(fruits.empty())
		return ;
	map<string,int> countMap;
	//1、将水果及其出现的次数统计出来
	for (size_t i=0; i<fruits.size(); i++)
	{
		countMap[fruits[i]]++;
	}

	//2、将countMap中的水果及次数存在vector中，再进行排序
	vector<map<string,int>::iterator> v;
	map<string,int>::iterator it = countMap.begin();
	while (it != countMap.end())
	{
		v.push_back(it);
		it++;
	}
	sort(v.begin(),v.end(),Greater());

	//3、打印水果及次数
	size_t index = 0;
	while (k--)
	{
		map<string,int>::iterator tmp = v[index++];
		cout<<tmp->first<<":"<<tmp->second<<endl;
	}
	cout<<endl;
}

//解法三：利用优先级队列进行求取前K个水果的操作
void GetFavoriteFruitP(const vector<string>& fruits,size_t k)
{
	if(fruits.empty())
		return ;
	//1、先将每种水果以及出现的次数统计在一个map中
	map<string,int> countMap;
	for (size_t i=0; i<fruits.size(); i++)
	{
		countMap[fruits[i]]++;	
	}
	//2、将水果以及对应次数放入优先级队列，则每次top()取出的都是次数最多的水果
	priority_queue<map<string,int>::iterator,vector<map<string,int>::iterator>,Less> pq;
	map<string,int>::iterator it = countMap.begin();
	while (it != countMap.end())
	{
		pq.push(it);
		it++;
	}	

	//3、打印前K种水果及其次数
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
	fruits.push_back("西瓜");
	fruits.push_back("水蜜桃");
	fruits.push_back("李子");
	fruits.push_back("西瓜");
	fruits.push_back("香蕉");
	fruits.push_back("西瓜");
	fruits.push_back("香蕉");
	fruits.push_back("苹果");
	fruits.push_back("水蜜桃");
	fruits.push_back("西瓜");
	fruits.push_back("苹果");
	fruits.push_back("香蕉");
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