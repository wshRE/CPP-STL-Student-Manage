#pragma once
//#include<iostream>
//#include"CString.h"
//#include"CList.h"
//const size_t WHITE = 0;//�½ڵ�
//const size_t GRAY = 1; //�ѷ���
//template<typename T, typename T1>  //T:KEY  T1:VALUE  
//class TreeAndLink {
//public:
//    //�ڵ�
//    template<typename T, typename T1>
//    struct TreePoint {
//        TreeNode() :m_tValue() {
//            m_tLeft = nullptr;
//            m_tRight = nullptr;
//            m_tFather = nullptr;
//            m_nHeight = 0;  //���Ҹ߶Ȳ�
//            m_list = new CList<T1>;
//        }
//        TreeNode(T t) :m_tValue(t){
//            m_tLeft = nullptr;
//            m_tRight = nullptr;
//            m_tFather = nullptr;
//            m_nHeight = 0;
//            m_list = new CList<T1>;
//        }
//        T m_tValue;  
//        int m_nHeight;   //���߶�
//        TreeNode<T, T1>* m_tLeft;
//        TreeNode<T, T1>* m_tRight;
//        TreeNode<T, T1>* m_tFather; //���ڵ�
//        CList<T1>* m_list;//��������
//    };
//    //�ǵݹ����ջ
//    template<typename T, typename T1>
//    struct TreeStack {
//        TreeStack() :nColor() {
//            tNode = nullptr;
//        }
//        TreeStack(size_t ncolor, TreeNode<T, T1>* tnode) {
//            nColor = ncolor;
//            tNode = tnode;
//        }
//        size_t nColor;    //��ɫ  0Ϊ��ɫ  1Ϊ��ɫ
//        TreeNode<T, T1>* tNode;  //�ڵ�
//    };
//
//
//    //�����׼�
//    TreeAndLink();
//    TreeAndLink(const TreeAndLink<T, T1>& t);
//    TreeAndLink(TreeAndLink<T, T1>&& t);
//    ~TreeAndLink();
//
//    //��ʼ�������
//    void Init();
//    void ClearTree(TreeNode<T, T1>* tree);
//    void ClearLink(TreeNode<T, T1>* tree);
//
//    //������
////�� 
//        //����ڵ�---�нڵ���ֱ�Ӳ�������û���򴴽��ڵ�
//    TreeAndLink<T, T1>& InsertNode(T tValue, T1 tvalue1);
//
//    //��
//            //����----ͨ����������----���������ڵ�
//    TreeNode<T, T1>* Find(T tValue);
//
//    //ɾ
//            //ɾ��----����KEYɾ�����ڵ�---11ɾ����ClearLink 2.ɾ�ڵ�
//    TreeAndLink<T, T1>& DeleteValue(T tValue);
//    //ɾ��----ɾ������ڵ�------T1������id����
//    TreeAndLink<T, T1>& DeleteLink(T tValue, T1 tValue1);
//
//
//
// //ƽ��
//        //�ݹ���ڵ�߶�----���µĸ߶Ȼ�˳�����겢��ֵ
//    int GetHeight(TreeNode<T, T1>* tnode);
//
//    //ֱ��ȡ�ڵ�߶�(�Ѹ�ֵ)
//    int GetHightRecord(TreeNode<T, T1>* tnode);
//
//    //�жϴӸýڵ㿪ʼ�����Ƿ�ƽ��
//    bool IsBalance(TreeNode<T, T1>* tnode);
//
//    //��ȡ���ڵ��ָ��
//    TreeNode<T, T1>* GetRoot() {
//        return tRoot;
//    }
//
//    //ƽ�⻯����
//    void BalaanceTWO(TreeNode<T, T1>* tnode);
//    //��ȡĳ���ڵ���������߶Ȳ�
//    int GetBalanceNum(TreeNode<T, T1>* tnode);
//    //���ҵ�һ����ƽ��ڵ� ���룺��ʼ��
//    TreeNode<T, T1>* FindBalance(TreeNode<T, T1>* tnode);
//
//private:
//    TreeNode<T, T1>* m_tRoot;  //���ڵ�
//};
