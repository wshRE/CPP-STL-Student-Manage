#pragma once
#include <cassert>

template<typename T>
class Iterator;

template<typename T>
class Reverse_Iterator;

template<typename T>
class CList
{
private:
    //�ڵ�
    struct tagNode
    {
        tagNode() :m_nVal() {};
        tagNode(const T& nVal) :m_nVal(nVal) {}
        T m_nVal;
        tagNode* m_pLast = nullptr;//ǰ�����
        tagNode* m_pNext = nullptr;//��̽��
    };

public:
    //�ڵ����
    using Node = tagNode*;
    //������
    using Iterator = Iterator<T>;
    using Reverse_Iterator = Reverse_Iterator<T>;

private:
    //��ʼ��----����ͷβ�ڵ㲢����
    void Init()
    {
        m_HeadNode = new tagNode;
        m_TailNode = new tagNode;
        m_HeadNode->m_pNext = m_TailNode;
        m_TailNode->m_pLast = m_HeadNode;
    }
public:
    //���������
        //���ص�һ��Ԫ��
    Iterator begin() {
        return Iterator(m_HeadNode->m_pNext, m_TailNode);
    }
    //�������һ��Ԫ��
    Iterator end() {
        return Iterator(m_TailNode, m_TailNode);
    }

    //���������
          //�������һ��Ԫ��
    Reverse_Iterator rbegin() {
        return Reverse_Iterator(m_HeadNode, m_TailNode->m_pLast);
    }
    //���ص�һ��Ԫ��
    Reverse_Iterator rend() {
        return Reverse_Iterator(m_HeadNode, m_HeadNode);
    }

    
    CList(std::initializer_list<T> ilist) {
        Init();
        for (auto i = ilist.begin(); i != ilist.end(); i++) {
            InsertTail(*i);
        }
    }

    //�޲ι���
    CList()
    {
        Init();
    };
    //����
    ~CList()
    {
        clear();
        if (m_HeadNode != nullptr)
        {
            delete m_HeadNode;
            delete m_TailNode;
        }

        m_nCount = 0;
    };
    //��������
    CList(const CList& cl)
    {
        Init();
        *this = cl;
    };
    //�ƶ�����
    CList(CList&& cl)
    {
        m_HeadNode = cl.m_HeadNode;
        m_TailNode = cl.m_TailNode;
        m_nCount = cl.GetCount();
        cl.m_HeadNode = nullptr;
        cl.m_TailNode = nullptr;
        cl.m_nCount = 0;
    };
    //����=
    CList& operator=(const CList& cl)
    {
        if (this == &cl)
        {
            return *this;
        }
        clear();
        Node nodeStart = cl.m_HeadNode->m_pNext;
        while (nodeStart != nullptr && nodeStart != cl.m_TailNode)
        {
            InsertTail(nodeStart->m_nVal);
            nodeStart = nodeStart->m_pNext;
        }
        return *this;
    };
    //����ڵ�
    CList& Insert(Node node, const T& data)
    {
        //����һ���½��
        if (node == nullptr)
        {
            return *this;
        }
        Node pNewNode = new tagNode(data);
        Node pNowNode = node->m_pLast;//�õ���һ�����
        pNowNode->m_pNext = pNewNode;
        node->m_pLast = pNewNode;
        pNewNode->m_pLast = pNowNode;
        pNewNode->m_pNext = node;
        ++m_nCount;
        return *this;
    };

    //ͷ��
    CList& InsertHead(const T& data)
    {
        return Insert(m_HeadNode->m_pNext, data);
    };

    //β��
    CList& InsertTail(const T& data)
    {
        return Insert(m_TailNode, data);
    };

    //ɾ���ڵ�
    CList& Delete(Node node)
    {
        if (node == nullptr)
        {
            return *this;
        }
        Node pLastNood = node->m_pLast;
        pLastNood->m_pNext = node->m_pNext;
        Node pNextNood = node->m_pNext;
        pNextNood->m_pLast = pLastNood;
        delete node;
        --m_nCount;
        return *this;
    };

