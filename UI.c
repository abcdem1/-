#include "declaration.h"

void Login(LPNODE phead, TEA pteacher, STU pstudent) {
	int count = 0;
	while (1) {
		system("cls");
		if (count == 3) {
			system("color 04");
			count = 0;
			for(int i = 0; i <= 100; i++) {
				printf("\n\n\n\n\n\n\t\t\t\t\t\t错误次数太多请稍后再试！");
				printf("\n\t\t\t\t\t\t我是惩罚进度条：%d\n", i);
				Sleep(100);
				if (i < 100) {
					system("cls");
				}
				else {
					printf("不要乱搞\n");
					system("pause");
					system("cls");
				}
			}
		}
		system("color 87");
		printf("\n");
		printf("\t\t\t\t\t\t 学生信息管理系统 \n");
		printf("\n\n\n");
		printf("\t\t\t\t\t   ┅┅┅       登录界面      ┅┅┅       \n");
		printf("\n\n\n");
		printf("\t\t\t\t\t======================================\n\n");
		printf("\t\t\t\t\t[请输入您的账号]：");
		char account[20];
		if (fgets(account, sizeof(account), stdin) == NULL) {
			printf("发生了错误！没能读入账号\n");
			continue;
		}
		if (!strcmp(account, "\n")) {
			printf("输入非法，即将返回初始界面\n");
			system("pause");
			break;
		}
		account[strcspn(account, "\n")] = 0;
		fflush(stdin);
		printf("\n\n\t\t\t\t\t======================================\n\n");
		if (JudgeAccount(account, phead)) {
			TEA cur = FindTeaByAccount(account, pteacher);
			if (cur != NULL) {
				if (!strcmp(cur->secure, "need show")) {
					LPNODE show = FindAccount(account, phead);
					printf("找回成功，你的密码是%s\n", show->password);
					printf("密保同时重置成功\n");
					strcpy(cur->secure, "0");
				}
			}
			STU curr = FindStuByAccount(account, pstudent);
			if (curr != NULL) {
				if (!strcmp(cur->secure, "need show")) {
					LPNODE show = FindAccount(account, phead);
					printf("找回成功，你的密码是%s\n", show->password);
					printf("密保同时重置成功\n");
					strcpy(cur->secure, "0");
				}
			}
		}
		printf("\t\t\t\t\t[请输入您的密码]：");
		char password[20];
		int i = 0;
		while (1) {
			if (i == 19) {
				printf("\n密码超出字数限制，即将返回初始界面......\n");
				system("pause");
				return;
			}
			char ptep = getch();
			if (ptep == '\r') {
				break;
			}
			else {
				password[i] = ptep;
				i++;
				printf("*");
			}
		}
		password[i] = '\0';
		password[strcspn(password, "\n")] = 0;
		fflush(stdin);
		printf("\n\t\t\t\t\t======================================\n");
		LPNODE tep = FindAccount(account, phead);
		if (!strcmp(IDENTITY, account) && !strcmp(ID, password)) {
			count = 0;
			if (Administrator(phead, pteacher, pstudent)) {
				break;
			}
			else {
				system("cls");
				continue;
			}
		}
		else if (JudgeTeacher(account, pteacher)) {
			if (!strcmp(tep->identity, "need enroll")) {
				printf("正在注册中，请等待管理员处理\n");
				system("pause");
				return;
			}
			if (JudgePassword(account, password, phead)) {
				count = 0;
				TEA move = FindTeaByAccount(account, pteacher);
				if (Teacher(move, phead, pstudent, pteacher)) {
					break;
				}
				else {
					system("cls");
					continue;
				}
			}
			else {
				printf("请输入正确的密码！\n");
				count++;
				system("pause");
				system("cls");
			}
		}
		else if (JudgeStudent(account, pstudent)) {
			if (!strcmp(tep->identity, "need enroll")) {
				printf("正在注册中，请等待管理员处理\n");
				system("pause");
				return;
			}
			if (JudgePassword(account, password, phead)) {
				count = 0;
				STU move = FindStuByAccount(account, pstudent);
				if (Student(move, pstudent)) {
					break;
				}
				else {
					system("cls");
					continue;
				}
			}
			else {
				count++;
				printf("请输入正确的密码！\n");
				system("pause");
				system("cls");
			}
		}
		else {
			count++;
			printf("该账号不存在\n");
			system("pause");
		}
	}
	return;
}

