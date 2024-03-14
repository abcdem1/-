#include "declaration.h"

bool power = true;

int main() {
	int num =  Choose();
	STU pstudent;
	TEA pteacher;
	LPNODE phead;
	if (num == 1) {
		pstudent = NewStudent();
		pteacher = NewTeacher();
		phead = NewMessage();
		SaveMes(phead);
		SaveStu(pstudent);
		SaveTea(pteacher);
	}
	else {
		phead = ReadMes();
		pstudent = ReadStu();
		pteacher = ReadTea();
	}
	system ("color 87");
	system("cls");
	printf("\n\n\n\n\n\t\t\t\t\t");
	printf("欢迎来到学生信息管理系统！");
	printf("\n\n\n\n\n\n\n\n\t\t\t\t");
	char tep[60] = {"请稍后，即将进入学生信息管理系统......\n\n\n\n"};
	for(int i = 0; i < strlen(tep); i++) {
		printf("%c", tep[i]);
		Sleep(100);
	}
	printf("注意事项：密码上限19位，密保上限99位，提醒和抱怨上限999位，班级上限20位，读入时超出限制的部分会自动清空\n");
	system("pause");
	system("cls");
	fflush(stdin);
	system("cls");
	while (1) {
		system ("color 87");
		printf("\t\t\t\t   ┅┅┅         学生信息管理系统     ┅┅┅       \n");
		printf("\t\t\t=========================================================\n");
		printf("\t\t\t\t1.登录\n\t\t\t\t2.注册\n\t\t\t\t3.密码找回\n\t\t\t\t4.密码修改\n\t\t\t\t0.退出系统\n");
		printf("\t\t\t=========================================================\n");
		char num = getch();
		int choose = num - '0';
		switch (choose){
		case 0:
			break;
		case 1:
			Login(phead, pteacher, pstudent);
			break;
		case 2:
			Enroll(phead);
			break;
		case 3:
			Back(phead, pteacher, pstudent);
			break;
		case 4:
			Change(phead, pteacher, pstudent);
			break;
		default:
			printf("\n\n\n请根据提示操作！\n");
			system("pause");
			break;
		}
		if (choose == 0) {
			break;
		}
		system("cls");
	}
	printf("成功退出！\n");
	SaveMes(phead);
	SaveStu(pstudent);
	SaveTea(pteacher);
	Destroy(phead, pteacher, pstudent);
	return 0;
}

