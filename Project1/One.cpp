#include"TreeKV.h"
#include"CString.h"
#include<iostream>
#include"Manange.h"
#include"Header.h"
int PrinAdd() {
    int nChoose;
    cout << "(1)新增学生(ID, 名字)" << endl ;
    cout << "(2)新增课程(ID,名字)" << endl ;
    cout << "(3)新增选课记录(学生ID, 课程ID, 分数) " << endl ;
    cin >> nChoose;
    return nChoose;
}
int PrinDel() {
    int nChoose;
    cout << "(4) 删除学生(ID) " << endl;
    cout << "(5) 删除课程(ID) " << endl;
    cout << "(6) 删除选课记录(学生ID, 课程ID) " << endl;
    cin >> nChoose;
    return nChoose;
}
int PrinCha() {
    int nChoose;
    cout << "(7) 改学生名字 " << endl;
    cout << "(8) 改课程名字 " << endl;
    cout << "(9) 改学生成绩 " << endl;
    cin >> nChoose;
    return nChoose;
}
int PrinFind() {
    int nChoose;
    cout << "(10) 通过学生ID查询学生姓名 " << endl;
    cout << "(11) 通过学生姓名查询学生ID " << endl;
    cout << "(12) 通过课程ID查询课程名 " << endl;
    cout << "(13) 通过课程名查询课程ID " << endl;
    cout << "(14) 通过课程ID查询选修了该课程的学生以及成绩 " << endl;
    cout << "(15) 通过学生ID查询该学生选修的课程信息  " << endl;
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
            "                1.增                   ",
            "                2.删                   ",
            "                3.改                   ",
            "                4.查                   ",
            "                0.退出                 ",
            "---------------------------------------",
            "---------------------------------------",
            "请选择使用的功能："
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
    //文件初始化
    //init();
    cout << "初始化中....." << endl;
    FileInit();
    system("cls");
    while (1) {
        fflush(stdin);
        switch (prin())  //分支选择
        {
        case 0:
            fflush(stdin);
            printf("退出系统\n");
            system("pause");
            return 0;
        //新增学生（ID 名字）
        case 1:
            fflush(stdin);
            cout << "学生姓名：" << endl;
            cin >> cStudentName;
            //cout << "学生ID：" << endl;
            //cin >> nStudentID;
            nStudentID = GetNewStuID();
            StudentAdd(cStudentName, nStudentID);
            break;
        //(2)新增课程(ID, 名字)
        case 2:
            fflush(stdin);
            cout << "课程姓名：" << endl;
            cin >> cCourseName;
            //cout << "课程ID：" << endl;
            //cin >> nCourseID;
            nCourseID = GetNewCouID();
            CourseAdd (cCourseName, nCourseID);
            break;
        //(3)新增选课记录(学生ID, 课程ID, 分数)
        case 3:
            fflush(stdin);
            cout << "课程ID：" << endl;
            cin >> nCourseID;
            cout << "学生ID：" << endl;
            cin >> nStudentID;
            cout << "分数" << endl;
            cin >> nMark;
            CourseRecord(nStudentID, nCourseID, nMark,-1);
            break;
        //(4) 删除学生(ID)
        case 4:
            fflush(stdin);
            cout << "学生ID：" << endl;
            cin >> nStudentID;
            StudentDel(nStudentID);
            break;
        //(5) 删除课程(ID)
        case 5:
            fflush(stdin);
            cout << "课程ID：" << endl;
            cin >> nCourseID;
            CourseDel(nCourseID);
            break;
        //(6) 删除选课记录(学生ID, 课程ID)
        case 6:
            fflush(stdin);
            cout << "课程ID：" << endl;
            cin >> nCourseID;
            cout << "学生ID：" << endl;
            cin >> nStudentID;
            CourseRecordDel(nStudentID, nCourseID);
            break;
        //(7) 改学生名字
        case 7:
            fflush(stdin);
            cout << "学生ID：" << endl;
            cin >> nStudentID;
            cout << "新学生姓名：" << endl;
            cin >> cStudentName;
            StudentNameChange(nStudentID, cStudentName);
            break;
        //(8) 改课程名字
        case 8:
            fflush(stdin);
            cout << "课程ID：" << endl;
            cin >> nCourseID;
            cout << "课程姓名：" << endl;
            cin >> cCourseName;
            CourseNameChange(nCourseID, cCourseName);
            break;
        //(9) 改学生成绩
        case 9:
            fflush(stdin);
            cout << "学生ID：" << endl;
            cin >> nStudentID;
            cout << "课程ID：" << endl;
            cin >> nCourseID;
            cout << "新分数" << endl;
            cin >> nMark;
            CourseMarkChange(nStudentID, nCourseID, nMark);
            break;
        //(10) 通过学生ID查询学生姓名
        case 10:
            fflush(stdin);
            cout << "学生ID：" << endl;
            cin >> nStudentID;
            StudentNameFind( nStudentID);
            system("pause");
            break;
        //(11) 通过学生姓名查询学生ID
        case 11:
            fflush(stdin);
            cout << "学生姓名：" << endl;
            cin >> cStudentName;
            StudentIDFind(cStudentName);
            system("pause");
            break;
        //(12) 通过课程ID查询课程名
        case 12:
            fflush(stdin);
            cout << "课程ID：" << endl;
            cin >> nCourseID;
            CourseNameFind( nCourseID);
            system("pause");
            break;
        //(13) 通过课程名查询课程ID
        case 13:
            fflush(stdin);
            rewind(stdin);
            cout << "课程姓名：" << endl;
            cin.get(cCourseName, 100);
            //cin >> cCourseName;
            CourseIDFind( cCourseName);
            system("pause");
            break;
        //(14) 通过课程ID查询选修了该课程的学生以及成绩
        case 14:
            fflush(stdin);
            cout << "课程ID：" << endl;
            cin >> nCourseID;
            CourseIDStuFind(nCourseID);
            system("pause");
            break;
        //(15) 通过学生ID查询该学生选修的课程信息
        case 15:
            fflush(stdin);
            cout << "学生ID：" << endl;
            cin >> nStudentID;
            StudentIDCouFind(nStudentID);
            system("pause");
            break;
        default:
            fflush(stdin);
            printf("输出错误，系统退出\n");
            system("pause");
            return 0;
        }
    }
}