#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include"Header.h"
#include <string.h>
using namespace std;
//文件内增加
void FileAddStruct(char name[100], int nID, int nFile) {
    setlocale(LC_ALL, "zh-CN");
    SetFile(nFile);
    int nLocal = 0;
    struct tagUserInput* taguserinput = (struct tagUserInput*)malloc(sizeof(wchar_t) * 400 + sizeof(int) * 4);
    mbstowcs(taguserinput->chName, name, strlen(name) * 2);

    // 写入时 tag->nNameLength *2  获取时 tag->nNameLength+1
    taguserinput->nNameLength = sizeof(wchar_t) * wcslen(taguserinput->chName) / 2;
    // 写入时 tag->nPhoneLength *2  获取时 tag->nPhoneLength+1

    //装入结构体----匹配编号 ------------编号，接口待匹配
    taguserinput->nNumber = nID;

    //查找空位
    nLocal = FileSpaceFind(taguserinput->nNameLength * 2 + 8);
    //文件写入
    StructWirteIn(taguserinput, nLocal);

    free(taguserinput);

}








//通过编号修改
void FileChangeStruct(char name[], int nNumber, int nFile) {
    setlocale(LC_ALL, "zh-CN");
    SetFile(nFile);
    struct tagUserInput* taguserinput = (struct tagUserInput*)malloc(sizeof(tagUserInput) + 1);
    struct tagStore  tagstore = { 0 };
    mbstowcs(taguserinput->chName, name, strlen(name) * 2);
    taguserinput->nNameLength = sizeof(wchar_t) * wcslen(taguserinput->chName) / 2; // 写入时 tag->nNameLength *2  获取时 tag->nNameLength+1
    taguserinput->nNumber = nNumber;

    ////编号查找仓库
    tagstore = FindStoreByNumber(nNumber);
    StructChange(tagstore, taguserinput);
}



//打印所有联系人
void MessagePrin(int nFile) {
    setlocale(LC_ALL, "zh-CN");
    SetFile(nFile);
    PrinAllMessage();
}




//通过编号查询
struct tagUserInput* FindByNumber(int nNumber, int nFile) {
    setlocale(LC_ALL, "zh-CN");
    SetFile(nFile);
    return FindMessageByNumber(nNumber);
}



//通过编号删除
void FileDelStruct(int nNumber, int nFile) {
    setlocale(LC_ALL, "zh-CN");
    SetFile(nFile);
    StoreDelete(nNumber);
}


//整理
//void Sort() {
//    setlocale(LC_ALL, "zh-CN");
//    Arrange();
//}