void Enroll(LPNODE phead) {
	system("cls");
	while (1) {
		system("cls");
		printf("\n");
		printf("\t\t\t\t\t\t 学生信息管理系统 \n");
		printf("\n\n\n");
		printf("\t\t\t\t\t   ┅┅┅       注册界面      ┅┅┅       \n");
		printf("\n\n\n");
		printf("\t\t\t\t\t=========================================================\n\n");
		printf("\t\t\t\t\t[请输入您想要并且未注册的账号]：(8位)");
		char account[20];
		if (fgets(account, sizeof(account), stdin) == NULL) {
			printf("发生了错误！没能读入账号\n");
			return;
		}
		if (!strcmp(account, "\n") || strlen(account) != 9) {
			printf("无效输入，即将返回初始界面\n");
			system("pause");
			return;
		}
		account[strcspn(account, "\n")] = 0;
		fflush(stdin);
		if (JudgeAccount(account, phead)) {
			printf("账号重复请换一个！\n");
			system("pause");
			continue;
		}
		printf("\n\t\t\t\t\t=========================================================\n\n");
		printf("\t\t\t\t\t[请输入您想要的密码]：");
		char password[20];
		if (fgets(password, sizeof(password), stdin) == NULL) {
			printf("发生了错误！没能读入密码\n");
			return;
		}
		if (!strcmp(password, "\n")) {
			printf("输入为空，无效输入，即将返回初始界面\n");
			system("pause");
			return;
		}
		password[strcspn(password, "\n")] = 0;
		fflush(stdin);
		LPNODE newMessage = NewMessage();
		strcpy(newMessage->account, account);
		strcpy(newMessage->password, password);
		strcpy(newMessage->identity, "need enroll");
		if (phead->next == NULL) {
			phead->next = newMessage;
		}
		else {
			newMessage->next = phead->next;
			phead->next = newMessage;
		}
		printf("注册请求发送成功！请等待管理员处理\n");
		system("pause");
		break;
	}
	return;
}

