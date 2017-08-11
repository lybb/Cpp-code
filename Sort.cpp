#include <iostream>
using namespace std;
#include <stack>
#include <cassert>

//插入排序
void InsertSort(int* a,int sz)
{
	if(a==NULL || sz<=0)
		return ;

	//2 5 4 9 3 6 8 7 1 0
	for (int index=1; index<sz; index++)
	{
		int pos = index-1;
		int tmp = a[index];
		while (pos>=0 && a[pos]>=tmp)
		{
			a[pos+1] = a[pos];
			pos--;
		}
		a[pos+1] = tmp;
	}
}

//希尔排序
void ShellSort(int* a,int sz)
{
	if(a==NULL || sz<=0)
		return ;
	int gap = 3;
	while (gap >1)
	{
		gap = gap/3 + 1;
		for (int index = gap; index<sz; index++)
		{
			int pos = index-gap;
			int tmp = a[index];
			while (pos>=0 && a[pos]>tmp)
			{
				a[pos+gap] = a[pos];
				pos -= gap;
			}
			a[pos+gap] = tmp;
		}
	}
}

//选择排序
void SelectSort1(int* a,int sz)
{
	if(a==NULL || sz<=0)
		return ;
	int min=0;
	for (int index=0; index<sz; index++)
	{
		min = index;
		for (int j=index+1; j<sz; j++)
		{
			if(a[j] < a[min])
				min = j;
		}
		swap(a[index],a[min]);
	}
}
void SelectSort2(int* a,int sz)
{
	if(a==NULL || sz<=0)
		return ;
	
	int left = 0;
	int right = sz-1;
	while (left < right)
	{
		int min=left;
		int max=left;
		for (int i=left; i<=right ;i++)
		{
			if(a[i] < a[min])
				min = i;
			if(a[i] > a[max])
				max = i;
		}
		swap(a[left],a[min]);
		if(left == max)
			max = min;
		swap(a[right],a[max]);
		left++;
		right--;
	}
}

//堆排序
void AdjustDown(int* a,int root,int sz)
{
	int parent = root;
	int child = parent*2+1;
	while (child <= sz)
	{
		if(child+1 < sz && a[child]<a[child+1])
			child++;
		if(a[child] > a[parent])
		{
			swap(a[child],a[parent]);
			parent = child;
			child = parent*2+1;
		}
		else
			break;
	}
}
void HeapSort(int* a,int sz)
{
	if(a==NULL || sz<=0)
		return ;
	int  i =0;
	for (i=(sz-1)/2; i>=0; i--)
	{
		AdjustDown(a,i,sz);
	}
	i=sz-1;
	while (i>0)
	{
		swap(a[0],a[i]);
		AdjustDown(a,0,i-1);
		--i;
	}
}


//冒泡排序    
void BubbleSort(int* a,int sz)
{
	if(a==NULL || sz<=0)
		return ;
	for (int i=0; i<sz; i++)
	{
		bool flag = false;
		for (int j=0; j<sz-1-i; j++)
		{
			if(a[j] > a[j+1])
			{
				swap(a[j],a[j+1]);
				flag = false;
			}
		}
		if(flag)
			break;
	}
}

//快排
int PartSort1(int* a,int left,int right)	//左右指针法 
{
	int start = left;
	int end = right;
	int key = a[end];
	while (start < end)
	{
		while (start < end && a[start] < key)
			start++;
		while (start < end && a[end] > key)
			end--;
		if(start < end)
			swap(a[start],a[end]);
	}
	if (a[start] > a[end])
	{
		swap(a[start],a[end]);
		return start;
	}
	else
		return start;
}

int PartSort2(int* a,int left,int right)	//挖坑法
{
	int start = left;
	int end = right;
	int key = a[end];
	while (start < end)
	{
		while (start < end && a[start] < key)
			start++;
		a[end] = a[start];
		while (start < end && a[end] > key)
			end--;
		a[start] = a[end];
	}
	a[start] = key;
	return start;
}

int PartSort3(int* a,int left,int right)	//前后指针法
{
	int cur = left;
	int prev = left-1;
	int key = a[right];
	while (cur < right)
	{
		if(a[cur]< key && ++prev!=cur)
			swap(a[cur],a[prev]);
		cur++;
	}
	swap(a[++prev],a[right]);
	return prev;
}

