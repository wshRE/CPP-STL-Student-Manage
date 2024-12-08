#pragma once
#include<iostream>
#include"CString.h"
#include"CList.h"
#include"CQueue.h"
#include"CStack.h"
const size_t WHITE = 0;//�½ڵ�
const size_t GRAY = 1; //�ѷ���
template<typename T, typename T1, typename T2>  //T:KEY  T1:VALUE  T2:LINK
class TreeKVAndLink {
public:
    //�ڵ�
    template<typename T, typename T1, typename T2>
    struct TreeNode {
        TreeNode() :m_tValue(), m_tValue1() {
            m_tLeft = nullptr;
            m_tRight = nullptr;
            m_tFather = nullptr;
            m_nHeight = 0;  //���Ҹ߶Ȳ�
            m_list = new CList<T2>();
            m_nStore = -1;    //�ļ�ƫ����----ѧ��id��/�γ�id��
        }
        TreeNode(T t, T1 t1) :m_tValue(t), m_tValue1(t1) {
            m_tLeft = nullptr;
            m_tRight = nullptr;
            m_tFather = nullptr;
            m_nHeight = 0;
            m_list = new CList<T2>();
            m_nStore = -1;
        }
        TreeNode(T t, T1 t1,int m_nStore) :m_tValue(t), m_tValue1(t1), m_nStore(m_nStore) {
            m_tLeft = nullptr;
            m_tRight = nullptr;
            m_tFather = nullptr;
            m_nHeight = 0;
            m_list = new CList<T2>();
        }
        T m_tValue;   //key  
        T1 m_tValue1;  //value
        int m_nHeight;   //���߶�
        int m_nStore;   //�ļ�ƫ�� --------------------ѧ��id��ר�ã���δ��ʼ����
        TreeNode<T, T1, T2>* m_tLeft;
        TreeNode<T, T1, T2>* m_tRight;
        TreeNode<T, T1, T2>* m_tFather; //���ڵ�
        CList<T2>* m_list;//��������
    };
    //�ǵݹ����ջ
    template<typename T, typename T1, typename T2>
    struct TreeStack {
        TreeStack() :nColor() {
            tNode = nullptr;
        }
        TreeStack(size_t ncolor, TreeNode<T, T1, T2>* tnode) {
            nColor = ncolor;
            tNode = tnode;
        }
        size_t nColor;    //��ɫ  0Ϊ��ɫ  1Ϊ��ɫ
        TreeNode<T, T1, T2>* tNode;  //�ڵ�
    };


    //�����׼�
/*���*/  TreeKVAndLink();
/*���*/  TreeKVAndLink(const TreeKVAndLink<T, T1, T2>& t);
/*���*/  TreeKVAndLink(TreeKVAndLink<T, T1, T2>&& t);
/*���*/  ~TreeKVAndLink();

    //��ʼ�������
/*���*/  void Init();
/*���*/  void ClearTree(TreeNode<T, T1, T2>* tree);
/*���*/  void ClearLink(TreeNode<T, T1, T2>* tree);

    //������
//�� 
        //����ڵ�---����ƫ��
    TreeKVAndLink<T, T1, T2>& InsertNode(T tValue, T1 tvalue1);
    TreeKVAndLink<T, T1, T2>& InsertNode(T tValue, T1 tvalue1,int nOffset);  //��ƫ��
        //��������----����id �� �ڵ�
    TreeKVAndLink<T, T1, T2>& InsertLink(T tValue, T2 tvalue1);
//��
        //����----ͨ����������----���������ڵ�
    TreeNode<T, T1, T2>* Find(T tValue);
        //�����̲���
    TreeNode<T, T1,T2>* FindInNode(TreeNode<T, T1,T2>* tnode);
//ɾ
        //ɾ��----����KEYɾ�����ڵ�---11ɾ����ClearLink 2.ɾ�ڵ�
    TreeKVAndLink<T, T1, T2>& DeleteValue(T tValue);
        //ɾ��----ɾ������ڵ�------T2:��ѧ��id���������ڵ�
    TreeKVAndLink<T, T1, T2>& DeleteLink(T tValue,T2 tValue1);

//��ͨ�������

//ƽ��

