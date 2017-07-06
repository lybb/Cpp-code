#include <iostream>
using namespace std;


//auto_ptr--->权限转移
template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr = NULL)
		:_ptr(ptr)
		,owner(true)	//赋予权限
	{}
	AutoPtr(AutoPtr<T>& ap)
	{
		_ptr = ap._ptr;
		ap.owner = false;	//转让权限
	}
	AutoPtr& operator =(AutoPtr<T>& ap)
	{
		if (this != &ap)
		{
			delete this->_ptr;
			this->_ptr = ap._ptr;
			ap._ptr = NULL;
			////转移权限
			//this->owner = true;
			//ap.owner = false;
		}
		return *this;
	}

	~AutoPtr()
	{
		if (owner)
		{
			this->owner = false;
			delete _ptr;
		}
	}

	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}

private:
	T* _ptr;
	bool owner;	//权限的拥有者
};

int main()
{
	//AutoPtr<pair<string,int>> ap1(new pair<string,int>("string",10));
	//AutoPtr<pair<string,int>> ap2(ap1);
	//(*ap1).first="ly";
	//auto_ptr两种缺陷
	AutoPtr<int> ap1(new int(1));
	if (1)
		AutoPtr<int> ap2(ap1);
	*ap1 = 10;
	system("pause");
	return 0;
}