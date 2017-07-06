#include <iostream>
using namespace std;

//���붨��ɾ����
class Deafult
{
public:
	void operator()(void* ptr)
	{
		delete ptr;
		cout<<"Default!"<<endl;
	}
};

struct Fclose
{
	void operator()(void* ptr)
	{
		fclose((FILE*)ptr);
		cout<<"Fclose!"<<endl;
	}
};

struct Free
{
	void operator()(void* ptr)
	{
		free(ptr);
		cout<<"Free!"<<endl;
	}
};

template<typename T,typename D=Deafult>
class SharedPtr
{
public:
	SharedPtr(T* ptr=0,D del=Deafult())
		:_ptr(ptr)
		,_count(new int(1))	//���캯�������һ���������Ӧ�ó�ʼ��Ϊ1
		,_del(del)
	{}
	SharedPtr(const SharedPtr<T>& sp)
	{
		//thisָ��ָ�����ռ䣬���ü�������ֵ+1
		_ptr = sp._ptr;	
		_count = sp._count;
		(*_count)++;
	}

	//sp3 = sp2
	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		if (this != &sp)	//��ֹ�Լ����Լ���ֵ
		{
			//��������һ��ָ������ռ������ָ�룬�����������ռ�
			//����һ�����ж�����Ϊ����ֵ֮ǰ������������ģ�sp3ָ����ǿ�ռ䲢����ֻ��sp3һ��ָ��ָ�򣬻�����������ָ��ָ��
			if (--(*_count) == 0)
			{
				_del(_ptr);
				//delete _ptr;
				delete _count;
				_ptr = _count = NULL;
			}

			//��ʱsp3��ָ��ʱthisָ��
			_ptr = sp._ptr;	//����͸�ָ�븳�µ�ֵ
			_count = sp._count;
			(*_count)++;
		}
	}
	T* operator->()
	{
		return _ptr;
	}
	T& operator*()
	{
		return *_ptr;
	}

	~SharedPtr()
	{
		if (--(*_count) == 0)	//�����ü�����Ϊ0��ʱ���ȥ�ͷſռ�
		{
			_del(_ptr);
			//delete _ptr;
			delete _count;
			_ptr = NULL;
			_count = NULL;
		}
	}
private:
	T* _ptr;
	int* _count; //���ü�����
	D _del;
	//static int _count;	
	//Ϊʲô����static��static����ı�����ȫ�ֵģ�ÿ��һ��ָ�뾲̬�����ͻ�++������ָ����ȷ��_count��ֵҲ����ȷ
};

void Test()
{
	//SharedPtr<int> sp1(new int(3));
	//SharedPtr<char> sp1("adadadad");
	//SharedPtr<char> sp2 = sp1;
	//SharedPtr<char> sp3(sp2);

	//����ɾ��������
	SharedPtr<int> sp1(new int(22));
	SharedPtr<int,Free> sp2((int*)malloc(sizeof(int)*10),Free());
	SharedPtr<FILE,Fclose> sp(fopen("test.txt","w"),Fclose());
}

int main()
{
	Test();
	system("pause");
	return 0;
}


//
////û�мӶ���ɾ����
//template<typename T>
//class SharedPtr
//{
//public:
//	SharedPtr(T* ptr)
//		:_ptr(ptr)
//		,_count(new int(0))
//	{}
//	SharedPtr(const SharedPtr<T>& sp)
//	{
//		//thisָ��ָ�����ռ䣬���ü�������ֵ+1
//		_ptr = sp._ptr;	
//		_count = sp._count;
//		(*_count)++;
//	}
//
//	//sp3 = sp2
//	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
//	{
//		if (this != &sp)	//��ֹ�Լ����Լ���ֵ
//		{
//			//��������һ��ָ������ռ������ָ�룬�����������ռ�
//			//����һ�����ж�����Ϊ����ֵ֮ǰ������������ģ�sp3ָ����ǿ�ռ䲢����ֻ��sp3һ��ָ��ָ�򣬻�����������ָ��ָ��
//			if (--(*_count) == 0)
//			{
//				delete _ptr;
//				delete _count;
//				_ptr = _count = NULL;
//			}
//
//			//��ʱsp3��ָ��ʱthisָ��
//			_ptr = sp._ptr;	//����͸�ָ�븳�µ�ֵ
//			_count = sp._count;
//			(*_count)++;
//		}
//	}
//	T* operator->()
//	{
//		return _ptr;
//	}
//	T& operator*()
//	{
//		return *_ptr;
//	}
//
//	~SharedPtr()
//	{
//		if (--(*_count) == 0)	//�����ü�����Ϊ0��ʱ���ȥ�ͷſռ�
//		{
//			delete _ptr;
//			delete _count;
//			_ptr = NULL;
//			_count = NULL;
//		}
//	}
//private:
//	T* _ptr;
//	int* _count; //���ü�����
//	//static int _count;	
//	//Ϊʲô����static��static����ı�����ȫ�ֵģ�ÿ��һ��ָ�뾲̬�����ͻ�++������ָ����ȷ��_count��ֵҲ����ȷ
//};
//
//int main()
//{
//	SharedPtr<int> sp1(new int(3));
//	//SharedPtr<char> sp1("adadadad");
//	//SharedPtr<char> sp2 = sp1;
//	//SharedPtr<char> sp3(sp2);
//	system("pause");
//	return 0;
//}