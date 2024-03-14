#include "declaration.h"

void Increase(TEA teacher, LPNODE phead, STU pstudent, STU student) {
	system("cls");
	char account[20];
	printf("\n\t\t\t请输入需要添加到班级内的学生账号/学号：(8位)");
	if (fgets(account, sizeof(account), stdin) == NULL) {
		printf("发生了错误！没能读入账号/学号\n");
		return;
	}
	if (!strcmp(account, "\n") || strlen(account) != 9) {
		printf("输入非法，即将返回教师界面......\n");
		system("pause");
		return;
	}
	account[strcspn(account, "\n")] = 0;
	fflush(stdin);
	if (JudgeAccount(account, phead)) {
		STU move = FindStuByAccount(account, pstudent);
		if (move == NULL) {
			printf("未能找到该学生\n");
			system("pause");
			return;
		}
		if (!strcmp(move->hClass, "无")) {
			strcpy(move->hClass, teacher->hClass);
			STU ptep = NewStudent();
			ptep->chinese = move->chinese;
			ptep->math = move->math;
			ptep->english = move->english;
			strcpy(ptep->hClass, move->hClass);
			strcpy(ptep->secure, move->secure);
			strcpy(ptep->account, move->account);
			strcpy(ptep->complaint, move->complaint);
			strcpy(ptep->name, move->name);
			if (student->next == NULL) {
				student->next = ptep;
			}
			else {
				ptep->next = student->next;
				student->next = ptep;
			}
			printf("添加成功！\n");
		}
		else if (!strcmp(move->hClass, teacher->hClass)) {
			printf("该学生已在班级中，无需添加！即将返回教师界面......\n");
		}
		else {
			printf("该学生已在其他班级中，请联系管理员更改！即将返回教师界面......\n");
		}
	}
	else {
		printf("账号/学号不存在！即将返回教师界面......\n");
	}
	system("pause");
	return;
}

void Forget(TEA teacher, STU pstudent, LPNODE phead, STU student) {
	system("cls");
	if (student->next == NULL) {
		printf("当前班级无学生，即将返回教师界面......\n");
		system("pause");
		return;
	}
	char tep[20];
	printf("\n\t\t\t请输入需要移出班级的学生账号/学号：(8位)");
	if (fgets(tep, sizeof(tep), stdin) == NULL) {
		printf("发生了错误！没能读入账号/学号\n");
		return;
	}
	if (!strcmp(tep, "\n") || strlen(tep) != 9) {
		printf("输入非法，即将返回教师界面......\n");
		system("pause");
		return;
	}
	tep[strcspn(tep, "\n")] = 0;
	fflush(stdin);
	if (!JudgeAccount(tep, phead)) {
		printf("该学生账号未注册，即将返回教师主界面\n");
		system("pause");
		return;
	}
	STU pre = student;
	STU move = student->next;
	while (move != NULL) {
		if (!strcmp(move->account, tep)) {
			break;
		}
		pre = move;
		move = move->next;
	}
	if (move == NULL) {
		printf("该学生不在班中，无需删除！\n");
	}
	else {
		STU pmove = FindStuByAccount(tep, pstudent);
		strcpy(pmove->hClass, "无");
		pre->next = move->next;
		free(move);
		printf("移出班级成功！\n");
	}
	system("pause");
	return;
}

