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
	cout<<"������Ҫ�����λ��";
	cin>>x;
	cout<<endl;
	pos = mylist.Find(x);
	cout<<"������Ҫ���������";
	cin>>num;
	cout<<endl;
	mylist.Insert(pos,num);
	cout<<mylist<<endl;
}

void menu()
{
	printf("-----------------------------------\n");
	printf("-------- 0.����    1.β�� ---------\n");
	printf("-------- 2.βɾ    3.ͷ��----------\n");
	printf("-------- 4.ͷɾ    5.ɾ��x  -------\n");
	printf("-------- 6.ɾ������x --------------\n");
	printf("-------- 7.����ָ��Ԫ�� -----------\n");
	printf("-------- 8.����         -----------\n");
	printf("-------- 9.��ʾ         -----------\n");
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
		cout<<"��ѡ��:";
		cin>>input;
		cout<<endl;
		switch(input)
		{
		case 0:
			exit(0);
			break;
		case 1:
			cout<<"��������������";
			cin>>data;
			mylist.PushBack(data);
			break;
		case 2:
			mylist.PopBack();
			break;
		case 3:
			cout<<"��������������";
			cin>>data;
			mylist.PushFront(data);
			break;
		case 4:
			mylist.PopFront();
			break;
		case 5:
			printf("����Ҫɾ��������");
			scanf("%d",&data);
			mylist.Remove(data);
			break;
		case 6:
			printf("����Ҫɾ��������");
			scanf("%d",&data);
			mylist.RemoveAll(data);
			break;
		case 7:
			cout<<"������Ҫ����һ��λ��ǰ����:";
			cin>>p;
			cout<<"������Ҫ���������";
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
			cout<<"��Чѡ��"<<endl;
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