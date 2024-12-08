#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include"Header.h"
#include <wchar.h>

char DicName[] = "Message.bin";  //学生存储文件名
char DicCouName[] = "CourseMessage.bin";  //课程存储文件名

char DicStore[] = "St.bin";   //当前学生存储结构体
char DicCouStore[] = "Ct.bin";  //当前课程存储结构体
char DicTemp[] = "Temp.bin";   //当前存储结构体

int nFile = 0; //0默认为学生  1为课程



void SetFile(int n) {
    nFile = n;
}

//打开文件
FILE* FileOpen(char* chDicName,const char* chNode) {
    FILE* pFile = NULL;
    pFile = fopen(chDicName, chNode);
    if (!pFile) {
        pFile = fopen(chDicName, "wb+");  //加b是指二进制写入
        FileClose(pFile);
        pFile = fopen(chDicName, chNode);
    }
    return pFile;
}


//关闭文件
void FileClose(FILE* pFile) {
    fclose(pFile);
}


//更新缓存
void FileFlush(FILE* pFile) {
    fflush(pFile);
}




//查找空间
int FileSpaceFind(int nSpaceNeed) {
    return Findspace(nSpaceNeed);  //查找空位
}


void  init() {
    FILE* fp = NULL;
    remove(DicName);
    remove(DicCouName);
    remove(DicTemp);
    remove(DicStore);
    remove(DicCouStore);
    fp = FileOpen(DicName, "wb+"); //读
    fclose(fp);
    fp = FileOpen(DicCouName, "wb+"); //读
    fclose(fp);
    fp = FileOpen(DicStore, "wb+"); //读
    fclose(fp);
    fp = FileOpen(DicCouStore, "wb+"); //读
    fclose(fp);
}

//查找空间
int Findspace(int nSpaceNeed) {
    int dwFileSize = 0;
    int i = 0;
    int nRe = 0;
    struct  tagStore tagstore = { 0 };
    FILE* pFile;
    if (nFile == 0) {
        pFile = FileOpen(DicStore, "rb+");//打开仓库文件
    }
    else {
        pFile = FileOpen(DicCouStore, "rb+");//打开仓库文件
    }
    //所有结构体之前－－－－－判断文件大小
    fseek(pFile, 0, SEEK_END);  //移动到文件末尾
    dwFileSize = ftell(pFile);//汇报当前指针位置,返回的是文件指针到文件头的总字节数,错误返回-1 
    rewind(pFile);//移到文件头,无返回值
    if (dwFileSize == 0) {
        FileClose(pFile);
        return 0;
    }
    fread(&tagstore, sizeof(tagstore), 1, pFile);
    if (tagstore.nStart >= nSpaceNeed) {  //第一个结构体之前有足够的空位
        FileClose(pFile);
        nRe = tagstore.nStart;
        return nRe;
    }
    //结构体之间
    int nLastEnd = tagstore.nEnd;  //上一个的结束位置
    for (i = 1; i < dwFileSize / sizeof(tagstore); i++) {  //循环所有
        fread(&tagstore, sizeof(tagstore), 1, pFile);
        if (tagstore.nStart - nLastEnd >= nSpaceNeed) {   //下一个的开始 - 上一个的结束 >=所需空间
            FileClose(pFile);
            return nLastEnd;
        }
        nLastEnd = tagstore.nEnd;
    }
    FileClose(pFile);
    return nLastEnd;
}


//结构体写入
void StructWirteIn(struct tagUserInput* taguserinput, int nWriteStart) {
    FILE* fp;
    if (nFile == 0) {
        fp = FileOpen(DicName, "rb+"); //读
    }
    else {
        fp = FileOpen(DicCouName, "rb+"); //读
    }

    fseek(fp, nWriteStart, SEEK_SET);   //跳转位置
    int nEnd = 0;

    //写入编号
    fwrite(&taguserinput->nNumber, sizeof(int), 1, fp);
    //写入名字长度
    fwrite(&taguserinput->nNameLength, sizeof(int), 1, fp);
    //写入名字
    fwrite(taguserinput->chName, taguserinput->nNameLength * 2, 1, fp);
    nEnd = ftell(fp);

    FileClose(fp);


    //更新仓库
    struct tagStore tagstore = { nWriteStart,nEnd,taguserinput->nNumber };
    StoreInsert(tagstore);
}


