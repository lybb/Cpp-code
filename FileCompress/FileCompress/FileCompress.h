#define _CRT_SECURE_NO_WARNINGS
#include "HuffmanTree.h"
#include <string>
#include <Windows.h>

typedef long long LongType;
struct CharInfo
{
	CharInfo(LongType count=0)
		:_count(count)
	{}

	CharInfo operator+(const CharInfo& info)
	{
		return CharInfo(_count + info._count);
	}
	bool operator< (const CharInfo& info)
	{
		return _count < info._count;
	}
	bool operator !=(const CharInfo& info)
	{
		return _count != info._count;
	}

	unsigned char _ch;		//���һ�����ֵ��ַ�
	LongType	_count;		//��¼ÿ���ַ����ֵĸ���
	string		_code;		//��¼�ַ�����
};


class FileCompress
{
public:
	FileCompress()
	{
		for (int i=0; i<256; i++)	
		{
			_info[i]._ch = i;
			_info[i]._count = 0;
		}
	}
public:
	//ѹ��
	string Compress(const char* filename)
	{
		//1.�����ƶ���ʽ���ļ�
		//2.ÿ�ζ�ȡһ���ַ���ͳ���ַ����ֵĴ���
		//3.���ô�������HuffmanTree
		//4.������������õ�ÿ���ַ���Ҷ�ڵ㣩��Huffman����
		//5.����ѹ������
		FILE* fout = fopen(filename,"rb");
		//assert(fout);
		if(fout == NULL)
		{
			throw "file is not exists or a open failed";
		}
		//ÿ�δ��ļ��ж�ȡһ���ַ���ͳ�Ƹ��ַ����ֵĴ���
		unsigned char ch = fgetc(fout);	
		if(feof(fout))
		{
			cout<<"ch==EOF"<<endl;
			fclose(fout);
			throw "A NULL File";
		}
		while(!feof(fout))
		{
			_info[ch]._count ++;
			ch = fgetc(fout);
		}
		

		//�ø��ַ��Ĵ���������������
		CharInfo invalid;
		HuffmanTree<CharInfo> h(_info,256,invalid);

		//�õ�����������
		string code;
		GenerateHuffmanTreeCode(h.GetRoot(),code);
		//GenerateHuffmanTreeCode(h.GetRoot());

		//����ѹ��
		string compressfile = filename;
		size_t index1 = compressfile.rfind('.');
		compressfile = compressfile.substr(0,index1);
		compressfile += ".huffman";	//�ȸı��ļ��ĺ�׺
		FILE* fin = fopen(compressfile.c_str(),"wb");//��д��ķ�ʽ��"compressfile.huffman"
		assert(fin);
		fseek(fout,0,SEEK_SET);	//�����ļ�ָ���λ��Ϊ�ļ���ͷ
		int pos = 0;
		char value = 0;
		unsigned char c = fgetc(fout);
		//while (c != EOF)
		while(!feof(fout))
		{
			//���ַ�תΪ������λ����8λ��д��
			string& code = _info[c]._code;
			for (size_t i=0; i<code.size(); ++i)
			{
				value <<= 1;
				if (code[i] == '1')	
					value |= 1;
				else
					value |= 0;
				++pos;	//��ʾ8λ������λ
				if(pos == 8)	//��8λ�ͽ�valueд��ѹ���ļ�
				{
					fputc(value,fin);
					pos = 0;
					value = 0;
				}
			}
			c = fgetc(fout);	//��ȡ��һ���ַ�
		}
		if (pos)	//pos==0��˵���պô���8λ��pos!=0��˵�����ж����λ
		{
			value <<= (8-pos);
			fputc(value,fin);
		}
		fclose(fin);
		fclose(fout);

		WriteInConfig(filename,compressfile);	//���������ļ�

		return compressfile;	//����ѹ���ļ����ļ���
	}
	
