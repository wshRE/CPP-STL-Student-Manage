#include "CString.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

CMyString::CMyString()
{
	Init();
}

CMyString::CMyString(const char* sz)
{
	//��ָ����
	if (sz == nullptr)
	{
		Init();
		return;
	}

	//�����ַ���
	SetStr(sz);
}

CMyString::CMyString(const CMyString& obj)
{
	//��ָ����
	if (obj.m_pBuff == nullptr)
	{
		Init();
		return;
	}
	else
	{
		//ǳ����
		m_nLen = obj.m_nLen;
		m_nBuffSize = obj.m_nBuffSize;
		m_pBuff = obj.m_pBuff;
		m_pnCount = obj.m_pnCount;
		++(*obj.m_pnCount);
	}
}

CMyString::~CMyString()
{
	DecreaseCount();
	m_pBuff = nullptr;
	m_pnCount = nullptr;
	m_nLen = 0;
	m_nBuffSize = 0;
}

size_t CMyString::GetLen() const
{
	return m_nLen;
}

const char* CMyString::GetStr() const
{
	return m_pBuff;
}

CMyString& CMyString::Append(const char* sz)
{
	//��ָ����
	if (sz == nullptr)
	{
		return *this;
	}

	//�������ڴ�洢������
	size_t nDstLen = strlen(sz);
	size_t nLen = nDstLen + m_nLen;
	size_t nBuffSize = nLen + 1;
	size_t* pnCount = new size_t(1);
	if (pnCount == nullptr)
	{
		return *this;
	}
	char* pBuff = new char[nDstLen + m_nLen + 1];
	if (pBuff == nullptr)
	{
		return *this;
	}
	memset(pBuff, 0, nBuffSize);
	if (m_pBuff != nullptr)
		strcpy(pBuff, m_pBuff);
	strcat(pBuff, sz);

	//������-1
	DecreaseCount();

	//���¶�������
	m_nLen = nLen;  //�����ַ�������
	m_nBuffSize = nBuffSize; //���»�������С
	m_pBuff = pBuff;         //������ָ��ָ���µĻ�����
	m_pnCount = pnCount;

	return *this;
}

CMyString& CMyString::Append(const CMyString& obj)
{
	return Append(obj.m_pBuff);
}

CMyString& CMyString::Append(char ch)
{
	char sz[2] = { ch,0 };
	return Append(sz);
}

CMyString& CMyString::Append(int n)
{
	char szTmp[11] = { 0 };
	sprintf(szTmp, "%d", n);
	return Append(szTmp);
}

CMyString& CMyString::Append(float f)
{
	char szTmp[128] = { 0 };
	sprintf(szTmp, "%.6f", f);
	return Append(szTmp);
}

CMyString& CMyString::Append(double dbl)
{
	char szTmp[0x1000] = { 0 };
	sprintf(szTmp, "%.6lf", dbl);
	return Append(szTmp);
}

CMyString& CMyString::Append(long i)
{
	char szTmp[20] = { 0 };
	sprintf(szTmp, "%d", i);
	return Append(szTmp);
}

CMyString& CMyString::Append(short i)
{
	char szTmp[6] = { 0 };
	sprintf(szTmp, "%d", i);
	return Append(szTmp);
}

CMyString& CMyString::Append(bool b)
{
	char szTmp[6] = { 0 };
	if (b == true)
	{
		sprintf(szTmp, "true");
	}
	else
	{
		sprintf(szTmp, "false");
	}
	return Append(szTmp);
}

int CMyString::Find(const char* sz) const
{
	if (sz == nullptr || m_pBuff == nullptr)
	{
		return -1;
	}

	if (strstr(m_pBuff, sz) != nullptr)
	{
		return (strstr(m_pBuff, sz) - m_pBuff);
	}
	else
	{
		return -1;
	}
}

int CMyString::Find(const CMyString& obj) const
{
	return Find(obj.m_pBuff);
}

int CMyString::ReverseFind(const char* sz) const
{
	if (sz == nullptr || m_pBuff == nullptr)
	{
		return -1;
	}

	for (int i = m_nLen - 1; i >= 0; i--)
	{
		if (memcmp(m_pBuff + i, sz, strlen(sz)) == 0)
		{
			return i;
		}
	}
	return -1;
}

int CMyString::ReverseFind(const CMyString& obj) const
{
	return ReverseFind(obj.m_pBuff);
}

CMyString& CMyString::Copy(const char* sz)
{
	//��ָ����
	if (sz == nullptr)
	{
		return *this;
	}

	//�������ڴ�洢������
	size_t nDstLen = strlen(sz);
	size_t nLen = nDstLen;
	size_t nBuffSize = nLen + 1;
	size_t* pnCount = new size_t(1);
	if (pnCount == nullptr)
	{
		return *this;
	}
	char* pBuff = new char[nDstLen + 1];
	if (pBuff == nullptr)
	{
		return *this;
	}
	memset(pBuff, 0, nBuffSize);
	strcpy(pBuff, sz);

	//������-1
	DecreaseCount();

	//���¶�������
	m_nLen = nLen;  //�����ַ�������
	m_nBuffSize = nBuffSize; //���»�������С
	m_pBuff = pBuff;         //������ָ��ָ���µĻ�����
	m_pnCount = pnCount;

	return *this;
}

CMyString& CMyString::Copy(const CMyString& obj)
{
	return Copy(obj.m_pBuff);
}

int CMyString::Compare(const char* sz) const
{
	if (sz == nullptr)
	{
		return 1;
	}

	if (m_pBuff == nullptr)
	{
		return -1;
	}

	return strcmp(m_pBuff, sz);
}

int CMyString::Compare(const CMyString& obj) const
{
	return Compare(obj.m_pBuff);
}

