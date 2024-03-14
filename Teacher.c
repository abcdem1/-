#include "declaration.h"

int Teacher(TEA teacher, LPNODE phead, STU pstudent, TEA pteacher) {
	if (!strcmp(teacher->name, "未命名")) {
		system("cls");
		printf("欢迎您首次进入教师端系统!\n");
		printf("下来请根据提示完成信息更改\n");
		system("pause");
		ChangeTea(teacher);
	}
	STU student = NewStudent();
	if (strcmp(teacher->hClass, "无")) {
		STU move = pstudent;
		while (move != NULL) {
			if (!strcmp(teacher->hClass, move->hClass)) {
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
	}
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t欢迎您进入教师端！");
	system("pause");
	system("cls");
	system("color 62");
	while (1) {
		system("cls");
		printf("\t\t\t\t\t   ┅┅┅       教师端     ┅┅┅       \n");
		printf("\t\t\t=========================================================\n");
		printf("\t\t\t1.增加新的学生信息\n\t\t\t2.删除学生信息\n\t\t\t3.修改学生信息\n\t\t\t4.查询学生信息\n\t\t\t5.输出本班成绩\n\t\t\t6.下载到文件中\n\t\t\t7.成绩分析\n\t\t\t8.提醒管理员进行成绩的更新\n\t\t\t9.修改密保\n\t\t\ta.将学生排序\n\t\t\tb.回应学生申诉\n\t\t\tc.退出并返回登陆界面\n\t\t\t0.退出并返回初始界面\n");
		printf("\t\t\t=========================================================\n");
		char num = getch();
		if (num == 'c') {
			printf("成功登出\n");
			system("pause");
			DestroyStu(student);
			return 0;
		}
		else if (num == 'a') {
			SortStu(student);
			continue;
		}
		else if (num == 'b') {
			ResComplaint(student, pstudent, phead);
			continue;
		}
		int choose = num - '0';
		switch (choose){
		case 0:
			break;
		case 1:
			Increase(teacher, phead, pstudent, student);
			break;
		case 2:
			Forget(teacher, pstudent, phead, student);
			break;
		case 3:
			Vary(pstudent, phead, student);
			break;
		case 4:
			Look(student);
			break;
		case 5:
			OutputScore(student);
			break;
		case 6:
			download(student);
			break;
		case 7:
			Analyse(student);
			break;
		case 8:
			Remind(teacher);
			break;
		case 9:
			SecureTea(teacher);
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
	system("pause");
	DestroyStu(student);
	return 1;
}
