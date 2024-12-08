#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
using namespace std;
class CMyString
{
public:
	//初始化
	CMyString();
	CMyString(const char* sz);
	CMyString(const CMyString& obj);

	//反初始化
	~CMyString();

	//属性
	size_t GetLen() const;
	const char* GetStr() const;

	//拼接\追加
	CMyString& Append(const char* sz);
	CMyString& Append(const CMyString& obj);
	CMyString& Append(char ch);
	CMyString& Append(int n);
	CMyString& Append(float f);
	CMyString& Append(double dbl);
	CMyString& Append(long i);
	CMyString& Append(short i);
	CMyString& Append(bool);

	//查询
	int Find(const char* sz) const; //-1 找不到
	int Find(const CMyString& obj) const;
	int ReverseFind(const char* sz) const;
	int ReverseFind(const CMyString& obj) const;

	//拷贝
	CMyString& Copy(const char* sz);
	CMyString& Copy(const CMyString& obj);

	//比较
	int Compare(const char* sz) const;
	int Compare(const CMyString& obj) const;

	//子串提取
	CMyString Left(size_t nCount) const; //从字符串左侧提出nCount个字符
	CMyString Right(size_t nCount) const;
	CMyString Mid(size_t nIdx, size_t nCount) const;//从索引nIdx提出nCount个字符


	static CMyString ValueOf(bool);
	static CMyString ValueOf(char c);
	static CMyString ValueOf(double d);
	static CMyString ValueOf(float f);
	static CMyString ValueOf(int i);
	static CMyString ValueOf(long i);
	static CMyString ValueOf(short i);
	static CMyString ValueOf(const char* data);
	static CMyString CopyValueOf(const char* data, int nOffset, int nCount); //char[] = "123" ==> string "123"
	static CMyString StringFromFormat(const char* format, ...);  //("%d", 123) ==> string "123"

	CMyString& operator=(const CMyString& obj);
	CMyString& operator=(const char* sz);
	friend ostream& operator<<(ostream& os, const CMyString& obj);
	friend CMyString operator+(const CMyString& obj1, const CMyString& obj2);
	friend CMyString operator+(const CMyString& obj1, int val);
	char& operator[](size_t nIndex);
	bool operator==(const char* sz);
	bool operator==(const CMyString& obj);
	bool operator!=(const char* sz);
	bool operator!=(const CMyString& obj);
	bool operator>(const char* sz);
	bool operator>(const CMyString& obj);
	bool operator<(const char* sz);
	bool operator<(const CMyString& obj);
	bool operator>=(const char* sz);
	bool operator>=(const CMyString& obj);

private:
	void Init();
	void SetStr(const char* sz);
	void DecreaseCount();


private:
	char* m_pBuff = nullptr;        //存储字符串的缓冲区
	size_t* m_pnCount = nullptr;    //引用计数
	size_t m_nLen = 0;        //字符串的长度
	size_t m_nBuffSize = 0;   //缓冲区的大小
};





