#include "declaration.h"

int Student(STU myself, STU pstudent) {
	if (!strcmp(myself->name, "未命名")) {
		system("cls");
		printf("欢迎您首次进入学生端系统!\n");
		printf("下来请根据提示完成信息更改\n");
		system("pause");
		ChangeStu(myself);
	}
	if (!strcmp(myself->hClass, "无")) {
		system("cls");
		printf("您还未加入班级，请联系您的老师操作！\n");
		printf("即将退出......\n");
		system("pause");
		return 1;
	}
	STU student = NewStudent();
	STU move = pstudent;
	while (move != NULL) {
		if (!strcmp(myself->hClass, move->hClass)) {
			STU target = NewStudent();
			target->chinese = move->chinese;
			target->math = move->math;
			target->english = move->english;
			strcpy(target->hClass, move->hClass);
			strcpy(target->secure, move->secure);
			strcpy(target->account, move->account);
			strcpy(target->complaint, move->complaint);
			strcpy(target->name, move->name);
			if (student->next == NULL) {
				student->next = target;
			}
			else {
				target->next = student->next;
				student->next = target;
			}
		}
		move = move->next;
	}
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t学生端进入完成！");
	system("pause");
	system("cls");
	system("color 37");
	while (1) {
		printf("\t\t\t\t\t   ┅┅┅       学生端     ┅┅┅       \n");
		printf("\t\t\t=========================================================\n");
		printf("\t\t\t1.成绩查询\n\t\t\t2.查询本班成绩\n\t\t\t3.成绩分析\n\t\t\t4.成绩申诉\n\t\t\t5.修改密保\n\t\t\ta.退出并返回登录界面\n\t\t\t0.退出并返回初始界面\n");
		printf("\t\t\t=========================================================\n");
		char num = getch();
		if (num == 'a') {
			printf("成功登出\n");
			system("pause");
			DestroyStu(student);
			return 0;
		}
		int choose = num - '0';
		switch (choose){
		case 0:
			break;
		case 1:
			LookSelf(myself);
			break;
		case 2:
			LookAll(student);
			break;
		case 3:
			AnalyseSelf(student, myself);
			break;
		case 4:
			Feedback(myself);
			break;
		case 5:
			SecureStu(myself);
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
	printf("成功登出！\n");
	DestroyStu(student);
	system("pause");
	return 1;
}