void Vary(STU pstudent, LPNODE phead, STU student) {
	if (!power) {
		printf("无法修改，权限已被锁定，请联系管理员！\n");
		system("pause");
		return;
	}
	while(1) {
		system("cls");
		printf("请输入你想要改变学生信息的账号/学号:(8位)");
		char tep[20];
		if (fgets(tep, sizeof(tep), stdin) == NULL) {
			printf("发生了错误！没能读入账号/学号\n");
			return;
		}
		if (!strcmp(tep, "\n") || strlen(tep) != 9) {
			printf("输入非法，即将返回教师界面......\n");
			system("pause");
			return;
		}
		tep[strcspn(tep, "\n")] = 0;
		fflush(stdin);
		if (JudgeAccount(tep, phead)) {
			STU move = FindStuByAccount(tep, student);
			STU pmove = FindStuByAccount(tep, pstudent);
			if (move == NULL) {
				printf("请输入本班学生的账号/学号，即将返回教师界面......\n");
				system("pause");
				break;
			}
			else {
				while (1) {
					printf("\n请输入您想要更改的成绩->1.语文成绩\t2.数学成绩\t3.英语成绩\t0.返回教师界面\n");
					char num = getch();
					int choose = num - '0';
					int score;
					switch(choose) {
					case 0:
						break;
					case 1:
						printf("\n请输入重新录入的语文成绩(0到100)：");
						if (fgets(tep, sizeof(tep), stdin) == NULL) {
							printf("发生了错误！没能读入语文成绩\n");
							return;
						}
						if (!strcmp(tep, "\n")) {
							printf("输入非法，即将返回教师界面......\n");
							system("pause");
							return;
						}
						tep[strcspn(tep, "\n")] = 0;
						fflush(stdin);
						if (sscanf(tep, "%d", &score) != 1 || score < 0 || score > 100) {
							printf("输入非法，未能成功录入！\n");
						}
						else {
							move->chinese = score;
							pmove->chinese = score;
							printf("修改成功\n");
							system("pause");
						}
						break;
					case 2:
						printf("\n请输入重新录入的数学成绩(0到100)：");
						if (fgets(tep, sizeof(tep), stdin) == NULL) {
							printf("发生了错误！没能读入数学成绩\n");
							return;
						}
						if (!strcmp(tep, "\n")) {
							printf("输入非法，即将返回教师界面......\n");
							system("pause");
							return;
						}
						tep[strcspn(tep, "\n")] = 0;
						fflush(stdin);
						if (sscanf(tep, "%d", &score) != 1 || score < 0 || score > 100) {
							printf("输入非法，未能成功录入！\n");
						}
						else {
							move->math = score;
							pmove->math = score;
							printf("修改成功\n");
							system("pause");
						}
						break;
					case 3:
						printf("\n请输入重新录入的英语成绩(0到100)：");
						if (fgets(tep, sizeof(tep), stdin) == NULL) {
							printf("发生了错误！没能读入英语成绩\n");
							return;
						}
						if (!strcmp(tep, "\n")) {
							printf("输入非法，即将返回教师界面......\n");
							system("pause");
							return;
						}
						tep[strcspn(tep, "\n")] = 0;
						fflush(stdin);
						if (sscanf(tep, "%d", &score) != 1 || score < 0 || score > 100) {
							printf("输入非法，未能成功录入！\n");
						}
						else {
							move->english = score;
							pmove->english = score;
							printf("修改成功\n");
							system("pause");
						}
						break;
					default:
						printf("\n\n\n请根据提示操作！\n");
						system("pause");
						break;
					}
					if (choose == 0) {
						printf("\n返回成功！\n");
						printf("这是修改后的信息->\n姓名：%s\t学号：%s\t班级：%s\t语文成绩：%d：\t数学成绩：%d\t英语成绩：%d\n", move->name, move->account, move->hClass, move->chinese,move->math, move->english);
						system("pause");
						return;
					}
					system("cls");
				}
			}
		}
		else {
			printf("账号/学号不存在！即将返回教师界面......\n");
			system("pause");
			break;
		}
	}
	return;
}

