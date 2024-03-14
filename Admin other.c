#include "declaration.h"

void EnterPortalTeacher(LPNODE phead, TEA pteacher, STU pstudent) {
	system("cls");
	printf("请输入您想要进入的教师界面账号：（退出教师端后自动返回管理员端）(8位)");
	char account[20];
	if (fgets(account, sizeof(account), stdin) == NULL) {
		printf("发生了错误！没能读入账号\n");
		return;
	}
	if (!strcmp(account, "\n") || strlen(account) != 9) {
		printf("无效输入，即将返回管理员端......\n");
		system("pause");
		return;
	}
	account[strcspn(account, "\n")] = 0;
	fflush(stdin);
	TEA move = FindTeaByAccount(account, pteacher);
	if (move == NULL) {
		printf("没能找到该教师！即将返回管理员界面......\n");
		system("pause");
	}
	else {
		Teacher(move, phead, pstudent, pteacher);
		system("color f8");
	}
	return;
}

void InsertMessage(LPNODE phead, TEA pteacher, STU pstudent) {
	system("cls");
	LPNODE newMessage = NewMessage();
	printf("\n\t\t\t请输入新账号：(8位)");
	if (fgets(newMessage->account, sizeof(newMessage->account), stdin) == NULL) {
		printf("发生了错误！没能读入账号\n");
		free(newMessage);
		return;
	}
	if (!strcmp(newMessage->account, "\n") || strlen(newMessage->account) != 9) {
		printf("输入非法，即将返回管理员界面......\n");
		free(newMessage);
		system("pause");
		return;
	}
	newMessage->account[strcspn(newMessage->account, "\n")] = 0;
	fflush(stdin);
	if (JudgeAccount(newMessage->account, phead)) {
		printf("该账号已存在或正在注册中！录入中断\n");
		free(newMessage);
		system("pause");
		return;
	}
	printf("\n\t\t\t请输入新密码：");
	if (fgets(newMessage->password, sizeof(newMessage->password), stdin) == NULL) {
		printf("发生了错误！没能读入密码\n");
		free(newMessage);
		return;
	}
	if (!strcmp(newMessage->password, "\n")) {
		printf("输入非法，即将返回管理员界面......\n");
		free(newMessage);
		system("pause");
		return;
	}
	newMessage->password[strcspn(newMessage->password, "\n")] = 0;
	fflush(stdin);
	while (1) {
		printf("\n\t\t\t请输入身份：1.学生\t2.教师\n");
		char tep = getch();
		int flag = tep - '0';
		switch (flag) {
		case 1:
			strcpy(newMessage->identity, "学生");
			STU newStudent = NewStudent();
			strcpy(newStudent->account, newMessage->account);
			strcpy(newStudent->name, "未命名");
			strcpy(newStudent->secure, "0");
			strcpy(newStudent->complaint, "0");
			strcpy(newStudent->hClass, "无");
			newStudent->chinese = 0;
			newStudent->math = 0;
			newStudent->english = 0;
			if (pstudent->next == NULL) {
				pstudent->next = newStudent;
			}
			else {
				newStudent->next = pstudent->next;
				pstudent->next = newStudent;
			}
			break;
		case 2 :
			strcpy(newMessage->identity, "教师");
			TEA newTeacher = NewTeacher();
			strcpy(newTeacher->account, newMessage->account);
			strcpy(newTeacher->secure, "0");
			strcpy(newTeacher->name, "未命名");
			strcpy(newTeacher->remind, "0");
			strcpy(newTeacher->hClass, "无");
			if (pteacher->next == NULL) {
				pteacher->next = newTeacher;
			}
			else {
				newTeacher->next = pteacher->next;
				pteacher->next = newTeacher;
			}
			break;
		default:
			printf("请按照提示操作！\n");
			system("pause");
			continue;
		}
		if (flag == 1 || flag == 2) {
			break;
		}
	}
	system("cls");
	while (1) {
		printf("\n\t\t\t请输入添加方式：1.普通添加\t2.精确添加\n");
		char tep = getch();
		int flag = tep - '0';
		switch (flag) {
		case 1:
			if (phead->next == NULL) {
				phead->next = newMessage;
			}
			else {
				newMessage->next = phead->next;
				phead->next = newMessage;
			}
			break;
		case 2 :
			printf("您想添加到哪个账号的后面：(8位)");
			char tep[20];
			if (fgets(tep, sizeof(tep), stdin) == NULL) {
				printf("发生了错误！没能读入账号\n");
				free(newMessage);
				return;
			}
			if (!strcmp(tep, "\n") || strlen(tep) != 9) {
				printf("输入非法，即将返回管理员界面......\n");
				free(newMessage);
				system("pause");
				return;
			}
			tep[strcspn(tep, "\n")] = 0;
			fflush(stdin);
			if (JudgeAccount(tep, phead)) {
				LPNODE pre = phead;
				LPNODE move = phead->next;
				while (move != NULL) {
					if (!strcmp(move->account, tep)) {
						break;
					}
					pre = move;
					move = move->next;
				}
				pre = move;
				move = move->next;
				pre->next = newMessage;
				newMessage->next = move;
			}
			else {
				printf("未找到该账号，即将采用普通添加的方式\n");
				if (phead->next == NULL) {
					phead->next = newMessage;
				}
				else {
					newMessage->next = phead->next;
					phead->next = newMessage;
				}
				system("pause");
				system("cls");
			}
			break;
		default:
			printf("请按照提示操作！\n");
			system("pause");
			continue;
		}
		if (flag == 1 || flag == 2) {
			break;
		}
	}
	printf("\n\n\n\n\t\t\t\t\t\t\t添加完成！\n");
	printf("\t\t\t这是具体信息：账号：%s\t密码：%s\t身份：%s\n",newMessage->account, newMessage->password, newMessage->identity);
	system("pause");
	return;
}

