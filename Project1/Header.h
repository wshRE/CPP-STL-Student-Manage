#pragma once

//���ṹ��������γ̺�����id��
typedef struct tagUserInput
{
    int nNumber;                  //���  id
    int nNameLength;                 //���ֳ���
    wchar_t chName[200];             //����
}tagUserInput;

//�����ֿ�
struct  tagStore
{
    int nStart; // ��ʼλ��
    int nEnd;   //����λ��   [)
    int nNumber; //��� 
};



/*--------------------------------------------Service��-----------------------------------------------*/

/*���
    ���ܣ�����ϵ�����
    ���룺��
    �������
*/
void FileAddStruct(char name[100], int nID, int nFile);


//�洢����ӡ
/*
    ���룺��
    �������
 */
void StorePrin();


//ͨ����Ų�ѯ
/*
    ���룺��
    �������
 */
struct tagUserInput* FindByNumber(int nNumber, int nFile);


//ͨ�����ɾ��
/*
    ���룺
    �����
 */
void FileDelStruct(int nNumber, int nFile);


//ͨ������޸�
/*
    ���룺��
    �������
 */
void FileChangeStruct(char name[], int nNumber, int nFile);



//�ṹ���޸�  
void StructChange(struct tagStore  tagstore, struct tagUserInput* taguserinput);




//����
/*
    ���룺��
    �������
 */
void Sort();




/*��ʼ��
    ���룺��
    �������
 */
void  init();


//��ӡ������ϵ��
/*
    ���룺��
    �������
 */
void MessagePrin(int nFile);


/*------------------------------------Dao---------------------------------------------------------------*/
//�ر��ļ�
/*
    ���룺�ļ�ָ��
    �������
 */
void FileClose(FILE* pFile);

//���ļ�
/*
    ���룺�򿪵��ļ� �򿪷�ʽ
    ������ļ�ָ��
 */
FILE* FileOpen(char* chDicName, char* chNode);



//д��ֿ�
/*
    ���룺�ֿ�ṹ��
    �������
 */
void StoreInsert(struct tagStore tagstore);



void init();


//���ҿռ�
/*
    ���룺�ռ�����
    �������
 */
int FileSpaceFind(int nSpaceNeed);

//�ṹ��д��
/*
    ���룺�洢�ṹ�� д��λ��
    �������
 */
void StructWirteIn(struct tagUserInput* taguserinput, int nWriteStart);

//-----------------------------

//��ӡ������ϵ��
/*
    ���룺��
    �������
 */
void PrinAllMessage();


//�ļ���ӡ
/*
    ���룺�ļ�����ʼ�±�
    �������
 */
void FilePrin(int nStart);
//----------------------------------------------------------------------------------------------------------------------------


//ͨ����Ų�ѯ
/*
    ���룺��
    �������
 */
struct tagUserInput* FindByNumber(int nNumber, int nFile);


//���ҿռ�
/*
    ���룺��Ҫ�Ŀռ��С
    �������
 */
int Findspace(int nSpaceNeed);


//ͨ����Ų�ѯ
/*
    ���룺���
    �������
 */
struct tagUserInput* FindMessageByNumber(int nNumber);


//ͨ����Ų�ѯ�ֿ�
/*
    ���룺���
    �������
 */
struct tagStore FindStoreByNumber(int nNumber);


//ͨ�����ɾ��
/*
    ���룺��
    �������
 */
void FileDelStruct(int nNumber, int nFile);


//�ֿ�ɾ��
/*
    ���룺���
    �������
 */
void StoreDelete(int nNumber);



//�洢����ӡ
/*
    ���룺��
    �������
 */
void StorePrin();



//����
/*
    ���룺��
    �������
 */
void Sort();

//����
/*
    ���룺��
    �������
 */
void Arrange();


//�ļ�����
/*
    ���룺��� ��ʼλ��
    �������
 */
void FileArrange(int nNumber, int nStart);


//�ռ��� 
/*
    ���룺Ŀ��ֿ�, ��Ҫ�ĳ���
    �������
 */
int spaceCheck(struct tagStore  tagstoreInput, int nSpaceNeed);



void SetFile(int n);