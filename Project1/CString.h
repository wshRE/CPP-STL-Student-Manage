#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
using namespace std;
class CMyString
{
public:
	//��ʼ��
	CMyString();
	CMyString(const char* sz);
	CMyString(const CMyString& obj);

	//����ʼ��
	~CMyString();

	//����
	size_t GetLen() const;
	const char* GetStr() const;

	//ƴ��\׷��
	CMyString& Append(const char* sz);
	CMyString& Append(const CMyString& obj);
	CMyString& Append(char ch);
	CMyString& Append(int n);
	CMyString& Append(float f);
	CMyString& Append(double dbl);
	CMyString& Append(long i);
	CMyString& Append(short i);
	CMyString& Append(bool);

	//��ѯ
	int Find(const char* sz) const; //-1 �Ҳ���
	int Find(const CMyString& obj) const;
	int ReverseFind(const char* sz) const;
	int ReverseFind(const CMyString& obj) const;

	//����
	CMyString& Copy(const char* sz);
	CMyString& Copy(const CMyString& obj);

	//�Ƚ�
	int Compare(const char* sz) const;
	int Compare(const CMyString& obj) const;

	//�Ӵ���ȡ
	CMyString Left(size_t nCount) const; //���ַ���������nCount���ַ�
	CMyString Right(size_t nCount) const;
	CMyString Mid(size_t nIdx, size_t nCount) const;//������nIdx���nCount���ַ�


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
	char* m_pBuff = nullptr;        //�洢�ַ����Ļ�����
	size_t* m_pnCount = nullptr;    //���ü���
	size_t m_nLen = 0;        //�ַ����ĳ���
	size_t m_nBuffSize = 0;   //�������Ĵ�С
};





