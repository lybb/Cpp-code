#include <gtest/gtest.h>

#include "Heap.h"
//#include "HuffmanTree.h"
#include "FileCompress.h"

//----------------------堆----------------------------

//测试：Size()
TEST(TestHeapSize,Return_0_when_Array_NULL)
{
	Heap<int> hp;
	EXPECT_EQ(0,hp.Size());
}
TEST(TestHeapSize,Return_Size_when_Array_NotNULL)
{
	int a[] = {10,16,18,12,11,13,15,17,14,19};
	int len = sizeof(a)/sizeof(a[0]);
	Heap<int> hp(a,len);
	EXPECT_EQ(10,hp.Size());
}

//class GlobalTest:public testing::Environment
//{
//public:
//	virtual void SetUp()
//	{
//		cout<<"gtest introduction example. SetUp"<<endl;
//	}
//	virtual void TearDown()
//	{
//		cout<<"gtest introduction example. TearDown"<<endl;
//	}
//	Heap<int> hp;
//};

class TestHeap:public testing::Test
{
public:
	//static void SetUpTestCase()
	//{
	//	cout<<"SetUpTestCase"<<endl;
	//}
	//static void TearDownTestCase()
	//{
	//	cout<<"TearDownTestCase"<<endl;
	//}
	void SetUp()
	{
		int a[] = {10,16,18,12,11,13,15,17,14,19};
		int len = sizeof(a)/sizeof(a[0]);
		for (int i=0; i<len; i++)
		{
			hp.Push(a[i]);
		}
	}
	void TearDown()
	{
		hp.Clear();
	}
	Heap<int> hp;
};

//测试：Top()
TEST_F(TestHeap,Return_Top)
{
	EXPECT_EQ(19,hp.Top());
}
//测试：Push()
TEST_F(TestHeap,Return_Push)
{
	hp.Push(10);
	EXPECT_EQ(19,hp.Top());
	hp.Push(20);
	EXPECT_EQ(20,hp.Top());
}
//测试：Pop()
TEST_F(TestHeap,Return_Pop)
{
	hp.Pop();
	EXPECT_EQ(18,hp.Top());
	EXPECT_EQ(9,hp.Size());
}
//测试：Clear()
TEST_F(TestHeap,Return_Clear)
{
	hp.Clear();
	EXPECT_EQ(0,hp.Size());
}

//----------------------文件压缩-----------------------------

 class TestFile:public testing::Test
 {
 public:
 	FileCompress fp;
 };

//配置文件：WriteInConfig
TEST_F(TestFile,ConfigTest_Ruturn_True_configFileName)
{
	EXPECT_STREQ("file.config",fp.WriteInConfig("file.txt","file.huffman").c_str());
}
TEST_F(TestFile,ConfigTest_Ruturn_False_configFileName1)
{
	EXPECT_STREQ("file.config",fp.WriteInConfig("file.test","file.huffman").c_str());
}
TEST_F(TestFile,ConfigTest_Ruturn_False_configFileName2)
{
	EXPECT_STRNE("file.config",fp.WriteInConfig("file.txt","Myfile.huffman").c_str());
}

//按行读取文件：ReadLine
TEST_F(TestFile,ReadLineTest_Ruturn_True_configFile1)	//ch!=EOF
{
	FILE* configfile = fopen("foutConfig.config","rb");
	string line;
	ASSERT_TRUE(fp.ReadLine(configfile,line));
}
TEST_F(TestFile,ReadLineTest_Ruturn_False_configFileNULL)	//ch==EOF
{
	FILE* configfile = fopen("foutConfig_null.config","rb");
	string line;
	ASSERT_FALSE(fp.ReadLine(configfile,line));
}

//读取配置文件：ReadFromConfig
 TEST_F(TestFile,ReadFromConfig_ErrThrow)
 {
 	EXPECT_THROW(fp.ReadFromConfig("fout.config"),char*);
 }

//压缩
 TEST_F(TestFile,Compress_Return_Right_Out)	 //正确输入有正确输出
 {
 	//string ret = fp.Compress("file.txt");
 	//const char* s_ret = ret.c_str();
 	//EXPECT_STREQ("file.huffman",s_ret);
 	EXPECT_STREQ("file.huffman",fp.Compress("file.txt").c_str());
 } 
 TEST_F(TestFile,Compress_ErrThrow_File_NotExist)	 //文件不存在 --- fout==NULL
 {
	 EXPECT_THROW(fp.Compress("test.txt"),char*);
 }
 TEST_F(TestFile,Compress_ErrThrow_File_NULL)	 //文件存在但为空 --- ch==EOF
 {
	 EXPECT_THROW(fp.Compress("file_null.txt"),char*);
 }
 
//解压
 TEST_F(TestFile,UnCompress_Return_Right_Out)	 //正确输入是否对应正确输出
 {
 	EXPECT_STREQ("file.unhuffman",fp.UnCompress("file.huffman").c_str());
 }
 TEST_F(TestFile,UnCompress_ErrThrow_File)	//判断异常流程----文件不存在
 {
	 EXPECT_THROW(fp.Compress(""),char*);
 }
 TEST_F(TestFile,UnCompress_ErrThrow_File_NotExist)	//判断异常流程----文件不存在
 {
 	EXPECT_THROW(fp.Compress("test.txt"),char*);
 }
 TEST_F(TestFile,UnCompress_ErrThrow_File_OpenFailed)	//判断异常流程----文件不存在
 {
	 fopen("file.huffman","rb");
	 EXPECT_THROW(fp.Compress("file.txt"),char*);
 }


//----------------------HuffmanTree-----------------------------

 TEST(TestHuffman,Right_Arr_Right_TreeRoot)
 {
	 int a[] = {1,2,3,4,5};
	 size_t size = sizeof(a)/sizeof(a[0]);
	 HuffmanTree<int> ht(a,size,0);
	 ASSERT_EQ(15,ht.GetRoot()->_weight);
 }
 TEST(TestHuffman,NULL_Arr_Error_TreeRoot)
 {
	 int a[] = {0};
	 size_t size = sizeof(a)/sizeof(a[0]);
	 HuffmanTree<int> ht(a,size,0);
	 //ASSERT_EQ(0,ht.GetRoot()->_weight);
 }

int main(int argc,char* argv[])
{
	testing::InitGoogleTest(&argc,argv);
	//testing::Environment* env = new GlobalTest();
	//testing::AddGlobalTestEnvironment(env);
	return RUN_ALL_TESTS();
}