void Change(LPNODE phead, TEA pteacher, STU pstudent) {
	system("cls");
	printf("\n");
	printf("\t\t\t\t\t\t 学生信息管理系统 \n");
	printf("\n\n\n");
	printf("\t\t\t\t\t   ┅┅┅       修改界面      ┅┅┅       \n");
	printf("\n\n\n");
	printf("\t\t\t\t\t======================================\n\n");
	printf("\t\t\t\t\t[请输入您想要修改密码的账号]：(8位)");
	char account[20];
	if (fgets(account, sizeof(account), stdin) == NULL) {
		printf("发生了错误！没能读入账号\n");
		system("pause");
		return;
	}
	if (!strcmp(account, "\n") || strlen(account) != 9) {
		printf("无效输入，即将返回初始界面\n");
		system("pause");
		return;
	}
	account[strcspn(account, "\n")] = 0;
	fflush(stdin);
	LPNODE move = FindAccount(account, phead);
	if (move == NULL) {
		printf("该账号不存在!即将返回主界面......\n");
		system("pause");
		return;
	}
	else {
		while (1) {
			system("cls");
			if (!strcmp(move->identity, "need enroll")) {
				printf("正在注册中，请等待管理员处理\n");
				system("pause");
				return;
			}
			printf("请输入修改方式：\n1.忘记密保需反馈管理员重制密码(密码重制后与默认账号相同)\n2.根据密保修改\n0.返回主界面\n");
			char flag = getch();
			int choose = flag - '0';
			switch (choose) {
			case 0:
				return;
			case 1:
				if (!strcmp(move->identity, "学生")) {
					STU pmove = FindStuByAccount(account, pstudent);
					strcpy(pmove->secure, "need change");
				}
				if (!strcmp(move->identity, "教师")) {
					TEA ppmove = FindTeaByAccount(account, pteacher);
					strcpy(ppmove->secure, "need change");
				}
				break;
			case 2:
				break;
			default:
				printf("请按照提示操作！\n");
				system("pause");
				break;
			}
			if (choose == 1 || choose == 2) {
				break;
			}
			system("cls");
		}
		char tep[100];
		char limit[20];
		if (!strcmp(move->identity, "学生")) {
			STU pmove = FindStuByAccount(account, pstudent);
			if (!strcmp(pmove->secure, "0")) {
				printf("无密保，可直接修改密码\n");
				printf("请输入您的新密码：");
				if (fgets(limit, sizeof(limit), stdin) == NULL) {
					printf("发生了错误！没能读入新密码\n");
					system("pause");
					return;
				}
				if (!strcmp(limit, "\n")) {
					printf("输入为空，无效输入，即将返回初始界面\n");
					system("pause");
					return;
				}
				limit[strcspn(limit, "\n")] = 0;
				fflush(stdin);
				strcpy(move->password, limit);
				printf("修改成功，这是您的新密码：%s\n", move->password);
				system("pause");
				return;
			}
			printf("请输入密保信息：");
			if (fgets(tep, sizeof(tep), stdin) == NULL) {
				printf("发生了错误！没能读入密保信息\n");
				system("pause");
				return;
			}
			if (!strcmp(tep, "\n")) {
				printf("输入为空，无效输入，即将返回初始界面\n");
				system("pause");
				return;
			}
			tep[strcspn(tep, "\n")] = 0;
			fflush(stdin);
			if (!strcmp(tep, pmove->secure)) {
				printf("密保正确!\n");
				printf("请输入您的新密码：");
				if (fgets(limit, sizeof(limit), stdin) == NULL) {
					printf("发生了错误！没能读入新密码\n");
					system("pause");
					return;
				}
				if (!strcmp(limit, "\n")) {
					printf("输入为空，无效输入，即将返回初始界面\n");
					system("pause");
					return;
				}
				limit[strcspn(limit, "\n")] = 0;
				fflush(stdin);
				strcpy(move->password, limit);
				printf("修改成功，这是您的新密码：%s\n", move->password);
				system("pause");
			}
			else {
				printf("密保错误，即将返回主界面......\n");
				system("pause");
			}
		}
		if (!strcmp(move->identity, "教师")) {
			TEA pmove = FindTeaByAccount(account, pteacher);
			if (!strcmp(pmove->secure, "0")) {
				printf("无密保，可直接找回密码\n");
				printf("请输入您的新密码：");
				if (fgets(limit, sizeof(limit), stdin) == NULL) {
					printf("发生了错误！没能读入新密码\n");
					system("pause");
					return;
				}
				if (!strcmp(limit, "\n")) {
					printf("输入为空，无效输入，即将返回初始界面\n");
					system("pause");
					return;
				}
				limit[strcspn(limit, "\n")] = 0;
				fflush(stdin);
				strcpy(move->password, limit);
				printf("修改成功，这是您的新密码：%s\n", move->password);
				system("pause");
				return;
			}
			printf("请输入密保信息：");
			if (fgets(tep, sizeof(tep), stdin) == NULL) {
				printf("发生了错误！没能读入密保信息\n");
				system("pause");
				return;
			}
			if (!strcmp(limit, "\n")) {
				printf("输入为空，无效输入，即将返回初始界面\n");
				system("pause");
				return;
			}
			tep[strcspn(tep, "\n")] = 0;
			fflush(stdin);
			if (!strcmp(tep, pmove->secure)) {
				printf("密保正确!\n");
				printf("请输入您的新密码：");
				if (fgets(limit, sizeof(limit), stdin) == NULL) {
					printf("发生了错误！没能读入新密码\n");
					system("pause");
					return;
				}
				limit[strcspn(limit, "\n")] = 0;
				fflush(stdin);
				strcpy(move->password, limit);
				printf("修改成功，这是您的新密码：%s\n", move->password);
				system("pause");
			}
			else {
				printf("密保错误，即将返回主界面......\n");
				system("pause");
			}
		}
	}
	return;
}