void Look(STU student) {
	while (1) {
		system("cls");
		printf("请输入您想要查询的科类：\n\t1.语文\t2.数学\t3.英语\n\t4.语数英\t0.返回教师界面\n");
		char num = getch();
		int choose = num - '0';
		STU move = student->next;
		char tep[3];
		int score1, score2, score3;
		switch(choose) {
		case 0:
			break;
		case 1:
			while (1) {
				printf("你想查找分数:1.以上\t2.以下\n");
				char flag = getch();
				int hh = flag - '0';
				switch (hh) {
				case 1:
					printf("您想查询多少分及以上：（0到100）\n");
					if (fgets(tep, sizeof(tep), stdin) == NULL) {
						printf("未能成功读取要求！即将返回上一层\n");
						break;
					}
					if (!strcmp(tep, "\n")) {
						printf("输入非法，即将返回教师界面......\n");
						system("pause");
						return;
					}
					tep[strcspn(tep, "\n")] = 0;
					fflush(stdin);
					if (sscanf(tep, "%d", &score1) != 1 || score1 > 100 || score1 < 0) {
						printf("未按照规范形式，即将返回上一层\n");
						continue;
					}
					system("cls");
					printf("语文高于%d学生如下：\n", score1);
					printf("姓名\t语文\n");
					while (move != NULL) {
						if (move->chinese > score1) {
							printf("%s\t%d\n", move->name, move->chinese);
						}
						move = move->next;
					}
					break;
				case 2:
					printf("您想查询多少分及以下：（0到100）\n");
					if (fgets(tep, sizeof(tep), stdin) == NULL) {
						printf("未能成功读取要求！即将返回上一层\n");
						break;
					}
					if (!strcmp(tep, "\n")) {
						printf("输入非法，即将返回教师界面......\n");
						system("pause");
						return;
					}
					tep[strcspn(tep, "\n")] = 0;
					fflush(stdin);
					if (sscanf(tep, "%d", &score1) != 1 || score1 > 100 || score1 < 0) {
						printf("未按照规范形式，即将返回上一层\n");
						continue;
					}
					system("cls");
					printf("语文低于%d学生如下：\n", score1);
					printf("姓名\t语文\n");
					while (move != NULL) {
						if (move->chinese < score1) {
							printf("%s\t%d\n", move->name, move->chinese);
						}
						move = move->next;
					}
					break;
				default:
					printf("\n\n\n请根据提示操作！\n");
					system("pause");
					break;
				}
				if (hh == 1 || hh == 2) {
					break;
				}
			}
			break;
		case 2:
			while (1) {
				printf("你想查找分数:1.以上\t2.以下\n");
				char flag = getch();
				int hh = flag - '0';
				switch (hh) {
				case 1:
					printf("您想查询多少分及以上：（0到100）\n");
					if (fgets(tep, sizeof(tep), stdin) == NULL) {
						printf("未能成功读取要求！即将返回上一层\n");
						break;
					}
					if (!strcmp(tep, "\n")) {
						printf("输入非法，即将返回教师界面......\n");
						system("pause");
						return;
					}
					tep[strcspn(tep, "\n")] = 0;
					fflush(stdin);
					if (sscanf(tep, "%d", &score1) != 1 || score1 > 100 || score1 < 0) {
						printf("未按照规范形式，即将返回上一层\n");
						continue;
					}
					system("cls");
					printf("数学高于%d学生如下：\n", score1);
					printf("姓名\t数学\n");
					while (move != NULL) {
						if (move->math > score1) {
							printf("%s\t%d\n", move->name, move->math);
						}
						move = move->next;
					}
					break;
				case 2:
					printf("您想查询多少分及以下：（0到100）\n");
					if (fgets(tep, sizeof(tep), stdin) == NULL) {
						printf("未能成功读取要求！即将返回上一层\n");
						break;
					}
					if (!strcmp(tep, "\n")) {
						printf("输入非法，即将返回教师界面......\n");
						system("pause");
						return;
					}
					tep[strcspn(tep, "\n")] = 0;
					fflush(stdin);
					if (sscanf(tep, "%d", &score1) != 1 || score1 > 100 || score1 < 0) {
						printf("未按照规范形式，即将返回上一层\n");
						continue;
					}
					system("cls");
					printf("数学低于%d学生如下：\n", score1);
					printf("姓名\t数学\n");
					while (move != NULL) {
						if (move->math < score1) {
							printf("%s\t%d\n", move->name, move->math);
						}
						move = move->next;
					}
					break;
				default:
					printf("\n\n\n请根据提示操作！\n");
					system("pause");
					break;
				}
				if (hh == 1 || hh == 2) {
					break;
				}
			}
			break;
		case 3:
			while (1) {
				printf("你想查找分数:1.以上\t2.以下\n");
				char flag = getch();
				int hh = flag - '0';
				switch (hh) {
				case 1:
					printf("您想查询多少分及以上：（0到100）\n");
					if (fgets(tep, sizeof(tep), stdin) == NULL) {
						printf("未能成功读取要求！即将返回上一层\n");
						break;
					}
					if (!strcmp(tep, "\n")) {
						printf("输入非法，即将返回教师界面......\n");
						system("pause");
						return;
					}
					tep[strcspn(tep, "\n")] = 0;
					fflush(stdin);
					if (sscanf(tep, "%d", &score1) != 1 || score1 > 100 || score1 < 0) {
						printf("未按照规范形式，即将返回上一层\n");
						continue;
					}
					system("cls");
					printf("英语高于%d学生如下：\n", score1);
					printf("姓名\t英语\n");
					while (move != NULL) {
						if (move->english > score1) {
							printf("%s\t%d\n", move->name, move->english);
						}
						move = move->next;
					}
					break;
				case 2:
					printf("您想查询多少分及以下：（0到100）\n");
					if (fgets(tep, sizeof(tep), stdin) == NULL) {
						printf("未能成功读取要求！即将返回上一层\n");
						break;
					}
					if (!strcmp(tep, "\n")) {
						printf("输入非法，即将返回教师界面......\n");
						system("pause");
						return;
					}
					tep[strcspn(tep, "\n")] = 0;
					fflush(stdin);
					if (sscanf(tep, "%d", &score1) != 1 || score1 > 100 || score1 < 0) {
						printf("未按照规范形式，即将返回上一层\n");
						continue;
					}
					system("cls");
					printf("英语低于%d学生如下：\n", score1);
					printf("姓名\t英语\n");
					while (move != NULL) {
						if (move->english < score1) {
							printf("%s\t%d\n", move->name, move->english);
						}
						move = move->next;
					}
					break;
				default:
					printf("\n\n\n请根据提示操作！\n");
					system("pause");
					break;
				}
				if (hh == 1 || hh == 2) {
					break;
				}
			}
			break;
		case 4:
			while (1) {
				printf("你想查找分数:1.以上\t2.以下\n");
				char flag = getch();
				int hh = flag - '0';
				switch (hh) {
				case 1:
					printf("您想查询语文多少分及以上：（0到100）\n");
					if (fgets(tep, sizeof(tep), stdin) == NULL) {
						printf("未能成功读取要求！即将返回上一层\n");
						break;
					}
					if (!strcmp(tep, "\n")) {
						printf("输入非法，即将返回教师界面......\n");
						system("pause");
						return;
					}
					tep[strcspn(tep, "\n")] = 0;
					fflush(stdin);
					if (sscanf(tep, "%d", &score1) != 1 || score1 > 100 || score1 < 0) {
						printf("未按照规范形式，即将返回上一层\n");
						continue;
					}
					printf("您想查询数学多少分及以上：（0到100）\n");
					if (fgets(tep, sizeof(tep), stdin) == NULL) {
						printf("未能成功读取要求！即将返回上一层\n");
						break;
					}
					if (!strcmp(tep, "\n")) {
						printf("输入非法，即将返回教师界面......\n");
						system("pause");
						return;
					}
					tep[strcspn(tep, "\n")] = 0;
					fflush(stdin);
					if (sscanf(tep, "%d", &score2) != 1 || score2 > 100 || score2 < 0) {
						printf("未按照规范形式，即将返回上一层\n");
						continue;
					}
					printf("您想查询英语多少分及以上：（0到100）\n");
					if (fgets(tep, sizeof(tep), stdin) == NULL) {
						printf("未能成功读取要求！即将返回上一层\n");
						break;
					}
					if (!strcmp(tep, "\n")) {
						printf("输入非法，即将返回教师界面......\n");
						system("pause");
						return;
					}
					tep[strcspn(tep, "\n")] = 0;
					fflush(stdin);
					if (sscanf(tep, "%d", &score3) != 1 || score3 > 100 || score3 < 0) {
						printf("未按照规范形式，即将返回上一层\n");
						continue;
					}
					system("cls");
					printf("语文高于%d且数学高于%d且英语高于%d学生如下：\n", score1, score2, score3);
					printf("姓名\t语文\t数学\t英语\n");
					while (move != NULL) {
						if (move->chinese > score1 && move->math > score2 && move->english > score3) {
							printf("%s\t%d\t%d\t%d\n", move->name, move->chinese, move->math, move->english);
						}
						move = move->next;
					}
					break;
				case 2:
					printf("您想查询语文多少分及以下：（0到100）\n");
					if (fgets(tep, sizeof(tep), stdin) == NULL) {
						printf("未能成功读取要求！即将返回上一层\n");
						break;
					}
					if (!strcmp(tep, "\n")) {
						printf("输入非法，即将返回教师界面......\n");
						system("pause");
						return;
					}
					tep[strcspn(tep, "\n")] = 0;
					fflush(stdin);
					if (sscanf(tep, "%d", &score1) != 1 || score1 > 100 || score1 < 0) {
						printf("未按照规范形式，即将返回上一层\n");
						continue;
					}
					printf("您想查询数学多少分及以下：（0到100）\n");
					if (fgets(tep, sizeof(tep), stdin) == NULL) {
						printf("未能成功读取要求！即将返回上一层\n");
						break;
					}
					if (!strcmp(tep, "\n")) {
						printf("输入非法，即将返回教师界面......\n");
						system("pause");
						return;
					}
					tep[strcspn(tep, "\n")] = 0;
					fflush(stdin);
					if (sscanf(tep, "%d", &score2) != 1 || score2 > 100 || score2 < 0) {
						printf("未按照规范形式，即将返回上一层\n");
						continue;
					}
					printf("您想查询英语多少分及以下：（0到100）\n");
					if (fgets(tep, sizeof(tep), stdin) == NULL) {
						printf("未能成功读取要求！即将返回上一层\n");
						break;
					}
					if (!strcmp(tep, "\n")) {
						printf("输入非法，即将返回教师界面......\n");
						system("pause");
						return;
					}
					tep[strcspn(tep, "\n")] = 0;
					fflush(stdin);
					if (sscanf(tep, "%d", &score3) != 1 || score3 > 100 || score3 < 0) {
						printf("未按照规范形式，即将返回上一层\n");
						continue;
					}
					system("cls");
					printf("语文低于%d且数学低于%d且英语低于%d学生如下：\n", score1, score2, score3);
					printf("姓名\t语文\t数学\t英语\n");
					while (move != NULL) {
						if (move->chinese < score1 && move->math < score2 && move->english < score3) {
							printf("%s\t%d\t%d\t%d\n", move->name, move->chinese, move->math, move->english);
						}
						move = move->next;
					}
					break;
				default:
					printf("\n\n\n请根据提示操作！\n");
					system("pause");
					break;
				}
				if (hh == 1 || hh == 2) {
					break;
				}
			}
			break;
		default:
			printf("\n\n\n请根据提示操作！\n");
			system("pause");
			break;
		}
		if (choose == 0) {
			break;
		}
		system("pause");
		system("cls");
	}
	return;
}