    //ȥͷ
    CList& DeleteHead()
    {
        if (m_nCount == 0)
        {
            return *this;
        }
        return Delete(m_HeadNode->m_pNext);
    };

    //ȥβ
    CList& DeleteTail()
    {
        if (m_nCount == 0)
        {
            return *this;
        }
        return Delete(m_TailNode->m_pLast);
    };

    //����[]
    T& operator[](Node node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        return node->m_nVal;
    };

    //�������ݲ��ҽڵ�
    Node Find(const T& data)
    {
        Node nodeStart = m_HeadNode->m_pNext;
        while (nodeStart != nullptr)
        {
            if (nodeStart->m_nVal == data)
            {
                return nodeStart;
            }
            nodeStart = nodeStart->m_pNext;
        }
        return nullptr;
    };

    //���
    void clear()
    {
        while (!IsEmpty())
        {
            DeleteHead();
        }
    };

    //��ȡ��ǰ����
    size_t GetCount()const
    {
        return m_nCount;

    };

    //�п�
    bool IsEmpty()const
    {
        return GetCount() == 0;
    };

public:
    Node m_HeadNode = nullptr;//ͷ���
    Node m_TailNode = nullptr;//β���
    size_t m_nCount = 0;//Ԫ�ظ���
};


//������ʵ��
template<typename T>
class Iterator
{
public:
    //�޲ι���
    Iterator() = default;

    //�ڵ��βָ��
    Iterator(typename CList<T>::Node pNode, typename CList<T>::Node pTailGuard)
    {
        m_pNode = pNode;
        m_pTailGuard = pTailGuard;
    }

    //��дǰ++ ---> ����һ��
    Iterator& operator++()
    {
        assert(m_pNode != nullptr); //����Ϊ��
        assert(m_pNode != m_pTailGuard);//���������ƶ�

        //�ƶ�
        m_pNode = m_pNode->m_pNext;

        return *this;
    }
    //��д��++
    Iterator operator++(int) {
        return ++ * this;
        //Iterator tTemp = *this;
        //++* this;
        //return tTemp;
    }



    //��д* -----> ȡֵ
    T& operator*() const
    {
        return m_pNode->m_nVal;
    }
    T* operator->() const {
        return &(operator*());
    }

    bool operator!=(const Iterator& itr)
    {
        return m_pNode != itr.m_pNode;
    }
    bool operator==(const Iterator& itr) const {
        return m_pNode == itr.m_pNode;
    }
private:
    typename CList<T>::Node m_pNode = nullptr;
    typename CList<T>::Node m_pTailGuard = nullptr;
};



//���������
template<typename T>
class Reverse_Iterator
{
public:
    //�޲ι���
    Reverse_Iterator() = default;

    //�ڵ��βָ��
    Reverse_Iterator(typename CList<T>::Node pHeadNode, typename CList<T>::Node pNode)
    {
        m_HeadNode = pHeadNode;
        m_pNode = pNode;
    }

    //��дǰ++ ---> ����һ��
    Reverse_Iterator& operator++()
    {
        assert(m_pNode != nullptr); //����Ϊ��
        assert(m_pNode != m_HeadNode);//���������ƶ�

        //�ƶ�
        m_pNode = m_pNode->m_pLast;

        return *this;
    }
    //��д��++
    Reverse_Iterator operator++(int) {
        return ++ * this;
    }


    //��д* -----> ȡֵ
    T& operator*() const
    {
        return m_pNode->m_nVal;
    }
    T* operator->() const {
        return &(operator*());
    }

    bool operator!=(const Reverse_Iterator& itr)
    {
        return m_pNode != itr.m_pNode;
    }
    bool operator==(const Reverse_Iterator& itr) const {
        return m_pNode == itr.m_pNode;
    }
private:
    typename CList<T>::Node m_HeadNode = nullptr;
    typename CList<T>::Node m_pNode = nullptr;
};
