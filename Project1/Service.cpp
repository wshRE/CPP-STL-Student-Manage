#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include"Header.h"
#include <string.h>
using namespace std;
//�ļ�������
void FileAddStruct(char name[100], int nID, int nFile) {
    setlocale(LC_ALL, "zh-CN");
    SetFile(nFile);
    int nLocal = 0;
    struct tagUserInput* taguserinput = (struct tagUserInput*)malloc(sizeof(wchar_t) * 400 + sizeof(int) * 4);
    mbstowcs(taguserinput->chName, name, strlen(name) * 2);

    // д��ʱ tag->nNameLength *2  ��ȡʱ tag->nNameLength+1
    taguserinput->nNameLength = sizeof(wchar_t) * wcslen(taguserinput->chName) / 2;
    // д��ʱ tag->nPhoneLength *2  ��ȡʱ tag->nPhoneLength+1

    //װ��ṹ��----ƥ���� ------------��ţ��ӿڴ�ƥ��
    taguserinput->nNumber = nID;

    //���ҿ�λ
    nLocal = FileSpaceFind(taguserinput->nNameLength * 2 + 8);
    //�ļ�д��
    StructWirteIn(taguserinput, nLocal);

    free(taguserinput);

}








//ͨ������޸�
void FileChangeStruct(char name[], int nNumber, int nFile) {
    setlocale(LC_ALL, "zh-CN");
    SetFile(nFile);
    struct tagUserInput* taguserinput = (struct tagUserInput*)malloc(sizeof(tagUserInput) + 1);
    struct tagStore  tagstore = { 0 };
    mbstowcs(taguserinput->chName, name, strlen(name) * 2);
    taguserinput->nNameLength = sizeof(wchar_t) * wcslen(taguserinput->chName) / 2; // д��ʱ tag->nNameLength *2  ��ȡʱ tag->nNameLength+1
    taguserinput->nNumber = nNumber;

    ////��Ų��Ҳֿ�
    tagstore = FindStoreByNumber(nNumber);
    StructChange(tagstore, taguserinput);
}



//��ӡ������ϵ��
void MessagePrin(int nFile) {
    setlocale(LC_ALL, "zh-CN");
    SetFile(nFile);
    PrinAllMessage();
}




//ͨ����Ų�ѯ
struct tagUserInput* FindByNumber(int nNumber, int nFile) {
    setlocale(LC_ALL, "zh-CN");
    SetFile(nFile);
    return FindMessageByNumber(nNumber);
}



//ͨ�����ɾ��
void FileDelStruct(int nNumber, int nFile) {
    setlocale(LC_ALL, "zh-CN");
    SetFile(nFile);
    StoreDelete(nNumber);
}


//����
//void Sort() {
//    setlocale(LC_ALL, "zh-CN");
//    Arrange();
//}