//写入仓库
void StoreInsert(struct tagStore tagstore) {
    size_t i = 0;
    FILE* fp;
    if (nFile == 0) {
        fp = FileOpen(DicStore, "rb+");//打开仓库文件
    }
    else {
        fp = FileOpen(DicCouStore, "rb+");//打开仓库文件
    }
    FILE* ft = FileOpen(DicTemp, "wb+"); //写
    struct tagStore tagTemp = { 0 };
    fseek(fp, 0, SEEK_END);  //移动到文件末尾
    int dwFileSize = ftell(fp);//汇报当前指针位置,返回的是文件指针到文件头的总字节数,错误返回-1 
    rewind(fp);//移到文件头,无返回值
    if (dwFileSize == 0 || tagstore.nStart == 0) {
        fwrite(&tagstore, sizeof(tagTemp), 1, ft);
    }
    for (i = 0; i < dwFileSize / sizeof(tagTemp); i++) { //每次拷贝一个结构体

        //读
        if (fread(&tagTemp, sizeof(tagTemp), 1, fp) < 1) { //读到哪,读多少,几个,文件指针
            if (feof(fp)) {  //是否到了文件尾
                break;//到了文件尾
            }
        }
        //写
        fwrite(&tagTemp, sizeof(tagTemp), 1, ft);//要写啥,写多少,写几个,写到哪
        //插入:
        if (tagstore.nStart == tagTemp.nEnd) {
            fwrite(&tagstore, sizeof(tagTemp), 1, ft);
        }
    }
    FileClose(fp);
    FileClose(ft);
    if (nFile == 0) {
        remove(DicStore);
        rename(DicTemp, DicStore);
    }
    else {
        remove(DicCouStore);
        rename(DicTemp, DicCouStore);
    }

    return;
}








//打印所有联系人
void PrinAllMessage() {
    size_t i = 0;
    int ftFileSize = 0;
    FILE* ft;
    if (nFile == 0) {
        ft = FileOpen(DicStore, "rb+");//打开仓库文件
    }
    else {
        ft = FileOpen(DicCouStore, "rb+");//打开仓库文件
    }
    struct tagStore tagTemp = { 0 };
    //获取仓库大小
    fseek(ft, 0, SEEK_END);
    ftFileSize = ftell(ft);
    rewind(ft);

    for (i = 0; i < ftFileSize / sizeof(tagTemp); i++) { //每次拷贝一个结构体
        //读
        if (fread(&tagTemp, sizeof(tagTemp), 1, ft) < 1) { //读到哪,读多少,几个,文件指针
            if (feof(ft)) {  //是否到了文件尾
                break;//到了文件尾
            }
        }
        FilePrin(tagTemp.nStart);
    }
    FileClose(ft);
}

//文件打印
void FilePrin(int nStart) {
    size_t i = 0;
    //获取结构体
    struct tagUserInput* taguserinput = (struct tagUserInput*)malloc(sizeof(tagUserInput) + 1);
    FILE* fp;
    if (nFile == 0) {
        fp = FileOpen(DicName, "rb+"); //读
    }
    else {
        fp = FileOpen(DicCouName, "rb+"); //读
    }
    fseek(fp, nStart, SEEK_SET);        //跳转
    fread(&taguserinput->nNumber, sizeof(int), 1, fp);
    //读取
    fread(&taguserinput->nNameLength, sizeof(int), 1, fp);
    fgetws(taguserinput->chName, taguserinput->nNameLength + 1, fp);  //成功
        //结果打印
    printf("编号:%d    ", taguserinput->nNumber);
    printf("名字长度:%d       ", taguserinput->nNameLength);
    wprintf(L"名字:%s        ", taguserinput->chName);
}


//联系人查找
struct tagUserInput* FileFindByStart(int nStart) {
    size_t i = 0;
    //获取结构体
    struct tagUserInput* taguserinput = (struct tagUserInput*)malloc(sizeof(tagUserInput) + 1);
    FILE* fp;
    if (nFile == 0) {
        fp = FileOpen(DicName, "rb+"); //读
    }
    else {
        fp = FileOpen(DicCouName, "rb+"); //读
    }
    fseek(fp, nStart, SEEK_SET);        //跳转
    fread(&taguserinput->nNumber, sizeof(int), 1, fp);
    //读取
    fread(&taguserinput->nNameLength, sizeof(int), 1, fp);
    fgetws(taguserinput->chName, taguserinput->nNameLength + 1, fp);  //成功
    return taguserinput;
}