        //��ȡ���ڵ��ָ��
    TreeNode<T, T1, T2>* GetRoot() {
        return m_tRoot;
    }
    //��ȡ�ڵ�߶�
    int GetHeight(TreeNode<T, T1, T2>* pNode);
    //����߶�
    void CalcHeight(TreeNode<T, T1, T2>* pNode);
    //�����߶�
    void AdjustHeight(TreeNode<T, T1, T2>* pNode);
    //����
    void LeftRotate(TreeNode<T, T1, T2>* pnode);
    //����
    void RightRotate(TreeNode<T, T1, T2>* pnode);


    size_t GetCount() {
        return m_nCount;
    }


private:
    TreeNode<T, T1, T2>* m_tRoot;  //���ڵ�
    size_t m_nCount = 0;    //�ڵ�����
};



//----------------------�����׼�--------------------
    //����
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>::TreeKVAndLink()
{
    Init();
}

//��������
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>::TreeKVAndLink(const TreeKVAndLink<T, T1, T2>& t)
{
    Init();
    *m_tRoot = *(t);
}
//�ƶ�����
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>::TreeKVAndLink(TreeKVAndLink<T, T1, T2>&& t)
{
    m_tRoot = t.m_tRoot;
    t.m_tRoot = nullptr;
}
//����
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>::~TreeKVAndLink()
{
    //�������
    ClearLink(m_tRoot);
    //�����
    ClearTree(m_tRoot);
    //����
    m_tRoot->m_tLeft = nullptr;
    m_tRoot->m_tRight = nullptr;
    m_tRoot->m_tFather = nullptr;
    m_tRoot->m_nHeight = 0;  //���Ҹ߶Ȳ�
    m_tRoot->m_list = nullptr;
}


//-------------------------��ʼ�������-------------------------------------
//��ʼ��
template<typename T, typename T1, typename T2>
inline void TreeKVAndLink<T, T1, T2>::Init()
{
    m_tRoot = new TreeNode<T, T1, T2>();
}
//�����
template<typename T, typename T1, typename T2>
inline void TreeKVAndLink<T, T1, T2>::ClearTree(TreeNode<T, T1, T2>* tree)
{
    if (!tree) {
        return;
    }
    ClearTree(tree->m_tLeft);
    ClearTree(tree->m_tRight);
    //��������
    if (tree->m_tFather && tree->m_tFather->m_tLeft == tree) {
        tree->m_tFather->m_tLeft = nullptr;
    }
    else if (tree->m_tFather && tree->m_tFather->m_tRight == tree) {
        tree->m_tFather->m_tRight = nullptr;
    }
    ClearLink(tree);
    delete tree;
    return;
}

//���ĳ�ڵ������
template<typename T, typename T1, typename T2>
inline void TreeKVAndLink<T, T1, T2>::ClearLink(TreeNode<T, T1, T2>* tnode)
{
    //ѭ��ɾ���ڵ������
    tnode->m_list->clear();
}

