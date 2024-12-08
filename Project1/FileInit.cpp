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
    //-------------------ѧ��     100791
    //��ѧ��������¼��
    infile.open("name.txt", ios::in | ios::out | ios::binary);
    if (!infile.is_open()) {
        return ;
    }
    //�ո񻮷�
    while (infile >> a ) {
        StudentInitAdd(a,nnameID++);
        //cout << nnameID - 1 << "  " << a << endl;
    }

    //--------------�γ�  996
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

    //--------------ѡ�μ�¼----100w
    //infileTwo.open("mark100w.txt", ios::in | ios::out | ios::binary);
    //if (!infileTwo.is_open()) {
    //    return;
    //}
    ////�ո񻮷�
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
    //��ȡ�ֿ��С
    fseek(ft, 0, SEEK_END);
    int ftFileSize = ftell(ft);
    rewind(ft);
    //ѭ��
    for (int i = 0; i < ftFileSize / (sizeof(int) * 3); i++) { //ÿ�ο���һ���ṹ��
        nAddress = ftell(ft);
        if (fread(&nStuID, sizeof(int), 1, ft) < 1) { //������,������,����,�ļ�ָ��
            if (feof(ft)) {  //�Ƿ����ļ�β
                break;//�����ļ�β
            }
        }
        fread(&nCouID, sizeof(int), 1, ft);
        fread(&nMark, sizeof(int), 1, ft);
        CourseRecord(nStuID, nCouID, nMark,nAddress);//����
    }
    fclose(ft);

    system("pause");
}


//�����µ�ѡ�μ�¼---����ƫ��
int ChooseInsert(int nStuID, int nCouID, int nMark) {
    FILE* fp = fopen("DicChoose.bin", "rb+");
    fseek(fp, 0, SEEK_END);//�ƶ���ĩβ
    int nAddress = ftell(fp);
    fwrite(&nStuID, sizeof(int), 1, fp);
    fwrite(&nCouID, sizeof(int), 1, fp);
    fwrite(&nMark, sizeof(int), 1, fp);
    fclose(fp);
    return nAddress;
}

//�޸�
void ChooseChange(int nAddress, int nStuID, int nCouID, int nMark) {
    FILE* fp = fopen("DicChoose.bin", "rb+");
    fseek(fp, nAddress, SEEK_SET);   //��תλ��
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