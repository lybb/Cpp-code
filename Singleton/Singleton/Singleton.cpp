#include <iostream>
using namespace std;
#include <mutex>
#include <assert.h>

class Singleton1
{
public:
	//�ⷨһ��ֻ�����ڵ��̣߳�һ�����̲߳������п��ܾ������̰߳�ȫ����
	//static Singleton1* GetInstance()
	//{
	//	if (_inst == NULL)
	//		_inst = new Singleton1();
	//	return _inst;
	//}

	//�ⷨ���������ⷨһ������--->���뻥����---->ʹЧ�ʽ���
	static Singleton1* GetInstance()
	{
		if (_inst == NULL)
		{
			std::lock_guard<std::mutex> lock(_mtx);
			if (_inst == NULL)
				_inst = new Singleton1();
		}
		return _inst;
	}

	void Display()
	{
		cout << "Singleton1::" << _count << endl;
	}
private:
	Singleton1()
		:_count(0)
	{}
	Singleton1(const Singleton1&);
	static Singleton1* _inst;
	static mutex _mtx;
	int _count;
};
Singleton1* Singleton1::_inst;
mutex Singleton1::_mtx;

//����ģʽ
class Singleton2
{
public:
	//static Singleton2* GetInstance()
	//{
	//	assert(_inst);
	//	return _inst;
	//}

	static Singleton2* GetInstance()
	{
		static Singleton2 _inst;
		return &_inst;
	}
	void Display()
	{
		cout << "Singleton2::" << _count << endl;
	}
private:
	Singleton2() 
		:_count(0)
	{}
	Singleton2(const Singleton2&);
	//static Singleton2* _inst;
	int _count;
};
//Singleton2* Singleton2::_inst = new Singleton2;

int main()
{
	Singleton1::GetInstance()->Display();
	Singleton1::GetInstance()->Display();
	Singleton1::GetInstance()->Display();

	Singleton2::GetInstance()->Display();
	Singleton2::GetInstance()->Display();
	Singleton2::GetInstance()->Display();
	system("pause");
	return 0;
}

//class Singleton
//{
//public:
//	static Singleton* GetInstance()	//�����ṩ�Ļ�ȡ����Ľӿ�
//	{
//		//assert(_inst);
//		if (_inst == NULL)	//ֻ�����ָ��Ϊ��ʱ��ȥ����һ������
//		{
//			_inst = new Singleton;
//		}
//		return _inst;
//	}
//
//	void print()
//	{
//		cout<<"Singleton::"<<_count<<endl;
//	}
//
//private:
//	Singleton()
//		:_count(0)
//	{}
//
//	Singleton(const Singleton& s);
//	Singleton& operator = (const Singleton&);
//	//��ֵ�������������Ϊ˽�е�Ҳ���Բ�����Ϊoperator=֮ǰ���������󣬶�operator =���ᴴ���¶���
//
//	static Singleton* _inst;//����һ��ָ��ʵ����ָ��
//	int  _count;
//};
//Singleton* Singleton::_inst = NULL;

int main()
{
	Singleton::GetInstance()->print();
	Singleton::GetInstance()->print();
	system("pause");
	return 0;
}