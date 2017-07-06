#include <iostream>
using namespace std;


//auto_ptr--->Ȩ��ת��
template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr = NULL)
		:_ptr(ptr)
		,owner(true)	//����Ȩ��
	{}
	AutoPtr(AutoPtr<T>& ap)
	{
		_ptr = ap._ptr;
		ap.owner = false;	//ת��Ȩ��
	}
	AutoPtr& operator =(AutoPtr<T>& ap)
	{
		if (this != &ap)
		{
			delete this->_ptr;
			this->_ptr = ap._ptr;
			ap._ptr = NULL;
			////ת��Ȩ��
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
	bool owner;	//Ȩ�޵�ӵ����
};

int main()
{
	//AutoPtr<pair<string,int>> ap1(new pair<string,int>("string",10));
	//AutoPtr<pair<string,int>> ap2(ap1);
	//(*ap1).first="ly";
	//auto_ptr����ȱ��
	AutoPtr<int> ap1(new int(1));
	if (1)
		AutoPtr<int> ap2(ap1);
	*ap1 = 10;
	system("pause");
	return 0;
}