//����ڵ�---����ƫ��
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>& TreeKVAndLink<T, T1, T2>::InsertNode(T tValue, T1 tvalue1)
{
    //// TODO: �ڴ˴����� return ���
    //    // TODO: �ڴ˴����� return ���
    //if (m_tRoot->m_tValue == NULL) {
    //    m_tRoot->m_tValue = tValue;
    //    m_tRoot->m_tValue1 = tvalue1;
    //    return *this;
    //}
    //TreeNode<T, T1, T2>* pTemp = m_tRoot;
    //TreeNode<T, T1, T2>* pTempPre = pTemp;
    //while (pTemp) {
    //    pTempPre = pTemp;
    //    if (pTemp->m_tValue < tValue) {
    //        pTemp = pTemp->m_tRight;
    //    }
    //    else if (pTemp->m_tValue == tValue) {
    //        return *this;
    //    }
    //    else {
    //        pTemp = pTemp->m_tLeft;
    //    }
    //}
    //if (pTempPre == nullptr) {
    //    return *this;
    //}
    //if (tValue < pTempPre->m_tValue) {
    //    pTempPre->m_tLeft = new TreeNode<T, T1, T2>(tValue, tvalue1);
    //    pTempPre->m_tLeft->m_tFather = pTempPre;
    //}
    //else if (tValue > pTempPre->m_tValue) {
    //    pTempPre->m_tRight = new TreeNode<T, T1, T2>(tValue, tvalue1);
    //    pTempPre->m_tRight->m_tFather = pTempPre;
    //}

               //������ڵ�Ϊ��,��Ĭ��������,�½�һ�����ڵ�
    if (m_tRoot == nullptr)
    {
        m_tRoot = new TreeNode<T, T1, T2>(tValue, tvalue1);
        m_nCount++;
        return *this;
    }

    //������ڵ�������
    TreeNode<T, T1, T2>* pCurNode = m_tRoot;
    TreeNode<T, T1, T2>* pNewNode = new TreeNode<T, T1, T2>(tValue, tvalue1);
    while (pCurNode != nullptr)
    {
        //������ݱȵ�ǰ���ڵ�С,�����ӿ�ʼ��ѯ
        if (tValue < pCurNode->m_tValue)
        {
            //������λ�õ������ǿյ�,��ô��ָ��ָ��ʼ�����ֵ,�����ܽ����+1
            if (pCurNode->m_tLeft == nullptr)
            {
                pCurNode->m_tLeft = pNewNode;
                pNewNode->m_tFather = pCurNode;
                m_nCount++;
                AdjustHeight(pCurNode);
                return *this;
            }
            pCurNode = pCurNode->m_tLeft;
        }
        //������ݱȵ�ǰ���ڵ��,���Һ��ӿ�ʼ��ѯ
        else if (tValue > pCurNode->m_tValue)
        {
            //������λ�õ������ǿյ�,��ô��ָ��ָ��ʼ�����ֵ,�����ܽ����+1
            if (pCurNode->m_tRight == nullptr)
            {
                pCurNode->m_tRight = pNewNode;
                pNewNode->m_tFather = pCurNode;
                m_nCount++;
                AdjustHeight(pCurNode);
                return *this;
            }
            pCurNode = pCurNode->m_tRight;
        }
        else
        {
            //�����Ѿ��д�����,�ͷ��ڴ�
            delete pNewNode;
            return *this;
        }
    }
    return *this;
}
//����---��ƫ��
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>& TreeKVAndLink<T, T1, T2>::InsertNode(T tValue, T1 tvalue1, int nOffset)
{

    //������ڵ�Ϊ��,��Ĭ��������,�½�һ�����ڵ�
    if (m_tRoot == nullptr)
    {
        m_tRoot = new TreeNode<T, T1, T2>(tValue, tvalue1, nOffset);
        m_nCount++;
        return *this;
    }

    //������ڵ�������
    TreeNode<T, T1, T2>* pCurNode = m_tRoot;
    TreeNode<T, T1, T2>* pNewNode = new TreeNode<T, T1, T2>(tValue, tvalue1, nOffset);
    while (pCurNode != nullptr)
    {
        //������ݱȵ�ǰ���ڵ�С,�����ӿ�ʼ��ѯ
        if (tValue < pCurNode->m_tValue)
        {
            //����ýڵ�û�����ӣ����½ڵ���뵽����
            if (pCurNode->m_tLeft == nullptr)
            {
                pCurNode->m_tLeft = pNewNode;
                pNewNode->m_tFather = pCurNode;
                m_nCount++;
                AdjustHeight(pCurNode);
                return *this;
            }
            pCurNode = pCurNode->m_tLeft;
        }
        //������ݱȵ�ǰ���ڵ��,���Һ��ӿ�ʼ��ѯ
        else if (tValue > pCurNode->m_tValue)
        {
            //������λ�õ������ǿյ�,��ô��ָ��ָ��ʼ�����ֵ,�����ܽ����+1
            if (pCurNode->m_tRight == nullptr)
            {
                pCurNode->m_tRight = pNewNode;
                pNewNode->m_tFather = pCurNode;
                m_nCount++;
                AdjustHeight(pCurNode);
                return *this;
            }
            pCurNode = pCurNode->m_tRight;
        }
        else
        {
            //�����Ѿ��д�����,�ͷ��ڴ�
            delete pNewNode;
            return *this;
        }
    }
    return *this;
}


