#include "declaration.h"

TEA FindTeaByClass(char* hClass, TEA pteacher) {
	TEA move = pteacher;
	while (move != NULL) {
		if (!strcmp(move->hClass, hClass)) {
			return move;
		}
		move = move->next;
	}
	return NULL;
}

STU FindStuByAccount(char* account, STU pstudent) {
	STU move= pstudent;
	while (move != NULL) {
		if (!strcmp(account, move->account)) {
			return move;
		}
		move = move->next;
	}
	return NULL;
}

STU FindStuInClass(char* account, STU student) {
	STU move = student;
	while (move != NULL) {
		if (!strcmp(move->account, account)) {
			return move;
		}
		move = move->next;
	}
	return NULL;
}

LPNODE FindAccount(char* account, LPNODE phead) {
	LPNODE move = phead;
	while (move != NULL) {
		if (!strcmp(move->account, account)) {
			return move;
		}
		move = move->next;
	}
	return NULL;
}

TEA FindTeaByAccount(char* account, TEA pteacher) {
	TEA move = pteacher;
	while (move != NULL) {
		if (!strcmp(move->account, account)) {
			return move;
		}
		move = move->next;
	}
	return NULL;
}

void Destroy(LPNODE phead, TEA pteacher, STU pstudent) {
	LPNODE move = phead;
	LPNODE tep;
	while (move != NULL) {
		tep = move;
		move = move->next;
		free(tep);
	}
	STU pmove = pstudent;
	STU ptep;
	while (pmove != NULL) {
		ptep = pmove;
		pmove = pmove->next;
		free(ptep);
	}
	TEA ppmove = pteacher;
	TEA pptep;
	while (ppmove != NULL) {
		pptep = ppmove;
		ppmove = ppmove->next;
		free(pptep);
	}
	return;
}

void DestroyStu(STU student) {
	STU move = student;
	while (move != NULL) {
		STU tep = move;
		move = move->next;
		free(tep);
	}
	return;
}
