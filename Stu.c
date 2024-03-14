#include "declaration.h"

void LookSelf(STU myself) {
	system("cls");
	printf("\n\t\t\t\t\t个人成绩查询\n");
	printf("\t\t\t---------------------------------------------\n");
	printf("\t\t\t姓名：%s\n", myself->name);
	printf("\t\t\t学号：%s\n", myself->account);
	printf("\t\t\t班级：%s\n", myself->hClass);
	printf("\t\t\t语文：%d 分\n", myself->chinese);
	printf("\t\t\t数学：%d 分\n", myself->math);
	printf("\t\t\t英语：%d 分\n", myself->english);
	printf("\t\t\t---------------------------------------------\n");
	system("pause");
	return;
}

void LookAll(STU student) {
	system("cls");
	printf("\n\t\t\t\t\t班级成绩查询\n");
	printf("\t\t\t---------------------------------------------\n");
	STU move = student->next;
	while (move != NULL) {
		printf("\t\t\t姓名：%s\t学号：%s\t班级：%s\n", move->name, move->account, move->hClass);
		printf("\t\t\t语文：%d 分\t数学：%d 分\t英语：%d 分\n", move->chinese, move->math, move->english);
		printf("\t\t\t---------------------------------------------\n");
		move = move->next;
	}
	system("pause");
	return;
}

void AnalyseSelf(STU student, STU myself) {
	system("cls");
	printf("\n\t\t\t\t\t个人成绩分析\n");
	printf("\t\t\t---------------------------------------------\n");
	double avgChinese = 0, avgMath = 0, avgEnglish = 0;
	int count = 0;
	STU move = student->next;
	int chi = 1, mat = 1, eng = 1, tot = 1;
	while (move != NULL) {
		if (move->chinese > myself->chinese) {
			chi++;
		}
		if (move->math > myself->math) {
			mat++;
		}
		if (move->english  > myself->english) {
			eng++;
		}
		if (move->math + move->chinese + move->english > myself->chinese + myself->math + myself->english) {
			tot++;
		}
		avgChinese += move->chinese;
		avgMath += move->math;
		avgEnglish += move->english;
		count++;
		move = move->next;
	}
	avgChinese /= count;
	avgMath /= count;
	avgEnglish /= count;
	printf("\t\t\t语文平均分: %.1f  你的排名：%d\n", avgChinese, chi);
	printf("\t\t\t数学平均分: %.1f  你的排名：%d\n", avgMath, mat);
	printf("\t\t\t英语平均分: %.1f  你的排名：%d\n", avgEnglish, eng);
	float avgTotal = (avgChinese + avgMath + avgEnglish) / 3;
	printf("\t\t\t总分平均分: %.1f  你的排名：%d\n", avgTotal, tot);
	printf("\t\t\t---------------------------------------------\n");
	system("pause");
	return;
}

void Feedback(STU myself) {
	system("cls");
	char tep[1000];
	printf("\n\t\t\t\t\t成绩申诉\n");
	printf("\t\t\t---------------------------------------------\n");
	printf("\t\t\t请输入成绩申诉内容：（单字符0即无内容申诉）\n\n\t\t\t");
	if (fgets(tep, sizeof(tep), stdin) == NULL) {
		printf("发生了错误！没能读入申诉内容\n");
		return;
	}
	if (!strcmp(tep, "\n")) {
		printf("输入为空，无效输入，即将返回学生界面\n");
		system("pause");
		return;
	}
	tep[strcspn(tep, "\n")] = 0;
	fflush(stdin);
	printf("\n\n\t\t\t申诉内容已提交，请等待管理员处理！\n");
	strcpy(myself->complaint, tep);
	printf("\t\t\t---------------------------------------------\n");
	system("pause");
	return;
}

void SecureStu(STU myself) {
	system("cls");
	char tep[100];
	if (!strcmp(myself->secure, "0")) {
		printf("当前无密保可以直接修改,请输入您希望的密保：（单字符0即不设密保）\n");
		if (fgets(tep, sizeof(tep), stdin) == NULL) {
			printf("发生了错误！没能读入您的输入\n");
			return;
		}
		if (!strcmp(tep, "\n")) {
			printf("输入为空，无效输入，即将返回学生界面......\n");
			system("pause");
			return;
		}
		tep[strcspn(tep, "\n")] = 0;
		fflush(stdin);
		strcpy(myself->secure, tep);
		printf("密保已更新！\n");
	}
	else {
		printf("请输入您设置的密保信息：\n");
		if (fgets(tep, sizeof(tep), stdin) == NULL) {
			printf("发生了错误！没能读入您的输入\n");
			return;
		}
		tep[strcspn(tep, "\n")] = 0;
		fflush(stdin);
		if (!strcmp(tep, myself->secure)) {
			printf("密保正确!下来请输入您希望更改的密保：（单字符0即不设密保）\n");
			if (fgets(tep, sizeof(tep), stdin) == NULL) {
				printf("发生了错误！没能读入密保内容\n");
				return;
			}
			if (!strcmp(tep, "\n")) {
				printf("输入为空，无效输入，即将返回学生界面......\n");
				system("pause");
				return;
			}
			tep[strcspn(tep, "\n")] = 0;
			fflush(stdin);
			strcpy(myself->secure, tep);
			printf("密保已更新！\n");
		}
		else {
			printf("密保信息错误！即将返回学生端界面......\n");
		}
	}
	system("pause");
	return;
}

void ChangeStu(STU student) {
	int flag = 0;
	while (1) {
		system("cls");
		char tep[100];
		printf("\t\t\t\t\t   ┅┅┅       信息填写     ┅┅┅       \n");
		printf("\t\t\t=========================================================\n");
		printf("\t\t\t1.姓名\n\t\t\t2.密保（用于进行权限的确认）（单字符0或跳过填写即不设密保）\n\t\t\t0.结束信息填写，进入学生端界面（请确保姓名填写正确）\n");
		printf("\t\t\t=========================================================\n");
		char num = getch();
		int choose = num - '0';
		switch (choose){
		case 0:
			break;
		case 1:
			printf("请输入您的姓名：");
			if (fgets(tep, sizeof(tep), stdin) == NULL) {
				printf("未能成功读取姓名！\n");
				return;
			}
			if (!strcmp(tep, "\n")) {
				printf("输入为空，无效输入\n");
				system("pause");
				break;
			}
			tep[strcspn(tep, "\n")] = 0;
			fflush(stdin);
			strcpy(student->name, tep);
			flag = 1;
			printf("姓名填写完成\n");
			system("pause");
			break;
		case 2:
			printf("请输入您的密保：");
			if (fgets(tep, sizeof(tep), stdin) == NULL) {
				printf("未能成功读取密保！\n");
				return;
			}
			if (!strcmp(tep, "\n")) {
				printf("输入为空，无效输入\n");
				system("pause");
				break;
			}
			tep[strcspn(tep, "\n")] = 0;
			fflush(stdin);
			strcpy(student->secure, tep);
			printf("密保填写完成\n");
			system("pause");
			break;
		default:
			printf("\n\n\n请根据提示操作！\n");
			system("pause");
			break;
		}
		if (choose == 0) {
			if (flag == 1) {
				break;
			}
			else {
				printf("请您填写姓名！\n");
				system("pause");
			}
		}
		system("cls");
	}
	return;
}
