#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include"Header.h"
#include <wchar.h>

char DicName[] = "Message.bin";  //ѧ���洢�ļ���
char DicCouName[] = "CourseMessage.bin";  //�γ̴洢�ļ���

char DicStore[] = "St.bin";   //��ǰѧ���洢�ṹ��
char DicCouStore[] = "Ct.bin";  //��ǰ�γ̴洢�ṹ��
char DicTemp[] = "Temp.bin";   //��ǰ�洢�ṹ��

int nFile = 0; //0Ĭ��Ϊѧ��  1Ϊ�γ�



void SetFile(int n) {
    nFile = n;
}

//���ļ�
FILE* FileOpen(char* chDicName,const char* chNode) {
    FILE* pFile = NULL;
    pFile = fopen(chDicName, chNode);
    if (!pFile) {
        pFile = fopen(chDicName, "wb+");  //��b��ָ������д��
        FileClose(pFile);
        pFile = fopen(chDicName, chNode);
    }
    return pFile;
}


//�ر��ļ�
void FileClose(FILE* pFile) {
    fclose(pFile);
}


//���»���
void FileFlush(FILE* pFile) {
    fflush(pFile);
}




//���ҿռ�
int FileSpaceFind(int nSpaceNeed) {
    return Findspace(nSpaceNeed);  //���ҿ�λ
}


void  init() {
    FILE* fp = NULL;
    remove(DicName);
    remove(DicCouName);
    remove(DicTemp);
    remove(DicStore);
    remove(DicCouStore);
    fp = FileOpen(DicName, "wb+"); //��
    fclose(fp);
    fp = FileOpen(DicCouName, "wb+"); //��
    fclose(fp);
    fp = FileOpen(DicStore, "wb+"); //��
    fclose(fp);
    fp = FileOpen(DicCouStore, "wb+"); //��
    fclose(fp);
}

//���ҿռ�
int Findspace(int nSpaceNeed) {
    int dwFileSize = 0;
    int i = 0;
    int nRe = 0;
    struct  tagStore tagstore = { 0 };
    FILE* pFile;
    if (nFile == 0) {
        pFile = FileOpen(DicStore, "rb+");//�򿪲ֿ��ļ�
    }
    else {
        pFile = FileOpen(DicCouStore, "rb+");//�򿪲ֿ��ļ�
    }
    //���нṹ��֮ǰ�����������ж��ļ���С
    fseek(pFile, 0, SEEK_END);  //�ƶ����ļ�ĩβ
    dwFileSize = ftell(pFile);//�㱨��ǰָ��λ��,���ص����ļ�ָ�뵽�ļ�ͷ�����ֽ���,���󷵻�-1 
    rewind(pFile);//�Ƶ��ļ�ͷ,�޷���ֵ
    if (dwFileSize == 0) {
        FileClose(pFile);
        return 0;
    }
    fread(&tagstore, sizeof(tagstore), 1, pFile);
    if (tagstore.nStart >= nSpaceNeed) {  //��һ���ṹ��֮ǰ���㹻�Ŀ�λ
        FileClose(pFile);
        nRe = tagstore.nStart;
        return nRe;
    }
    //�ṹ��֮��
    int nLastEnd = tagstore.nEnd;  //��һ���Ľ���λ��
    for (i = 1; i < dwFileSize / sizeof(tagstore); i++) {  //ѭ������
        fread(&tagstore, sizeof(tagstore), 1, pFile);
        if (tagstore.nStart - nLastEnd >= nSpaceNeed) {   //��һ���Ŀ�ʼ - ��һ���Ľ��� >=����ռ�
            FileClose(pFile);
            return nLastEnd;
        }
        nLastEnd = tagstore.nEnd;
    }
    FileClose(pFile);
    return nLastEnd;
}


//�ṹ��д��
void StructWirteIn(struct tagUserInput* taguserinput, int nWriteStart) {
    FILE* fp;
    if (nFile == 0) {
        fp = FileOpen(DicName, "rb+"); //��
    }
    else {
        fp = FileOpen(DicCouName, "rb+"); //��
    }

    fseek(fp, nWriteStart, SEEK_SET);   //��תλ��
    int nEnd = 0;

    //д����
    fwrite(&taguserinput->nNumber, sizeof(int), 1, fp);
    //д�����ֳ���
    fwrite(&taguserinput->nNameLength, sizeof(int), 1, fp);
    //д������
    fwrite(taguserinput->chName, taguserinput->nNameLength * 2, 1, fp);
    nEnd = ftell(fp);

    FileClose(fp);


    //���²ֿ�
    struct tagStore tagstore = { nWriteStart,nEnd,taguserinput->nNumber };
    StoreInsert(tagstore);
}