void OutputScore(STU student) {
	while (1) {
		system("cls");
		printf("请输入您想要输出的科目：\n\t1.语文\t2.数学\t3.英语\n\t4.总分\t5.四项\t0.返回教师界面\n");
		char num = getch();
		int choose = num - '0';
		STU move = student->next;
		system("cls");
		switch(choose) {
		case 0:
			break;
		case 1:
			printf("学号\t\t姓名\t语文成绩：\n");
			while (move != NULL) {
				printf("%s\t%s\t%d\n", move->account, move->name, move->chinese);
				move = move->next;
			}
			break;
		case 2:
			printf("学号\t\t姓名\t数学成绩：\n");
			while (move != NULL) {
				printf("%s\t%s\t%d\n", move->account, move->name, move->math);
				move = move->next;
			}
			break;
		case 3:
			printf("学号\t\t姓名\t英语成绩：\n");
			while (move != NULL) {
				printf("%s\t%s\t%d\n", move->account, move->name, move->english);
				move = move->next;
			}
			break;
		case 4:
			printf("学号\t\t姓名\t总成绩：\n");
			while (move != NULL) {
				printf("%s\t%s\t%d\n", move->account, move->name, move->chinese + move->math + move->english);
				move = move->next;
			}
			break;
		case 5:
			printf("\t\t学号\t\t姓名\t语文\t数学\t英语\t总分\n");
			while (move != NULL) {
				printf("\t\t%s\t%s\t%d\t%d\t%d\t%d\n", move->account, move->name, move->chinese, move->math, move->english, move->chinese + move->math + move->english);
				move = move->next;
			}
			break;
		default:
			printf("\n\n\n请根据提示操作！\n");
			break;
		}
		if (choose == 0) {
			printf("输出完成！\n");
			break;
		}
		system("pause");
		system("cls");
	}
	return;
}

