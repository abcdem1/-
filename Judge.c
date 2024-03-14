#include "declaration.h"

int JudgeTeacher(char* account, TEA pteacher) {
	TEA move = pteacher;
	while (move != NULL) {
		if (!strcmp(move->account, account)) {
			break;
		}
		move = move->next;
	}
	if (move == NULL) {
		return 0;
	}
	return 1;
}

int JudgeStudent(char* account, STU pstudent) {
	STU move = pstudent;
	while (move != NULL) {
		if (!strcmp(move->account, account)) {
			break;
		}
		move = move->next;
	}
	if (move == NULL) {
		return 0;
	}
	return 1;
}

int JudgeAccount(char* account, LPNODE phead) {
	LPNODE move = phead;
	while (move != NULL) {
		if (!strcmp(move->account, account)) {
			break;
		}
		move = move->next;
	}
	if (move == NULL) {
		return 0;
	}
	return 1;
}

int JudgePassword(char* account, char* password, LPNODE phead) {
	LPNODE move = phead;
	while (move != NULL) {
		if (!strcmp(move->account, account)) {
			break;
		}
		move = move->next;
	}
	if (!strcmp(move->password, password)) {
		return 1;
	}
	return 0;
}
