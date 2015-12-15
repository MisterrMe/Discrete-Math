#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
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
	float a[5][4];
	int xi1[5] = {1, 2, 3, 4, 5}, xj1[4] = {6, 7, 8, 9};
	int xi2[4] = {1, 2, 3, 4}, xj2[5] = {5, 6, 7, 8, 9};
	float a1[4][5], a2[5][4];
	float b1[4], b2[5];
	float c1[5], c2[4];
	float d1, d2;
	float g1, g2;
	float u1[5], u2[4];
	float x1[5], x2[4];
	float buf[5][5];
	//счетчики
	int k = 0, l = 0, m = 0;

	//проверка считывания файла
	if (file1 == NULL)
	{
		printf("Файл не считался.\n");
		_getch();
		return -1;
	}

	//Запись массива
	k = 0; l = 0; m = 0;
	fgets(buffer, sizeof(buffer), file1);
	for (int i = 0; i < 1000; i++)
	{
		k = 0;
		if (buffer[i] == 32 && buffer[i + 1] != 32 && buffer[i + 1] != 91 && m != 4)
		{
			while (1)
			{
				i += 1;
				sbuffer[k] = buffer[i];
				k += 1;
				if (buffer[i + 1] == 32 || buffer[i + 1] == 93)
				{
					a[l][m] = atof(sbuffer);
					m += 1;
					break;
				}
			}
		}
		if (m == 4 && l != 4)
		{
			l += 1;
			i = -1;
			m = 0;
			fgets(buffer, sizeof(buffer), file1);
		}
	}
	//Конец записи массива

	//запись начального массива
	printf("Начальный массив\n\n");
	printf("Стратегии    b1    b2    b3    b4\n");
	printf("       a1  %5.2f %5.2f %5.2f %5.2f\n", a[0][0], a[0][1], a[0][2], a[0][3]);
	printf("       a2  %5.2f %5.2f %5.2f %5.2f\n", a[1][0], a[1][1], a[1][2], a[1][3]);
	printf("       a3  %5.2f %5.2f %5.2f %5.2f\n", a[2][0], a[2][1], a[2][2], a[2][3]);
	printf("       a4  %5.2f %5.2f %5.2f %5.2f\n", a[3][0], a[3][1], a[3][2], a[3][3]);
	printf("       a5  %5.2f %5.2f %5.2f %5.2f\n", a[4][0], a[4][1], a[4][2], a[4][3]);
	//конец записи начального массива

	//Задаем элементы для первого случая
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			a1[i][j] = -a[j][i];
		}
	}
	for (int i = 0; i < 4; i++)
		b1[i] = -1;
	for (int i = 0; i < 5; i++)
		c1[i] = 1;
	d1 = 0;
	//Конец задания элементов

	//Выводим на экран таблицу первого случая
	printf("\n\nПервый случай\n");
	printf("            %7d %7d %7d %7d %7d\n", xi1[0], xi1[1], xi1[2], xi1[3], xi1[4]);
	printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[0], b1[0], a1[0][0], a1[0][1], a1[0][2], a1[0][3], a1[0][4]);
	printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[1], b1[1], a1[1][0], a1[1][1], a1[1][2], a1[1][3], a1[1][4]);
	printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[2], b1[2], a1[2][0], a1[2][1], a1[2][2], a1[2][3], a1[2][4]);
	printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[3], b1[3], a1[3][0], a1[3][1], a1[3][2], a1[3][3], a1[3][4]);
	printf("      %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n\n", d1, c1[0], c1[1], c1[2], c1[3], c1[4]);
	//Конец вывода таблицы на экран

	//Допустимое решение первый случай
	//Находим строку и столбец
	while (1)
	{
		float minb1 = 0, minc1 = 0;
		l = 0; m = 0;
		for (int i = 0; i < 4; i++)
		{
			if (b1[i] < 0 & b1[i] < minb1)
			{
				minb1 = b1[i];
				l = i;
			}
		}
		if (minb1 != 0)
		{
			for (int j = 0; j < 5; j++)
			{
				if (a1[l][j] < 0 & a1[l][j] < minc1)
				{
					minc1 = a1[l][j];
					m = j;
				}
			}
			//Конец нахождения строки и столбца

			//Замена
			int buf = xi1[m];
			xi1[m] = xj1[l];
			xj1[l] = buf;

			d1 = d1 - b1[l] * c1[m] / a1[l][m];

			for (int i = 0; i < 4; i++)
			{
				if (i == l)
					continue;
				else
					b1[i] = b1[i] - a1[i][m] * b1[l] / a1[l][m];
			}
			b1[l] = b1[l] / a1[l][m];

			for (int i = 0; i < 5; i++)
			{
				if (i == m)
					continue;
				else
					c1[i] = c1[i] - a1[l][i] * c1[m] / a1[l][m];
			}
			c1[m] = -c1[m] / a1[l][m];

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (i != l && j != m)
						a1[i][j] = a1[i][j] - (a1[i][m] * a1[l][j] / a1[l][m]);
				}
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (i == l && j != m)
						a1[i][j] = a1[i][j] / a1[l][m];
				}
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (i != l && j == m)
						a1[i][j] = -a1[i][j] / a1[l][m];
				}
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (i == l && j == m)
						a1[i][j] = 1 / a1[l][m];
				}
			}
			//Конец замены

			//Запись измененного массива
			printf("Разрешающая строка %1d. Разрешающий столбец %1d.\n", xj1[l],xi1[m]);
			printf("            %7d %7d %7d %7d %7d\n", xi1[0], xi1[1], xi1[2], xi1[3], xi1[4]);
			printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[0], b1[0], a1[0][0], a1[0][1], a1[0][2], a1[0][3], a1[0][4]);
			printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[1], b1[1], a1[1][0], a1[1][1], a1[1][2], a1[1][3], a1[1][4]);
			printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[2], b1[2], a1[2][0], a1[2][1], a1[2][2], a1[2][3], a1[2][4]);
			printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[3], b1[3], a1[3][0], a1[3][1], a1[3][2], a1[3][3], a1[3][4]);
			printf("      %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n\n", d1, c1[0], c1[1], c1[2], c1[3], c1[4]);
			//Конец записи измененного массива
		}
		else
			break;
	}
	//Конец допустимого решения первого случая

	printf("Допустимое решение.\n");
	printf("            %7d %7d %7d %7d %7d\n", xi1[0], xi1[1], xi1[2], xi1[3], xi1[4]);
	printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[0], b1[0], a1[0][0], a1[0][1], a1[0][2], a1[0][3], a1[0][4]);
	printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[1], b1[1], a1[1][0], a1[1][1], a1[1][2], a1[1][3], a1[1][4]);
	printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[2], b1[2], a1[2][0], a1[2][1], a1[2][2], a1[2][3], a1[2][4]);
	printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[3], b1[3], a1[3][0], a1[3][1], a1[3][2], a1[3][3], a1[3][4]);
	printf("      %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n\n", d1, c1[0], c1[1], c1[2], c1[3], c1[4]);

	//Поиск оптимального решения
	while (1)
	{
		float minb1 = 1000, minc1 = 0;
		l = 0; m = 0;
		for (int i = 0; i < 5; i++)
		{
			if (c1[i] < 0 & c1[i] < minc1)
			{
				minc1 = c1[i];
				m = i;
			}
		}
		if (minc1 != 0)
		{
			for (int i = 0; i < 4; i++)
			{
				if (a1[i][m] == 0)
					continue;
				if ((b1[i] / a1[i][m]) < minb1 & (b1[i] / a1[i][m]) > 0)
				{
					l = i;
					minb1 = b1[i] / a1[i][m];
				}
			}
			//Замена
			int buf = xi1[m];
			xi1[m] = xj1[l];
			xj1[l] = buf;

			d1 = d1 - b1[l] * c1[m] / a1[l][m];

			for (int i = 0; i < 4; i++)
			{
				if (i == l)
					continue;
				else
					b1[i] = b1[i] - a1[i][m] * b1[l] / a1[l][m];
			}
			b1[l] = b1[l] / a1[l][m];

			for (int i = 0; i < 5; i++)
			{
				if (i == m)
					continue;
				else
					c1[i] = c1[i] - a1[l][i] * c1[m] / a1[l][m];
			}
			c1[m] = -c1[m] / a1[l][m];

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (i != l && j != m)
						a1[i][j] = a1[i][j] - (a1[i][m] * a1[l][j] / a1[l][m]);
				}
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (i == l && j != m)
						a1[i][j] = a1[i][j] / a1[l][m];
				}
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (i != l && j == m)
						a1[i][j] = -a1[i][j] / a1[l][m];
				}
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (i == l && j == m)
						a1[i][j] = 1 / a1[l][m];
				}
			}
			//Конец замены

			//Запись измененного массива
			printf("Разрешающая строка %1d. Разрешающий столбец %1d.\n", xj1[l], xi1[m]);
			printf("            %7d %7d %7d %7d %7d\n", xi1[0], xi1[1], xi1[2], xi1[3], xi1[4]);
			printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[0], b1[0], a1[0][0], a1[0][1], a1[0][2], a1[0][3], a1[0][4]);
			printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[1], b1[1], a1[1][0], a1[1][1], a1[1][2], a1[1][3], a1[1][4]);
			printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[2], b1[2], a1[2][0], a1[2][1], a1[2][2], a1[2][3], a1[2][4]);
			printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj1[3], b1[3], a1[3][0], a1[3][1], a1[3][2], a1[3][3], a1[3][4]);
			printf("      %7.2f %7.2f %7.2f %7.2f %7.2f %7.2f\n\n", d1, c1[0], c1[1], c1[2], c1[3], c1[4]);
			//Конец записи измененного массива
		}
		else
			break;
	}
	d1 = -d1;
	//Конец поиска оптимального решения

	//Поиск и вывод ответа в случае 1
	for (int i = 0; i < 5; i++)
	{
		k = 0;
		for (int j = 0; j < 5; j++)
		{
			if (xj1[j] == i+1)
			{
				u1[i] = b1[j];
				k = 1;
			}
		}
		if ( k == 0)
			u1[i] = 0;
	}
	for (int i = 0; i < 5;i++)
		printf("u%d = %f\n", i+1,u1[i]);
	printf("W = %f\n", d1);
	g1 = 1 / d1;
	printf("g = %f\n", g1);
	for (int i = 0; i < 5; i++)
	{
		x1[i] = g1*u1[i];
	}
	for (int i = 0; i < 5; i++)
		printf("x%d = %f\n", i+1, x1[i]);
	printf("Смешанная стратегии игрока А (");
	for (int i = 0; i < 5; i++)
		printf("%f ",x1[i]);
	printf(")");
	//Конец поиска и вывода ответа


	//Задаем элементы для второго случая
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			a2[i][j] = a[i][j];
		}
	}
	for (int i = 0; i < 5; i++)
		b2[i] = 1;
	for (int i = 0; i < 4; i++)
		c2[i] = -1;
	d2 = 0;
	//Конец задания элементов

	//Выводим на экран таблицу второго случая
	printf("\n\n\n\n\n\nВторой случай\n");
	printf("            %7d %7d %7d %7d\n", xi2[0], xi2[1], xi2[2], xi2[3]);
	printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj2[0], b2[0], a2[0][0], a2[0][1], a2[0][2], a2[0][3]);
	printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj2[1], b2[1], a2[1][0], a2[1][1], a2[1][2], a2[1][3]);
	printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj2[2], b2[2], a2[2][0], a2[2][1], a2[2][2], a2[2][3]);
	printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj2[3], b2[3], a2[3][0], a2[3][1], a2[3][2], a2[3][3]);
	printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj2[4], b2[4], a2[4][0], a2[4][1], a2[4][2], a2[4][3]);
	printf("      %7.2f %7.2f %7.2f %7.2f %7.2f\n\n", d2, c2[0], c2[1], c2[2], c2[3], c2[4]);
	//Конец вывода таблицы на экран

	//Поиск оптимального решения
	while (1)
	{
		float minb2 = 1000, minc2 = 0;
		l = 0; m = 0;
		for (int i = 0; i < 4; i++)
		{
			if (c2[i] < 0 & c2[i] < minc2)
			{
				minc2 = c2[i];
				m = i;
			}
		}
		if (minc2 != 0)
		{
			for (int i = 0; i < 5; i++)
			{
				if (a2[i][m] == 0)
					continue;
				if ((b2[i] / a2[i][m]) < minb2 & (b2[i] / a2[i][m]) > 0)
				{
					l = i;
					minb2 = b2[i] / a2[i][m];
				}
			}
			//Замена
			int buf = xi2[m];
			xi2[m] = xj2[l];
			xj2[l] = buf;

			d2 = d2 - b2[l] * c2[m] / a2[l][m];

			for (int i = 0; i < 5; i++)
			{
				if (i == l)
					continue;
				else
					b2[i] = b2[i] - a2[i][m] * b2[l] / a2[l][m];
			}
			b2[l] = b2[l] / a2[l][m];

			for (int i = 0; i < 4; i++)
			{
				if (i == m)
					continue;
				else
					c2[i] = c2[i] - a2[l][i] * c2[m] / a2[l][m];
			}
			c2[m] = -c2[m] / a2[l][m];

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (i != l && j != m)
						a2[i][j] = a2[i][j] - (a2[i][m] * a2[l][j] / a2[l][m]);
				}
			}

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (i == l && j != m)
						a2[i][j] = a2[i][j] / a2[l][m];
				}
			}

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (i != l && j == m)
						a2[i][j] = -a2[i][j] / a2[l][m];
				}
			}

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (i == l && j == m)
						a2[i][j] = 1 / a2[l][m];
				}
			}
			//Конец замены

			//Запись измененного массива
			printf("Разрешающая строка %1d. Разрешающий столбец %1d.\n", xj2[l], xi2[m]);
			printf("            %7d %7d %7d %7d\n", xi2[0], xi2[1], xi2[2], xi2[3]);
			printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj2[0], b2[0], a2[0][0], a2[0][1], a2[0][2], a2[0][3]);
			printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj2[1], b2[1], a2[1][0], a2[1][1], a2[1][2], a2[1][3]);
			printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj2[2], b2[2], a2[2][0], a2[2][1], a2[2][2], a2[2][3]);
			printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj2[3], b2[3], a2[3][0], a2[3][1], a2[3][2], a2[3][3]);
			printf("%5d %7.2f %7.2f %7.2f %7.2f %7.2f\n", xj2[4], b2[4], a2[4][0], a2[4][1], a2[4][2], a2[4][3]);
			printf("      %7.2f %7.2f %7.2f %7.2f %7.2f\n\n", d2, c2[0], c2[1], c2[2], c2[3], c2[4]);
			//Конец записи измененного массива
		}
		else
			break;
	}
	//Конец поиска оптимального решения

	//Поиск и вывод ответа
	for (int i = 0; i < 5; i++)
	{
		k = 0;
		for (int j = 0; j < 5; j++)
		{
			if (xj2[j] == i + 1)
			{
				u2[i] = b2[j];
				k = 1;
			}
		}
		if (k == 0)
			u2[i] = 0;
	}
	for (int i = 0; i < 4; i++)
		printf("u%d = %f\n", i+1, u2[i]);
	printf("W = %f\n", d2);
	g2 = 1 / d2;
	printf("g = %f\n", g2);
	for (int i = 0; i < 4; i++)
	{
		x2[i] = g2*u2[i];
	}
	for (int i = 0; i < 4; i++)
		printf("x%d = %f\n", i+1, x2[i]);
	printf("Смешанная стратегии игрока А (");
	for (int i = 0; i < 4; i++)
		printf("%f ", x2[i]);
	printf(")");
	//Конец поиска и вывода ответа

	_getch();
}