void Back(LPNODE phead, TEA pteacher, STU pstudent) {
	system("cls");
	printf("\n");
	printf("\t\t\t\t\t\t 学生信息管理系统 \n");
	printf("\n\n\n");
	printf("\t\t\t\t\t   ┅┅┅       找回界面      ┅┅┅       \n");
	printf("\n\n\n");
	printf("\t\t\t\t\t======================================\n\n");
	printf("\t\t\t\t\t[请输入您想要找回密码的账号]：(8位)");
	char account[20];
	if (fgets(account, sizeof(account), stdin) == NULL) {
		printf("发生了错误！没能读入账号\n");
		system("pause");
		return;
	}
	if (!strcmp(account, "\n") || strlen(account) != 9) {
		printf("检测到恶意输入，即将返回初始界面\n");
		system("pause");
		return;
	}
	account[strcspn(account, "\n")] = 0;
	fflush(stdin);
	LPNODE move = FindAccount(account, phead);
	if (move == NULL) {
		printf("该账号不存在!即将返回主界面......\n");
		system("pause");
		return;
	}
	else {
		if (!strcmp(move->identity, "need enroll")) {
			printf("正在注册中，请等待管理员处理\n");
			system("pause");
			return;
		}
		TEA cur = FindTeaByAccount(account, pteacher);
		if (cur != NULL) {
			if (!strcmp(cur->secure, "need back")) {
				printf("正在找回中\n");
				system("pause");
				return;
			}
			if (!strcmp(cur->secure, "need show")) {
				LPNODE show = FindAccount(account, phead);
				printf("找回成功，你的密码是%s\n", show->password);
				printf("密保同时重置成功\n");
				strcpy(cur->secure, "0");
				system("pause");
				return;
			}
		}
		STU curr = FindStuByAccount(account, pstudent);
		if (curr != NULL) {
			if (!strcmp(curr->secure, "need back")) {
				printf("正在找回中\n");
				system("pause");
				return;
			}
			if (!strcmp(curr->secure, "need show")) {
				LPNODE show = FindAccount(account, phead);
				printf("找回成功，你的密码是%s\n", show->password);
				printf("密保同时重置成功\n");
				strcpy(cur->secure, "0");
				system("pause");
				return;
			}
		}
		while (1) {
			system("cls");
			printf("请输入找回方式：\n1.忘记密保需反馈管理员找回密码并且重置密保\n2.根据密保找回\n0.返回主界面\n");
			char flag = getch();
			int choose = flag - '0';
			switch (choose) {
			case 0:
				return;
			case 1:
				if (!strcmp(move->identity, "学生")) {
					STU pmove = FindStuByAccount(account, pstudent);
					strcpy(pmove->secure, "need back");
				}
				if (!strcmp(move->identity, "教师")) {
					TEA ppmove = FindTeaByAccount(account, pteacher);
					strcpy(ppmove->secure, "need back");
				}
				printf("反馈成功，请等待管理员处理\n");
				system("pause");
				return;
			case 2:
				break;
			default:
				printf("请按照提示操作！\n");
				system("pause");
				break;
			}
			if (choose == 1 || choose == 2) {
				break;
			}
			system("cls");
		}
		char tep[100];
		if (!strcmp(move->identity, "学生")) {
			STU pmove = FindStuByAccount(account, pstudent);
			if (!strcmp(pmove->secure, "0")) {
				printf("无密保，可直接找回密码\n");
				printf("您的密码是：%s\n", move->password);
				system("pause");
				return;
			}
			printf("请输入密保信息：");
			if (fgets(tep, sizeof(tep), stdin) == NULL) {
				printf("发生了错误！没能读入密保信息\n");
				system("pause");
				return;
			}
			if (!strcmp(tep, "\n")) {
				printf("输入为空，无效输入，即将返回初始界面\n");
				system("pause");
				return;
			}
			tep[strcspn(tep, "\n")] = 0;
			fflush(stdin);
			if (!strcmp(tep, pmove->secure)) {
				system("cls");
				printf("密保正确!\n");
				printf("您的密码是：%s\n", move->password);
				system("pause");
			}
			else {
				printf("密保错误，即将返回主界面......\n");
				system("pause");
			}
		}
		if (!strcmp(move->identity, "教师")) {
			TEA pmove = FindTeaByAccount(account, pteacher);
			if (!strcmp(pmove->secure, "0")) {
				printf("无密保，可直接找回密码\n");
				printf("您的密码是：%s\n", move->password);
				system("pause");
				return;
			}
			printf("请输入密保信息：");
			if (fgets(tep, sizeof(tep), stdin) == NULL) {
				printf("发生了错误！没能读入密保信息\n");
				system("pause");
				return;
			}
			if (!strcmp(tep, "\n")) {
				printf("输入为空，无效输入，即将返回初始界面\n");
				system("pause");
				return;
			}
			tep[strcspn(tep, "\n")] = 0;
			fflush(stdin);
			if (!strcmp(tep, pmove->secure)) {
				printf("密保正确!\n");
				printf("您的密码是：%s\n", move->password);
				system("pause");
			}
			else {
				printf("密保错误，即将返回主界面......\n");
				system("pause");
			}
		}
	}
	return;
}
