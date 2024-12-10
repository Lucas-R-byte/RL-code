#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
int count = 1; //���ڼ����ı�������1��ʼ��Ϊ��һ����1������0

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
		printf("�ļ��޷���\n");
		return;
	}

	for (int i = 0; i < student_count; i++)
	{
		fprintf(pf, "%s %d\n", students[i].name, students[i].score);
	}
	fclose(pf);
	printf("ѧ����Ϣ�ѱ��浽�ļ���\n");
}
void input()//�ɼ�����
{
	int num = 0;
	printf("��ѡ��������������:");
	scanf("%d", &num);
	for (int i = 1; i <= num; i++)
	{
		printf("�ɼ�����\n");
		printf("����ѧ������: ");
		scanf("%49s", &students[student_count].name);
		printf("����ѧ���ɼ�: ");
		scanf("%d", &students[student_count].score);
		student_count++;
		printf("ѧ����Ϣ��ӳɹ���\n");

	}
	save_file();
	system("pause");
}




void delete_file(const char* name_to_delete)
{
	FILE* fp = fopen("grade.txt", "r");
	FILE* fp1 = fopen("linshi.txt", "w"); // ����һ����ʱ�ļ�����д��
	char ch;
	char buffer[1024]; // ����һ�в��ᳬ��1024���ַ�,�������ڴ洢��ǰ��ȡ���С�
	int current_line = 0;
	int line_to_delete = -1;
	int found = 0;

	if (!fp || !fp1)
	{
		printf("�ļ���ʧ��\n");
		exit(1);
	}

	// ���ж�ȡԭʼ�ļ�������
	while (fgets(buffer, sizeof(buffer), fp))
	{
		current_line++;
		// ��鵱ǰ���Ƿ����Ҫɾ��������
		if (strstr(buffer, name_to_delete) != NULL)//strstr �������ڼ�鵱ǰ���Ƿ����ָ�������� name_to_delete
		{
			line_to_delete = current_line;
		}
		else if (current_line != line_to_delete)
		{
			// �����ǰ�в���Ҫɾ�����У��򽫸���д����ʱ�ļ�
			fputs(buffer, fp1);
		}
	}

	fclose(fp);
	fclose(fp1);

	// ɾ��ԭ�ļ�
	if (remove("grade.txt") != 0)
	{
		perror("ɾ��ԭ�ļ�ʧ��");
		exit(1);
	}

	// ����ʱ�ļ�������Ϊԭ�ļ���
	if (rename("linshi.txt", "grade.txt") != 0)
	{
		perror("�������ļ�ʧ��");
		exit(1);
	}
}

void del() // �ɼ�ɾ��
{
	printf("�ɼ�ɾ��\n");
	char name_to_delete[100];
	printf("������Ҫɾ����ѧ������: ");
	scanf("%99s", name_to_delete); // ��ȡѧ�����������99���ַ�
	delete_file(name_to_delete);
	system("pause");
}





void find() 
{
	char name[100]; // ��������������99���ַ�
	printf("�ɼ�����\n");
	printf("������Ҫ����ѧ���ɼ�������:");
	scanf("%99s", name); // ʹ��%99s�����⻺�������

	FILE* fp = fopen("grade.txt", "r");
	if (fp == NULL) 
	{
		printf("�ļ���ʧ��\n");
		return; // ����ļ���ʧ�ܣ����˳�����
	}

	char buffer[1024]; // ����һ�в��ᳬ��1024���ַ�
	int found = 0; // ����Ƿ��ҵ�����

	// ���ж�ȡ�ļ�����
	while (fgets(buffer, sizeof(buffer), fp)) 
	{
		// ȥ�����ܵĻ��з�
		buffer[strcspn(buffer, "\n")] = 0;//strcspn �������ڼ����ַ����е�һ��ƥ������ַ����е��ַ�������

		// ��鵱ǰ���Ƿ����Ҫ���ҵ�����
		char* token = strtok(buffer, " ");//strtok �������ڽ��ַ����ָ��һϵ�еı�ǣ�tokens��," " ��һ�����������ո��ַ����ַ����������� strtok ʹ�ÿո���Ϊ�ָ������ָ� buffer
		if (token != NULL && strcmp(token, name) == 0)//trcmp �������ڱȽ������ַ���
		{
			// �ҵ������󣬴�ӡ�ɼ�
			token = strtok(NULL, " "); // ��������������ɼ�,�� strtok �ĺ��������д��� NULL����Ϊ�˸��ߺ�����������һ�ηָ�ֹͣ�ĵط���ʼ�����ַ�����������Ϊ strtok ά����һ���ڲ���ָ̬�룬����¼����һ�ε���ʱ��λ�á�����һ�ε��� strtok ʱ�����ָ�뱻��ʼ�������ں��������У�ͨ������ NULL�������������ڲ�ָ��ָʾ��λ�ü��������ַ�����
			if (token != NULL) 
			{
				printf("�ҵ�ѧ�� %s �ĳɼ�: %s\n", name, token);
				found = 1; // �����ҵ����Ϊ��
			}
			else 
			{
				printf("δ�ҵ�ѧ�� %s �ĳɼ�����ʽ����\n", name);
			}
		}
	}

	if (!found)
	{
		printf("û���ҵ�ѧ�� %s �ĳɼ�\n", name); // ���û���ҵ�����ӡ��Ϣ
	}

	fclose(fp); // �ر��ļ�
	system("pause");
}


