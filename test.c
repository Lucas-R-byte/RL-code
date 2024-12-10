#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
int count = 1; //用于计数的变量，从1开始因为第一行是1而不是0

typedef struct 
{
	char name[100];
	int score;
} Student;

Student students[MAX_STUDENTS]; 
int student_count = 0; 

void save_file()
{

	FILE* pf = fopen("grade.txt", "a+");
	if (pf == NULL)
	{
		printf("文件无法打开\n");
		return;
	}

	for (int i = 0; i < student_count; i++)
	{
		fprintf(pf, "%s %d\n", students[i].name, students[i].score);
	}
	fclose(pf);
	printf("学生信息已保存到文件。\n");
}
void input()//成绩输入
{
	int num = 0;
	printf("请选择输入数据数量:");
	scanf("%d", &num);
	for (int i = 1; i <= num; i++)
	{
		printf("成绩输入\n");
		printf("输入学生姓名: ");
		scanf("%49s", &students[student_count].name);
		printf("输入学生成绩: ");
		scanf("%d", &students[student_count].score);
		student_count++;
		printf("学生信息添加成功！\n");

	}
	save_file();
	system("pause");
}




void delete_file(const char* name_to_delete)
{
	FILE* fp = fopen("grade.txt", "r");
	FILE* fp1 = fopen("linshi.txt", "w"); // 创建一个临时文件用于写入
	char ch;
	char buffer[1024]; // 假设一行不会超过1024个字符,数组用于存储当前读取的行。
	int current_line = 0;
	int line_to_delete = -1;
	int found = 0;

	if (!fp || !fp1)
	{
		printf("文件打开失败\n");
		exit(1);
	}

	// 逐行读取原始文件的内容
	while (fgets(buffer, sizeof(buffer), fp))
	{
		current_line++;
		// 检查当前行是否包含要删除的名字
		if (strstr(buffer, name_to_delete) != NULL)//strstr 函数用于检查当前行是否包含指定的名字 name_to_delete
		{
			line_to_delete = current_line;
		}
		else if (current_line != line_to_delete)
		{
			// 如果当前行不是要删除的行，则将该行写入临时文件
			fputs(buffer, fp1);
		}
	}

	fclose(fp);
	fclose(fp1);

	// 删除原文件
	if (remove("grade.txt") != 0)
	{
		perror("删除原文件失败");
		exit(1);
	}

	// 将临时文件重命名为原文件名
	if (rename("linshi.txt", "grade.txt") != 0)
	{
		perror("重命名文件失败");
		exit(1);
	}
}

void del() // 成绩删除
{
	printf("成绩删除\n");
	char name_to_delete[100];
	printf("请输入要删除的学生姓名: ");
	scanf("%99s", name_to_delete); // 读取学生姓名，最多99个字符
	delete_file(name_to_delete);
	system("pause");
}





void find() 
{
	char name[100]; // 假设姓名不超过99个字符
	printf("成绩查找\n");
	printf("请输入要查找学生成绩的姓名:");
	scanf("%99s", name); // 使用%99s来避免缓冲区溢出

	FILE* fp = fopen("grade.txt", "r");
	if (fp == NULL) 
	{
		printf("文件打开失败\n");
		return; // 如果文件打开失败，则退出函数
	}

	char buffer[1024]; // 假设一行不会超过1024个字符
	int found = 0; // 标记是否找到姓名

	// 逐行读取文件内容
	while (fgets(buffer, sizeof(buffer), fp)) 
	{
		// 去除可能的换行符
		buffer[strcspn(buffer, "\n")] = 0;//strcspn 函数用于计算字符串中第一个匹配给定字符集中的字符的索引

		// 检查当前行是否包含要查找的姓名
		char* token = strtok(buffer, " ");//strtok 函数用于将字符串分割成一系列的标记（tokens）," " 是一个包含单个空格字符的字符串，它告诉 strtok 使用空格作为分隔符来分割 buffer
		if (token != NULL && strcmp(token, name) == 0)//trcmp 函数用于比较两个字符串
		{
			// 找到姓名后，打印成绩
			token = strtok(NULL, " "); // 假设姓名后紧跟成绩,在 strtok 的后续调用中传递 NULL，是为了告诉函数继续从上一次分割停止的地方开始处理字符串。这是因为 strtok 维护了一个内部静态指针，它记录了上一次调用时的位置。当第一次调用 strtok 时，这个指针被初始化，而在后续调用中，通过传递 NULL，函数会从这个内部指针指示的位置继续处理字符串。
			if (token != NULL) 
			{
				printf("找到学生 %s 的成绩: %s\n", name, token);
				found = 1; // 设置找到标记为真
			}
			else 
			{
				printf("未找到学生 %s 的成绩，格式错误\n", name);
			}
		}
	}

	if (!found)
	{
		printf("没有找到学生 %s 的成绩\n", name); // 如果没有找到，打印消息
	}

	fclose(fp); // 关闭文件
	system("pause");
}