//��������---T2Ϊ����ڵ�
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>& TreeKVAndLink<T, T1, T2>::InsertLink(T tValue, T2 tvalue1)
{
    // TODO: �ڴ˴����� return ���
    TreeNode<T, T1, T2>* treenode = Find(tValue);  //���ҽڵ�
    //����ڵ㲻���� �� ���أ���Ϊȱ�ٿγ���
    if (treenode == nullptr) {
        return *this;
    }
    //if (treenode->m_list->Find(tvalue1) == NULL) { 
    //    treenode->m_list->InsertHead(tvalue1);
    //}
    treenode->m_list->InsertHead(tvalue1);
    return *this;
}

//���ҽڵ�
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>::TreeNode<T, T1, T2>* TreeKVAndLink<T, T1, T2>::Find(T tValue)
{
    TreeNode<T, T1,T2>* pTemp = m_tRoot;
    while (pTemp) {
        if (pTemp->m_tValue < tValue) {
            pTemp = pTemp->m_tRight;
        }
        else if (pTemp->m_tValue > tValue) {
            pTemp = pTemp->m_tLeft;
        }
        else {
            return pTemp;
        }
    }
    return nullptr;
}

//����������
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>::TreeNode<T, T1, T2>* TreeKVAndLink<T, T1, T2>::FindInNode(TreeNode<T, T1, T2>* tnode)
{
    TreeNode<T, T1,T2>* tTempRoot = m_tRoot;
    TreeNode<T, T1,T2>* tTemp = m_tRoot;
    while (tTempRoot) {
        if (tTempRoot->m_tValue > tnode->m_tValue) {
            tTemp = tTempRoot;
            tTempRoot = tTempRoot->m_tLeft;
        }
        else {
            tTempRoot = tTempRoot->m_tRight;
        }
    }
    return tTemp;
}


