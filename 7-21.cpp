#include <iostream>
//�������⡿--����һ������N����ôN�Ľ׳�N��ĩβ�ж��ٸ�0�أ����磺N��10��N����3 628 800��
//N����ĩβ������0��
//˼·������������������N�Ľ׳ˣ��ٽ���ת�����ַ�������0�Ļ�����Ҫ���ǵ�N�Ľ׳��п��ܴܺ�һ��
//���ʹ�Ų��£�������ĩβ��0��˼·ת������10�ı�������10�ı���ʱ˼·��ת�������ܱ�2����5��������
size_t CountTail0(int num)
{
	int i=1;
	int count = 0;
	for (; i<=num; i++)
	{
		if (i%5 == 0)
			count++;
	}
	return count;
}

int main()
{
	int ret = CountTail0(5);
	cout<<ret<<endl;
	system("pause");
	return 0;
}