//模糊查找
void FindCharacter() {
    int nTempOne = 0;
    int nTempTwo = 0;
    struct tagUserInput* taguserinput = NULL;
    size_t i = 0;
    int ftFileSize = 0;                     //仓库大小
    wchar_t chCharacter[100];                //子
    FILE* fp;
    FILE* ft;
    if (nFile == 0) {
        fp = FileOpen(DicName, "rb+"); //读
        ft = FileOpen(DicStore, "rb+"); //仓库
    }
    else {
        fp = FileOpen(DicCouName, "rb+"); //读
        ft = FileOpen(DicCouStore, "rb+"); //仓库
    }

    struct tagStore tagTemp = { 0 };
    printf("输入待查找的子串");
    wscanf(L"%100s", chCharacter);
    //获取仓库大小
    fseek(ft, 0, SEEK_END);
    ftFileSize = ftell(ft);
    rewind(ft);
    if (ftFileSize == 0) {
        printf("当前仓库为空\r\n");
        FileClose(fp);
        FileClose(ft);
        return;
    }
    for (i = 0; i < ftFileSize / sizeof(tagTemp); i++) { //每次拷贝一个结构体
        nTempTwo = 0;
        nTempOne = 0;
        //读
        if (fread(&tagTemp, sizeof(tagTemp), 1, ft) < 1) { //读到哪,读多少,几个,文件指针
            if (feof(ft)) {  //是否到了文件尾
                break;//到了文件尾
            }
        }
        taguserinput = FileFindByStart(tagTemp.nStart);  //获取结构体
        if (wcsstr(taguserinput->chName, chCharacter)) {
            printf("编号:%d    ", taguserinput->nNumber);
            printf("名字长度:%d       ", taguserinput->nNameLength);
            wprintf(L"名字:%s        ", taguserinput->chName);
        }
        //free(taguserinput);//未经过验证
    }
    FileClose(fp);
    FileClose(ft);

}




//通过编号查询
struct tagUserInput* FindMessageByNumber(int nNumber) {
    struct  tagStore tagstore = FindStoreByNumber(nNumber);  //仓库查找
    struct tagUserInput* taguserinput = FileFindByStart(tagstore.nStart);    //获取结构体
    return taguserinput;  //返回结构体
}


//通过编号查询仓库
struct tagStore FindStoreByNumber(int nNumber) {
    size_t i = 0;
    FILE* fp;
    if (nFile == 0) {
        fp = FileOpen(DicStore, "rb+");//打开仓库文件
    }
    else {
        fp = FileOpen(DicCouStore, "rb+");//打开仓库文件
    }
    struct tagStore tagTemp = { 0 };

    fseek(fp, 0, SEEK_END);  //移动到文件末尾
    int dwFileSize = ftell(fp);//汇报当前指针位置,返回的是文件指针到文件头的总字节数,错误返回-1 
    rewind(fp);//移到文件头,无返回值

    for (i = 0; i < dwFileSize / sizeof(tagTemp); i++) { //每次拷贝一个结构体
        //读
        if (fread(&tagTemp, sizeof(tagTemp), 1, fp) < 1) { //读到哪,读多少,几个,文件指针
            if (feof(fp)) {  //是否到了文件尾
                break;//到了文件尾
            }
        }
        if (tagTemp.nNumber == nNumber) {
            FileClose(fp);
            return tagTemp;
        }
    }
    FileClose(fp);
}



//仓库删除
void StoreDelete(int nNumber) {
    size_t i = 0;
    FILE* fp;
    if (nFile == 0) {
        fp = FileOpen(DicStore, "rb+");//打开仓库文件
    }
    else {
        fp = FileOpen(DicCouStore, "rb+");//打开仓库文件
    }
    FILE* ft = FileOpen(DicTemp, "wb+"); //写
    struct tagStore tagTemp = { 0 };

    fseek(fp, 0, SEEK_END);  //移动到文件末尾
    int dwFileSize = ftell(fp);//汇报当前指针位置,返回的是文件指针到文件头的总字节数,错误返回-1 
    rewind(fp);//移到文件头,无返回值

    for (i = 0; i < dwFileSize / sizeof(tagTemp); i++) { //每次拷贝一个结构体
        //读
        if (fread(&tagTemp, sizeof(tagTemp), 1, fp) < 1) { //读到哪,读多少,几个,文件指针
            if (feof(fp)) {  //是否到了文件尾
                break;//到了文件尾
            }
        }
        if (tagTemp.nNumber != nNumber) {
            //写
            fwrite(&tagTemp, sizeof(tagTemp), 1, ft);//要写啥,写多少,写几个,写到哪
        }

    }
    FileClose(fp);
    FileClose(ft);
    if (nFile == 0) {
        remove(DicStore);
        rename(DicTemp, DicStore);
    }
    else {
        remove(DicCouStore);
        rename(DicTemp, DicCouStore);
    }

}