void download(STU student) {
	FILE* fp = fopen("score.txt", "w+");
	if (fp == NULL) {
		printf("打开文件score.txt失败\n");
		return;
	}
	while (1) {
		system("cls");
		printf("请输入您想要下载的科目：\n\t1.语文\t2.数学\t3.英语\n\t4.总分\t5.四项\t0.返回教师界面\n");
		char num = getch();
		int choose = num - '0';
		STU move = student->next;
		switch(choose) {
		case 0:
			break;
		case 1:
			fprintf(fp, "姓名\t语文\n");
			while (move != NULL) {
				fprintf(fp, "%s\t%d\n", move->name, move->chinese);
				move = move->next;
			}
			break;
		case 2:
			fprintf(fp, "姓名\t数学\n");
			while (move != NULL) {
				fprintf(fp, "%s\t%d\n", move->name, move->math);
				move = move->next;
			}
			break;
		case 3:
			fprintf(fp, "姓名\t英语\n");
			while (move != NULL) {
				fprintf(fp, "%s\t%d\n", move->name, move->english);
				move = move->next;
			}
			break;
		case 4:
			fprintf(fp, "姓名\t总分\n");
			while (move != NULL) {
				fprintf(fp, "%s\t%d\n", move->name, move->chinese + move->math + move->english);
				move = move->next;
			}
			break;
		case 5:
			fprintf(fp, "\t\t学号\t\t姓名\t语文\t数学\t英语\t总分\n");
			while (move != NULL) {
				fprintf(fp, "\t\t%s\t%s\t%d\t%d\t%d\t%d\n", move->account, move->name, move->chinese, move->math, move->english, move->chinese + move->math + move->english);
				move = move->next;
			}
			break;
		default:
			printf("\n\n\n请根据提示操作！\n");
			system("pause");
			break;
		}
		if (choose == 0 || choose == 1 || choose == 2 || choose == 3 || choose == 4 || choose == 5) {
			break;
		}
		system("cls");
	}
	printf("下载完成\n");
	system("pause");
	fclose(fp);
	return;
}

