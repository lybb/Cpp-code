#include"LinkList_cpp.h"

void test2()
{
	LinkList mylist;
	mylist.PushBack(4);
	mylist.PushBack(1);
	mylist.PushBack(4);
	mylist.PushBack(2);
	mylist.PushBack(4);
	mylist.PushBack(3);
	mylist.PushBack(4);
	mylist.PushBack(4);
	mylist.PushBack(5);
	mylist.PushBack(4);
	//mylist.Remove(4);
	mylist.RemoveAll(4);
	//mylist.PopBack();
	//mylist.PushFront(12);
	//mylist.PushFront(13);
	//mylist.PopFront();
	//mylist.Sort();
	cout<<mylist<<endl;
}
void test1()
{
	LinkList mylist;
	//mylist.PushBack(4);
	mylist.PushBack(1);
	////mylist.PushBack(4);
	//mylist.PushBack(2);
	////mylist.PushBack(4);
	//mylist.PushBack(3);
	//mylist.PushBack(4);
	////mylist.PushBack(4);
	//mylist.PushBack(5);
	//mylist.PushBack(4);
	cout<<mylist<<endl;
	Node* pos = NULL;
	int x = 0;
	int num = 0;
	cout<<"请输入要插入的位置";
	cin>>x;
	cout<<endl;
	pos = mylist.Find(x);
	cout<<"请输入要插入的数字";
	cin>>num;
	cout<<endl;
	mylist.Insert(pos,num);
	cout<<mylist<<endl;
}

void menu()
{
	printf("-----------------------------------\n");
	printf("-------- 0.结束    1.尾插 ---------\n");
	printf("-------- 2.尾删    3.头插----------\n");
	printf("-------- 4.头删    5.删除x  -------\n");
	printf("-------- 6.删除所有x --------------\n");
	printf("-------- 7.插入指定元素 -----------\n");
	printf("-------- 8.排序         -----------\n");
	printf("-------- 9.显示         -----------\n");
}
void test()
{
	LinkList mylist;
	int input = 1;
	DataType data = 0;
	DataType p = 0;
	Node* pos = NULL;
	while(input)
	{
		menu();
		cout<<"请选择:";
		cin>>input;
		cout<<endl;
		switch(input)
		{
		case 0:
			exit(0);
			break;
		case 1:
			cout<<"请输入插入的数：";
			cin>>data;
			mylist.PushBack(data);
			break;
		case 2:
			mylist.PopBack();
			break;
		case 3:
			cout<<"请输入插入的数：";
			cin>>data;
			mylist.PushFront(data);
			break;
		case 4:
			mylist.PopFront();
			break;
		case 5:
			printf("输入要删除的数：");
			scanf("%d",&data);
			mylist.Remove(data);
			break;
		case 6:
			printf("输入要删除的数：");
			scanf("%d",&data);
			mylist.RemoveAll(data);
			break;
		case 7:
			cout<<"请输入要在哪一个位置前插入:";
			cin>>p;
			cout<<"请输入要插入的数：";
			cin>>data;
			pos = mylist.Find(p);
			mylist.Insert(pos,data);
			break;
		case 8:
			mylist.Sort();
			break;
		case 9:
			mylist.Display();
			break;
		default:
			cout<<"无效选择"<<endl;
			break;
		}
	}
}

int main()
{
	test();
	system("pause");
	return 0;
}