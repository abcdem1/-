#include "declaration.h"

void SaveStu(STU pstudent) {
	FILE* fp = fopen("stu.bin", "wb+");
	if (fp == NULL) {
		printf("打开文件stu.bin失败\n");
		return;
	}
	STU tep = pstudent;
	while (tep != NULL) {
		fwrite(tep, sizeof(struct STUDENT), 1, fp);
		tep = tep->next;
	}
	fclose(fp);
	return;
}

STU ReadStu() {
	FILE* fp = fopen("stu.bin", "rb+");
	if (fp == NULL) {
		printf("打开文件失败\n");
		return NULL;
	}
	STU head = NULL;
	STU tail = NULL;
	struct STUDENT tep;
	while (fread(&tep, sizeof(struct STUDENT), 1, fp) == 1) {
		STU newStudent = NewStudent();
		memcpy(newStudent, &tep, sizeof(struct STUDENT));
		if (head == NULL) {
			head = newStudent;
			tail = newStudent;
		} else {
			tail->next = newStudent;
			tail = newStudent;
		}
	}
	fclose(fp);
	if (head != NULL) {
		tail->next = NULL;
	}
	return head;
}

void SaveTea(TEA pteacher) {
	FILE* fp = fopen("tea.bin", "wb+");
	if (fp == NULL) {
		printf("打开文件tea.bin失败\n");
		return;
	}
	TEA tep = pteacher;
	while (tep != NULL) {
		fwrite(tep, sizeof(struct TEACHER), 1, fp);
		tep = tep->next;
	}
	fclose(fp);
	return;
}

TEA ReadTea() {
	FILE* fp = fopen("tea.bin", "rb+");
	if (fp == NULL) {
		printf("打开文件失败\n");
		return NULL;
	}
	TEA head = NULL;
	TEA tail = NULL;
	struct TEACHER tep;
	while (fread(&tep, sizeof(struct TEACHER), 1, fp) == 1) {
		TEA newTeacher = NewTeacher();
		memcpy(newTeacher, &tep, sizeof(struct TEACHER));
		if (head == NULL) {
			head = newTeacher;
			tail = newTeacher;
		} else {
			tail->next = newTeacher;
			tail = newTeacher;
		}
	}
	fclose(fp);
	if (head != NULL) {
		tail->next = NULL;
	}
	return head;
}

void SaveMes(LPNODE phead) {
	FILE* fp = fopen("mes.bin", "wb+");
	if (fp == NULL) {
		printf("打开文件mes.bin失败\n");
		return;
	}
	LPNODE tep = phead;
	while (tep != NULL) {
		fwrite(tep, sizeof(struct MESSAGE), 1, fp);
		tep = tep->next;
	}
	fclose(fp);
	return;
}

LPNODE ReadMes() {
	FILE* fp = fopen("mes.bin", "rb+");
	if (fp == NULL) {
		printf("打开文件失败\n");
		return NULL;
	}
	LPNODE head = NULL;
	LPNODE tail = NULL;
	struct MESSAGE tep;
	while (fread(&tep, sizeof(struct MESSAGE), 1, fp) == 1) {
		LPNODE newMessage = NewMessage();
		memcpy(newMessage, &tep, sizeof(struct MESSAGE));
		if (head == NULL) {
			head = newMessage;
			tail = newMessage;
		} else {
			tail->next = newMessage;
			tail = newMessage;
		}
	}
	fclose(fp);
	if (head != NULL) {
		tail->next = NULL;
	}
	return head;
}

int Choose() {
	while(1) {
		system("cls");
		printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t  下面请选择：\n\n\t\t\t\t1.新建库（将会清空原有库）\t\t2.自动导入已有库\n");
		char tep = getch();
		int flag = tep - '0';
		switch(flag) {
		case 1:
			return 1;
		case 2:
			return 2;
		default:
			printf("\n\n\n请根据提示操作！\n");
			system("pause");
			break;
		}
	}
	return 2;
}
