#include"TreeKV.h"
#include"CString.h"
#include<iostream>
#include"Manange.h"
#include"Header.h"
//链表节点
    //课程id树的链表节点
    //一个学生id 一个课程id 锁定唯一的偏移量
struct CourseLinkNode {
    size_t nStudentID;    //学生id
    int nCourseMark;   //课程分数
    int nOffset;       //选课记录偏移量
    bool operator==(CourseLinkNode cln) {
        if (cln.nStudentID == nStudentID) {
            return true;
        }
        return false;
    }
};
//学生id树的链表节点
struct StudentLinkNode {
    size_t nCourseID;
    int nCourseMark;
    int nOffset;       //选课记录偏移量
    bool operator==(StudentLinkNode cln) {
        return cln.nCourseID == nCourseID;
    }
};
//课程id树
TreeKVAndLink<size_t, CMyString, CourseLinkNode> tCourseID;
//学生id树
TreeKVAndLink<size_t, CMyString, StudentLinkNode> tStudentID;

//课程名
TreeKVAndLink<CMyString, size_t, size_t> tCourseName;
//学生名
TreeKVAndLink<CMyString, size_t, size_t> tStudentName;

//学生id树节点
TreeKVAndLink<size_t, CMyString, StudentLinkNode>::TreeNode<size_t, CMyString, StudentLinkNode>* pStuTreeNode;
CList<StudentLinkNode>::Iterator lStulistI;
//课程id树节点
TreeKVAndLink<size_t, CMyString, CourseLinkNode>::TreeNode<size_t, CMyString, CourseLinkNode>* pCouTreeNode;
CList<CourseLinkNode>::Iterator lCoulistI;
//课程名字树节点
TreeKVAndLink<CMyString, size_t, size_t>::TreeStack<CMyString, size_t, size_t>* pCouNameNode;
//学生名字树节点
TreeKVAndLink<CMyString, size_t, size_t>::TreeStack<CMyString, size_t, size_t>* pStuNameNode;
char cStudentName[100] = {};
char cCourseName[100] = {};
int nMark;


//1.新增学生（ID 名字）
void StudentAdd(char cStudentName[], size_t nStudentID) {
    //if (nOffset == -1) {
    //    //分配并返回偏移
    //    nOffset = StudentFileAdd(cStudentName);
    //}
    FileAddStruct(cStudentName, nStudentID,0);//文件添加
    tStudentID.InsertNode(nStudentID, cStudentName);  // 学生id 名字
    tStudentName.InsertNode(cStudentName, 0);   //学生名  value默认0
    tStudentName.InsertLink(cStudentName, nStudentID); //学生名  学生id
}
void StudentInitAdd(char cStudentName[], size_t nStudentID) {
    tStudentID.InsertNode(nStudentID, cStudentName);  // 学生id 名字
    tStudentName.InsertNode(cStudentName, 0);   //学生名  value默认0
    tStudentName.InsertLink(cStudentName, nStudentID); //学生名  学生id
}


//(2)新增课程(ID, 名字)
void CourseAdd(char cCourseName[], size_t nCourseID) {
    //if (nOffset == -1) {
    //    nOffset = CourseFileAdd(cCourseName);
    //}
    FileAddStruct(cCourseName, nCourseID, 1);//文件添加
    tCourseID.InsertNode(nCourseID, cCourseName);
    tCourseName.InsertNode(cCourseName, 0);        //课程名   value默认为0
    tCourseName.InsertLink(cCourseName, nCourseID);      //课程名   课程id
}
void CourseInitAdd(char cCourseName[], size_t nCourseID) {
    tCourseID.InsertNode(nCourseID, cCourseName);
    tCourseName.InsertNode(cCourseName, 0);        //课程名   value默认为0
    tCourseName.InsertLink(cCourseName, nCourseID);      //课程名   课程id
}



//(3)新增选课记录(学生ID, 课程ID, 分数)
void CourseRecord( size_t nStudentID,size_t nCourseID, int nMark,int nAdress) {
    if (nAdress == -1) {
        if (tStudentID.Find(nStudentID) == nullptr) {
            cout << "没有该学生 " << endl;
            return;
        }
        if (tCourseID.Find(nCourseID) == nullptr) {
            cout << "没有该课程 " << endl;
            return;
        }
        //分配空间
        nAdress = ChooseInsert( nStudentID,  nCourseID,  nMark);
    }
    tStudentID.InsertLink(nStudentID, { nCourseID,nMark ,nAdress });   // 学生id  课程号-分数
    tCourseID.InsertLink(nCourseID, { nStudentID,nMark,nAdress });
}

