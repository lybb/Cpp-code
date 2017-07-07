#include <assert.h>
#include <iostream>
using namespace std;

class Singleton
{
public:
	static Singleton* GetInstance()	//�����ṩ�Ļ�ȡ����Ľӿ�
	{
		//assert(_inst);
		if (_inst == NULL)	//ֻ�����ָ��Ϊ��ʱ��ȥ����һ������
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
	//��ֵ�������������Ϊ˽�е�Ҳ���Բ�����Ϊoperator=֮ǰ���������󣬶�operator =���ᴴ���¶���

	static Singleton* _inst;//����һ��ָ��ʵ����ָ��
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