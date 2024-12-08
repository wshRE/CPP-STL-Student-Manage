#pragma once

//本结构体适用与课程和名字id树
typedef struct tagUserInput
{
    int nNumber;                  //编号  id
    int nNameLength;                 //名字长度
    wchar_t chName[200];             //名字
}tagUserInput;

//定长仓库
struct  tagStore
{
    int nStart; // 开始位置
    int nEnd;   //结束位置   [)
    int nNumber; //编号 
};



/*--------------------------------------------Service层-----------------------------------------------*/

/*添加
    功能：新联系人添加
    输入：无
    输出：无
*/
void FileAddStruct(char name[100], int nID, int nFile);


//存储区打印
/*
    输入：无
    输出：无
 */
void StorePrin();


//通过编号查询
/*
    输入：无
    输出：无
 */
struct tagUserInput* FindByNumber(int nNumber, int nFile);


//通过编号删除
/*
    输入：
    输出：
 */
void FileDelStruct(int nNumber, int nFile);


//通过编号修改
/*
    输入：无
    输出：无
 */
void FileChangeStruct(char name[], int nNumber, int nFile);



//结构体修改  
void StructChange(struct tagStore  tagstore, struct tagUserInput* taguserinput);




//整理
/*
    输入：无
    输出：无
 */
void Sort();




/*初始化
    输入：无
    输出：无
 */
void  init();


//打印所有联系人
/*
    输入：无
    输出：无
 */
void MessagePrin(int nFile);


/*------------------------------------Dao---------------------------------------------------------------*/
//关闭文件
/*
    输入：文件指针
    输出：无
 */
void FileClose(FILE* pFile);

//打开文件
/*
    输入：打开的文件 打开方式
    输出：文件指针
 */
FILE* FileOpen(char* chDicName, char* chNode);



//写入仓库
/*
    输入：仓库结构体
    输出：无
 */
void StoreInsert(struct tagStore tagstore);



void init();


//查找空间
/*
    输入：空间需求
    输出：无
 */
int FileSpaceFind(int nSpaceNeed);

//结构体写入
/*
    输入：存储结构体 写入位置
    输出：无
 */
void StructWirteIn(struct tagUserInput* taguserinput, int nWriteStart);

//-----------------------------

//打印所有联系人
/*
    输入：无
    输出：无
 */
void PrinAllMessage();


//文件打印
/*
    输入：文件的起始下标
    输出：无
 */
void FilePrin(int nStart);
//----------------------------------------------------------------------------------------------------------------------------


//通过编号查询
/*
    输入：无
    输出：无
 */
struct tagUserInput* FindByNumber(int nNumber, int nFile);


//查找空间
/*
    输入：需要的空间大小
    输出：无
 */
int Findspace(int nSpaceNeed);


//通过编号查询
/*
    输入：编号
    输出：无
 */
struct tagUserInput* FindMessageByNumber(int nNumber);


//通过编号查询仓库
/*
    输入：编号
    输出：无
 */
struct tagStore FindStoreByNumber(int nNumber);


//通过编号删除
/*
    输入：无
    输出：无
 */
void FileDelStruct(int nNumber, int nFile);


//仓库删除
/*
    输入：编号
    输出：无
 */
void StoreDelete(int nNumber);



//存储区打印
/*
    输入：无
    输出：无
 */
void StorePrin();



//整理
/*
    输入：无
    输出：无
 */
void Sort();

//调整
/*
    输入：无
    输出：无
 */
void Arrange();


//文件调整
/*
    输入：编号 起始位置
    输出：无
 */
void FileArrange(int nNumber, int nStart);


//空间检查 
/*
    输入：目标仓库, 需要的长度
    输出：无
 */
int spaceCheck(struct tagStore  tagstoreInput, int nSpaceNeed);



void SetFile(int n);