	//��ѹ��
	string UnCompress(const char* filename)
	{
		//assert(filename);
		if(filename == NULL)
		{
			throw "an error FileName";
		}

		//��ȡ�����ļ�---��ȡ�ַ����ֵĴ���
		ReadFromConfig(filename);

		//����Huaaman��
		CharInfo invalid;
		HuffmanTree<CharInfo> h1(_info,256,invalid);
		//���ڵ��ȨֵΪ�ַ����ֵ��ܺ�
		LongType charCount = h1.GetRoot()->_weight._count;
		//ѹ���ļ�
		string name = filename;
		size_t index = name.rfind('.');
		name = name.substr(0,index);
		name += ".huffman";
		FILE* fout = fopen(name.c_str(),"rb");
		if(fout == NULL)
			throw "open file.huffman failed";
		//assert(fout);
		//��ѹ���ļ���ԭԭ�ļ�
		string uncompressfilename = filename;
		size_t index2 = uncompressfilename.find('.');
		uncompressfilename = uncompressfilename.substr(0,index2);
		uncompressfilename += ".unhuffman";
		FILE* foutuncompress = fopen(uncompressfilename.c_str(),"wb");
		//assert(foutuncompress);
		if(!foutuncompress)
			throw "open UncompressFile Failed";

		int pos = 7;
		unsigned char c = fgetc(fout);
		HuffmanTreeNode<CharInfo>* root = h1.GetRoot();
		HuffmanTreeNode<CharInfo>* cur = root;
		//while (charCount && ch != EOF)
		while (charCount && !feof(fout))
		{
			//��Ҷ�ӽڵ�˵���ҵ��ַ��������ѹ�ļ�
			if (cur->_left == NULL && cur->_right == NULL)
			{
				fputc(cur->_weight._ch,foutuncompress);
				charCount--;
				cur = root;
			} 
			//�������Ҷ�ӽ�����Ҷ�ӽڵ㣬0�����ߣ�1������
			if (c & (1<<pos))
				cur = cur->_right;
			else
				cur = cur->_left;
			pos--;
			//��pos<0ʱ��˵����ʱ�Ѿ���ѹ��һ���ֽڣ���ʼ��ѹ��һ���ֽ�
			if (pos < 0)
			{
				pos = 7;
				c = fgetc(fout);
			}
			//��charCount == 0ʱ���ַ��Ѿ�ȫ����ѹ��
			if (charCount == 0)
				break;
		}
		//return uncompressfilename.c_str();
		return uncompressfilename;
	}

public:
	//�����ļ�---�洢�ַ����ֵĴ���
	string WriteInConfig(const char* filename,std::string compressfile)
	{
		size_t index1 = compressfile.rfind('.');
		string configfilename = filename;
		size_t index2 = configfilename.rfind('.');
		configfilename = configfilename.substr(0,index1);
		configfilename += ".config";
		FILE* foutConfig = fopen(configfilename.c_str(),"wb");
		string line;
		char buff[128];
		for(size_t i=0; i<256; ++i)
		{
			if (_info[i]._count)
			{
				line += _info[i]._ch;
				line += ',';
				line += _itoa(_info[i]._count,buff,10);
				line += '\n';
				fputs(line.c_str(),foutConfig);
				//fwrite(line.c_str(),1,line.size(),foutConfig);//��Ƶ����Ƶ
				line.clear();
			}
		}
		fclose(foutConfig);
		return configfilename;	//���������ļ����ļ���
	}

	//��ȡ�ļ���һ�� 
	bool ReadLine(FILE* configfile,string& line)
	{
		char ch = fgetc(configfile);
		if (ch == EOF)
			return false;
		while (ch != EOF && ch != '\n')
		{
			line += ch;
			ch = fgetc(configfile);
		}
		return true;
	}

	//��ȡ�����ļ�����ȡ�ַ��Լ���Ӧ�ĳ��ִ���
	void ReadFromConfig(const char* filename)
	{
		string configfilename = filename;	//filename --- "file.huffman"	�����ļ�---"file.config"
		size_t index1 = configfilename.rfind('.');
		configfilename = configfilename.substr(0,index1);
		configfilename += ".config";
		FILE* foutConfig = fopen(configfilename.c_str(),"rb");
		//assert(foutConfig);
		if(!foutConfig)
			throw "open ConfigFile failed";
		string line;
		unsigned char ch = 0;
		while (ReadLine(foutConfig,line))
		{
			if (line.empty())
			{
				line += '\n';
				continue;
			}
			else
			{
				ch = line[0];
				_info[ch]._count = atoi(line.substr(2).c_str());
				line.clear();
			}
		}
	}
protected:
	void GenerateHuffmanTreeCode(HuffmanTreeNode<CharInfo>* root,string& code)//�õ�����������
	{
		if(root == NULL)
			return ;


		GenerateHuffmanTreeCode(root->_left,code+'0');
		GenerateHuffmanTreeCode(root->_right,code+'1');

		if (root->_left == NULL && root->_right == NULL)//��Ҷ�ӽ�㣬˵���������
			_info[root->_weight._ch]._code = code;

		//�ȱ������������ٱ���������
		//if (root->_left)	//��Ϊ0
		//GenerateHuffmanTreeCode(root->_left,code+'0');
		//if (root->_right)		//��Ϊ1
		//GenerateHuffmanTreeCode(root->_right,code+'1');
	}
private:
	CharInfo _info[256];	//һ���ṹ������
};


void MyTestCompress()
{
	FileCompress filecompress;
	int start = GetTickCount();
	filecompress.Compress("file.txt");
	//filecompress.Compress("music.mp3");
	//filecompress.Compress("picture.jpg");
	//filecompress.Compress("Input.BIG");
	int end = GetTickCount();
	cout<<"Compress():"<<end-start<<endl;

	start = GetTickCount();
	filecompress.UnCompress("file.huffman");
	//filecompress.UnCompress("music.huffman");
	//filecompress.UnCompress("picture.huffman");
	//filecompress.UnCompress("Input.huffman");
	end = GetTickCount();
	cout<<"UnCompress():"<<end-start<<endl;
}