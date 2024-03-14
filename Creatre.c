#include "declaration.h"

LPNODE NewMessage() {
	LPNODE newMessage = (LPNODE)malloc(sizeof(struct MESSAGE));
	if (newMessage == NULL) {
		printf("未能成功为新用户分配空间\n");
		return NULL;
	}
	newMessage->next = NULL;
	return newMessage;
}

TEA NewTeacher() {
	TEA newTeacher = (TEA)malloc(sizeof(struct TEACHER));
	if (newTeacher == NULL) {
		printf("未能成功为新老师分配空间\n");
		return NULL;
	}
	newTeacher->next = NULL;
	return newTeacher;
}

STU NewStudent() {
	STU newStudent = (STU)malloc(sizeof(struct STUDENT));
	if (newStudent == NULL) {
		printf("未能成功为新学生分配空间\n");
		return NULL;
	}
	newStudent->next = NULL;
	return newStudent;
}
