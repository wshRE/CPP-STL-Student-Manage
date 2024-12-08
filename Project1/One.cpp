#include"TreeKV.h"
#include"CString.h"
#include<iostream>
#include"Manange.h"
#include"Header.h"
int PrinAdd() {
    int nChoose;
    cout << "(1)����ѧ��(ID, ����)" << endl ;
    cout << "(2)�����γ�(ID,����)" << endl ;
    cout << "(3)����ѡ�μ�¼(ѧ��ID, �γ�ID, ����) " << endl ;
    cin >> nChoose;
    return nChoose;
}
int PrinDel() {
    int nChoose;
    cout << "(4) ɾ��ѧ��(ID) " << endl;
    cout << "(5) ɾ���γ�(ID) " << endl;
    cout << "(6) ɾ��ѡ�μ�¼(ѧ��ID, �γ�ID) " << endl;
    cin >> nChoose;
    return nChoose;
}
int PrinCha() {
    int nChoose;
    cout << "(7) ��ѧ������ " << endl;
    cout << "(8) �Ŀγ����� " << endl;
    cout << "(9) ��ѧ���ɼ� " << endl;
    cin >> nChoose;
    return nChoose;
}
int PrinFind() {
    int nChoose;
    cout << "(10) ͨ��ѧ��ID��ѯѧ������ " << endl;
    cout << "(11) ͨ��ѧ��������ѯѧ��ID " << endl;
    cout << "(12) ͨ���γ�ID��ѯ�γ��� " << endl;
    cout << "(13) ͨ���γ�����ѯ�γ�ID " << endl;
    cout << "(14) ͨ���γ�ID��ѯѡ���˸ÿγ̵�ѧ���Լ��ɼ� " << endl;
    cout << "(15) ͨ��ѧ��ID��ѯ��ѧ��ѡ�޵Ŀγ���Ϣ  " << endl;
    cin >> nChoose;
    return nChoose;
}
int prin() {
    int i = 0;
    int nChoose = 0;
    system("cls");
    char a[15][50] = {
        "-------------------------------------------",
            "---------------------------------------",
            "                1.��                   ",
            "                2.ɾ                   ",
            "                3.��                   ",
            "                4.��                   ",
            "                0.�˳�                 ",
            "---------------------------------------",
            "---------------------------------------",
            "��ѡ��ʹ�õĹ��ܣ�"
    };
    for (i = 0; i < 10; i++) {
        printf("%s\r\n", a[i]);
    }
    fflush(stdin);
    cin >> nChoose;
    system("cls");
    if (nChoose == 0) {
        return 0;
    }else if (nChoose == 1) {
        return PrinAdd();
    }
    else if (nChoose == 2) {
        return PrinDel();
    }
    else if (nChoose == 3) {
        return  PrinCha();
    }
    else if(nChoose == 4) {
        return PrinFind();
    }
    else {
        return 20;
    }
}

