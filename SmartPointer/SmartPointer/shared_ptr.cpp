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
				delete _ptr;
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
			delete _ptr;
			delete _count;
			_ptr = NULL;
			_count = NULL;
		}
	}
private:
	T* _ptr;
	int* _count; //���ü�����
	//static int _count;	
	//Ϊʲô����static��static����ı�����ȫ�ֵģ�ÿ��һ��ָ�뾲̬�����ͻ�++������ָ����ȷ��_count��ֵҲ����ȷ
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