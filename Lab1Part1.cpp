#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <stdlib.h>
#include "conio.h"
#include <locale.h>
char *setlocale(int type, const char *locale);

int main()
{	//Включаем поддержку русского языка
	setlocale(LC_ALL, "RUS");

	//Задаем переменные
	int check = 0;
	int count1 = 0;
	int count2 = 0;
	char buffer[1500];
	char c1[1500];
	char c2[1500];
	char set1[1500];
	char set2[1500];
	char set3[3000];
	FILE *file1;
	file1 = fopen("Datafiles\\in.txt", "r");

	//Проверяем считался ли файл
	if (file1 == NULL) 
	{
		printf("ошибка\n");
		_getch();
		return -1;
	}

	//считываем кол-во элементов в первом множестве
	fgets(buffer, sizeof(buffer), file1);
	for (int i = 0; i < 150; i++)
	{
		int k=0;
		if (buffer[i] != 32)
			c1[k]=buffer[i];
		if (buffer[i] = 10)
			break;
	}
	count1=atoi(c1);
	for (int i = 0; i < 150; i++)
		c1[i] = 0;
	for (int i = 0; i < 150; i++)
		buffer[i] = 0;

	//записали вторую строку в буфер
	fgets(buffer, sizeof(buffer), file1);
	for (int i=0;i<150;i++)
	{
		if (buffer[i]==0)
		{
			buffer[i]=10;
			break;
		}
	}
	//Записываем элементы первого множества в массив
	for (int i = 0; i < 150; i++)
	{
		set1[i] = buffer[i];
	}

	for (int i=0;i<150;i++)
	{
		if (buffer [i] != 32 && i==0)
			check+=1;
		if (buffer[i] == 32 && buffer[i + 1] != 32 && buffer[i + 1] != 10 )
			check+=1;
	}
	if (check < count1)
		{
			printf("Кол-во элементов 1 множества не соотвествует указанному\n");
			_getch();
			return -1;
		}
	check=0;

	//Очищаем буфер(избавляемся от мусора)
	for (int i = 0; i < 150; i++)
		buffer[i] = 0;

	//Считываем кол-во элементов во 2 множестве
	fgets(buffer, sizeof(buffer), file1);
	for (int i = 0; i < 150; i++)
	{
		int k=0;
		if (buffer[i] != 32)
			c2[k]=buffer[i];
		if (buffer[i] = 10)
			break;
	}
	count2=atoi(c2);
	for (int i = 0; i < 150; i++)
		c2[i] = 0;
	for (int i = 0; i < 150; i++)
		buffer[i] = 0;

	//записали четвертую строку в буфер
	fgets(buffer, sizeof(buffer), file1);
	for (int i=0;i<150;i++)
	{
		if (buffer[i]==0)
		{
			buffer[i]=10;
			break;
		}
	}
	//Записываем элементы второго множества в массив
	for (int i = 0; i < 150; i++)
	{
		set2[i] = buffer[i];
	}
	for (int i=0;i<150;i++)
	{
		if (buffer [i] != 32 && i==0)
			check+=1;
		if (buffer[i] == 32 && buffer[i + 1] != 32 && buffer[i + 1] != 10 )
			check+=1;
	}
	if (check < count2)
		{
			printf("Кол-во элементов 2 множества не соотвествует указанному\n");
			_getch();
			return -1;
		}
	check=0;
	//Очищаем буфер(избавляемся от мусора)
	for (int i = 0; i < 150; i++)
		buffer[i] = 0;

	//Выполняем декартового произведение множеств
	set3[0] = '{';
	int k = 1;
	int l = 0;
	int cc1=count1;
	for (int i = 0; i < 150; i++)
	{
		if (set1[i] != 32 && set1[i] != 10)
		{
			buffer[l] = set1[i];
			l += 1;
		}
		if (set1[i + 1] == 32 || set1[i+1] == 10)
		{
			cc1-=1;
			if (cc1<0)
				break;
			set3[k] = '('; k += 1;
			for (int n = 0; n < l; n++)
			{
				set3[k] = buffer[n]; k += 1;
			}
			set3[k] = ','; k += 1;
			int cc2=count2;
			for (int j = 0; j < 150; j++)
			{
				if (set2[j] != 32 && set2[j] != 10)
				{
					set3[k] = set2[j]; k += 1;
				}
				if (set2[j] == 32 && set2[j + 1] != 32)
				{
					set3[k] = ')'; k += 1;
					cc2-=1;
					if (cc2==0)
					{
						set3[k] = 10; k += 1;
						break;
					}
					set3[k] = '('; k += 1;
					for (int n = 0; n < l; n++)
					{
						set3[k] = buffer[n]; k += 1;
					}
					set3[k] = ','; k += 1;
				}
				if (set2[j] == 10)
				{
					set3[k] = ')'; k += 1;
					break;
				}
			}
			for (int n = 0; n < l; n++)
			{
				buffer[n]=0;
			}
			l = 0;
		}
		if (set1[i+1] == 10)
			break;
	}
	set3[k] = '}'; k += 1;
	for (int i = k; i < 3000; i++)
		set3[i] = 0;
	file1 = fopen("Datafiles\\out.txt", "w");
	fprintf(file1, "Лабораторную работу 1 по дискретной математике выполнил Штуров Михаил. Группа Иу8-34.\n\n");
	cc1=count1;
	for (int i=0;i<150;i++)
	{
		if (set1[i]!=32 && (set1[i+1]==32 || set1[i+1]==10))
			cc1-=1;
		if (set1[i+1]==10)
			break;
		if (cc1==0)
		{
			for (int j=i+2;j<150;j++)
				set1[j]=0;
			break;
		}
	}
	fprintf(file1, "Множество 1\n%s\n",set1);
	int cc2=count2;
	for (int i=0;i<150;i++)
	{
		if (set2[i]!=32 && (set2[i+1]==32 || set2[i+1]==10))
			cc2-=1;
		if (set2[i+1]==10)
			break;
		if (cc2==0)
		{
			for (int j=i+2;j<150;j++)
				set2[j]=0;
			break;
		}
	}
	fprintf(file1, "Множество 2\n%s\n\n",set2);
	fprintf(file1, "Декартовое произведение множеств\n%s", set3);
	_getch();
	return 0;
}
