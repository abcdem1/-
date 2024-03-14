#include "declaration.h"

int Administrator(LPNODE phead, TEA pteacher, STU pstudent) {
	system("color f8");
	while (1) {
		system("cls");
		printf("\t\t\t\t\t   ┅┅┅       管理员端     ┅┅┅       \n");
		printf("\t\t\t=========================================================\n");
		printf("\t\t\t1.查看代办选项\n\t\t\t2.进入教师端进行信息修改\n\t\t\t3.增加账号及密码\n\t\t\t4.删除账号及密码\n\t\t\t5.修改指定用户的密码\n\t\t\t6.查找指定用户的所有信息\n\t\t\t7.录入所有账号及密码（终端界面操作）\n\t\t\t8.输出所有账号密码\n\t\t\t9.手动重新录入（修改）学生信息\n\t\t\ta.锁定更改成绩权限\n\t\t\tb.解除权限锁定\n\t\t\tc.按学号排序\n\t\t\td.从文件中录入账号密码\n\t\t\te.退出并返回登陆界面\n\t\t\t0.退出并返回初始界面\n");
		printf("\t\t\t=========================================================\n");
		char num = getch();
		int choose;
		if (num == 'e') {
			return 0;
		}
		else if (num == 'd') {
			InsertFile(phead, pteacher, pstudent);
			continue;
		}
		else if (num == 'c') {
			SortAcc(phead);
			continue;
		}
		else if (num == 'a') {
			power = false;
			printf("更改成绩权限已经锁定\n");
			system("pause");
		}
		else if (num == 'b') {
			power = true;
			printf("更改成绩权限已经解开\n");
			system("pause");
		}
		else {
			choose = num - '0';
			switch (choose){
			case 0:
				break;
			case 1:
				ReviewAgency(phead, pteacher, pstudent);
				break;
			case 2:
				EnterPortalTeacher(phead, pteacher, pstudent);
				break;
			case 3:
				InsertMessage(phead, pteacher, pstudent);
				break;
			case 4:
				DeleteMessage(phead, pteacher, pstudent);
				break;
			case 5:
				ChangeMessage(phead, pteacher, pstudent);
				break;
			case 6:
				FindMessage(phead, pteacher, pstudent);
				break;
			case 7:
				InputAllMessage(phead, pteacher, pstudent);
				break;
			case 8:
				OutputAllMessage(phead);
				break;
			case 9:
				InputMessageInHand(phead, pteacher, pstudent);
				break;
			default:
				printf("\n\n\n请根据提示操作！\n");
				system("pause");
				break;
			}
			if (choose == 0) {
				break;
			}
		}
	}
	printf("成功登出！即将返回初始界面......\n");
	system("pause");
	return 1;
}
