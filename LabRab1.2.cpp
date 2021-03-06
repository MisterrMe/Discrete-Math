#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "stdio.h"
#include <stdlib.h>
#include "conio.h"
#include <cmath>

int main()
{
	//Задаем локализацию
	setlocale(LC_ALL, "rus");

	//Задаем параметры
	FILE *file1;
	file1 = fopen("Datafiles\\in.txt", "r");
	//Буфер считывания
	char buffer[1500];
	char sbuffer[100];
	//Переменные
	float a[3][3];
	float b[3];
	float c[3];
	float d = 0;
	int xi[3] = { 1, 2, 3 }, xj[3] = { 4, 5, 6 };
	//счетчики
	int i = 0, j = 0, k = 0, l = 0;

	//проверка считывания файла
	if (file1 == NULL)
	{
		printf("Файл не считался.\n");
		_getch();
		return -1;
	}

	//запись данных из файла в переменные
	fgets(buffer, sizeof(buffer), file1);

	//запись массива С
	fgets(buffer, sizeof(buffer), file1);
	for (i = 0; i<1000; i++)
	{
		k = 0;
		if (buffer[i] == 32 && buffer[i + 1] != 32 && j != 3)
		{
			while (1)
			{
				i += 1;
				sbuffer[k] = buffer[i];
				k += 1;
				if (buffer[i + 1] == 32 || buffer[i + 1] == 93)
				{
					c[j] = -atof(sbuffer);
					j += 1;
					break;
				}
			}
		}
	}
	//конец записи массива С

	//Запись массива A
	i = 0; j = 0; k = 0; l = 0;
	fgets(buffer, sizeof(buffer), file1);
	fgets(buffer, sizeof(buffer), file1);
	for (i = 0; i<1000; i++)
	{
		k = 0;
		if (buffer[i] == 32 && buffer[i + 1] != 32 && buffer[i + 1] != 91 && j != 3)
		{
			while (1)
			{
				i += 1;
				sbuffer[k] = buffer[i];
				k += 1;
				if (buffer[i + 1] == 32 || buffer[i + 1] == 93)
				{
					a[l][j] = atof(sbuffer);
					j += 1;
					break;
				}
			}
		}
		if (j == 3 && l != 2)
		{
			l += 1;
			i = -1;
			j = 0;
			fgets(buffer, sizeof(buffer), file1);
		}
	}
	//конец записи массива А

	//запись массива B
	i = 0; j = 0; k = 0; l = 0;
	fgets(buffer, sizeof(buffer), file1);
	fgets(buffer, sizeof(buffer), file1);
	for (i = 0; i<1000; i++)
	{
		k = 0;
		if (buffer[i] == 32 && buffer[i + 1] != 32 && j != 3)
		{
			while (1)
			{
				i += 1;
				sbuffer[k] = buffer[i];
				k += 1;
				if (buffer[i + 1] == 32 || buffer[i + 1] == 93)
				{
					b[j] = atof(sbuffer);
					j += 1;
					break;
				}
			}
		}
	}
	//конец записи массива В

	//запись начального массива
	printf("Начальный массив\n");
	printf("                    %9d %9d %9d\n", xi[0], xi[1], xi[2]);
	printf("%9d %9.5f %9.5f %9.5f %9.5f\n", xj[0], b[0], a[0][0], a[0][1], a[0][2]);
	printf("%9d %9.5f %9.5f %9.5f %9.5f\n", xj[1], b[1], a[1][0], a[1][1], a[1][2]);
	printf("%9d %9.5f %9.5f %9.5f %9.5f\n", xj[2], b[2], a[2][0], a[2][1], a[2][2]);
	printf("          %9.5f %9.5f %9.5f %9.5f\n\n", d, c[0], c[1], c[2]);
	//конец записи начального массива

	//математические рассчеты
	k=0;
	int m = 0;
	while (1)
	{
		float minc = 0;
		for (i = 0; i < 3; i++)
		{
			if (c[i] <= 0 && c[i] <= minc)
			{
				minc = c[i];
				m = i;
			}
		}
		if (minc != 0)
		{
			i = m;
			float min = 100;
			for (int j = 0; j < 3; j++)
			{
				if (a[j][i] == 0)
					continue;
				if (fabs(b[j] / a[j][i]) < min)
				{
					k = j;
					min = fabs(b[j] / a[j][i]);
				}
			}
			printf("Разрешающий столбец %d. Разрешающая строка %d.\n", k + 1, i + 1);

			//Замена
			int buf = xj[k];
			xj[k] = xi[i];
			xi[i] = buf;

			d = d - b[i] * c[k] / a[i][k];

			for (int l = 0; l < 3; l++)
			{
				if (l == i)
					continue;
				else
					b[l] = b[l] - a[l][k] * b[i] / a[i][k];

			}
			b[i] = b[i] / a[i][k];

			for (int l = 0; l < 3; l++)
			{
				if (l == i)
					continue;
				else
					c[l] = c[l] - a[i][l] * c[i] / a[i][k];
			}
			c[i] = -c[i] / a[i][k];

			for (int l = 0; l < 3; l++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (l != i && j != k)
						a[l][j] = a[l][j] - (a[l][k] * a[i][j] / a[i][k]);
				}
			}

			for (int l = 0; l < 3; l++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (l == i && j != k)
						a[l][j] = a[l][j] / a[i][k];
				}
			}

			for (int l = 0; l < 3; l++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (l != i && j == k)
						a[l][j] = -a[l][j] / a[i][k];
				}
			}

			for (int l = 0; l < 3; l++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (l == i && j == k)
						a[l][j] = 1 / a[i][k];
				}
			}
			//конец замены

			//запись измененного массива
			printf("                    %9d %9d %9d\n", xi[0], xi[1], xi[2]);
			printf("%9d %9.5f %9.5f %9.5f %9.5f\n", xj[0], b[0], a[0][0], a[0][1], a[0][2]);
			printf("%9d %9.5f %9.5f %9.5f %9.5f\n", xj[1], b[1], a[1][0], a[1][1], a[1][2]);
			printf("%9d %9.5f %9.5f %9.5f %9.5f\n", xj[2], b[2], a[2][0], a[2][1], a[2][2]);
			printf("          %9.5f %9.5f %9.5f %9.5f\n\n", d, c[0], c[1], c[2]);
			//конец записи измененного массива
		}
		else
			break;
		k = 0;
	}
	//конец мат. рассчетов

	//вывод ответа
	printf("\n\n  Ответ:\n\n");
	printf("Итоговый массив:\n");
	printf("                    %9d %9d %9d\n", xi[0], xi[1], xi[2]);
	printf("%9d %9.5f %9.5f %9.5f %9.5f\n", xj[0], b[0], a[0][0], a[0][1], a[0][2]);
	printf("%9d %9.5f %9.5f %9.5f %9.5f\n", xj[1], b[1], a[1][0], a[1][1], a[1][2]);
	printf("%9d %9.5f %9.5f %9.5f %9.5f\n", xj[2], b[2], a[2][0], a[2][1], a[2][2]);
	printf("          %9.5f %9.5f %9.5f %9.5f\n\n", d, c[0], c[1], c[2]);
	k = 1;
	while (1)
	{
		if (k == 4)
			break;
		for (i = 0; i < 3; i++)
		{
			if (xi[i] == k)
			{
				printf("X%d=0\n", k);
				k += 1;
				continue;
			}
			if (xj[i] == k)
			{
				printf("X%d=%f\n", k, b[i]);
				k += 1;
				continue;
			}
		}
	}
	printf("F=%f\n", d);
	//конец вывода ответа
	_getch();
}