void QuickSort(int* a,int left,int right)
{
	if(a==NULL || (right-left)<=0)
		return ;
	if(left < right)
	{
		//int div = PartSort1(a,left,right);
		//int div = PartSort2(a,left,right);
		int div = PartSort3(a,left,right);
		QuickSort(a,left,div-1);
		QuickSort(a,div+1,right);
	}
}

//快排优化----三数取中
int GetMidNum(int* a,int left,int right)	//返回中间数的下标
{
	int mid = left + ((right-left)>>1);
	if(a[left] < a[right])
	{
		if(a[right] < a[mid])
			return right;
		else if(a[left] < a[mid])
			return mid;
		else
			return left;
	}
	else
	{
		if(a[left] < a[mid])
			return left;
		else if(a[right] < a[mid])
			return mid;
		else
			return right;
	}
}
void QuickSortMid(int* a,int left,int right)
{

}

//快排非递归
void QuickSortR(int* a,int left,int right)
{
	stack<int> s;
	s.push(right);
	s.push(left);
	while (!s.empty())
	{
		int start = s.top();
		s.pop();
		int end = s.top();
		s.pop();
		int div = PartSort1(a,start,end);
		if(start < div-1)
		{
			s.push(div-1);
			s.push(start);
		}
		if(div+1 < end)
		{
			s.push(end);
			s.push(div+1);
		}
	}
}


//归并排序
void _MergeSort(int* a,int* tmp,int left,int right)
{
	int mid = left+((right-left)>>1);
	if(left < mid)
		_MergeSort(a,tmp,left,mid);
	if(mid+1 < right)
		_MergeSort(a,tmp,mid+1,right);
	int start1 = left;
	int end1 = mid;
	int start2 = mid+1;
	int end2 = right;
	int index = left;
	while (start1<=end1 && start2<=end2)
	{
		if(a[start1] < a[start2])
			tmp[index++] = a[start1++];
		else
			tmp[index++] = a[start2++];
	}
	while (start1 <= end1)
		tmp[index++] = a[start1++];
	while (start2 <= end2)
		tmp[index++] = a[start2++];

	for (int i=0; i<index; i++)
	{
		a[i] = tmp[i];
	}
}
void MergeSort(int* a,int left,int right)
{
	if(a==NULL || (right-left)<=0)
		return ;
	int* tmp = new int[right+1-left];
	_MergeSort(a,tmp,left,right);
	delete[] tmp;
}


//非比较排序
//计数排序
void CountSort(int* a,int sz)
{
	assert(a);
	int max = a[0];
	int min = a[0];
	for(int i=0; i<sz; i++)
	{
		if (a[i] < min)
			min = a[i];
		if (a[i] > max)
			max = a[i];
	}

	int range = max+1-min;
	int* tmp = new int[range];
	memset(tmp,0,sizeof(int)*range);
	int index = 0;
	for (int i=0; i<sz; i++)
	{
		index = a[i];
		tmp[index-min]++;
	}
	int i=0;
	for (index=0; index<range; index++)
	{
		while (tmp[index])
		{
			a[i++] = index+min;
			tmp[index]--;
		}
	}
}


void Display(int* a,int sz)
{
	for (int i=0; i<sz; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

void Test()
{
	//int a[] = {2,5,4,9,3,6,8,7,1,0};
	//int a[] = {9,5,4,9,3,6,8,7,1,0};
	//int a[] = {0,5,4,9,3,6,8,7,1,9};
	//int sz = sizeof(a)/sizeof(a[0]);
	//InsertSort(a,sz);
	//ShellSort(a,sz);
	//SelectSort1(a,sz);
	//SelectSort2(a,sz);
	//HeapSort(a,sz);
	//BubbleSort(a,sz);
	//QuickSort(a,0,sz-1);
	//QuickSortR(a,0,sz-1);
	//MergeSort(a,0,sz-1);

	//int a[] = {2,2,9,5,3,6,9};
	int a[] = {73,22,93,43,55,14,28,65,39,81};
	int sz = sizeof(a)/sizeof(a[0]);
	CountSort(a,sz);
	Display(a,sz);
}