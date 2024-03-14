#include "declaration.h"

void ReviewAgency(LPNODE phead, TEA pteacher, STU pstudent) {
	while(1) {
		system("cls");
		printf("\t\t\t\t\t   ┅┅┅       代办     ┅┅┅       \n");
		printf("\t\t\t=========================================================\n");
		printf("\t\t\t1.密码注册\n\t\t\t2.密码修改\n\t\t\t3.密码找回\n\t\t\t4.更新成绩库\n\t\t\ta.返回上一层\n");
		printf("\t\t\t=========================================================\n");
		char num = getch();
		if (num == 'a') {
			break;
		}
		int	choose = num - '0';
		switch(choose) {
		case 1:
			ResEnroll(phead, pteacher, pstudent);
			break;
		case 2:
			ResChange(phead, pteacher, pstudent);
			break;
		case 3:
			ResBack(phead, pteacher, pstudent);
			break;
		case 4:
			ResUpdate(phead, pteacher, pstudent);
			break;
		default:
			printf("\n\n\n请根据提示操作！\n");
			system("pause");
			break;
		}
		system("cls");
	}
	return;
}

void ResEnroll(LPNODE phead, TEA pteacher, STU pstudent) {
	LPNODE pre = phead;
	LPNODE move = phead->next;
	while (move != NULL) {
		if (!strcmp(move->identity, "need enroll")) {
			while(1) {
				system("cls");
				printf("新注册用户：账号%s 密码%s\n", move->account, move->password);
				printf("请您浏览：\n\t\t\t1.暂不予处理（保留空账号内容，下次仍能看到）\n\t\t\t2.已知晓立即注册（清空该条信息）\n\t\t\t3.恶意注册立即清空账号\n\t\t\t0.返回上一层界面\n");
				char tep = getch();
				int num = tep - '0';
				switch (num) {
				case 0:
					return;
				case 1:
					break;
				case 2:
					while (1) {
						printf("请为该用户选择身份：1.学生\t2.教师\n");
						char flag = getch();
						int choose = flag - '0';
						switch (choose) {
						case 1:
							strcpy(move->identity, "学生");
							STU newStudent = NewStudent();
							strcpy(newStudent->account, move->account);
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
						case 2:
							strcpy(move->identity, "教师");
							TEA newTeacher = NewTeacher();
							strcpy(newTeacher->account, move->account);
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
							printf("\n\n\n请按照提示操作！\n");
							system("pause");
							break;
						}
						if (choose == 1 || choose == 2) {
							break;
						}
					}
					break;
				case 3:
					pre->next = move->next;
					free(move);
					printf("清除成功！\n");
					system("pause");
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
		if (move == NULL) {
			move = pre->next;
		}
		else {
			pre = move;
			move = move->next;
		}
	}
	system("cls");
	printf("无需要处理的注册\n");
	system("pause");
	return;
}

void ResChange(LPNODE phead, TEA pteacher, STU pstudent) {
	system("cls");
	TEA move = pteacher;
	while (move != NULL) {
		if(!strcmp(move->secure, "need change")) {
			printf("教师账号%s请求修改密码但忘记密保，需要重置密码\n", move->account);
			while(1) {
				printf("请您浏览：\n\t\t\t1.暂不予处理（保留请求内容，下次仍能看到）\n\t\t\t2.已知晓立即重置密码（清空该条信息）\n\t\t\t3.恶意请求不予理会\n\t\t\t0.返回上一层界面\n");
				char tep = getch();
				int num = tep - '0';
				switch (num) {
				case 0:
					return;
				case 1:
					break;
				case 2:
					LPNODE pmove = FindAccount(move->account, phead);
					strcpy (pmove->password, pmove->account);
					printf("重置完成\n");
					system("pause");
					break;
				case 3:
					strcpy(move->secure, "not need");
					printf("清除成功！\n");
					system("pause");
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
	STU ppmove = pstudent;
	while (ppmove != NULL) {
		if(!strcmp(ppmove->secure, "need change")) {
			printf("学生账号%s请求修改密码但忘记密保，需要重置密码\n", move->account);
			while(1) {
				printf("请您浏览：\n\t\t\t1.暂不予处理（保留请求内容，下次仍能看到）\n\t\t\t2.已知晓立即重置密码（清空该条信息）\n\t\t\t3.恶意请求不予理会\n\t\t\t0.返回上一层界面\n");
				char tep = getch();
				int num = tep - '0';
				switch (num) {
				case 0:
					return;
				case 1:
					break;
				case 2:
					LPNODE pmove = FindAccount(move->account, phead);
					strcpy (pmove->password, pmove->account);
					printf("重置完成\n");
					system("pause");
					break;
				case 3:
					strcpy(ppmove->secure, "not need");
					printf("清除成功！\n");
					system("pause");
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
		ppmove = ppmove->next;
	}
	system("cls");
	printf("无需要处理的修改\n");
	system("pause");
	return;
}

void ResBack(LPNODE phead, TEA pteacher, STU pstudent) {
	system("cls");
	TEA move = pteacher;
	while (move != NULL) {
		if(!strcmp(move->secure, "need back")) {
			printf("教师账号%s请求找回密码但忘记密保\n", move->account);
			while(1) {
				printf("请您浏览：\n\t\t\t1.暂不予处理（保留请求内容，下次仍能看到）\n\t\t\t2.已知晓立即找回（清空该条信息）\n\t\t\t3.恶意请求不予理会\n\t\t\t0.返回上一层界面\n");
				char tep = getch();
				int num = tep - '0';
				switch (num) {
				case 0:
					return;
				case 1:
					break;
				case 2:
					strcpy(move->secure, "need show");
					printf("处理完成\n");
					system("pause");
					break;
				case 3:
					strcpy(move->secure, "not need");
					printf("清除成功！\n");
					system("pause");
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
	STU ppmove = pstudent;
	while (ppmove != NULL) {
		if(!strcmp(ppmove->secure, "need back")) {
			printf("学生账号%s请求找回密码但忘记密保\n", move->account);
			while(1) {
				printf("请您浏览：\n\t\t\t1.暂不予处理（保留请求内容，下次仍能看到）\n\t\t\t2.已知晓立即找回（清空该条信息）\n\t\t\t3.恶意请求不予理会\n\t\t\t0.返回上一层界面\n");
				char tep = getch();
				int num = tep - '0';
				switch (num) {
				case 0:
					return;
				case 1:
					break;
				case 2:
					strcpy(ppmove->secure, "need show");
					printf("处理完成\n");
					system("pause");
					break;
				case 3:
					strcpy(ppmove->secure, "not need");
					printf("清除成功！\n");
					system("pause");
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
		ppmove = ppmove->next;
	}
	system("cls");
	printf("无需要处理的找回\n");
	system("pause");
	return;
}

void ResUpdate(LPNODE phead, TEA pteacher, STU pstudent) {
	TEA move = pteacher->next;
	while (move != NULL) {
		system("cls");
		if(strcmp(move->remind, "0")) {
			printf("账号%s 班级%s %s\n提醒更新：%s\n", move->account, move->hClass, move->name, move->remind);
			while(1) {
				printf("请您浏览：\n\t\t\t1.暂不予处理（保留待更新内容，下次仍能看到）\n\t\t\t2.已知晓即将更新（清空该条信息）\n\t\t\t3.垃圾信息直接清空\n");
				char tep = getch();
				int num = tep - '0';
				switch (num) {
				case 1:
					break;
				case 2:
					printf("请记住更新内容：\n账号%s 班级%s %s提醒更新：%s\n", move->account, move->hClass, move->name, move->remind);
					printf("请记住需要更改信息的学生账号，即将进入更改界面\n");
					strcpy(move->remind, "0");
					system("pause");
					InputMessageInHand(phead, pteacher, pstudent);
					break;
				case 3:
					strcpy(move->remind, "0");
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
	printf("无需要处理的提醒\n");
	system("pause");
	return;
}
