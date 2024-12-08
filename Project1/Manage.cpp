#include"TreeKV.h"
#include"CString.h"
#include<iostream>
#include"Manange.h"
#include"Header.h"
//����ڵ�
    //�γ�id��������ڵ�
    //һ��ѧ��id һ���γ�id ����Ψһ��ƫ����
struct CourseLinkNode {
    size_t nStudentID;    //ѧ��id
    int nCourseMark;   //�γ̷���
    int nOffset;       //ѡ�μ�¼ƫ����
    bool operator==(CourseLinkNode cln) {
        if (cln.nStudentID == nStudentID) {
            return true;
        }
        return false;
    }
};
//ѧ��id��������ڵ�
struct StudentLinkNode {
    size_t nCourseID;
    int nCourseMark;
    int nOffset;       //ѡ�μ�¼ƫ����
    bool operator==(StudentLinkNode cln) {
        return cln.nCourseID == nCourseID;
    }
};
//�γ�id��
TreeKVAndLink<size_t, CMyString, CourseLinkNode> tCourseID;
//ѧ��id��
TreeKVAndLink<size_t, CMyString, StudentLinkNode> tStudentID;

//�γ���
TreeKVAndLink<CMyString, size_t, size_t> tCourseName;
//ѧ����
TreeKVAndLink<CMyString, size_t, size_t> tStudentName;

//ѧ��id���ڵ�
TreeKVAndLink<size_t, CMyString, StudentLinkNode>::TreeNode<size_t, CMyString, StudentLinkNode>* pStuTreeNode;
CList<StudentLinkNode>::Iterator lStulistI;
//�γ�id���ڵ�
TreeKVAndLink<size_t, CMyString, CourseLinkNode>::TreeNode<size_t, CMyString, CourseLinkNode>* pCouTreeNode;
CList<CourseLinkNode>::Iterator lCoulistI;
//�γ��������ڵ�
TreeKVAndLink<CMyString, size_t, size_t>::TreeStack<CMyString, size_t, size_t>* pCouNameNode;
//ѧ���������ڵ�
TreeKVAndLink<CMyString, size_t, size_t>::TreeStack<CMyString, size_t, size_t>* pStuNameNode;
char cStudentName[100] = {};
char cCourseName[100] = {};
int nMark;


//1.����ѧ����ID ���֣�
void StudentAdd(char cStudentName[], size_t nStudentID) {
    //if (nOffset == -1) {
    //    //���䲢����ƫ��
    //    nOffset = StudentFileAdd(cStudentName);
    //}
    FileAddStruct(cStudentName, nStudentID,0);//�ļ����
    tStudentID.InsertNode(nStudentID, cStudentName);  // ѧ��id ����
    tStudentName.InsertNode(cStudentName, 0);   //ѧ����  valueĬ��0
    tStudentName.InsertLink(cStudentName, nStudentID); //ѧ����  ѧ��id
}
void StudentInitAdd(char cStudentName[], size_t nStudentID) {
    tStudentID.InsertNode(nStudentID, cStudentName);  // ѧ��id ����
    tStudentName.InsertNode(cStudentName, 0);   //ѧ����  valueĬ��0
    tStudentName.InsertLink(cStudentName, nStudentID); //ѧ����  ѧ��id
}


//(2)�����γ�(ID, ����)
void CourseAdd(char cCourseName[], size_t nCourseID) {
    //if (nOffset == -1) {
    //    nOffset = CourseFileAdd(cCourseName);
    //}
    FileAddStruct(cCourseName, nCourseID, 1);//�ļ����
    tCourseID.InsertNode(nCourseID, cCourseName);
    tCourseName.InsertNode(cCourseName, 0);        //�γ���   valueĬ��Ϊ0
    tCourseName.InsertLink(cCourseName, nCourseID);      //�γ���   �γ�id
}
void CourseInitAdd(char cCourseName[], size_t nCourseID) {
    tCourseID.InsertNode(nCourseID, cCourseName);
    tCourseName.InsertNode(cCourseName, 0);        //�γ���   valueĬ��Ϊ0
    tCourseName.InsertLink(cCourseName, nCourseID);      //�γ���   �γ�id
}



//(3)����ѡ�μ�¼(ѧ��ID, �γ�ID, ����)
void CourseRecord( size_t nStudentID,size_t nCourseID, int nMark,int nAdress) {
    if (nAdress == -1) {
        if (tStudentID.Find(nStudentID) == nullptr) {
            cout << "û�и�ѧ�� " << endl;
            return;
        }
        if (tCourseID.Find(nCourseID) == nullptr) {
            cout << "û�иÿγ� " << endl;
            return;
        }
        //����ռ�
        nAdress = ChooseInsert( nStudentID,  nCourseID,  nMark);
    }
    tStudentID.InsertLink(nStudentID, { nCourseID,nMark ,nAdress });   // ѧ��id  �γ̺�-����
    tCourseID.InsertLink(nCourseID, { nStudentID,nMark,nAdress });
}