//(4) 删除学生(ID)
void StudentDel(size_t nStudentID) {

    pStuTreeNode = tStudentID.Find(nStudentID);//查找节点
    if (pStuTreeNode == nullptr) {
        cout << "该学生不存在" << endl;
        return;
    }
    FileDelStruct(nStudentID,0);
    //删除课程id树的相关信息
    auto list = pStuTreeNode->m_list;
    if (list == nullptr) {
        cout << "该学生没有课程" << endl;
        return;
    }
    //课程id树中与该学生相关的删除
    for (auto& i : *list) {
        tCourseID.DeleteLink(i.nCourseID, { nStudentID ,0 });
    }

    //删除名字树中的链表节点 
    tStudentName.DeleteLink(pStuTreeNode->m_tValue1, nStudentID);
    //删除id树的节点
    tStudentID.DeleteValue(nStudentID);
}

//(5) 删除课程(ID)
void CourseDel(size_t nCourseID) {

    pCouTreeNode = tCourseID.Find(nCourseID);//查找节点
    if (pCouTreeNode == nullptr) {
        cout << "没有该课程 " << endl;
        return;
    }
    FileDelStruct(nCourseID, 1);
    //读学生id，并删除学生id链表
    for (auto& i : *(pCouTreeNode->m_list)) {
        tStudentID.DeleteLink(i.nStudentID, { nCourseID ,0 });
    }
    //删除名字树中的链表节点
    tCourseName.DeleteLink(pCouTreeNode->m_tValue1, nCourseID);
    //删除id树的节点
    tCourseID.DeleteValue(nCourseID);
}

//(6) 删除选课记录(学生ID, 课程ID)
void CourseRecordDel(size_t nStudentID, size_t nCourseID) {
    if (tStudentID.Find(nStudentID) == nullptr) {
        cout << "没有该学生 " << endl;
        return;
    }
    if (tCourseID.Find(nCourseID) == nullptr) {
        cout << "没有该课程 " << endl;
        return;
    }
    tStudentID.DeleteLink(nStudentID, { nCourseID ,0 });
    tCourseID.DeleteLink(nCourseID, { nStudentID ,0 });
}


//(7) 改学生名字
void StudentNameChange(size_t nStudentID, char cStudentName[]) {

    pStuTreeNode = tStudentID.Find(nStudentID);//查找节点
    if (pStuTreeNode == nullptr) {
        cout << "没有找到该学生" << endl;
        return;
    }
    //文件修改
    FileChangeStruct(cStudentName, nStudentID,0);
    ////1.记录原来的偏移（加上已删除
    //int nStorePre = pStuTreeNode->m_nStore;
    //2.在末尾追加新的数据
    //3.修改存储的偏移量
    tStudentName.DeleteLink(pStuTreeNode->m_tValue1, nStudentID);//删除名字树节点
    tStudentName.InsertNode(cStudentName, 0); //添加名字树新节点
    tStudentName.InsertLink(cStudentName, nStudentID); //添加名字树新链表
    pStuTreeNode->m_tValue1 = cStudentName; //修改名字
}

//(8) 改课程名字
void CourseNameChange(size_t nCourseID, char cCourseName[]) {
    pCouTreeNode = tCourseID.Find(nCourseID);//查找节点
    if (pCouTreeNode == nullptr) {
        cout << "没有找到该课程" << endl;
        return;
    }
    FileChangeStruct(cCourseName, nCourseID, 1);
    tCourseName.DeleteLink(pCouTreeNode->m_tValue1, nCourseID);//删除名字树节点
    tCourseName.InsertNode(cCourseName, 0); //添加名字树新节点
    tStudentName.InsertLink(cCourseName, nCourseID); //添加名字树新链表
    pCouTreeNode->m_tValue1 = cCourseName; //修改名字
}

