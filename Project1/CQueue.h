#pragma once
#include"CList.h"
#include<iostream>
template<typename T>
struct CQueue {
    CQueue();
    CQueue(T t);
    CQueue(std::initializer_list<T> ilist);
    CQueue(const CQueue& cq);   //��������
    CQueue(CQueue&& cq);  //�ƶ�����
    ~CQueue();

    //���ز�����
            // =  == 
    CQueue& operator = (const CQueue& cq);
    bool operator==(const CQueue& cq);

    //ջ���� 
        //�����
    CQueue& EnQueue(T t);
    //�����в�����
    T& DeQueue();
    //���ض�βԪ��
    T& GetHead();
    //���ж�---�շ���true 
    bool QueueEmtpy();

private:
    void Init();           //��ʼ��
    void Clear();         //ɾ��
    CList<T>* m_pList = nullptr;//����
};

template<typename T>
inline CQueue<T>::CQueue()
{
    Init();
}

//-------------------�����--------------------------------
template<typename T>
inline CQueue<T>::CQueue(T t)
{
    Init();
    m_pList->InsertHead(t);
}

template<typename T>
inline CQueue<T>::CQueue(std::initializer_list<T> ilist)
{
    m_pList = new CList<T>(ilist);
}

template<typename T>
inline CQueue<T>::CQueue(const CQueue& cq)
{
    Init();
    *m_pList = *(cq.m_pList);
}

template<typename T>
inline CQueue<T>::CQueue(CQueue&& cq) :
    m_pList(cq.m_pList)
{//  //    m_pList(std::move(cs.m_pList))
    cq.m_pList = nullptr;
}

template<typename T>
inline CQueue<T>::~CQueue()
{
    Clear();
}

template<typename T>
inline CQueue<T>& CQueue<T>::operator=(const CQueue<T>& cq)
{
    // TODO: �ڴ˴����� return ���
    Clear();
    Init();
    *m_pList = *(cq.m_pList); //�۲��ڴ�
    return *this;
}

template<typename T>
inline bool CQueue<T>::operator==(const CQueue<T>& cq)
{
    return m_pList == cq.m_pList;
}

template<typename T>
inline CQueue<T>& CQueue<T>::EnQueue(T t)
{
    // TODO: �ڴ˴����� return ���
    m_pList->InsertHead(t);  //ͷ��
    return *this;
}

template<typename T>
inline T& CQueue<T>::DeQueue()
{
    // TODO: �ڴ˴����� return ���
    T tTemp = *(m_pList->end());  //βȡ
    m_pList->DeleteTail();
    return tTemp;
}

template<typename T>
inline T& CQueue<T>::GetHead()
{
    // TODO: �ڴ˴����� return ���
    return *(m_pList->end());  //βȡ
}

template<typename T>
inline bool CQueue<T>::QueueEmtpy()
{
    return m_pList->GetCount() == 0;
}

//--------------��ʼ�������
template<typename T>
inline void CQueue<T>::Init()
{
    m_pList = new CList<T>();
}

template<typename T>
inline void CQueue<T>::Clear()
{
    delete m_pList;
}