void Analyse(STU student) {
	while (1) {
		system("cls");
		printf("请输入您想要分析的科目->\n\t1.语文\t2.数学\n\t3.英语\t4.总分\t0.返回教师界面\n");
		char num = getch();
		int choose = num - '0';
		STU move = student->next;
		int pcount = 0;
		int pscore = 0;
		int max = 0;
		switch(choose) {
		case 0:
			break;
		case 1:
			while (move != NULL) {
				max = fmax(max, move->chinese);
				pcount++;
				pscore += move->chinese;
				move = move->next;
			}
			printf("语文平均分为%.1lf，最高分为%d\n", 1.0 * pscore / pcount, max);
			break;
		case 2:
			while (move != NULL) {
				max = fmax(max, move->math);
				pcount++;
				pscore += move->math;
				move = move->next;
			}
			printf("数学平均分为%.1lf，最高分为%d\n", 1.0 * pscore / pcount, max);
			break;
		case 3:
			while (move != NULL) {
				max = fmax(max, move->english);
				pcount++;
				pscore += move->english;
				move = move->next;
			}
			printf("英语平均分为%.1lf，最高分为%d\n", 1.0 * pscore / pcount, max);
			break;
		case 4:
			while (move != NULL) {
				max = fmax(max, move->chinese + move->math + move->english);
				pcount++;
				pscore += move->chinese + move->math + move->english;
				move = move->next;
			}
			printf("总分平均分为%.1lf，最高分为%d\n", 1.0 * pscore / pcount, max);
			break;
		default:
			printf("\n\n\n请根据提示操作！\n");
			system("pause");
			break;
		}
		if (choose == 0) {
			break;
		}
		system("pause");
		system("cls");
	}
	return;
}

void Remind(TEA teacher) {
	system("cls");
	char tep[1000];
	printf("\n\t\t\t\t\t提醒更新\n");
	printf("\t\t\t---------------------------------------------\n");
	printf("\t\t\t请输入需要更新的内容：（单字符0即表示无需要提醒）(需要更新学生成绩请输入相应学生的学号！)\n\n\t\t\t");
	if (fgets(tep, sizeof(tep), stdin) == NULL) {
		printf("发生了错误！没能读入需要更新的内容\n");
		return;
	}
	if (!strcmp(tep, "\n")) {
		printf("输入非法，即将返回教师界面......\n");
		system("pause");
		return;
	}
	tep[strcspn(tep, "\n")] = 0;
	fflush(stdin);
	strcpy(teacher->remind, tep);
	printf("\n\t\t\t需要更新的内容已提交，请等待管理员处理！\n");
	printf("\t\t\t---------------------------------------------\n");
	system("pause");
	return;
}

void SecureTea(TEA teacher) {
	system("cls");
	char tep[100];
	if (!strcmp(teacher->secure, "0")) {
		printf("无密保可直接修改，请输入您的密保信息：(单字符0即表示不设密保)\n");
		if (fgets(tep, sizeof(tep), stdin) == NULL) {
			printf("发生了错误！没能读入密保内容\n");
			return;
		}
		if (!strcmp(tep, "\n")) {
			printf("输入非法，即将返回教师界面......\n");
			system("pause");
			return;
		}
		tep[strcspn(tep, "\n")] = 0;
		fflush(stdin);
		strcpy(teacher->secure, tep);
		printf("密保已更新！\n");
	}
	else {
		printf("请输入您设置的密保信息：\n");
		if (fgets(tep, sizeof(tep), stdin) == NULL) {
			printf("发生了错误！没能读入您的输入\n");
			return;
		}
		if (!strcmp(tep, "\n")) {
			printf("输入非法，即将返回教师界面......\n");
			system("pause");
			return;
		}
		tep[strcspn(tep, "\n")] = 0;
		fflush(stdin);
		if (!strcmp(tep, teacher->secure)) {
			printf("密保正确!下来请输入您希望更改的密保：（单字符0即表示不设密保）\n");
			if (fgets(tep, sizeof(tep), stdin) == NULL) {
				printf("发生了错误！没能读入密保内容\n");
				return;
			}
			if (!strcmp(tep, "\n")) {
				printf("输入非法，即将返回教师界面......\n");
				system("pause");
				return;
			}
			tep[strcspn(tep, "\n")] = 0;
			fflush(stdin);
			strcpy(teacher->secure, tep);
			printf("密保已更新！\n");
		}
		else {
			printf("密保信息错误！即将返回教师端界面......\n");
		}
	}
	system("pause");
	return;
}