//(4) ɾ��ѧ��(ID)
void StudentDel(size_t nStudentID) {

    pStuTreeNode = tStudentID.Find(nStudentID);//���ҽڵ�
    if (pStuTreeNode == nullptr) {
        cout << "��ѧ��������" << endl;
        return;
    }
    FileDelStruct(nStudentID,0);
    //ɾ���γ�id���������Ϣ
    auto list = pStuTreeNode->m_list;
    if (list == nullptr) {
        cout << "��ѧ��û�пγ�" << endl;
        return;
    }
    //�γ�id�������ѧ����ص�ɾ��
    for (auto& i : *list) {
        tCourseID.DeleteLink(i.nCourseID, { nStudentID ,0 });
    }

    //ɾ���������е�����ڵ� 
    tStudentName.DeleteLink(pStuTreeNode->m_tValue1, nStudentID);
    //ɾ��id���Ľڵ�
    tStudentID.DeleteValue(nStudentID);
}

//(5) ɾ���γ�(ID)
void CourseDel(size_t nCourseID) {

    pCouTreeNode = tCourseID.Find(nCourseID);//���ҽڵ�
    if (pCouTreeNode == nullptr) {
        cout << "û�иÿγ� " << endl;
        return;
    }
    FileDelStruct(nCourseID, 1);
    //��ѧ��id����ɾ��ѧ��id����
    for (auto& i : *(pCouTreeNode->m_list)) {
        tStudentID.DeleteLink(i.nStudentID, { nCourseID ,0 });
    }
    //ɾ���������е�����ڵ�
    tCourseName.DeleteLink(pCouTreeNode->m_tValue1, nCourseID);
    //ɾ��id���Ľڵ�
    tCourseID.DeleteValue(nCourseID);
}

//(6) ɾ��ѡ�μ�¼(ѧ��ID, �γ�ID)
void CourseRecordDel(size_t nStudentID, size_t nCourseID) {
    if (tStudentID.Find(nStudentID) == nullptr) {
        cout << "û�и�ѧ�� " << endl;
        return;
    }
    if (tCourseID.Find(nCourseID) == nullptr) {
        cout << "û�иÿγ� " << endl;
        return;
    }
    tStudentID.DeleteLink(nStudentID, { nCourseID ,0 });
    tCourseID.DeleteLink(nCourseID, { nStudentID ,0 });
}


//(7) ��ѧ������
void StudentNameChange(size_t nStudentID, char cStudentName[]) {

    pStuTreeNode = tStudentID.Find(nStudentID);//���ҽڵ�
    if (pStuTreeNode == nullptr) {
        cout << "û���ҵ���ѧ��" << endl;
        return;
    }
    //�ļ��޸�
    FileChangeStruct(cStudentName, nStudentID,0);
    ////1.��¼ԭ����ƫ�ƣ�������ɾ��
    //int nStorePre = pStuTreeNode->m_nStore;
    //2.��ĩβ׷���µ�����
    //3.�޸Ĵ洢��ƫ����
    tStudentName.DeleteLink(pStuTreeNode->m_tValue1, nStudentID);//ɾ���������ڵ�
    tStudentName.InsertNode(cStudentName, 0); //����������½ڵ�
    tStudentName.InsertLink(cStudentName, nStudentID); //���������������
    pStuTreeNode->m_tValue1 = cStudentName; //�޸�����
}

//(8) �Ŀγ�����
void CourseNameChange(size_t nCourseID, char cCourseName[]) {
    pCouTreeNode = tCourseID.Find(nCourseID);//���ҽڵ�
    if (pCouTreeNode == nullptr) {
        cout << "û���ҵ��ÿγ�" << endl;
        return;
    }
    FileChangeStruct(cCourseName, nCourseID, 1);
    tCourseName.DeleteLink(pCouTreeNode->m_tValue1, nCourseID);//ɾ���������ڵ�
    tCourseName.InsertNode(cCourseName, 0); //����������½ڵ�
    tStudentName.InsertLink(cCourseName, nCourseID); //���������������
    pCouTreeNode->m_tValue1 = cCourseName; //�޸�����
}