CMyString CMyString::Left(size_t nCount) const
{
	return Mid(0, nCount);
}

CMyString CMyString::Right(size_t nCount) const
{
	return Mid(m_nLen - nCount, nCount);
}

CMyString CMyString::Mid(size_t nIdx, size_t nCount) const
{
	//�߽���
	if (nCount + nIdx > m_nLen)
	{
		return CMyString();
	}

	//��ȡ
	char* pBuff = new char[nCount + 1];
	if (pBuff == nullptr)
	{
		return CMyString();
	}
	memset(pBuff, '\0', nCount + 1);
	memcpy(pBuff, m_pBuff + nIdx, nCount);

	CMyString strRet(pBuff);
	delete[] pBuff;
	pBuff = nullptr;

	return strRet;
}

CMyString CMyString::ValueOf(bool b)
{
	return StringFromFormat("%s", b ? "true" : "false");
}

CMyString CMyString::ValueOf(char c)
{
	return StringFromFormat("%ch", c);
}

CMyString CMyString::ValueOf(double d)
{
	return StringFromFormat("%lf", d);
}

CMyString CMyString::ValueOf(float f)
{
	return StringFromFormat("%f", f);
}

CMyString CMyString::ValueOf(int i)
{
	return StringFromFormat("%d", i);
}

CMyString CMyString::ValueOf(long i)
{
	return StringFromFormat("%ld", i);
}

CMyString CMyString::ValueOf(short i)
{
	return StringFromFormat("%hd", i);
}

CMyString CMyString::ValueOf(const char* data)
{
	return StringFromFormat("%s", data);
}

CMyString CMyString::CopyValueOf(const char* data, int nOffset, int nCount)
{
	return StringFromFormat("%s", CMyString(data).Mid(nOffset, nCount).GetStr());
}

CMyString CMyString::StringFromFormat(const char* format, ...)
{
	va_list v1;                             //����һ��va_list����
	va_start(v1, format);                   //ʹv1ָ���һ���ɱ�����ڶ�ջ�ĵ�ַ

	int nSize = _vscprintf(format, v1) + 1; //_vscprintf���ظ�ʽ���ַ����е��ַ���(������\0)
	char* pBuff = new char[nSize];
	memset(pBuff, '\0', nSize);
	vsprintf(pBuff, format, v1);           //ʹ�ò����б��͸�ʽ�������������

	va_end(v1);                            //���v1

	CMyString strRet(pBuff);               //���췵��ֵ
	delete[] pBuff;                        //ɾ��������ڴ�

	return strRet;                         //ֱ�ӷ���CMyString(pBuff)û�л����ͷ�pBuff�ڴ�
}

CMyString& CMyString::operator=(const CMyString& obj)
{
	m_nLen = obj.m_nLen;
	m_nBuffSize = obj.m_nBuffSize;
	m_pBuff = obj.m_pBuff;
	m_pnCount = obj.m_pnCount;
	++(*obj.m_pnCount);
	return *this;
}

CMyString& CMyString::operator=(const char* sz)
{
	return Copy(sz);
}

char& CMyString::operator[](size_t nIndex)
{
	assert(nIndex < m_nLen);
	return m_pBuff[nIndex];
}

bool CMyString::operator==(const char* sz)
{
	if (Compare(sz))
	{
		return false;
	}
	return true;
}

bool CMyString::operator==(const CMyString& obj)
{
	return *this == obj.m_pBuff;
}

bool CMyString::operator!=(const char* sz)
{
	return !(*this == sz);
}

bool CMyString::operator!=(const CMyString& obj)
{
	return !(*this == obj);
}

bool CMyString::operator>(const char* sz)
{
	if (Compare(sz) > 0)
	{
		return true;
	}
	return false;
}

bool CMyString::operator>(const CMyString& obj)
{
	return *this > obj.m_pBuff;
}

bool CMyString::operator<(const char* sz)
{
	if (Compare(sz) < 0)
	{
		return true;
	}
	return false;
}

bool CMyString::operator<(const CMyString& obj)
{
	return *this < obj.m_pBuff;
}

bool CMyString::operator>=(const char* sz)
{
	if (Compare(sz) == 0)
	{
		return true;
	}
	return false;
}

bool CMyString::operator>=(const CMyString& obj)
{
	return *this < obj.m_pBuff;
}

void CMyString::Init()
{
	m_pBuff = nullptr;
	m_pnCount = nullptr;
	m_nLen = 0;
	m_nBuffSize = 0;
}

void CMyString::SetStr(const char* sz)
{
	//�����ڴ棬�洢�ַ���
	m_nLen = strlen(sz);
	m_nBuffSize = m_nLen + 1;
	m_pBuff = new char[m_nBuffSize];
	m_pnCount = new size_t(1);
	if (m_pBuff == nullptr)
	{
		Init();
		return;
	}
	strcpy(m_pBuff, sz);
}

void CMyString::DecreaseCount()
{
	if (m_pnCount != nullptr)
	{
		//��������
		--(*m_pnCount);

		//����Ϊ0�ͷ��ڴ�
		if (*m_pnCount == 0)
		{
			delete[] m_pBuff;
			delete m_pnCount;
			m_pBuff = nullptr;
			m_pnCount = nullptr;
			m_nLen = 0;
			m_nBuffSize = 0;
		}
	}
}

ostream& operator<<(ostream& os, const CMyString& obj)
{
	os << obj.m_pBuff;
	return os;
}

CMyString operator+(const CMyString& obj1, const CMyString& obj2)
{
	return CMyString(obj1).Append(obj2);
}

CMyString operator+(const CMyString& obj1, int val)
{

	return  CMyString(obj1).Append(to_string(val).c_str());
}
