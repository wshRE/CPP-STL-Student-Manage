#pragma once
//1.新增学生（ID 名字）---偏移
void StudentAdd(char cStudentName[], size_t nStudentID);
void StudentInitAdd(char cStudentName[], size_t nStudentID);

//(2)新增课程(ID, 名字)---偏移
void CourseAdd(char cCourseName[], size_t nCourseID);
void CourseInitAdd(char cCourseName[], size_t nCourseID);

//(3)新增选课记录(学生ID, 课程ID, 分数)---偏移
void CourseRecord(size_t nStudentID, size_t nCourseID, int nMark,int nAdress);

//(4) 删除学生(ID)
void StudentDel(size_t nStudentID);

//(5) 删除课程(ID)
void CourseDel(size_t nCourseID);

//(6) 删除选课记录(学生ID, 课程ID)
void CourseRecordDel(size_t nStudentID, size_t nCourseID);

//(7) 改学生名字---偏移
void StudentNameChange(size_t nStudentID, char cStudentName[]);

//(8) 改课程名字---偏移
void CourseNameChange(size_t nCourseID, char cCourseName[]);

//(9) 改学生成绩
void CourseMarkChange(size_t nStudentID, size_t nCourseID, int nMark);

//(10) 通过学生ID查询学生姓名
void StudentNameFind(size_t nStudentID);

//(11) 通过学生姓名查询学生ID
void StudentIDFind(char cStudentName[]);

//(12) 通过课程ID查询课程名
void CourseNameFind(size_t nCourseID);

//(13) 通过课程名查询课程ID
void CourseIDFind(char cCourseName[]);

//(14) 通过课程ID查询选修了该课程的学生以及成绩
void CourseIDStuFind(size_t nCourseID);

//(15) 通过学生ID查询该学生选修的课程信息
void StudentIDCouFind(size_t nStudentID);

//文件初始化
void FileInit();


//文件相关
//    //课程添加---写入数据并返回偏移
//int CourseFileAdd(char cCourseName[]);
//    //学生添加
//int StudentFileAdd(char cStudentName[]);
    //选课记录添加
//int CourseChooseFileAdd(size_t nStudentID, size_t nCourseID, int nMark);


int GetNewStuID();
int GetNewCouID();


int GetStuID();
int GetCouID();

//----------------------------------------------------------------------------

//修改文件的选课记录
void ChooseChange(int nAddress, int nStuID, int nCouID, int nMark);
//插入新的选课记录---返回偏移
int ChooseInsert(int nStuID, int nCouID, int nMark);