//存储区打印
void StorePrin() {
    int j = 0;
    size_t i = 0;
    int ftFileSize = 0;
    FILE* ft;
    if (nFile == 0) {
        ft = FileOpen(DicStore, "rb+");//打开仓库文件
    }
    else {
        ft = FileOpen(DicCouStore, "rb+");//打开仓库文件
    }
    struct tagUserInput* taguserinput = NULL;
    struct tagStore tagTempLast = { 0 };
    struct tagStore tagTempNext = { 0 };
    //获取仓库大小
    fseek(ft, 0, SEEK_END);
    ftFileSize = ftell(ft);
    rewind(ft);
    if (ftFileSize == 0) {
        FileClose(ft);
        printf("当前存储空\r\n");
    }
    //遍历仓库
    fread(&tagTempLast, sizeof(tagTempLast), 1, ft);
    if (tagTempLast.nStart > 0) {
        printf("F[0,%d) , ", tagTempLast.nStart);
    }
    printf("U[%d,%d) , ", tagTempLast.nStart, tagTempLast.nEnd);
    for (i = 1; i < ftFileSize / sizeof(tagTempLast); i++) { //每次拷贝一个结构体
        //读
        if (fread(&tagTempNext, sizeof(tagTempNext), 1, ft) < 1) { //读到哪,读多少,几个,文件指针
            if (feof(ft)) {  //是否到了文件尾
                break;//到了文件尾
            }
        }
        //打印
        if (tagTempLast.nEnd != tagTempNext.nStart) {
            printf("F[%d,%d) , ", tagTempLast.nEnd, tagTempNext.nStart);

        }
        printf("U[%d,%d) , ", tagTempNext.nStart, tagTempNext.nEnd);
        tagTempLast = tagTempNext; //last更新到现在
    }
    printf("\r\n");
    FileClose(ft);
}






//调整
void Arrange() {
    size_t i = 0;
    int ftFileSize = 0;
    FILE* ft;
    if (nFile == 0) {
        ft = FileOpen(DicStore, "rb+");//打开仓库文件
    }
    else {
        ft = FileOpen(DicCouStore, "rb+");//打开仓库文件
    }
    FILE* fp = FileOpen(DicTemp, "wb+"); //临时 写
    struct tagStore tagTempLast = { 0 };
    struct tagStore tagTempNext = { 0 };

    //获取仓库大小
    fseek(ft, 0, SEEK_END);
    ftFileSize = ftell(ft);
    rewind(ft);

    //遍历仓库
    fread(&tagTempLast, sizeof(tagTempLast), 1, ft);
    if (tagTempLast.nStart != 0)
    {
        FileArrange(tagTempLast.nNumber, 0);
        tagTempLast.nEnd = tagTempLast.nEnd - tagTempLast.nStart;
        tagTempLast.nStart = 0;
    }
    fwrite(&tagTempLast, sizeof(tagTempNext), 1, fp);  //写入
    for (i = 1; i < ftFileSize / sizeof(tagTempNext); i++) { //每次拷贝一个结构体
        //读
        if (fread(&tagTempNext, sizeof(tagTempNext), 1, ft) < 1) { //读到哪,读多少,几个,文件指针
            if (feof(ft)) {  //是否到了文件尾
                break;//到了文件尾
            }
        }
        if (tagTempLast.nEnd != tagTempNext.nStart) {
            //跳转到调整 
            FileArrange(tagTempNext.nNumber, tagTempLast.nEnd);

            //重写仓库
            tagTempNext.nEnd = tagTempNext.nEnd - (tagTempNext.nStart - tagTempLast.nEnd);
            tagTempNext.nStart = tagTempLast.nEnd;

        }
        fwrite(&tagTempNext, sizeof(tagTempNext), 1, fp);
        tagTempLast = tagTempNext; //last更新到现在
    }
    FileClose(ft);
    FileClose(fp);
    if (nFile == 0) {
        remove(DicStore);
        rename(DicTemp, DicStore);
    }
    else {
        remove(DicCouStore);
        rename(DicTemp, DicCouStore);
    }

}