void ChangeTea(TEA teacher) {
	int flag1 = 0, flag2 = 0;
	while (1) {
		system("cls");
		char tep[100];
		printf("\t\t\t\t\t   ┅┅┅       信息填写     ┅┅┅       \n");
		printf("\t\t\t=========================================================\n");
		printf("\t\t\t1.姓名\n\t\t\t2.班级\n\t\t\t3.密保（用于进行权限的确认）（单字符0或者跳过填写即不设密保）\n\t\t\t0.结束信息填写，进入教师端界面（请确保姓名和班级填写正确）\n");
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
			strcpy(teacher->name, tep);
			flag1 = 1;
			printf("姓名填写成功\n");
			system("pause");
			break;
		case 2:
			printf("请输入您的班级：");
			if (fgets(tep, sizeof(tep), stdin) == NULL) {
				printf("未能成功读取班级！\n");
				return;
			}
			if (!strcmp(tep, "\n")) {
				printf("输入为空，无效输入\n");
				system("pause");
				break;
			}
			tep[strcspn(tep, "\n")] = 0;
			fflush(stdin);
			strcpy(teacher->hClass, tep);
			flag2 = 1;
			printf("班级填写成功\n");
			system("pause");
			break;
		case 3:
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
			strcpy(teacher->secure, tep);
			printf("密保填写成功\n");
			system("pause");
			break;
		default:
			printf("\n\n\n请根据提示操作！\n");
			system("pause");
			break;
		}
		if (choose == 0) {
			if (flag1 == 1 && flag2 == 1) {
				break;
			}
			else {
				printf("请完整填写信息！\n");
				system("pause");
			}
		}
		system("cls");
	}
	return;
}

void SortStu(STU student) {
	while(1) {
		system("cls");
		STU tep, min, pre, i, j;
		printf("请选择排序依据：\n1.学号\t2.语文\t3.数学\t\n4.英语\t5.总分\t0.返回教师界面\n");
		char ptep = getch();
		int flag = ptep - '0';
		switch (flag) {
		case 0:
			return;
		case 1:
			while (1) {
			printf("1.升序排列\t2.降序排列\n");
			char num = getch();
			int choose = num - '0';
			switch (choose){
			case 1:
				for (i = student; i && i->next; i = i->next) {
					min = i->next;
					for (j = i->next, pre = i; j; pre = j, j = j->next) {
						if (strcmp(j->account, min->account) < 0) {
							min = j;
							tep = pre;
						}
					}
					if (i->next != min) {
						tep->next = min->next;
						min->next = i->next;
						i->next = min;
					}
				}
				break;
			case 2:
				for (i = student; i && i->next; i = i->next) {
					min = i->next;
					for (j = i->next, pre = i; j; pre = j, j = j->next) {
						if (strcmp(j->account, min->account) > 0) {
							min = j;
							tep = pre;
						}
					}
					if (i->next != min) {
						tep->next = min->next;
						min->next = i->next;
						i->next = min;
					}
				}
				break;
			default:
				printf("\n\n\n请根据提示操作！\n");
				system("pause");
				break;
			}
				if (choose == 1 || choose == 2) {
					break;
				}
			}
			break;
		case 2:
			while (1) {
				printf("1.升序排列\t2.降序排列\n");
				char num = getch();
				int choose = num - '0';
				switch (choose){
				case 1:
					for (i = student; i && i->next; i = i->next) {
						min = i->next;
						for (j = i->next, pre = i; j; pre = j, j = j->next) {
							if (j->chinese < min->chinese) {
								min = j;
								tep = pre;
							}
						}
						if (i->next != min) {
							tep->next = min->next;
							min->next = i->next;
							i->next = min;
						}
					}
					break;
				case 2:
					for (i = student; i && i->next; i = i->next) {
						min = i->next;
						for (j = i->next, pre = i; j; pre = j, j = j->next) {
							if (j->chinese > min->chinese) {
								min = j;
								tep = pre;
							}
						}
						if (i->next != min) {
							tep->next = min->next;
							min->next = i->next;
							i->next = min;
						}
					}
					break;
				default:
					printf("\n\n\n请根据提示操作！\n");
					system("pause");
					break;
				}
				if (choose == 1 || choose == 2) {
					break;
				}
			}
			break;
		case 3:
			while (1) {
				printf("1.升序排列\t2.降序排列\n");
				char num = getch();
				int choose = num - '0';
				switch (choose){
				case 1:
					for (i = student; i && i->next; i = i->next) {
						min = i->next;
						for (j = i->next, pre = i; j; pre = j, j = j->next) {
							if (j->math < min->math) {
								min = j;
								tep = pre;
							}
						}
						if (i->next != min) {
							tep->next = min->next;
							min->next = i->next;
							i->next = min;
						}
					}
					break;
				case 2:
					for (i = student; i && i->next; i = i->next) {
						min = i->next;
						for (j = i->next, pre = i; j; pre = j, j = j->next) {
							if (j->math > min->math) {
								min = j;
								tep = pre;
							}
						}
						if (i->next != min) {
							tep->next = min->next;
							min->next = i->next;
							i->next = min;
						}
					}
					break;
				default:
					printf("\n\n\n请根据提示操作！\n");
					system("pause");
					break;
				}
				if (choose == 1 || choose == 2) {
					break;
				}
			}
			break;
		case 4:
			while (1) {
				printf("1.升序排列\t2.降序排列\n");
				char num = getch();
				int choose = num - '0';
				switch (choose){
				case 1:
					for (i = student; i && i->next; i = i->next) {
						min = i->next;
						for (j = i->next, pre = i; j; pre = j, j = j->next) {
							if (j->english < min->english) {
								min = j;
								tep = pre;
							}
						}
						if (i->next != min) {
							tep->next = min->next;
							min->next = i->next;
							i->next = min;
						}
					}
					break;
				case 2:
					for (i = student; i && i->next; i = i->next) {
						min = i->next;
						for (j = i->next, pre = i; j; pre = j, j = j->next) {
							if (j->english > min->english) {
								min = j;
								tep = pre;
							}
						}
						if (i->next != min) {
							tep->next = min->next;
							min->next = i->next;
							i->next = min;
						}
					}
					break;
				default:
					printf("\n\n\n请根据提示操作！\n");
					system("pause");
					break;
				}
				if (choose == 1 || choose == 2) {
					break;
				}
			}
			break;
		case 5:
			while (1) {
				printf("1.升序排列\t2.降序排列\n");
				char num = getch();
				int choose = num - '0';
				switch (choose){
				case 1:
					for (i = student; i && i->next; i = i->next) {
						min = i->next;
						for (j = i->next, pre = i; j; pre = j, j = j->next) {
							if (j->english + j->chinese + j->math < min->english + min->chinese + min->math) {
								min = j;
								tep = pre;
							}
						}
						if (i->next != min) {
							tep->next = min->next;
							min->next = i->next;
							i->next = min;
						}
					}
					break;
				case 2:
					for (i = student; i && i->next; i = i->next) {
						min = i->next;
						for (j = i->next, pre = i; j; pre = j, j = j->next) {
							if (j->english + j->chinese + j->math > min->english + min->chinese + min->math) {
								min = j;
								tep = pre;
							}
						}
						if (i->next != min) {
							tep->next = min->next;
							min->next = i->next;
							i->next = min;
						}
					}
					break;
				default:
					printf("\n\n\n请根据提示操作！\n");
					system("pause");
					break;
				}
				if (choose == 1 || choose == 2) {
					break;
				}
			}
			break;
		default:
			printf("请根据提示操作\n");
			system("pause");
			break;
		}
		if (flag == 1 || flag == 2 || flag == 3 || flag == 4 || flag == 5) {
			printf("排序完成\n");
			system("pause");
			break;
		}
	}
	return;
}