//д��ֿ�
void StoreInsert(struct tagStore tagstore) {
    size_t i = 0;
    FILE* fp;
    if (nFile == 0) {
        fp = FileOpen(DicStore, "rb+");//�򿪲ֿ��ļ�
    }
    else {
        fp = FileOpen(DicCouStore, "rb+");//�򿪲ֿ��ļ�
    }
    FILE* ft = FileOpen(DicTemp, "wb+"); //д
    struct tagStore tagTemp = { 0 };
    fseek(fp, 0, SEEK_END);  //�ƶ����ļ�ĩβ
    int dwFileSize = ftell(fp);//�㱨��ǰָ��λ��,���ص����ļ�ָ�뵽�ļ�ͷ�����ֽ���,���󷵻�-1 
    rewind(fp);//�Ƶ��ļ�ͷ,�޷���ֵ
    if (dwFileSize == 0 || tagstore.nStart == 0) {
        fwrite(&tagstore, sizeof(tagTemp), 1, ft);
    }
    for (i = 0; i < dwFileSize / sizeof(tagTemp); i++) { //ÿ�ο���һ���ṹ��

        //��
        if (fread(&tagTemp, sizeof(tagTemp), 1, fp) < 1) { //������,������,����,�ļ�ָ��
            if (feof(fp)) {  //�Ƿ����ļ�β
                break;//�����ļ�β
            }
        }
        //д
        fwrite(&tagTemp, sizeof(tagTemp), 1, ft);//Ҫдɶ,д����,д����,д����
        //����:
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








//��ӡ������ϵ��
void PrinAllMessage() {
    size_t i = 0;
    int ftFileSize = 0;
    FILE* ft;
    if (nFile == 0) {
        ft = FileOpen(DicStore, "rb+");//�򿪲ֿ��ļ�
    }
    else {
        ft = FileOpen(DicCouStore, "rb+");//�򿪲ֿ��ļ�
    }
    struct tagStore tagTemp = { 0 };
    //��ȡ�ֿ��С
    fseek(ft, 0, SEEK_END);
    ftFileSize = ftell(ft);
    rewind(ft);

    for (i = 0; i < ftFileSize / sizeof(tagTemp); i++) { //ÿ�ο���һ���ṹ��
        //��
        if (fread(&tagTemp, sizeof(tagTemp), 1, ft) < 1) { //������,������,����,�ļ�ָ��
            if (feof(ft)) {  //�Ƿ����ļ�β
                break;//�����ļ�β
            }
        }
        FilePrin(tagTemp.nStart);
    }
    FileClose(ft);
}

//�ļ���ӡ
void FilePrin(int nStart) {
    size_t i = 0;
    //��ȡ�ṹ��
    struct tagUserInput* taguserinput = (struct tagUserInput*)malloc(sizeof(tagUserInput) + 1);
    FILE* fp;
    if (nFile == 0) {
        fp = FileOpen(DicName, "rb+"); //��
    }
    else {
        fp = FileOpen(DicCouName, "rb+"); //��
    }
    fseek(fp, nStart, SEEK_SET);        //��ת
    fread(&taguserinput->nNumber, sizeof(int), 1, fp);
    //��ȡ
    fread(&taguserinput->nNameLength, sizeof(int), 1, fp);
    fgetws(taguserinput->chName, taguserinput->nNameLength + 1, fp);  //�ɹ�
        //�����ӡ
    printf("���:%d    ", taguserinput->nNumber);
    printf("���ֳ���:%d       ", taguserinput->nNameLength);
    wprintf(L"����:%s        ", taguserinput->chName);
}


//��ϵ�˲���
struct tagUserInput* FileFindByStart(int nStart) {
    size_t i = 0;
    //��ȡ�ṹ��
    struct tagUserInput* taguserinput = (struct tagUserInput*)malloc(sizeof(tagUserInput) + 1);
    FILE* fp;
    if (nFile == 0) {
        fp = FileOpen(DicName, "rb+"); //��
    }
    else {
        fp = FileOpen(DicCouName, "rb+"); //��
    }
    fseek(fp, nStart, SEEK_SET);        //��ת
    fread(&taguserinput->nNumber, sizeof(int), 1, fp);
    //��ȡ
    fread(&taguserinput->nNameLength, sizeof(int), 1, fp);
    fgetws(taguserinput->chName, taguserinput->nNameLength + 1, fp);  //�ɹ�
    return taguserinput;
}

//ģ������
void FindCharacter() {
    int nTempOne = 0;
    int nTempTwo = 0;
    struct tagUserInput* taguserinput = NULL;
    size_t i = 0;
    int ftFileSize = 0;                     //�ֿ��С
    wchar_t chCharacter[100];                //��
    FILE* fp;
    FILE* ft;
    if (nFile == 0) {
        fp = FileOpen(DicName, "rb+"); //��
        ft = FileOpen(DicStore, "rb+"); //�ֿ�
    }
    else {
        fp = FileOpen(DicCouName, "rb+"); //��
        ft = FileOpen(DicCouStore, "rb+"); //�ֿ�
    }

    struct tagStore tagTemp = { 0 };
    printf("��������ҵ��Ӵ�");
    wscanf(L"%100s", chCharacter);
    //��ȡ�ֿ��С
    fseek(ft, 0, SEEK_END);
    ftFileSize = ftell(ft);
    rewind(ft);
    if (ftFileSize == 0) {
        printf("��ǰ�ֿ�Ϊ��\r\n");
        FileClose(fp);
        FileClose(ft);
        return;
    }
    for (i = 0; i < ftFileSize / sizeof(tagTemp); i++) { //ÿ�ο���һ���ṹ��
        nTempTwo = 0;
        nTempOne = 0;
        //��
        if (fread(&tagTemp, sizeof(tagTemp), 1, ft) < 1) { //������,������,����,�ļ�ָ��
            if (feof(ft)) {  //�Ƿ����ļ�β
                break;//�����ļ�β
            }
        }
        taguserinput = FileFindByStart(tagTemp.nStart);  //��ȡ�ṹ��
        if (wcsstr(taguserinput->chName, chCharacter)) {
            printf("���:%d    ", taguserinput->nNumber);
            printf("���ֳ���:%d       ", taguserinput->nNameLength);
            wprintf(L"����:%s        ", taguserinput->chName);
        }
        //free(taguserinput);//δ������֤
    }
    FileClose(fp);
    FileClose(ft);

}




//ͨ����Ų�ѯ
struct tagUserInput* FindMessageByNumber(int nNumber) {
    struct  tagStore tagstore = FindStoreByNumber(nNumber);  //�ֿ����
    struct tagUserInput* taguserinput = FileFindByStart(tagstore.nStart);    //��ȡ�ṹ��
    return taguserinput;  //���ؽṹ��
}


//ͨ����Ų�ѯ�ֿ�
struct tagStore FindStoreByNumber(int nNumber) {
    size_t i = 0;
    FILE* fp;
    if (nFile == 0) {
        fp = FileOpen(DicStore, "rb+");//�򿪲ֿ��ļ�
    }
    else {
        fp = FileOpen(DicCouStore, "rb+");//�򿪲ֿ��ļ�
    }
    struct tagStore tagTemp = { 0 };

    fseek(fp, 0, SEEK_END);  //�ƶ����ļ�ĩβ
    int dwFileSize = ftell(fp);//�㱨��ǰָ��λ��,���ص����ļ�ָ�뵽�ļ�ͷ�����ֽ���,���󷵻�-1 
    rewind(fp);//�Ƶ��ļ�ͷ,�޷���ֵ

    for (i = 0; i < dwFileSize / sizeof(tagTemp); i++) { //ÿ�ο���һ���ṹ��
        //��
        if (fread(&tagTemp, sizeof(tagTemp), 1, fp) < 1) { //������,������,����,�ļ�ָ��
            if (feof(fp)) {  //�Ƿ����ļ�β
                break;//�����ļ�β
            }
        }
        if (tagTemp.nNumber == nNumber) {
            FileClose(fp);
            return tagTemp;
        }
    }
    FileClose(fp);
}



//�ֿ�ɾ��
void StoreDelete(int nNumber) {
    size_t i = 0;
    FILE* fp;
    if (nFile == 0) {
        fp = FileOpen(DicStore, "rb+");//�򿪲ֿ��ļ�
    }
    else {
        fp = FileOpen(DicCouStore, "rb+");//�򿪲ֿ��ļ�
    }
    FILE* ft = FileOpen(DicTemp, "wb+"); //д
    struct tagStore tagTemp = { 0 };

    fseek(fp, 0, SEEK_END);  //�ƶ����ļ�ĩβ
    int dwFileSize = ftell(fp);//�㱨��ǰָ��λ��,���ص����ļ�ָ�뵽�ļ�ͷ�����ֽ���,���󷵻�-1 
    rewind(fp);//�Ƶ��ļ�ͷ,�޷���ֵ

    for (i = 0; i < dwFileSize / sizeof(tagTemp); i++) { //ÿ�ο���һ���ṹ��
        //��
        if (fread(&tagTemp, sizeof(tagTemp), 1, fp) < 1) { //������,������,����,�ļ�ָ��
            if (feof(fp)) {  //�Ƿ����ļ�β
                break;//�����ļ�β
            }
        }
        if (tagTemp.nNumber != nNumber) {
            //д
            fwrite(&tagTemp, sizeof(tagTemp), 1, ft);//Ҫдɶ,д����,д����,д����
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





//�洢����ӡ
void StorePrin() {
    int j = 0;
    size_t i = 0;
    int ftFileSize = 0;
    FILE* ft;
    if (nFile == 0) {
        ft = FileOpen(DicStore, "rb+");//�򿪲ֿ��ļ�
    }
    else {
        ft = FileOpen(DicCouStore, "rb+");//�򿪲ֿ��ļ�
    }
    struct tagUserInput* taguserinput = NULL;
    struct tagStore tagTempLast = { 0 };
    struct tagStore tagTempNext = { 0 };
    //��ȡ�ֿ��С
    fseek(ft, 0, SEEK_END);
    ftFileSize = ftell(ft);
    rewind(ft);
    if (ftFileSize == 0) {
        FileClose(ft);
        printf("��ǰ�洢��\r\n");
    }
    //�����ֿ�
    fread(&tagTempLast, sizeof(tagTempLast), 1, ft);
    if (tagTempLast.nStart > 0) {
        printf("F[0,%d) , ", tagTempLast.nStart);
    }
    printf("U[%d,%d) , ", tagTempLast.nStart, tagTempLast.nEnd);
    for (i = 1; i < ftFileSize / sizeof(tagTempLast); i++) { //ÿ�ο���һ���ṹ��
        //��
        if (fread(&tagTempNext, sizeof(tagTempNext), 1, ft) < 1) { //������,������,����,�ļ�ָ��
            if (feof(ft)) {  //�Ƿ����ļ�β
                break;//�����ļ�β
            }
        }
        //��ӡ
        if (tagTempLast.nEnd != tagTempNext.nStart) {
            printf("F[%d,%d) , ", tagTempLast.nEnd, tagTempNext.nStart);

        }
        printf("U[%d,%d) , ", tagTempNext.nStart, tagTempNext.nEnd);
        tagTempLast = tagTempNext; //last���µ�����
    }
    printf("\r\n");
    FileClose(ft);
}






//����
void Arrange() {
    size_t i = 0;
    int ftFileSize = 0;
    FILE* ft;
    if (nFile == 0) {
        ft = FileOpen(DicStore, "rb+");//�򿪲ֿ��ļ�
    }
    else {
        ft = FileOpen(DicCouStore, "rb+");//�򿪲ֿ��ļ�
    }
    FILE* fp = FileOpen(DicTemp, "wb+"); //��ʱ д
    struct tagStore tagTempLast = { 0 };
    struct tagStore tagTempNext = { 0 };

    //��ȡ�ֿ��С
    fseek(ft, 0, SEEK_END);
    ftFileSize = ftell(ft);
    rewind(ft);

    //�����ֿ�
    fread(&tagTempLast, sizeof(tagTempLast), 1, ft);
    if (tagTempLast.nStart != 0)
    {
        FileArrange(tagTempLast.nNumber, 0);
        tagTempLast.nEnd = tagTempLast.nEnd - tagTempLast.nStart;
        tagTempLast.nStart = 0;
    }
    fwrite(&tagTempLast, sizeof(tagTempNext), 1, fp);  //д��
    for (i = 1; i < ftFileSize / sizeof(tagTempNext); i++) { //ÿ�ο���һ���ṹ��
        //��
        if (fread(&tagTempNext, sizeof(tagTempNext), 1, ft) < 1) { //������,������,����,�ļ�ָ��
            if (feof(ft)) {  //�Ƿ����ļ�β
                break;//�����ļ�β
            }
        }
        if (tagTempLast.nEnd != tagTempNext.nStart) {
            //��ת������ 
            FileArrange(tagTempNext.nNumber, tagTempLast.nEnd);

            //��д�ֿ�
            tagTempNext.nEnd = tagTempNext.nEnd - (tagTempNext.nStart - tagTempLast.nEnd);
            tagTempNext.nStart = tagTempLast.nEnd;

        }
        fwrite(&tagTempNext, sizeof(tagTempNext), 1, fp);
        tagTempLast = tagTempNext; //last���µ�����
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





//�ļ�����
void FileArrange(int nNumber, int nStart) {
    size_t i = 0;
    //��ȡ�ṹ��
    struct tagUserInput* taguserinput = FindMessageByNumber(nNumber);
    //StructWirteIn(taguserinput, nStart);
    FILE* fp;
    if (nFile == 0) {
        fp = FileOpen(DicName, "rb+"); //��
    }
    else {
        fp = FileOpen(DicCouName, "rb+"); //��
    }
    fseek(fp, nStart, SEEK_SET);   //��תλ��
    int nEnd = 0;

    //д����
    fwrite(&taguserinput->nNumber, sizeof(int), 1, fp);
    //д�����ֳ���
    fwrite(&taguserinput->nNameLength, sizeof(int), 1, fp);
    //д������
    fwrite(taguserinput->chName, taguserinput->nNameLength * 2, 1, fp);
    nEnd = ftell(fp);

    FileClose(fp);

    //��ת ��ŵ���

}


//�ṹ���޸�  
void StructChange(struct tagStore  tagstore, struct tagUserInput* taguserinput) {
    int nLocal = 0;
    struct tagUserInput* taguserinputbefore = FindMessageByNumber(tagstore.nNumber);
    //��鱾�����޿ռ�
    if (spaceCheck(tagstore, taguserinput->nNameLength * 2 + 8) == 1) {
        StoreDelete(tagstore.nNumber);
        StructWirteIn(taguserinput, tagstore.nStart);
    }
    else {
        StoreDelete(tagstore.nNumber);
        //���ҿ�λ
        nLocal = FileSpaceFind(taguserinput->nNameLength * 2 + 8);
        //�ļ�д��
        StructWirteIn(taguserinput, nLocal);
    }
    free(taguserinputbefore);
}

//�ռ��� ����: Ŀ��ֿ�, ��Ҫ�ĳ���
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
    //���нṹ��֮ǰ�����������ж��ļ���С
    fseek(pFile, 0, SEEK_END);  //�ƶ����ļ�ĩβ
    dwFileSize = ftell(pFile);//�㱨��ǰָ��λ��,���ص����ļ�ָ�뵽�ļ�ͷ�����ֽ���,���󷵻�-1 
    rewind(pFile);//�Ƶ��ļ�ͷ,�޷���ֵ

    //ֻ�д�һ��
    if (dwFileSize / sizeof(tagstoreLast) == 1) {
        FileClose(pFile);
        return 1;
    }
    //�������
    if (dwFileSize / sizeof(tagstoreLast) == 2) {
        fread(&tagstoreLast, sizeof(tagstoreLast), 1, pFile);  //ǰһ����ֵ
        fread(&tagstoreNext, sizeof(tagstoreLast), 1, pFile);//��һ����ֵ
        FileClose(pFile);
        if (tagstoreNext.nNumber == tagstoreInput.nNumber) {
            return 1;
        }
        if (tagstoreNext.nStart >= nSpaceNeed) {
            return 1;
        }
        return -1;
    }
    for (i = 2; i < dwFileSize / sizeof(tagstoreLast); i++) {  //ѭ������
        fread(&tagstoreNext, sizeof(tagstoreLast), 1, pFile);  //����
        //��ͬ
        if (tagstoreNext.nNumber == tagstoreInput.nNumber) {
            if (i + 1 == dwFileSize / sizeof(tagstoreLast)) { //���һ��
                FileClose(pFile);
                return 1;
            }
            fread(&tagstoreNext, sizeof(tagstoreLast), 1, pFile);//��ǰ��һ��
            if (tagstoreNext.nStart - tagstoreLast.nEnd >= nSpaceNeed) {
                FileClose(pFile);
                return 1;
            }
            FileClose(pFile);
            return -1;
        }
        //��ͬ
        tagstoreLast = tagstoreNext;
    }
    FileClose(pFile);
    return -1;
}