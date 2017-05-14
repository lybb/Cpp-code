#define  _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//дʱ����������
//class String
//{
//	friend ostream& operator<<(ostream& os,const String& s);
//public:
//	String(const char* s)
//		:_str(new char[strlen(s)+1])
//	{
//		strcpy(_str,s);
//	}
//	//���
//	String(String& s)		//��������
//		:_str(new char[strlen(s)+1])
//	{
//		strcpy(_str,s._str);
//	}
//private:
//	char* _str;
//};
//void test1()
//{
//	String str1("abcde");
//	String str2(str1);
//	cout<<str1<<endl;
//	cout<<str2<<endl;
//}

//���ü���
//class String
//{
//	friend ostream& operator<<(ostream& os,const String& s);
//public:
//	String(const char* s = "")
//		:_str(new char[strlen(s)+1])
//		,_pCount(new int(1))
//	{
//		cout<<"gouzao"<<endl;
//		strcpy(_str,s);
//	}
//	String(String& s)		//��������
//		:_str(s._str)
//		,_pCount(s._pCount)
//	{
//		cout<<"kaobeigouzao"<<endl;
//		++ *_pCount;
//	}
//	~String()
//	{
//		if(--_pCount[0] == 0)
//		{
//			cout<<"~String()"<<endl;
//			delete[] _str;
//			delete _pCount;
//		}
//	}
//	String& operator = (const String& s)
//	{
//		_str = s._str;
//		_pCount = s._pCount;
//		if (this != &s)		//����Ƿ��Ը�ֵ
//		{
//			if(--*_pCount == 0)
//			{
//				delete[] _str;
//				_str = new char[strlen(s._str)+1];
//				strcpy(_str,s._str);
//			}
//		}
//		return *this;
//	}
//private:
//	char* _str;
//	int* _pCount;
//};
//ostream& operator<<(ostream& os,const String& s)
//{
//	os<<s._str<<endl;
//	return os;
//}
//void test()
//{
//	String str1("abcde");
//	String str2(str1);
//	String str3;
//	str3 = str2;
//	cout<<str1<<endl;
//	cout<<str2<<endl;
//	cout<<str3<<endl;
//}

class String
{
	friend ostream& operator<<(ostream& os,String& s);
public:
	String(const char*str = "")
		:_str(new char[strlen(str)+1+4])
	{
		*(int *)_str = 1;	//*_pCount = 1
		_str = _str+4;	//�ҵ����ݴ�ŵ�λ��
		strcpy(_str,str);
		GetCount() = 1;
	}
	String(const String& str)
		:_str(str._str)
	{
		++GetCount();
	}
	~String()
	{
		if(--GetCount() == 0)
		{
			delete[] (_str-4);
		}
	}
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			if (--GetCount() == 0)
			{
				delete[] (_str-4);  
			}
			++GetCount();
			_str = s._str;
		}
		return *this;
	}
private:
	int& GetCount()		//���_pCount
	{
		return *((int *)_str-1);
	}
private:
	char *_str;
};
ostream& operator<<(ostream& os,String& s)
{
	os<<s._str;
	return os;
}
void test1()
{
	String str1("abcde");
	String str2(str1);
	String str3;
	str3 = str2;
	cout<<str1<<endl;
	cout<<str2<<endl;
	cout<<str3<<endl;
}

int main()
{
	test1();
	system("pause");
	return 0;
}