//(9) ��ѧ���ɼ�
void CourseMarkChange(size_t nStudentID, size_t nCourseID, int nMark) {
    pStuTreeNode = tStudentID.Find(nStudentID);//���ҽڵ�
    if (pStuTreeNode == nullptr) {
        cout << "û�и�ѧ��" << endl;
        return;
    }

    //�޸�ѧ��id��
    auto i = pStuTreeNode->m_list->Find({ nCourseID ,0 });
    if (i == nullptr) {
        cout << "��ѧ��û��ѡ�޸ÿγ�" << endl;
        return;
    }
    i->m_nVal.nCourseMark = nMark;
    //�޸Ĵ洢�ļ�
    ChooseChange(i->m_nVal.nOffset, nStudentID, nCourseID, nMark);
    //�޸Ŀγ�id��
    pCouTreeNode = tCourseID.Find(nCourseID);//���ҽڵ�
    pCouTreeNode->m_list->Find({ nStudentID ,0 })->m_nVal.nCourseMark = nMark;
}

//(10) ͨ��ѧ��ID��ѯѧ������
void StudentNameFind(size_t nStudentID) {
    if (nStudentID > GetStuID()) {
        cout << "û�и�ѧ��" << endl;
        return;
    }
    auto stid = tStudentID.Find(nStudentID);
    if (stid == nullptr) {
        cout << "û�и�ѧ��" << endl;
        return;
    }
    cout <<"ѧ��������" << stid->m_tValue1 << endl;
}

//(11) ͨ��ѧ��������ѯѧ��ID
void StudentIDFind(char cStudentName[]) {
    auto stuname = tStudentName.Find(cStudentName);
    if (stuname == nullptr || stuname->m_list == nullptr) {
        cout << "����ʧ�ܣ��޸�ѧ��" << endl;
        return;
    }
    //ѭ�����ѧ��id
    for (auto i : *(stuname->m_list)) {
        cout << "ѧ��id�� " << i << endl;
    }
    //cout << *(stuname->m_list->end()) << endl;
}


//(12) ͨ���γ�ID��ѯ�γ���
void CourseNameFind(size_t nCourseID) {
    if (nCourseID > GetCouID()) {
        cout << "û�иÿγ�" << endl;
        return;
    }
    auto cid = tCourseID.Find(nCourseID);
    if (cid == nullptr) {
        cout << "û�иÿγ�" << endl;
        return;
    }
    cout << "�γ�����" << cid->m_tValue1 << endl;
}

//(13) ͨ���γ�����ѯ�γ�ID
void CourseIDFind(char cCourseName[]) {
    auto couname = tCourseName.Find(cCourseName);
    if (couname == nullptr) {
        cout << "û�иÿγ�" << endl;
        return;
    }
    //ѭ������γ�id
    for (auto i : *(couname->m_list)) {
        cout << "�γ�id��" << i << endl;
    }
    //if (couname->m_list->end() != couname->m_list->begin()) {
    //    cout << *(couname->m_list->end()) << endl;
    //}
}

//(14) ͨ���γ�ID��ѯѡ���˸ÿγ̵�ѧ���Լ��ɼ�
void CourseIDStuFind(size_t nCourseID) {
    if (nCourseID > GetCouID()) {
        cout << "û�иÿγ�" << endl;
        return;
    }
    auto aCouFind = tCourseID.Find(nCourseID);
    if (aCouFind == nullptr) {
        cout << "û�иÿγ�" << endl;
        return;
    }
    auto ii = aCouFind->m_list;
    if (ii == nullptr) {
        cout << "û��ѡ���˸ÿγ̵�ͬѧ" << endl;
        return;
    }
    for (auto& i : *ii) {
        cout << " ѧ��id��" << i.nStudentID << "    �γ̷�����" << i.nCourseMark << endl;
    }
    //if (ii->begin() != ii->end()) {
    //    cout << (*(ii->end())).nStudentID << "   " << (*(ii->end())).nCourseMark << endl;
    //}
}

//(15) ͨ��ѧ��ID��ѯ��ѧ��ѡ�޵Ŀγ���Ϣ
void StudentIDCouFind(size_t nStudentID) {
    if (nStudentID > GetStuID()) {
        cout << "û�и�ѧ��" << endl;
        return;
    }
    auto aStuFind = tStudentID.Find(nStudentID);
    if (aStuFind == nullptr) {
        cout << "û�и�ѧ��" << endl;
        return;
    }
    auto stucou = aStuFind->m_list;
    if (stucou->IsEmpty()) {
        cout << "û�м�¼" << endl;
        return;
    }
    for (auto& i : *stucou) {
        cout << "  �γ�id��" << i.nCourseID << "   �γ̷�����" << i.nCourseMark << endl;
    }
}









