void DeleteMessage(LPNODE phead, TEA pteacher, STU pstudent) {
	system("cls");
	printf("\n\n\n\n\t\t\t请输入您想删除用户的账号：(8位)");
	char account[20];
	if (fgets(account, sizeof(account), stdin) == NULL) {
		printf("发生了错误！没能读入账号\n");
		return;
	}
	if (!strcmp(account, "\n") || strlen(account) != 9) {
		printf("输入非法，即将返回管理员界面......\n");
		system("pause");
		return;
	}
	account[strcspn(account, "\n")] = 0;
	fflush(stdin);
	LPNODE pre = phead;
	LPNODE move = phead->next;
	while (move != NULL) {
		if (!strcmp(move->account, account)) {
			break;
		}
		pre = move;
		move = move->next;
	}
	if (move == NULL) {
		printf("没能找到该用户！\n");
		system("pause");
	} 
	else {
		if (!strcmp(move->identity, "学生")) {
			STU ppre = pstudent;
			STU pmove = pstudent->next;
			while (pmove != NULL) {
				if (!strcmp(pmove->account, account)) {
					break;
				}
				ppre = pmove;
				pmove = pmove->next;
			}
			if (strcmp(pmove->hClass, "无")) {
				printf("无法删除，该学生仍在%s中，请先将该学生移除班级\n", pmove->hClass);
				system("pause");
				return;
			}
			ppre->next = pmove->next;
			free(pmove);
		}
		else if (!strcmp(move->identity, "教师")) {
			TEA ppre = pteacher;
			TEA pmove = pteacher->next;
			while (pmove != NULL) {
				if (!strcmp(pmove->account, account)) {
					break;
				}
				ppre = pmove;
				pmove = pmove->next;
			}
			if(strcmp(pmove->hClass, "无")){
				STU tep = pstudent;
				while (tep != NULL) {
					if (!strcmp(tep->hClass, pmove->hClass)) {
						printf("无法删除，该老师的班级中仍有学生，请先清空%s中的学生\n", pmove->hClass);
						system("pause");
						return;
					}
					tep = tep->next;
				}
			}
			ppre->next = pmove->next;
			free(pmove);
		}
		pre->next = move->next;
		free(move);
		printf("删除成功！\n");
	}
	system("pause");
	return;
}

