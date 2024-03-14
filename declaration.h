#ifndef DECLARATION_H
#define DECLARATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

#define IDENTITY "abcdem"
#define ID "666666"

typedef struct STUDENT{
	char name[20];
	char hClass[10];
	char account[20];
	int chinese;
	int math;
	int english;
	char secure[100];
	char complaint[1000];
	struct STUDENT* next;
}*STU;

typedef struct TEACHER{
	char name[20];
	char hClass[20];
	char account[20];
	char secure[100];
	char remind[1000];
	struct TEACHER* next;
}*TEA;

typedef struct MESSAGE{
	char account[20];
	char password[20];
	char identity[20];
	struct MESSAGE* next;
}*LPNODE;

extern bool power;

void UI(LPNODE, TEA, STU);
void Login(LPNODE, TEA, STU);
void Enroll(LPNODE);
void Change(LPNODE, TEA, STU);
void Back(LPNODE, TEA, STU);


int Administrator(LPNODE, TEA, STU);

void ReviewAgency(LPNODE, TEA, STU);
void ResEnroll(LPNODE, TEA, STU);
void ResChange(LPNODE, TEA, STU);
void ResBack(LPNODE, TEA, STU);
void ResUpdate(LPNODE, TEA, STU);

void EnterPortalTeacher(LPNODE, TEA, STU);
void InsertMessage(LPNODE, TEA, STU);
void DeleteMessage(LPNODE, TEA, STU);
void ChangeMessage(LPNODE, TEA, STU);
void FindMessage(LPNODE, TEA, STU);
void InputAllMessage(LPNODE, TEA, STU);
void OutputAllMessage(LPNODE);
void InputMessageInHand(LPNODE, TEA, STU);
void SortAcc(LPNODE);
void InsertFile(LPNODE, TEA, STU);


int Teacher(TEA, LPNODE, STU, TEA);

void Increase(TEA, LPNODE, STU, STU);
void Forget(TEA, STU, LPNODE, STU);
void Vary(STU, LPNODE, STU);
void Look(STU);
void OutputScore(STU);
void download(STU);
void Analyse(STU);
void Remind(TEA);
void SecureTea(TEA);
void ChangeTea(TEA);
void SortStu(STU);
void ResComplaint(STU, STU, LPNODE);


int Student(STU, STU);

void LookSelf(STU);
void LookAll(STU);
void AnalyseSelf(STU, STU);
void Feedback(STU);
void SecureStu(STU);
void ChangeStu(STU);


int JudgeTeacher(char*, TEA);
int JudgeStudent(char*, STU);
int JudgeAccount(char*, LPNODE);
int JudgePassword(char*, char*, LPNODE);

void SaveMes(LPNODE);
LPNODE ReadMes();
void SaveTea(TEA);
TEA ReadTea();
void SaveStu(STU);
STU ReadStu();
int Choose();

LPNODE NewMessage();
TEA NewTeacher();
STU NewStudent();

TEA FindTeaByClass(char*, TEA);
STU FindStuByAccount(char*, STU);
STU FindStuInClass(char*, STU);
LPNODE FindAccount(char*, LPNODE);
TEA FindTeaByAccount(char*, TEA);

void Destroy(LPNODE, TEA, STU);
void DestroyStu(STU);

#endif
