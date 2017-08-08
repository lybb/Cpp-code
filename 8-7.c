//ģ��ʵ��C���memcpy��memmove��

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//dst��src���ص�
void* MyMemcpy(void* dst,const void* src,size_t nums)
{
 	//assert(dst);
 	//assert(src);
	char* pdst = (char*)dst;
	const char* psrc = (const char*)src;
	while(nums--)
	{
		*pdst++ = *psrc++;
	}
	return dst;
}

// dst��src�п��ܻ��ص�
 void* MyMemmove(void* dst,const void* src,size_t nums)
 {
 	//assert(dst);
 	//assert(src);
 	char* pdst = (char*)dst;
 	const char* psrc = (const char*)src;
	size_t count = strlen(psrc);
	if (psrc<pdst && pdst<psrc+count)	//psrc<pdst<psrc+count----�Ӻ���ǰ
	{
		pdst = pdst+nums-1;
		psrc = psrc+nums-1;
		while (nums--)
			*pdst-- = *psrc--;
	}
	else
	{
		while (nums--)
			*pdst++ = *psrc++;
	}
 	return dst;
 }


int main()
{
	int i=0;
	//char* src = "abcdef";
	char dst[20]="123456789";;
	//size_t len = strlen(src);
//-------------------MyMemcpy---------------------
	//memcpy(dst,src,3);
	//MyMemcpy(dst,src,3);
	//MyMemcpy(dst,src,0);
	//MyMemcpy(dst,src,7);
	//MyMemcpy(dst,src,len);
	//printf("%s\n",dst);

//-------------------MyMemmove---------------------;
	//memmove(dst+2,dst,4);	//�ص���---121234789
	//memmove(dst+10,dst,6);//���ص���---123456789
	//MyMemmove(dst+2,dst,4);	//�ص���---121234789
	MyMemmove(dst+10,dst,6);	//���ص���---123456789
	printf("%s\n",dst);
	system("pause");
	return 0;
}