//ɾ���ڵ�
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>& TreeKVAndLink<T, T1, T2>::DeleteValue(T tValue)
{
    // TODO: �ڴ˴����� return ���
    TreeNode<T, T1, T2>* tnode = Find(tValue);
    if (tnode == nullptr) {
        return *this;
    }
    //ɾ������
    ClearLink(tnode);

    //ɾ���ڵ�
               //Ҷ�ӽڵ�
    if (tnode->m_tLeft == nullptr && tnode->m_tRight == nullptr)
    {
        //����Ǹ��ڵ�,ֱ��ɾ��
        if (tnode->m_tFather == nullptr)
        {
            m_tRoot = nullptr;
        }
        //����ڵ�ֵ����������ֵ,��ʾҪɾ���Ľ�����������Ҳ�,���������Ҳ�ָ���ÿ�
        else if (tnode->m_tFather->m_tValue < tnode->m_tValue)
        {
            tnode->m_tFather->m_tRight = nullptr;
        }
        //����ڵ�ֵС��������ֵ,��ʾҪɾ���Ľ�������������,�����������ָ���ÿ�
        else if (tnode->m_tFather->m_tValue > tValue)
        {
            tnode->m_tFather->m_tLeft = nullptr;

        }
        //����������ǿ�,��ʾ���Ǹ��ڵ�,��Ҫһ��һ�����ϱ���,�����߶ȸ���
        if (tnode->m_tFather != nullptr)
        {
            AdjustHeight(tnode->m_tFather);
        }
        //�ͷſռ�
        delete tnode;
        m_nCount--;
        return *this;
    }
    //�����ӽڵ�
    else if (tnode->m_tLeft != nullptr && tnode->m_tRight == nullptr)
    {
        //���Ҫɾ���Ľڵ�������,���Һ����ǿյ�
        TreeNode<T, T1, T2>* pDel = nullptr;
        //��������ǿյ�,��ôҪɾ���Ľ��Ϊ���ڵ�,������������λ��,���Ž�������ÿ�
        if (tnode->m_tFather == nullptr)
        {
            m_tRoot = tnode->m_tLeft;
            pDel = m_tRoot;
            m_tRoot->m_tFather = nullptr;
        }
        //������Ǹ��ڵ�
        else
        {
            //���Ҫɾ���Ľ��������ֵ��������ֵ,˵����ɾ���Ľ�������
            if (tnode->m_tFather->m_tValue > tnode->m_tValue)
            {
                //���Ҫɾ����ֵ���ĺ��ӵĸ���ָ��ָ��Ҫɾ����ֵ�ĸ���,���׵���ָ�����Ҫɾ����ֵ����ڵ�
                tnode->m_tLeft->m_tFather = tnode->m_tFather;
                tnode->m_tFather->m_tLeft = tnode->m_tLeft;
                pDel = tnode->m_tLeft;
            }
            //���Ҫɾ���Ľ��������ֵС������ֵ,˵����ɾ���Ľ�����ұ�
            else if (tnode->m_tFather->m_tValue < tnode->m_tValue)
            {
                //��ɾ���Ľ�����ӵĸ���ָ��ָ��ɾ�����ĸ���ָ��,����ָ�����ָ��ָ��ɾ��ֵ���Һ���
                tnode->m_tLeft->m_tFather = tnode->m_tFather;
                tnode->m_tFather->m_tRight = tnode->m_tLeft;
                pDel = tnode->m_tLeft;
            }
        }
        delete tnode;
        AdjustHeight(pDel);
    }
    else if (tnode->m_tLeft == nullptr && tnode->m_tRight != nullptr)//���Һ��ӣ�����Ϊ��
    {
        TreeNode<T, T1, T2>* pDel = nullptr;
        if (tnode->m_tFather == nullptr)//���ڵ�
        {
            m_tRoot = tnode->m_tRight;
            m_tRoot->m_tFather = nullptr;
            pDel = m_tRoot;
        }
        else//���Ǹ��ڵ�
        {
            if (tnode->m_tFather->m_tValue > tValue)//Ҫɾ�� ���ڵ��ֵ������val�����ԷŸ��ڵ����
            {
                tnode->m_tRight->m_tFather = tnode->m_tFather;//Ҫɾ�� �Һ��ӵĸ��ڵ�ָ�� Ҫɾ���ڵ� �ĸ��ڵ�
                tnode->m_tFather->m_tLeft = tnode->m_tRight;//Ҫɾ�� ���ڵ�� ���ӽڵ� ָ��Ҫɾ���ڵ�� �Һ���
                pDel = tnode->m_tRight;
            }
            else if (tnode->m_tFather->m_tValue < tValue)//Ҫɾ�� ���ڵ��ֵ��С��val�����ԷŸ��ڵ��ұ�
            {
                tnode->m_tRight->m_tFather = tnode->m_tFather;
                tnode->m_tFather->m_tRight = tnode->m_tRight;
                pDel = tnode->m_tRight;
            }
        }
        delete tnode;
        AdjustHeight(pDel);
    }

    //˫���ӽڵ�
    else if (tnode->m_tLeft != nullptr && tnode->m_tRight != nullptr)
    {

        TreeNode<T, T1, T2>* pMax = tnode->m_tLeft;
        TreeNode<T, T1, T2>* pDel = tnode->m_tLeft;
        while (pMax->m_tRight)
        {
            pMax = pMax->m_tRight;
        }
        pDel = pMax;

        //���������ֵ ���汻ɾ�ڵ��λ��,
        if (tnode->m_tFather != nullptr)
        {
            if (tnode->m_tFather->m_tValue > tValue)
            {
                tnode->m_tFather->m_tLeft = pMax;
            }
            else if (tnode->m_tFather->m_tValue < tValue)
            {
                tnode->m_tFather->m_tRight = pMax;
            }

        }

        tnode->m_tRight->m_tFather = pMax;
        //���������û���ҽڵ㡣��������һ���������
        if (pMax->m_tFather == tnode)
        {
            tnode->m_tLeft = tnode->m_tLeft->m_tLeft;
        }
        else
        {
            pMax->m_tFather->m_tRight = nullptr;
            tnode->m_tLeft->m_tFather = pMax;
        }

        if (tnode->m_tFather != nullptr)
        {
            pMax->m_tFather = tnode->m_tFather;//��Ϊ���ڵ㣬�Ͱ��滻�����ֵ ָ�򸸽ڵ�
        }
        else
        {
            pDel = pMax->m_tFather;
            pMax->m_tFather = nullptr;//����Ǹ��ڵ㣬���ڵ�Ϊ��

            m_tRoot = pMax;
        }
        pMax->m_tLeft = tnode->m_tLeft;
        pMax->m_tRight = tnode->m_tRight;
        if (pDel->m_tFather == tnode)
        {
            delete tnode;
            AdjustHeight(pMax->m_tLeft);
        }
        else
        {
            delete tnode;
            AdjustHeight(pDel);
        }

    }
    return *this;



    //   //˼·һ�� 
    ////  1.������������Сֵ����¼ֵ
    ////  2.ɾ����Сֵ�Ľڵ�
    ////  3.����ֵΪ��Сֵ
    ////˼·��
    ////����Ϊ��
    //TreeNode<T, T1, T2>* tNodePre = tnode->m_tFather;
    //TreeNode<T, T1, T2>* tInNodeNext = tNodePre;
    ////ɾ�����ڵ�
    //if (tNodePre == nullptr) {
    //    //������������---��������
    //    if (tnode->m_tLeft && tnode->m_tRight) {
    //        tInNodeNext = FindInNode(tnode); //������
    //        if (tInNodeNext->m_tFather->m_tLeft == tInNodeNext) {
    //            tInNodeNext->m_tFather->m_tLeft = tInNodeNext->m_tRight;
    //        }
    //        else {
    //            tInNodeNext->m_tFather->m_tRight = tInNodeNext->m_tRight;
    //        }
    //        if (tInNodeNext->m_tRight) {
    //            tInNodeNext->m_tRight->m_tFather = tInNodeNext->m_tFather;
    //        }
    //        m_tRoot->m_tValue = tInNodeNext->m_tValue;
    //        m_tRoot->m_tValue1 = tInNodeNext->m_tValue1;
    //        delete tInNodeNext;
    //    }
    //    //����������
    //    else if (tnode->m_tLeft && !tnode->m_tRight) {
    //        m_tRoot = tnode->m_tLeft;
    //        m_tRoot->m_tFather = nullptr;
    //        delete tnode;
    //    }
    //    //����������
    //    else if (!tnode->m_tLeft && tnode->m_tRight) {
    //        m_tRoot = tnode->m_tRight;
    //        m_tRoot->m_tFather = nullptr;
    //        delete tnode;
    //    }//���ڵ�������������
    //    //����������
    //    else {
    //        tnode->m_tValue = NULL;
    //    }
    //}//ɾ���Ǹ��ڵ�
    ////ɾ���Ĳ��Ǹ��ڵ�
    //else {
    //    //������������---��������
    //    if (tnode->m_tLeft && tnode->m_tRight) {
    //        tInNodeNext = FindInNode(tnode); //������
    //        //������������丸�ڵ��������
    //        if (tInNodeNext->m_tFather->m_tLeft == tInNodeNext) {
    //            tInNodeNext->m_tFather->m_tLeft = tInNodeNext->m_tRight;
    //        }
    //        else {
    //            tInNodeNext->m_tFather->m_tRight = tInNodeNext->m_tRight;
    //        }

    //        if (tInNodeNext->m_tRight != nullptr) {
    //            tInNodeNext->m_tRight->m_tFather = tInNodeNext->m_tFather;
    //        }
    //        tnode->m_tValue = tInNodeNext->m_tValue;
    //        tnode->m_tValue1 = tInNodeNext->m_tValue1;
    //        delete tInNodeNext;
    //    }
    //    //����������
    //    else if (tnode->m_tLeft && !tnode->m_tRight) {
    //        if (tNodePre->m_tLeft == tnode) {
    //            tNodePre->m_tLeft = tnode->m_tLeft;
    //        }
    //        else {
    //            tNodePre->m_tRight = tnode->m_tLeft;
    //        }
    //        tnode->m_tLeft->m_tFather = tNodePre;
    //        AdjustHeight(tNodePre);
    //        delete tnode;
    //    }
    //    //����������
    //    else if (!tnode->m_tLeft && tnode->m_tRight) {
    //        if (tNodePre->m_tLeft == tnode) {
    //            tNodePre->m_tLeft = tnode->m_tRight;
    //        }
    //        else {
    //            tNodePre->m_tRight = tnode->m_tRight;
    //        }
    //        tnode->m_tRight->m_tFather = tNodePre;
    //        AdjustHeight(tNodePre);
    //        delete tnode;
    //    }
    //    //���Ǹ��ڵ㲢��û����������
    //    else {
    //        if (tNodePre->m_tLeft == tnode) {
    //            tNodePre->m_tLeft = nullptr;
    //        }
    //        else {
    //            tNodePre->m_tRight = nullptr;
    //        }
    //        AdjustHeight(tNodePre);
    //        delete tnode;
    //    }
    //}
    //return *this;
}


