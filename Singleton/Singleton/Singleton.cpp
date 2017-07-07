#include <assert.h>
#include <iostream>
using namespace std;

class Singleton
{
public:
	static Singleton* GetInstance()	//对外提供的获取对象的接口
	{
		//assert(_inst);
		if (_inst == NULL)	//只有这个指针为空时才去构造一个对象
		{
			_inst = new Singleton;
		}
		return _inst;
	}

	void print()
	{
		cout<<"Singleton::"<<_count<<endl;
	}

private:
	Singleton()
		:_count(0)
	{}

	Singleton(const Singleton& s);
	Singleton& operator = (const Singleton&);
	//赋值运算符可以声明为私有的也可以不，因为operator=之前有两个对象，而operator =不会创建新对象

	static Singleton* _inst;//定义一个指向实例的指针
	int  _count;
};
Singleton* Singleton::_inst = NULL;

int main()
{
	Singleton::GetInstance()->print();
	Singleton::GetInstance()->print();
	system("pause");
	return 0;
}