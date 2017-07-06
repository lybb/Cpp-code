#include <iostream>
using namespace std;


//scoped_ptr--->防拷贝
template<class T>
class ScopedPtr
{
public:
	ScopedPtr(T* ptr)
		:_ptr(ptr)
	{}
	~ScopedPtr()
	{
		delete _ptr;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
protected:
	ScopedPtr(ScopedPtr<T>& sp);	//拷贝构造
	ScopedPtr<T>& operator=(ScopedPtr<T>& sp);	//赋值运算符重载
private:
	T* _ptr;
};

int main()
{
	//ScopedPtr<char> sp1("asasas");
	ScopedPtr<int> sp1(new int(88));
	//ScopedPtr<int> sp2(sp1);
	//ScopedPtr<int> sp3 = sp1;
	system("pause");
	return 0;
}