//ɾ�������ڵ�ĳ��ֵ
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>& TreeKVAndLink<T, T1, T2>::DeleteLink(T tValue, T2 tValue1)
{
    // TODO: �ڴ˴����� return ���
    TreeNode<T, T1, T2>* tnode = Find(tValue);//�ҵ��ڵ�
    //������û���ҵ�ƥ��  ----���
    if (tnode->m_list->Find(tValue1) == NULL) {
        return *this;
    }
    tnode->m_list->Delete(tnode->m_list->Find(tValue1));

    return *this;

}


template<typename T, typename T1, typename T2>
inline int TreeKVAndLink<T, T1, T2>::GetHeight(TreeNode<T, T1, T2>* pNode)
{
    return pNode == nullptr ? 0 : pNode->m_nHeight;
}

template<typename T, typename T1, typename T2>
inline void TreeKVAndLink<T, T1, T2>::CalcHeight(TreeNode<T, T1, T2>* pNode)
{
    pNode->m_nHeight = max(GetHeight(pNode->m_tRight), GetHeight(pNode->m_tLeft)) + 1;
    return;
}

//�����߶�
template<typename T, typename T1, typename T2>
inline void TreeKVAndLink<T, T1, T2>::AdjustHeight(TreeNode<T, T1, T2>* pNode)
{
    while (pNode != nullptr)
    {
        //����߶�
        CalcHeight(pNode);

        //�ж��Ƿ�ƽ��
        if (std::abs(GetHeight(pNode->m_tLeft) - GetHeight(pNode->m_tRight)) > 1)
        {
            if (GetHeight(pNode->m_tRight) > GetHeight(pNode->m_tLeft))
            {
                auto pK = pNode->m_tRight;
                /*
                        p                          p
                        |                          |
                        n                          k
                          \                      /   \
                            k          ==>      n      kr
                           /  \                  \      \
                          kl   kr                 kl    krr
                                \
                                 krr
                */
                if (GetHeight(pK->m_tLeft) < GetHeight(pK->m_tRight))
                {
                    LeftRotate(pNode);
                }
                /*
                        p                   p                       p
                        |                   |                       |
                        n                   n                       kl
                          \        K ����     \           n ����   /   \
                            k        ==>       kl          ==>  n      k
                           /  \               /  \               \      \
                          kl   kr           klr   k               klr   kr
                         /                         \
                        klr                        kr
                */
                else
                {
                    RightRotate(pK);
                    LeftRotate(pNode);
                }
            }
            else
            {
                auto pK = pNode->m_tLeft;
                /*
                        p                          p
                        |                          |
                        n                          k
                      /                          /   \
                     k                 ==>     kl      n
                   /  \                       /      /
                  kl   kr                   kll     kr
                  /
                kll
                */
                if (GetHeight(pK->m_tLeft) > GetHeight(pK->m_tRight))
                {
                    RightRotate(pNode);
                }
                /*
                        p                  p                  p
                        |                  |                  |
                        n    k ����         n    n ����        kr
                      /                  /                  /   \
                     k         ==>     kr         ==>     k      n
                   /  \               /  \               /      /
                  kl   kr           k    krr           kl      krr
                        \          /
                        krr       kl
                */
                else
                {
                    LeftRotate(pK);
                    RightRotate(pNode);
                }
            }
        }
        //���Ÿ��ڵ�һ·����
        pNode = pNode->m_tFather;
    }
}