void ChangeMessage(LPNODE phead, TEA pteacher, STU pstudent) {
	system("cls");
	printf("\n\n\n\n\t\t\t请输入您想更改用户密码的账号：(8位)");
	char account[20];
	if (fgets(account, sizeof(account), stdin) == NULL) {
		printf("发生了错误！没能读入账号\n");
		return;
	}
	if (!strcmp(account, "\n") || strlen(account) != 9) {
		printf("输入非法，即将返回管理员界面......\n");
		system("pause");
		return;
	}
	account[strcspn(account, "\n")] = 0;
	fflush(stdin);
	LPNODE move = FindAccount(account, phead);
	if (move == NULL) {
		printf("没能找到该用户！\n");
	}
	else {
		printf("找到了！\t这是具体信息:账号：%s\t密码：%s\t身份：%s\n", move->account, move->password, move->identity);
		system("pause");
		while(1) {
			char tep[20];
			system("cls");
			printf("请输入更改后的密码：");
			if (fgets(tep, sizeof(tep), stdin) == NULL) {
				printf("发生了错误！没能读入密码\n");
				return;
			}
			if (!strcmp(tep, "\n")) {
				printf("输入非法，即将返回管理员界面......\n");
				system("pause");
				return;
			}
			tep[strcspn(tep, "\n")] = 0;
			fflush(stdin);
			strcpy(move->password, tep);
		}
		system("cls");
		printf("这是修改后的信息：账号：%s\t密码：%s\t身份：%s\n", move->account, move->password, move->identity);
	}
	system("pause");
	return;
}

void FindMessage(LPNODE phead, TEA pteacher, STU pstudent) {
	system("cls");
	printf("\n\n\n\n\t\t\t请输入您想查找用户的账号：(8位)");
	char account[20];
	if (fgets(account, sizeof(account), stdin) == NULL) {
		printf("发生了错误！没能读入账号\n");
		return;
	}
	if (!strcmp(account, "\n") || strlen(account) != 9) {
		printf("输入非法，即将返回管理员界面......\n");
		system("pause");
		return;
	}
	account[strcspn(account, "\n")] = 0;
	fflush(stdin);
	LPNODE move = FindAccount(account, phead);
	if (move != NULL) {
		if (!strcmp(move->identity, "need enroll")) {
			printf("该用户正在注册中，请先处理其请求\n");
		}
		else if (!strcmp(move->identity, "学生")) {
			STU tep = FindStuByAccount(account, pstudent);
			printf("找到了！这是具体信息：\n账号：%s\t密码：%s\t身份：%s\n", move->account, move->password, move->identity);
			printf("姓名：%s\t班级：%s\n语文：%d\t数学：%d\t英语：%d\n", tep->name, tep->hClass, tep->chinese, tep->math, tep->english);
		}
		else {
			TEA tep = FindTeaByAccount(account, pteacher);
			printf("找到了！这是具体信息：\n账号：%s\t密码：%s\t身份：%s\n", move->account, move->password, move->identity);
			printf("姓名：%s\t班级：%s\n", tep->name, tep->hClass);
		}
	}
	else {
		printf("没能找到该用户！\n");
	}
	system("pause");
	return;
}