void sort() 
{
	FILE* fp = fopen("grade.txt", "r");
	if (fp == NULL) 
	{
		printf("文件打开失败\n");
		return;
	}

	// 读取文件中的学生信息
	while (fscanf(fp, "%99s %d", students[student_count].name, &students[student_count].score) == 2) 
	{
		student_count++;
	}
	fclose(fp); // 关闭文件

	// 排序学生信息
	for (int i = 0; i < student_count-1; i++) 
	{
		for (int j = 0; j < student_count - i-1; j++) 
		{
			if (students[j].score < students[j + 1].score) 
			{
				// 交换两个学生的信息
				Student temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
		}
	}

	// 打印排序后的学生信息
	printf("学生信息已按成绩降序排序。\n");
	for (int i = 0; i < student_count; i++)
	{
		printf("%s %d\n", students[i].name, students[i].score);
	}
	system("pause");
}


void alter() 
{
	FILE* fp = fopen("grade.txt", "r");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return;
	}

	printf("成绩修改\n");

	// 重新读取文件中的学生信息，并存储到students数组中
	while (fscanf(fp, "%99s %d", students[student_count].name, &students[student_count].score) == 2)
	{
		student_count++;
	}
	fclose(fp); // 关闭文件

	// 打印当前的学生信息
	printf("当前学生信息：\n");
	for (int i = 0; i < student_count; i++)
	{
		printf("%s %d\n", students[i].name, students[i].score);
	}
	char name[100];
	// 修改成绩
	printf("请输入要修改的学生姓名：");
	scanf("%s", name);
	for (int i = 0; i < student_count; i++)
	{
		if (strcmp(students[i].name, name) == 0)
		{
			printf("请输入新的成绩：");
			scanf("%d", &students[i].score);
			break;
		}
	}

	// 重新写入文件
	fp = fopen("grade.txt", "w");
	if (fp == NULL) 
	{
		printf("文件写入失败\n");
		return;
	}
	for (int i = 0; i < student_count; i++) 
	{
		fprintf(fp, "%s %d\n", students[i].name, students[i].score);
	}
	fclose(fp); // 关闭文件

	printf("成绩修改完成。\n");
	system("pause");
}
void menu() 
{
	/*显示菜单*/
	system("cls");
	printf("\n\n\n\t\t\t欢迎使用学生成绩管理系统\n\n\n");
	printf("\t\t\t***********************\n");
	printf("\t\t\t        *主菜单*       \n");
	printf("\t\t\t***********************\n\n\n");
	printf("\t\t       1  成绩输入     2  成绩删除\n\n");
	printf("\t\t       3  成绩查找     4  成绩排序\n\n");
	printf("\t\t       5  成绩修改     6  退出系统\n\n");
	printf("\t\t       请选择【1/2/3/4/5/6】:");
}

int main()
{
	int j;
	while (1) 
	{
		menu();
		scanf("%d", &j);
		switch (j)
		{
		case 1:input(); break;
		case 2:del(); break;
		case 3:find(); break;
		case 4:sort(); break;
		case 5:alter(); break;
		case 6:exit(0);
		}
	}
	return 0;
}