//文件调整
void FileArrange(int nNumber, int nStart) {
    size_t i = 0;
    //获取结构体
    struct tagUserInput* taguserinput = FindMessageByNumber(nNumber);
    //StructWirteIn(taguserinput, nStart);
    FILE* fp;
    if (nFile == 0) {
        fp = FileOpen(DicName, "rb+"); //读
    }
    else {
        fp = FileOpen(DicCouName, "rb+"); //读
    }
    fseek(fp, nStart, SEEK_SET);   //跳转位置
    int nEnd = 0;

    //写入编号
    fwrite(&taguserinput->nNumber, sizeof(int), 1, fp);
    //写入名字长度
    fwrite(&taguserinput->nNameLength, sizeof(int), 1, fp);
    //写入名字
    fwrite(taguserinput->chName, taguserinput->nNameLength * 2, 1, fp);
    nEnd = ftell(fp);

    FileClose(fp);

    //跳转 编号调整

}


//结构体修改  
void StructChange(struct tagStore  tagstore, struct tagUserInput* taguserinput) {
    int nLocal = 0;
    struct tagUserInput* taguserinputbefore = FindMessageByNumber(tagstore.nNumber);
    //检查本地有无空间
    if (spaceCheck(tagstore, taguserinput->nNameLength * 2 + 8) == 1) {
        StoreDelete(tagstore.nNumber);
        StructWirteIn(taguserinput, tagstore.nStart);
    }
    else {
        StoreDelete(tagstore.nNumber);
        //查找空位
        nLocal = FileSpaceFind(taguserinput->nNameLength * 2 + 8);
        //文件写入
        StructWirteIn(taguserinput, nLocal);
    }
    free(taguserinputbefore);
}

//空间检查 输入: 目标仓库, 需要的长度
int spaceCheck(struct tagStore  tagstoreInput, int nSpaceNeed) {
    int nLastStart = 0;
    int nNextStart = 0;
    int dwFileSize = 0;
    int i = 0;
    struct tagStore tagstoreLast = { 0 };
    struct tagStore tagstoreNext = { 0 };
    FILE* pFile;
    if (nFile == 0) {
        pFile = FileOpen(DicStore, "rb+");
    }
    else {
        pFile = FileOpen(DicCouStore, "rb+");
    }
    //所有结构体之前－－－－－判断文件大小
    fseek(pFile, 0, SEEK_END);  //移动到文件末尾
    dwFileSize = ftell(pFile);//汇报当前指针位置,返回的是文件指针到文件头的总字节数,错误返回-1 
    rewind(pFile);//移到文件头,无返回值

    //只有存一个
    if (dwFileSize / sizeof(tagstoreLast) == 1) {
        FileClose(pFile);
        return 1;
    }
    //存放两个
    if (dwFileSize / sizeof(tagstoreLast) == 2) {
        fread(&tagstoreLast, sizeof(tagstoreLast), 1, pFile);  //前一个赋值
        fread(&tagstoreNext, sizeof(tagstoreLast), 1, pFile);//后一个赋值
        FileClose(pFile);
        if (tagstoreNext.nNumber == tagstoreInput.nNumber) {
            return 1;
        }
        if (tagstoreNext.nStart >= nSpaceNeed) {
            return 1;
        }
        return -1;
    }
    for (i = 2; i < dwFileSize / sizeof(tagstoreLast); i++) {  //循环所有
        fread(&tagstoreNext, sizeof(tagstoreLast), 1, pFile);  //拷贝
        //相同
        if (tagstoreNext.nNumber == tagstoreInput.nNumber) {
            if (i + 1 == dwFileSize / sizeof(tagstoreLast)) { //最后一个
                FileClose(pFile);
                return 1;
            }
            fread(&tagstoreNext, sizeof(tagstoreLast), 1, pFile);//往前走一部
            if (tagstoreNext.nStart - tagstoreLast.nEnd >= nSpaceNeed) {
                FileClose(pFile);
                return 1;
            }
            FileClose(pFile);
            return -1;
        }
        //不同
        tagstoreLast = tagstoreNext;
    }
    FileClose(pFile);
    return -1;
}