void InputAllMessage(LPNODE phead, TEA pteacher, STU pstudent) {
	system("cls");
	printf("\t\t\t\t--注意事项--\n");
	printf("读入顺序与项数：账号(8位)\t密码\t身份\n");
	printf("\t\t请在一行内只输入一组需要录入信息，保证各项间以空格间隙\n\t\t并且学生和教师请分别以1和2输入!\n");
	printf("\t\t请一定按照规范输入，否则将会半途停止或者录入错误！\n");
	system("pause");
	system("cls");
	printf("请开始您的输入:\n");
	printf("录完的信息将会自动显示！\n");
	printf("若已经输入完所有信息，请按两次回车\n");
	char tep[100];
	while (1) {
		LPNODE newMessage = NewMessage();
		if (fgets(tep, sizeof(tep), stdin) == NULL) {
			printf("未能成功读取账号！\n");
			free(newMessage);
			return;
		}
		tep[strcspn(tep, "\n")] = 0;
		fflush(stdin);
		if (tep[0] == '\0') {
			printf("输入为空，结束录入\n");
			free(newMessage);
			break;
		}
		if ((sscanf(tep, "%s %s %s", newMessage->account, newMessage->password, newMessage->identity) != 3) || strlen(newMessage->account) != 8) {
			printf("未按照规范形式，该行信息未能读入：%s\n", tep);
			free(newMessage);
			continue;
		}
		if (JudgeAccount(newMessage->account, phead)) {
			printf("该账号已存在！录入中断，自动进行下一行的录入\n");
			free(newMessage);
			system("pause");
			continue;
		}
		if (!strcmp(newMessage->identity, "1")) {
			strcpy(newMessage->identity, "学生");
			STU newStudent = NewStudent();
			strcpy(newStudent->account, newMessage->account);
			strcpy(newStudent->name, "未命名");
			strcpy(newStudent->secure, "0");
			strcpy(newStudent->complaint, "0");
			strcpy(newStudent->hClass, "无");
			newStudent->chinese = 0;
			newStudent->math = 0;
			newStudent->english = 0;
			if (pstudent->next == NULL) {
				pstudent->next = newStudent;
			}
			else {
				newStudent->next = pstudent->next;
				pstudent->next = newStudent;
			}
		}
		else if (!strcmp(newMessage->identity, "2")) {
			strcpy(newMessage->identity, "教师");
			TEA newTeacher = NewTeacher();
			strcpy(newTeacher->account, newMessage->account);
			strcpy(newTeacher->name, "未命名");
			strcpy(newTeacher->secure, "0");
			strcpy(newTeacher->remind, "0");
			strcpy(newTeacher->hClass, "无");
			if (pteacher->next != NULL) {
				newTeacher->next = pteacher->next;
				pteacher->next = newTeacher;
			}
			else {
				pteacher->next = newTeacher;
			}
		}
		else {
			printf("未按照规范形式（身份格式错误），该行信息未能读入：%s\n", tep);
			free(newMessage);
			continue;
		}
		fflush(stdin);
		if (phead->next == NULL) {
			phead->next = newMessage;
		}
		else {
			newMessage->next = phead->next;
			phead->next = newMessage;
		}
		printf("添加完毕=>账号：%s\t密码：%s\t身份：%s\n", newMessage->account, newMessage->password, newMessage->identity);
	}
	system("pause");
	return;
}

void OutputAllMessage(LPNODE phead) {
	system("cls");
	LPNODE move = phead->next;
	printf("   账号        密码        身份\n");
	while (move != NULL) {
		if (strcmp(move->identity, "need enroll")) {
			printf("%s      %s      %s\n", move->account, move->password, move->identity);
		}
		move = move->next;
	}
	printf("输出完成！\n");
	system("pause");
	return;
}

