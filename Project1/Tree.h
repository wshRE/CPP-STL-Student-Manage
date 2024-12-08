#pragma once
//#include<iostream>
//#include"CString.h"
//#include"CList.h"
//const size_t WHITE = 0;//新节点
//const size_t GRAY = 1; //已访问
//template<typename T, typename T1>  //T:KEY  T1:VALUE  
//class TreeAndLink {
//public:
//    //节点
//    template<typename T, typename T1>
//    struct TreePoint {
//        TreeNode() :m_tValue() {
//            m_tLeft = nullptr;
//            m_tRight = nullptr;
//            m_tFather = nullptr;
//            m_nHeight = 0;  //左右高度差
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
//        int m_nHeight;   //树高度
//        TreeNode<T, T1>* m_tLeft;
//        TreeNode<T, T1>* m_tRight;
//        TreeNode<T, T1>* m_tFather; //父节点
//        CList<T1>* m_list;//挂载链表
//    };
//    //非递归遍历栈
//    template<typename T, typename T1>
//    struct TreeStack {
//        TreeStack() :nColor() {
//            tNode = nullptr;
//        }
//        TreeStack(size_t ncolor, TreeNode<T, T1>* tnode) {
//            nColor = ncolor;
//            tNode = tnode;
//        }
//        size_t nColor;    //颜色  0为白色  1为灰色
//        TreeNode<T, T1>* tNode;  //节点
//    };
//
//
//    //基础套件
//    TreeAndLink();
//    TreeAndLink(const TreeAndLink<T, T1>& t);
//    TreeAndLink(TreeAndLink<T, T1>&& t);
//    ~TreeAndLink();
//
//    //初始化与结束
//    void Init();
//    void ClearTree(TreeNode<T, T1>* tree);
//    void ClearLink(TreeNode<T, T1>* tree);
//
//    //树操作
////增 
//        //插入节点---有节点则直接插入链表，没有则创建节点
//    TreeAndLink<T, T1>& InsertNode(T tValue, T1 tvalue1);
//
//    //查
//            //查找----通过主键查找----仅返回树节点
//    TreeNode<T, T1>* Find(T tValue);
//
//    //删
//            //删除----按照KEY删除树节点---11删链表ClearLink 2.删节点
//    TreeAndLink<T, T1>& DeleteValue(T tValue);
//    //删除----删除链表节点------T1：传入id即可
//    TreeAndLink<T, T1>& DeleteLink(T tValue, T1 tValue1);
//
//
//
// //平衡
//        //递归求节点高度----其下的高度会顺便求完并赋值
//    int GetHeight(TreeNode<T, T1>* tnode);
//
//    //直接取节点高度(已赋值)
//    int GetHightRecord(TreeNode<T, T1>* tnode);
//
//    //判断从该节点开始的树是否平衡
//    bool IsBalance(TreeNode<T, T1>* tnode);
//
//    //获取根节点的指针
//    TreeNode<T, T1>* GetRoot() {
//        return tRoot;
//    }
//
//    //平衡化改造
//    void BalaanceTWO(TreeNode<T, T1>* tnode);
//    //获取某个节点的左右树高度差
//    int GetBalanceNum(TreeNode<T, T1>* tnode);
//    //查找第一个不平衡节点 输入：起始点
//    TreeNode<T, T1>* FindBalance(TreeNode<T, T1>* tnode);
//
//private:
//    TreeNode<T, T1>* m_tRoot;  //根节点
//};
