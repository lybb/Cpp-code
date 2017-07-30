#include <iostream>
using namespace std;
#include <mutex>
#include <assert.h>

class Singleton1
{
public:
	//解法一：只适用于单线程，一旦多线程并发，有可能就引发线程安全问题
	//static Singleton1* GetInstance()
	//{
	//	if (_inst == NULL)
	//		_inst = new Singleton1();
	//	return _inst;
	//}

	//解法二：针对与解法一的问题--->加入互斥锁---->使效率降低
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

//饱汉模式
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
//	static Singleton* GetInstance()	//对外提供的获取对象的接口
//	{
//		//assert(_inst);
//		if (_inst == NULL)	//只有这个指针为空时才去构造一个对象
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
//	//赋值运算符可以声明为私有的也可以不，因为operator=之前有两个对象，而operator =不会创建新对象
//
//	static Singleton* _inst;//定义一个指向实例的指针
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