void ResComplaint(STU student, STU pstudent, LPNODE phead) {
	STU move = student->next;
	while (move != NULL) {
		if(strcmp(move->complaint, "0")) {
			system("cls");
			STU cur = FindStuByAccount(move->account, pstudent);
			printf("账号%s 班级%s %s提出成绩申诉：%s\n", move->account, move->hClass, move->name, move->complaint);
			while(1) {
				printf("请您浏览：\n\t\t\t1.暂不予处理（保留申诉内容，下次仍能看到）\n\t\t\t2.已知晓即将处理（清空该条信息）\n\t\t\t3.垃圾信息直接清空\n\t\t\t0.返回上一层界面\n");
				char tep = getch();
				int num = tep - '0';
				switch (num) {
				case 0:
					return;
				case 1:
					break;
				case 2:
					printf("请记住申诉内容：\n账号%s 班级%s %s\n提出成绩申诉：%s\n", move->account, move->hClass, move->name, move->complaint);
					printf("即将自动进入更改成绩界面，请记得学生账号\n");
					strcpy(move->complaint, "0");
					strcpy(cur->complaint, "0");
					system("pause");
					Vary(pstudent, phead, student);
					break;
				case 3:
					strcpy(move->complaint, "0");
					strcpy(cur->complaint, "0");
					break;
				default:
					printf("请按照提示操作！\n");
					system("pause");
					break;
				}
				if (num == 1 || num == 2 || num == 3) {
					break;
				}
				system("cls");
			}
		}
		move = move->next;
	}
	system("cls");
	printf("无需要处理的申诉\n");
	system("pause");
	return;
}