int main() {
    size_t nStudentID;
    size_t nCourseID;
    char cStudentName[100] = {};
    char cCourseName[100] = {};
    int nMark;
    //�ļ���ʼ��
    //init();
    cout << "��ʼ����....." << endl;
    FileInit();
    system("cls");
    while (1) {
        fflush(stdin);
        switch (prin())  //��֧ѡ��
        {
        case 0:
            fflush(stdin);
            printf("�˳�ϵͳ\n");
            system("pause");
            return 0;
        //����ѧ����ID ���֣�
        case 1:
            fflush(stdin);
            cout << "ѧ��������" << endl;
            cin >> cStudentName;
            //cout << "ѧ��ID��" << endl;
            //cin >> nStudentID;
            nStudentID = GetNewStuID();
            StudentAdd(cStudentName, nStudentID);
            break;
        //(2)�����γ�(ID, ����)
        case 2:
            fflush(stdin);
            cout << "�γ�������" << endl;
            cin >> cCourseName;
            //cout << "�γ�ID��" << endl;
            //cin >> nCourseID;
            nCourseID = GetNewCouID();
            CourseAdd (cCourseName, nCourseID);
            break;
        //(3)����ѡ�μ�¼(ѧ��ID, �γ�ID, ����)
        case 3:
            fflush(stdin);
            cout << "�γ�ID��" << endl;
            cin >> nCourseID;
            cout << "ѧ��ID��" << endl;
            cin >> nStudentID;
            cout << "����" << endl;
            cin >> nMark;
            CourseRecord(nStudentID, nCourseID, nMark,-1);
            break;
        //(4) ɾ��ѧ��(ID)
        case 4:
            fflush(stdin);
            cout << "ѧ��ID��" << endl;
            cin >> nStudentID;
            StudentDel(nStudentID);
            break;
        //(5) ɾ���γ�(ID)
        case 5:
            fflush(stdin);
            cout << "�γ�ID��" << endl;
            cin >> nCourseID;
            CourseDel(nCourseID);
            break;
        //(6) ɾ��ѡ�μ�¼(ѧ��ID, �γ�ID)
        case 6:
            fflush(stdin);
            cout << "�γ�ID��" << endl;
            cin >> nCourseID;
            cout << "ѧ��ID��" << endl;
            cin >> nStudentID;
            CourseRecordDel(nStudentID, nCourseID);
            break;
        //(7) ��ѧ������
        case 7:
            fflush(stdin);
            cout << "ѧ��ID��" << endl;
            cin >> nStudentID;
            cout << "��ѧ��������" << endl;
            cin >> cStudentName;
            StudentNameChange(nStudentID, cStudentName);
            break;
        //(8) �Ŀγ�����
        case 8:
            fflush(stdin);
            cout << "�γ�ID��" << endl;
            cin >> nCourseID;
            cout << "�γ�������" << endl;
            cin >> cCourseName;
            CourseNameChange(nCourseID, cCourseName);
            break;
        //(9) ��ѧ���ɼ�
        case 9:
            fflush(stdin);
            cout << "ѧ��ID��" << endl;
            cin >> nStudentID;
            cout << "�γ�ID��" << endl;
            cin >> nCourseID;
            cout << "�·���" << endl;
            cin >> nMark;
            CourseMarkChange(nStudentID, nCourseID, nMark);
            break;
        //(10) ͨ��ѧ��ID��ѯѧ������
        case 10:
            fflush(stdin);
            cout << "ѧ��ID��" << endl;
            cin >> nStudentID;
            StudentNameFind( nStudentID);
            system("pause");
            break;
        //(11) ͨ��ѧ��������ѯѧ��ID
        case 11:
            fflush(stdin);
            cout << "ѧ��������" << endl;
            cin >> cStudentName;
            StudentIDFind(cStudentName);
            system("pause");
            break;
        //(12) ͨ���γ�ID��ѯ�γ���
        case 12:
            fflush(stdin);
            cout << "�γ�ID��" << endl;
            cin >> nCourseID;
            CourseNameFind( nCourseID);
            system("pause");
            break;
        //(13) ͨ���γ�����ѯ�γ�ID
        case 13:
            fflush(stdin);
            rewind(stdin);
            cout << "�γ�������" << endl;
            cin.get(cCourseName, 100);
            //cin >> cCourseName;
            CourseIDFind( cCourseName);
            system("pause");
            break;
        //(14) ͨ���γ�ID��ѯѡ���˸ÿγ̵�ѧ���Լ��ɼ�
        case 14:
            fflush(stdin);
            cout << "�γ�ID��" << endl;
            cin >> nCourseID;
            CourseIDStuFind(nCourseID);
            system("pause");
            break;
        //(15) ͨ��ѧ��ID��ѯ��ѧ��ѡ�޵Ŀγ���Ϣ
        case 15:
            fflush(stdin);
            cout << "ѧ��ID��" << endl;
            cin >> nStudentID;
            StudentIDCouFind(nStudentID);
            system("pause");
            break;
        default:
            fflush(stdin);
            printf("�������ϵͳ�˳�\n");
            system("pause");
            return 0;
        }
    }
}