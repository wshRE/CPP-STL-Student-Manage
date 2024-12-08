#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <fstream>
#include <time.h>
#include"Manange.h"
using namespace std;
int nnameID = 1;  //id
int nCourseID = 1;//id
void FileInit() {
    ifstream infile;
    ifstream infileOne;
    ifstream infileTwo;
    char a[100] = { 0 };
    char b[100] = { 0 };
    //-------------------学号     100791
    //读学生名单并录入
    infile.open("name.txt", ios::in | ios::out | ios::binary);
    if (!infile.is_open()) {
        return ;
    }
    //空格划分
    while (infile >> a ) {
        StudentInitAdd(a,nnameID++);
        //cout << nnameID - 1 << "  " << a << endl;
    }

    //--------------课程  996
    infileOne.open("course.txt", ios::in | ios::out | ios::binary);
    if (!infileOne.is_open()) {
        return ;
    }
    while (infileOne.getline(b, 100, '\n'))
    {
        b[strlen(b) - 1] = '\0';
        CourseInitAdd(b, nCourseID++);
        //cout << nCourseID-1 << " " << b << endl;
    }

    //--------------选课记录----100w
    //infileTwo.open("mark100w.txt", ios::in | ios::out | ios::binary);
    //if (!infileTwo.is_open()) {
    //    return;
    //}
    ////空格划分
    //int nStuID;
    //int nCouID;
    //int nMark;
    //while (infileTwo >> nStuID >> nCouID >> nMark) {
    //    CourseRecord(nStuID, nCouID, nMark);
    //    //cout << nStuID << " " << nCouID << " " << nMark << endl;
    //}
    //----------------
    int nStuID;
    int nCouID;
    int nMark;
    int nAddress;
    FILE* ft = fopen("DicChoose.bin", "rb+");
    //获取仓库大小
    fseek(ft, 0, SEEK_END);
    int ftFileSize = ftell(ft);
    rewind(ft);
    //循环
    for (int i = 0; i < ftFileSize / (sizeof(int) * 3); i++) { //每次拷贝一个结构体
        nAddress = ftell(ft);
        if (fread(&nStuID, sizeof(int), 1, ft) < 1) { //读到哪,读多少,几个,文件指针
            if (feof(ft)) {  //是否到了文件尾
                break;//到了文件尾
            }
        }
        fread(&nCouID, sizeof(int), 1, ft);
        fread(&nMark, sizeof(int), 1, ft);
        CourseRecord(nStuID, nCouID, nMark,nAddress);//插入
    }
    fclose(ft);

    system("pause");
}


//插入新的选课记录---返回偏移
int ChooseInsert(int nStuID, int nCouID, int nMark) {
    FILE* fp = fopen("DicChoose.bin", "rb+");
    fseek(fp, 0, SEEK_END);//移动到末尾
    int nAddress = ftell(fp);
    fwrite(&nStuID, sizeof(int), 1, fp);
    fwrite(&nCouID, sizeof(int), 1, fp);
    fwrite(&nMark, sizeof(int), 1, fp);
    fclose(fp);
    return nAddress;
}

//修改
void ChooseChange(int nAddress, int nStuID, int nCouID, int nMark) {
    FILE* fp = fopen("DicChoose.bin", "rb+");
    fseek(fp, nAddress, SEEK_SET);   //跳转位置
    fwrite(&nStuID, sizeof(int), 1, fp);
    fwrite(&nCouID, sizeof(int), 1, fp);
    fwrite(&nMark, sizeof(int), 1, fp);
    fclose(fp);
    return;
}


int GetNewStuID() {
    return nnameID++;
}

int GetNewCouID() {
    return nCourseID++;
}
int GetStuID() {
    return nnameID-1;
}
int GetCouID() {
    return nCourseID - 1;
}