template<typename T, typename T1, typename T2>
inline void TreeKVAndLink<T, T1, T2>::LeftRotate(TreeNode<T, T1, T2>* pnode)
{
    TreeNode<T, T1, T2>* pMon = pnode;
    TreeNode<T, T1, T2>* pFather = pnode->m_tFather;
    TreeNode<T, T1, T2>* pRightSon = pnode->m_tRight;
    TreeNode<T, T1, T2>* pLeftSon = pRightSon->m_tLeft;

    if (pFather != nullptr)
    {
        if (pFather->m_tRight == pMon)
        {
            pFather->m_tRight = pRightSon;
        }
        else
        {
            pFather->m_tLeft = pRightSon;
        }
    }
    else
    {
        m_tRoot = pRightSon;
    }
    if (pLeftSon != nullptr)
    {
        pLeftSon->m_tFather = pMon;
    }
    pRightSon->m_tLeft = pMon;
    pRightSon->m_tFather = pFather;
    pMon->m_tRight = pLeftSon;
    pMon->m_tFather = pRightSon;
    CalcHeight(pMon);
    CalcHeight(pRightSon);
}

template<typename T, typename T1, typename T2>
inline void TreeKVAndLink<T, T1, T2>::RightRotate(TreeNode<T, T1, T2>* pnode)
{
    TreeNode<T, T1, T2>* pMon = pnode;
    TreeNode<T, T1, T2>* pFather = pnode->m_tFather;
    TreeNode<T, T1, T2>* pLeftSon = pnode->m_tLeft;
    TreeNode<T, T1, T2>* pRightSon = pLeftSon->m_tRight;

    if (pFather != nullptr)
    {
        if (pFather->m_tLeft == pMon)
        {
            pFather->m_tLeft = pLeftSon;
        }
        else
        {
            pFather->m_tRight = pLeftSon;
        }
    }
    else
    {
        m_tRoot = pLeftSon;
    }
    if (pRightSon != nullptr)
    {
        pRightSon->m_tFather = pMon;
    }
    pLeftSon->m_tRight = pMon;
    pLeftSon->m_tFather = pFather;
    pMon->m_tLeft = pRightSon;
    pMon->m_tFather = pLeftSon;
    CalcHeight(pMon);
    CalcHeight(pLeftSon);
}




