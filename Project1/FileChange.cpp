#include<iostream>
#include <fstream>
#include <time.h>
#include"Manange.h"
using namespace std;
//学生相关
    //学生添加
//int StudentFileAdd(char cStudentName[]) {//偏移
//    fstream fout;
//    fout.open("name.txt", fstream::binary | fstream::out | fstream::in );
//    fout.seekg(0, ios::end);  //移动到文件末尾
//    int nOffset = fout.tellg();//获取文件位置
//    //写入
//    fout << endl;
//    fout << cStudentName << endl;
//    return nOffset;
//}

////用空格覆盖
//void StudentFileDel(int nOffset) {
//    fstream fout;
//    fout.open("course.txt", fstream::binary | fstream::out | fstream::in);
//}



//课程相关

    //课程添加---写入数据并返回偏移
//int CourseFileAdd(char cCourseName[]) {//偏移
//    fstream fout;
//    fout.open("course.txt", fstream::binary | fstream::out | fstream::in);
//    fout.seekg(0, ios::end);  //移动到文件末尾
//    int nOffset = fout.tellg();//获取文件位置
//    //写入
//    fout << endl;
//    fout << cCourseName << endl;
//    return nOffset;
//}


//选课记录相关

    //选课记录添加
//int CourseChooseFileAdd(size_t nStudentID, size_t nCourseID, int nMark) {//偏移
//    fstream fout;
//    fout.open("mark100w.txt", fstream::binary | fstream::out | fstream::in);
//    fout.seekg(0, ios::end);  //移动到文件末尾
//    int nOffset = fout.tellg();//获取文件位置
//    //写入
//    fout << endl;
//    fout << nStudentID << " " << nCourseID << " " << nMark << endl;
//    return nOffset;
//}