#include <iostream>
using namespace std;


template<typename T>
class SharedPtr
{
public:
	SharedPtr(T* ptr)
		:_ptr(ptr)
		,_count(new int(0))
	{}
	SharedPtr(const SharedPtr<T>& sp)
	{
		//this指针指向这块空间，引用计数器的值+1
		_ptr = sp._ptr;	
		_count = sp._count;
		(*_count)++;
	}

	//sp3 = sp2
	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		if (this != &sp)	//防止自己给自己赋值
		{
			//如果是最后一个指向这个空间的智能指针，负责销毁这块空间
			//做这一步的判断是因为：赋值之前是有两个对象的，sp3指向的那块空间并不是只有sp3一个指针指向，还可能有其他指针指向
			if (--(*_count) == 0)
			{
				delete _ptr;
				delete _count;
				_ptr = _count = NULL;
			}

			//此时sp3的指针时this指针
			_ptr = sp._ptr;	//否则就给指针赋新的值
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
		if (--(*_count) == 0)	//当引用计数减为0的时候才去释放空间
		{
			delete _ptr;
			delete _count;
			_ptr = NULL;
			_count = NULL;
		}
	}
private:
	T* _ptr;
	int* _count; //引用计数器
	//static int _count;	
	//为什么不用static？static定义的变量是全局的，每来一个指针静态变量就会++，导致指向不明确，_count的值也不明确
};

int main()
{
	SharedPtr<int> sp1(new int(3));
	//SharedPtr<char> sp1("adadadad");
	//SharedPtr<char> sp2 = sp1;
	//SharedPtr<char> sp3(sp2);
	system("pause");
	return 0;
}