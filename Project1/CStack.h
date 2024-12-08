#pragma once
#include<iostream>
#include<cassert>
#include"CList.h"
//�ط�װListʵ����ջ
template<typename T>
struct CStack {
    //���� ���� �ƶ�
    CStack();
    CStack(T t);  //��ջ
    CStack(std::initializer_list<T> ilist); //������ջ
    CStack(const CStack& cs);    //��������
    CStack(CStack&& cs);    //�ƶ�����
    ~CStack();              //����
//���ز�����
    // =  == 
    CStack& operator = (const CStack& cs);
    bool operator==(const CStack& cs);
    //ջ���� 
       //Push��ջ
    CStack& Push(T t);

    //Pop��ջ
    T& Pop();

    //GetTop  ��ȡջ��
    T& GetTop();

    //StackEmtpy  ջ���ж�
    bool StackEmtpy();

private:
    void Init();           //��ʼ��
    void Clear();         //ɾ��
    CList<T>* m_pList = nullptr;//����
};



template<typename T>
inline CStack<T>::CStack()
{
    Init();
}

//--------------------------------����ʵ��---------------------------------
template<typename T>
inline CStack<T>::CStack(T t)
{
    Init();
    m_pList->InsertHead(t);
}


template<typename T>
inline CStack<T>::CStack(std::initializer_list<T> ilist)
{
    Init();
    for (auto i : ilist) {
        m_pList->InsertHead(i);
    }
}


template<typename T>
inline CStack<T>::CStack(const CStack& cs)
{
    Init();
    *m_pList = *(cs.m_pList);
}
template<typename T>
inline CStack<T>::CStack(CStack&& cs) :
    m_pList(cs.m_pList)
{
    //    m_pList(std::move(cs.m_pList))
    cs.m_pList = nullptr;
}

template<typename T>
inline CStack<T>::~CStack()
{
    Clear();
}


template<typename T>
CStack<T>& CStack<T>::operator=(const CStack& cs)
{
    Clear();
    Init();
    *m_pList = *(cs.m_pList); //�۲��ڴ�
    return *this;
    // TODO: �ڴ˴����� return ���
}

template<typename T>
inline bool CStack<T>::operator==(const CStack& cs)
{
    return m_pList == cs.m_pList;
}

template<typename T>
inline CStack<T>& CStack<T>::Push(T t)
{
    // TODO: �ڴ˴����� return ���
    m_pList->InsertHead(t);
    return *this;
}

template<typename T>
inline T& CStack<T>::Pop()
{
    // TODO: �ڴ˴����� return ���
    T tTemp = *(m_pList->begin());
    m_pList->DeleteHead();
    return tTemp;
}

template<typename T>
inline T& CStack<T>::GetTop()
{
    // TODO: �ڴ˴����� return ���
    return *(m_pList->begin());
}

template<typename T>
inline bool CStack<T>::StackEmtpy()
{
    return m_pList->GetCount() == 0;
}

template<typename T>
inline void CStack<T>::Init()
{
    m_pList = new  CList<T>();
}

template<typename T>
inline void CStack<T>::Clear()
{
    delete m_pList;
}