void sort() 
{
	FILE* fp = fopen("grade.txt", "r");
	if (fp == NULL) 
	{
		printf("�ļ���ʧ��\n");
		return;
	}

	// ��ȡ�ļ��е�ѧ����Ϣ
	while (fscanf(fp, "%99s %d", students[student_count].name, &students[student_count].score) == 2) 
	{
		student_count++;
	}
	fclose(fp); // �ر��ļ�

	// ����ѧ����Ϣ
	for (int i = 0; i < student_count-1; i++) 
	{
		for (int j = 0; j < student_count - i-1; j++) 
		{
			if (students[j].score < students[j + 1].score) 
			{
				// ��������ѧ������Ϣ
				Student temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
		}
	}

	// ��ӡ������ѧ����Ϣ
	printf("ѧ����Ϣ�Ѱ��ɼ���������\n");
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
		printf("�ļ���ʧ��\n");
		return;
	}

	printf("�ɼ��޸�\n");

	// ���¶�ȡ�ļ��е�ѧ����Ϣ�����洢��students������
	while (fscanf(fp, "%99s %d", students[student_count].name, &students[student_count].score) == 2)
	{
		student_count++;
	}
	fclose(fp); // �ر��ļ�

	// ��ӡ��ǰ��ѧ����Ϣ
	printf("��ǰѧ����Ϣ��\n");
	for (int i = 0; i < student_count; i++)
	{
		printf("%s %d\n", students[i].name, students[i].score);
	}
	char name[100];
	// �޸ĳɼ�
	printf("������Ҫ�޸ĵ�ѧ��������");
	scanf("%s", name);
	for (int i = 0; i < student_count; i++)
	{
		if (strcmp(students[i].name, name) == 0)
		{
			printf("�������µĳɼ���");
			scanf("%d", &students[i].score);
			break;
		}
	}

	// ����д���ļ�
	fp = fopen("grade.txt", "w");
	if (fp == NULL) 
	{
		printf("�ļ�д��ʧ��\n");
		return;
	}
	for (int i = 0; i < student_count; i++) 
	{
		fprintf(fp, "%s %d\n", students[i].name, students[i].score);
	}
	fclose(fp); // �ر��ļ�

	printf("�ɼ��޸���ɡ�\n");
	system("pause");
}
void menu() 
{
	/*��ʾ�˵�*/
	system("cls");
	printf("\n\n\n\t\t\t��ӭʹ��ѧ���ɼ�����ϵͳ\n\n\n");
	printf("\t\t\t***********************\n");
	printf("\t\t\t        *���˵�*       \n");
	printf("\t\t\t***********************\n\n\n");
	printf("\t\t       1  �ɼ�����     2  �ɼ�ɾ��\n\n");
	printf("\t\t       3  �ɼ�����     4  �ɼ�����\n\n");
	printf("\t\t       5  �ɼ��޸�     6  �˳�ϵͳ\n\n");
	printf("\t\t       ��ѡ��1/2/3/4/5/6��:");
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