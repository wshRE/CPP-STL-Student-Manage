#pragma once
//1.����ѧ����ID ���֣�---ƫ��
void StudentAdd(char cStudentName[], size_t nStudentID);
void StudentInitAdd(char cStudentName[], size_t nStudentID);

//(2)�����γ�(ID, ����)---ƫ��
void CourseAdd(char cCourseName[], size_t nCourseID);
void CourseInitAdd(char cCourseName[], size_t nCourseID);

//(3)����ѡ�μ�¼(ѧ��ID, �γ�ID, ����)---ƫ��
void CourseRecord(size_t nStudentID, size_t nCourseID, int nMark,int nAdress);

//(4) ɾ��ѧ��(ID)
void StudentDel(size_t nStudentID);

//(5) ɾ���γ�(ID)
void CourseDel(size_t nCourseID);

//(6) ɾ��ѡ�μ�¼(ѧ��ID, �γ�ID)
void CourseRecordDel(size_t nStudentID, size_t nCourseID);

//(7) ��ѧ������---ƫ��
void StudentNameChange(size_t nStudentID, char cStudentName[]);

//(8) �Ŀγ�����---ƫ��
void CourseNameChange(size_t nCourseID, char cCourseName[]);

//(9) ��ѧ���ɼ�
void CourseMarkChange(size_t nStudentID, size_t nCourseID, int nMark);

//(10) ͨ��ѧ��ID��ѯѧ������
void StudentNameFind(size_t nStudentID);

//(11) ͨ��ѧ��������ѯѧ��ID
void StudentIDFind(char cStudentName[]);

//(12) ͨ���γ�ID��ѯ�γ���
void CourseNameFind(size_t nCourseID);

//(13) ͨ���γ�����ѯ�γ�ID
void CourseIDFind(char cCourseName[]);

//(14) ͨ���γ�ID��ѯѡ���˸ÿγ̵�ѧ���Լ��ɼ�
void CourseIDStuFind(size_t nCourseID);

//(15) ͨ��ѧ��ID��ѯ��ѧ��ѡ�޵Ŀγ���Ϣ
void StudentIDCouFind(size_t nStudentID);

//�ļ���ʼ��
void FileInit();


//�ļ����
//    //�γ����---д�����ݲ�����ƫ��
//int CourseFileAdd(char cCourseName[]);
//    //ѧ�����
//int StudentFileAdd(char cStudentName[]);
    //ѡ�μ�¼���
//int CourseChooseFileAdd(size_t nStudentID, size_t nCourseID, int nMark);


int GetNewStuID();
int GetNewCouID();


int GetStuID();
int GetCouID();

//----------------------------------------------------------------------------

//�޸��ļ���ѡ�μ�¼
void ChooseChange(int nAddress, int nStuID, int nCouID, int nMark);
//�����µ�ѡ�μ�¼---����ƫ��
int ChooseInsert(int nStuID, int nCouID, int nMark);