//(9) 改学生成绩
void CourseMarkChange(size_t nStudentID, size_t nCourseID, int nMark) {
    pStuTreeNode = tStudentID.Find(nStudentID);//查找节点
    if (pStuTreeNode == nullptr) {
        cout << "没有该学生" << endl;
        return;
    }

    //修改学生id树
    auto i = pStuTreeNode->m_list->Find({ nCourseID ,0 });
    if (i == nullptr) {
        cout << "该学生没有选修该课程" << endl;
        return;
    }
    i->m_nVal.nCourseMark = nMark;
    //修改存储文件
    ChooseChange(i->m_nVal.nOffset, nStudentID, nCourseID, nMark);
    //修改课程id树
    pCouTreeNode = tCourseID.Find(nCourseID);//查找节点
    pCouTreeNode->m_list->Find({ nStudentID ,0 })->m_nVal.nCourseMark = nMark;
}

//(10) 通过学生ID查询学生姓名
void StudentNameFind(size_t nStudentID) {
    if (nStudentID > GetStuID()) {
        cout << "没有该学生" << endl;
        return;
    }
    auto stid = tStudentID.Find(nStudentID);
    if (stid == nullptr) {
        cout << "没有该学生" << endl;
        return;
    }
    cout <<"学生姓名：" << stid->m_tValue1 << endl;
}

//(11) 通过学生姓名查询学生ID
void StudentIDFind(char cStudentName[]) {
    auto stuname = tStudentName.Find(cStudentName);
    if (stuname == nullptr || stuname->m_list == nullptr) {
        cout << "搜索失败，无该学生" << endl;
        return;
    }
    //循环输出学生id
    for (auto i : *(stuname->m_list)) {
        cout << "学生id： " << i << endl;
    }
    //cout << *(stuname->m_list->end()) << endl;
}


//(12) 通过课程ID查询课程名
void CourseNameFind(size_t nCourseID) {
    if (nCourseID > GetCouID()) {
        cout << "没有该课程" << endl;
        return;
    }
    auto cid = tCourseID.Find(nCourseID);
    if (cid == nullptr) {
        cout << "没有该课程" << endl;
        return;
    }
    cout << "课程名：" << cid->m_tValue1 << endl;
}

//(13) 通过课程名查询课程ID
void CourseIDFind(char cCourseName[]) {
    auto couname = tCourseName.Find(cCourseName);
    if (couname == nullptr) {
        cout << "没有该课程" << endl;
        return;
    }
    //循环输出课程id
    for (auto i : *(couname->m_list)) {
        cout << "课程id：" << i << endl;
    }
    //if (couname->m_list->end() != couname->m_list->begin()) {
    //    cout << *(couname->m_list->end()) << endl;
    //}
}

//(14) 通过课程ID查询选修了该课程的学生以及成绩
void CourseIDStuFind(size_t nCourseID) {
    if (nCourseID > GetCouID()) {
        cout << "没有该课程" << endl;
        return;
    }
    auto aCouFind = tCourseID.Find(nCourseID);
    if (aCouFind == nullptr) {
        cout << "没有该课程" << endl;
        return;
    }
    auto ii = aCouFind->m_list;
    if (ii == nullptr) {
        cout << "没有选修了该课程的同学" << endl;
        return;
    }
    for (auto& i : *ii) {
        cout << " 学生id：" << i.nStudentID << "    课程分数：" << i.nCourseMark << endl;
    }
    //if (ii->begin() != ii->end()) {
    //    cout << (*(ii->end())).nStudentID << "   " << (*(ii->end())).nCourseMark << endl;
    //}
}

//(15) 通过学生ID查询该学生选修的课程信息
void StudentIDCouFind(size_t nStudentID) {
    if (nStudentID > GetStuID()) {
        cout << "没有该学生" << endl;
        return;
    }
    auto aStuFind = tStudentID.Find(nStudentID);
    if (aStuFind == nullptr) {
        cout << "没有该学生" << endl;
        return;
    }
    auto stucou = aStuFind->m_list;
    if (stucou->IsEmpty()) {
        cout << "没有记录" << endl;
        return;
    }
    for (auto& i : *stucou) {
        cout << "  课程id：" << i.nCourseID << "   课程分数：" << i.nCourseMark << endl;
    }
}









