void SortAcc(LPNODE phead) {
	LPNODE tep, min, pre, i, j;
	system("cls");
	while (1) {
		printf("1.升序排列\t2.降序排列\t0.返回上一层\n");
		char num = getch();
		int choose = num - '0';
		switch (choose){
		case 0:
			return;
		case 1:
			for (i = phead; i && i->next; i = i->next) {
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
			for (i = phead; i && i->next; i = i->next) {
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
		system("cls");
	}
	printf("排序完成\n");
	system("pause");
	return;
}

void InputMessageInHand(LPNODE phead, TEA pteacher, STU pstudent) {
	int score1, score2, score3;
	char tep1[20], tep2[20];
	system("cls");
	printf("\n\n请输入您想要重新录入信息的学生账号：(8位)");
	char tep[20];
	if (fgets(tep, sizeof(tep), stdin) == NULL) {
		printf("发生了错误！没能读入账号\n");
		return;
	}
	if (!strcmp(tep, "\n") || strlen(tep) != 9) {
		printf("输入非法，即将返回管理员界面......\n");
		system("pause");
		return;
	}
	tep[strcspn(tep, "\n")] = 0;
	fflush(stdin);
	STU move = FindStuByAccount(tep, pstudent);
	if (move == NULL) {
		printf("没能找到该学生！即将返回管理员界面......\n");
		system("pause");
	}
	else {
		while(1) {
			system("cls");
			printf("\t\t\t\t\t   ┅┅┅     重新录入学生信息      ┅┅┅       \n");
			printf("\t\t\t=========================================================\n");
			printf("\t\t\t请输入您想要录入学生的信息:\n\t\t\t1.姓名\n\t\t\t2.班级\n\t\t\t3.语文成绩\n\t\t\t4.数学成绩\n\t\t\t5.英语成绩\n\t\t\t6.重制安保\n\t\t\t7.一键录入(无防护措施慎用)\n\t\t\t0.退出返回管理员界面\n");
			printf("\t\t\t=========================================================\n");
			char num = getch();
			int choose = num - '0';
			switch(choose) {
			case 0:
				break;
			case 1:
				printf("请输入重新录入的姓名：");
				if (fgets(tep1, sizeof(tep1), stdin) == NULL) {
					printf("发生了错误！没能读入姓名\n");
					return;
				}
				if (!strcmp(tep1, "\n")) {
					printf("输入非法，未成功录入......\n");
					system("pause");
					break;
				}
				tep1[strcspn(tep1, "\n")] = 0;
				fflush(stdin);
				strcpy(move->name, tep1);
				printf("录入成功\n");
				break;
			case 2:
				printf("请输入重新录入的班级：");
				if (fgets(tep2, sizeof(tep2), stdin) == NULL) {
					printf("发生了错误！没能读入班级\n");
					return;
				}
				if (!strcmp(tep2, "\n")) {
					printf("输入非法，未成功录入......\n");
					system("pause");
					break;
				}
				tep2[strcspn(tep2, "\n")] = 0;
				fflush(stdin);
				strcpy(move->hClass, tep2);
				printf("录入成功\n");
				break;
			case 3:
				printf("请输入重新录入的语文成绩(0到100)：");
				if (fgets(tep, sizeof(tep), stdin) == NULL) {
					printf("发生了错误！没能读入语文成绩\n");
					return;
				}
				if (!strcmp(tep, "\n")) {
					printf("输入非法，未成功录入......\n");
					system("pause");
					break;
				}
				tep[strcspn(tep, "\n")] = 0;
				fflush(stdin);
				if (sscanf(tep, "%d", &score1) != 1 || score1 < 0 || score1 > 100) {
					printf("输入非法，未能成功录入！\n");
				}
				else {
					move->chinese = score1;
					printf("录入成功\n");
				}
				break;
			case 4:
				printf("请输入重新录入的数学成绩(0到100)：");
				if (fgets(tep, sizeof(tep), stdin) == NULL) {
					printf("发生了错误！没能读入数学成绩\n");
					return;
				}
				if (!strcmp(tep, "\n")) {
					printf("输入非法，未成功录入......\n");
					system("pause");
					break;
				}
				tep[strcspn(tep, "\n")] = 0;
				fflush(stdin);
				if (sscanf(tep, "%d", &score2) != 1 || score2 < 0 || score2 > 100) {
					printf("输入非法，未能成功录入！\n");
				}
				else {
					move->math = score2;
					printf("录入成功\n");
				}
				break;
			case 5:
				printf("请输入重新录入的英语成绩(0到100)：");
				if (fgets(tep, sizeof(tep), stdin) == NULL) {
					printf("发生了错误！没能读入英语成绩\n");
					return;
				}
				if (!strcmp(tep, "\n")) {
					printf("输入非法，未成功录入......\n");
					system("pause");
					break;
				}
				tep[strcspn(tep, "\n")] = 0;
				fflush(stdin);
				if (sscanf(tep, "%d", &score3) != 1 || score3 < 0 || score3 > 100) {
					printf("输入非法，未能成功录入！\n");
				}
				else {
					move->english = score3;
					printf("录入成功\n");
				}
				break;
			case 6:
				strcpy(move->secure, "0");
				printf("重制成功！\n");
				break;
			case 7:
				printf("请输入：");
				char ptep[40];
				if (fgets(ptep, sizeof(ptep), stdin) == NULL) {
					printf("发生了错误！没能读入英语成绩\n");
					return;
				}
				if (!strcmp(ptep, "\n")) {
					printf("输入非法，未成功录入......\n");
					system("pause");
					break;
				}
				ptep[strcspn(ptep, "\n")] = 0;
				fflush(stdin);
				sscanf(ptep, "%s %s %d %d %d", move->name, move->hClass, &move->chinese, &move->math, &move->english);
					printf("录入完成\n");
				break;
			default:
				printf("\n\n\n请根据提示操作！\n");
				break;
			}
			if (choose == 0) {
				printf("退出成功！\n");
				printf("这是修改后的信息->\n姓名：%s\t学号：%s\t班级：%s\t语文成绩：%d：\t数学成绩：%d\t英语成绩：%d\n", move->name, move->account, move->hClass, move->chinese,move->math, move->english);
				system("pause");
				break;
			}
			system("pause");
			system("cls");
		}
	}
	return;
}

void InsertFile(LPNODE phead, TEA pteacher, STU pstudent) {
	system("cls");
	printf("\t\t\t\t--注意事项--\n");
	printf("读入顺序与项数：账号(8位)\t密码\t身份\n");
	printf("\t\t文件内请在一行内只输入一组需要录入信息，保证各项间以空格间隙\n\t\t并且学生和教师请分别以1和2输入!\n");
	printf("\t\t请一定按照规范输入，否则将会半途停止或者录入错误！\n");
	system("pause");
	system("cls");
	printf("请输入文件:\n");
	char tep[100];
	if (fgets(tep, sizeof(tep), stdin) == NULL) {
		printf("未能成功读取文件！\n");
		return;
	}
	tep[strcspn(tep, "\n")] = 0;
	fflush(stdin);
	FILE* fp = fopen(tep, "r+");
	if (fp == NULL) {
		printf("打开文件失败\n");
		system("pause");
		return;
	}
	while (!feof(fp)) {
		LPNODE newMessage = NewMessage();
		if (fgets(tep, sizeof(tep), fp) == NULL) {
			printf("未能成功读取账号！\n");
			free(newMessage);
			return;
		}
		tep[strcspn(tep, "\n")] = 0;
		fflush(stdin);
		if ((sscanf(tep, "%s %s %s", newMessage->account, newMessage->password, newMessage->identity) != 3) || strlen(newMessage->account) != 8) {
			printf("未按照规范形式，该行信息未能读入：%s\n", tep);
			free(newMessage);
			continue;
		}
		if (JudgeAccount(newMessage->account, phead)) {
			printf("该账号已存在！录入中断，自动进行下一行的录入\n");
			free(newMessage);
			system("pause");
			continue;
		}
		if (!strcmp(newMessage->identity, "1")) {
			strcpy(newMessage->identity, "学生");
			STU newStudent = NewStudent();
			strcpy(newStudent->account, newMessage->account);
			strcpy(newStudent->name, "未命名");
			strcpy(newStudent->secure, "0");
			strcpy(newStudent->complaint, "0");
			strcpy(newStudent->hClass, "无");
			newStudent->chinese = 0;
			newStudent->math = 0;
			newStudent->english = 0;
			if (pstudent->next == NULL) {
				pstudent->next = newStudent;
			}
			else {
				newStudent->next = pstudent->next;
				pstudent->next = newStudent;
			}
		}
		else if (!strcmp(newMessage->identity, "2")) {
			strcpy(newMessage->identity, "教师");
			TEA newTeacher = NewTeacher();
			strcpy(newTeacher->account, newMessage->account);
			strcpy(newTeacher->name, "未命名");
			strcpy(newTeacher->secure, "0");
			strcpy(newTeacher->remind, "0");
			strcpy(newTeacher->hClass, "无");
			if (pteacher->next != NULL) {
				newTeacher->next = pteacher->next;
				pteacher->next = newTeacher;
			}
			else {
				pteacher->next = newTeacher;
			}
		}
		else {
			printf("未按照规范形式（身份格式错误），该行信息未能读入：%s\n", tep);
			free(newMessage);
			continue;
		}
		fflush(stdin);
		if (phead->next == NULL) {
			phead->next = newMessage;
		}
		else {
			newMessage->next = phead->next;
			phead->next = newMessage;
		}
		printf("添加完毕=>账号：%s\t密码：%s\t身份：%s\n", newMessage->account, newMessage->password, newMessage->identity);
	}
	system("pause");
	fclose(fp);
	return;
}
