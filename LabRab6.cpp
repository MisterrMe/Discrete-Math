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
	float buf,buff;
	float Bernulli[5], Vald[5], Optimist[5], Gurvic[5];
	float RiskTable[5][4], RiskLine[5];
	int points[5] = { 0, 0, 0, 0, 0 };
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

	//Критерий Бернулли
	for (int i = 0; i < 5; i++)
	{
		buf = 0;
		for (int j = 0; j < 4; j++)
		{
			buf += a[i][j];
		}
		Bernulli[i] = buf / 5;
	}
	buf = 0;
	for (int i = 0; i < 5; i++)
	{
		if (Bernulli[i] > buf)
			buf = Bernulli[i];
	}
	printf("Согласно критерию Бернулли ожидания выигрыша равны:\n%6.4f, %6.4f, %6.4f, %6.4f, %6.4f.\n", Bernulli[0], Bernulli[1], Bernulli[2], Bernulli[3], Bernulli[4]);
	printf("К выбору рекомендованы:");
	for (int i = 0; i < 5; i++)
	{
		if (Bernulli[i] == buf)
		{
			points[i] += 1;
			printf("%d ",i+1);
		}
	}
	printf("\n\n");

	//Критерий Вальда
	for (int i = 0; i < 5; i++)
	{
		buf = 1000;
		for (int j = 0; j < 4; j++)
		{
			if (a[i][j] < buf)
				buf = a[i][j];
		}
		Vald[i] = buf;
	}
	buf = 0;
	for (int i = 0; i < 5; i++)
	{
		if (Vald[i] > buf)
			buf = Vald[i];
	}
	printf("Согласно критерию Вальда ожидания выигрыша равны:\n%6.4f, %6.4f, %6.4f, %6.4f, %6.4f.\n", Vald[0], Vald[1], Vald[2], Vald[3], Vald[4]);
	printf("К выбору рекомендованы:");
	for (int i = 0; i < 5; i++)
	{
		if (Vald[i] == buf)
		{
			points[i] += 1;
			printf("%d ", i+1);
		}
	}
	printf("\n\n");

	//Критерий Оптимистический
	for (int i = 0; i < 5; i++)
	{
		buf = 0;
		for (int j = 0; j < 4; j++)
		{
			if (a[i][j] > buf)
				buf = a[i][j];
		}
		Optimist[i] = buf;
	}
	buf = 0; k = 0;
	for (int i = 0; i < 5; i++)
	{
		if (Optimist[i] > buf)
			buf = Optimist[i];
	}
	printf("Согласно оптимистической стратегии ожидания выигрыша равны:\n%6.4f, %6.4f, %6.4f, %6.4f, %6.4f.\n", Optimist[0], Optimist[1], Optimist[2], Optimist[3], Optimist[4]);
	printf("К выбору рекомендованы:");
	for (int i = 0; i < 5; i++)
	{
		if (Optimist[i] == buf)
		{
			points[i] += 1;
			printf("%d ", i + 1);
		}
	}
	printf("\n\n");

	//Критерий Гурвица
	for (int i = 0; i < 5; i++)
	{
		buf = 0;
		for (int j = 0; j < 4; j++)
			if (a[i][j] > buf)
				buf = a[i][j];
		buff = 1000;
		for (int j = 0; j < 4; j++)
		{
			if (a[i][j] < buff)
				buff = a[i][j];
		}
		Gurvic[i] = (buf+buff)/2;
	}
	buf = 0; k = 0;
	for (int i = 0; i < 5; i++)
	{
		if (Gurvic[i] > buf)
			buf = Gurvic[i];
	}
	printf("Согласно критерию Гурвица ожидания выигрыша равны:\n%6.4f, %6.4f, %6.4f, %6.4f, %6.4f.\n", Gurvic[0], Gurvic[1], Gurvic[2], Gurvic[3], Gurvic[4]);
	printf("К выбору рекомендованы:");
	for (int i = 0; i < 5; i++)
	{
		if (Gurvic[i] == buf)
		{
			points[i] += 1;
			printf("%d ", i + 1);
		}
	}
	printf("\n\n");

	//Критерий оптимальной рисковой стратегии
	for (int i = 0; i < 4; i++)
	{
		buf = 0;
		for (int j = 0; j < 5; j++)
		{
			if (a[j][i] > buf)
				buf = a[j][i];
		}
		for (int j = 0; j < 5; j++)
		{
			RiskTable[j][i] = buf - a[j][i];
		}
	}
	for (int i = 0; i < 5; i++)
	{
		buf = 0;
		for (int j = 0; j < 4; j++)
		{
			if (RiskTable[i][j] > buf)
				buf = RiskTable[i][j];
		}
		RiskLine[i] = buf;
	}
	buf = 10000; k = 0;
	for (int i = 0; i < 5; i++)
	{
		if (RiskLine[i] < buf)
			buf = RiskLine[i];
	}
	printf("Согласно оптимальной рисковой стратегии риски проигрыша равны:\n%6.4f, %6.4f, %6.4f, %6.4f, %6.4f.\n", RiskLine[0], RiskLine[1], RiskLine[2], RiskLine[3], RiskLine[4]);
	printf("К выбору рекомендованы:");
	for (int i = 0; i < 5; i++)
	{
		if (RiskLine[i] == buf)
		{
			points[i] += 1;
			printf("%d ", i + 1);
		}
	}
	printf("\n\n");

	for (int i = 0; i < 5; i++)
	{
		buf = 0; k = 0;
		if (points[i] > buf)
		{
			buf = points[i];
			k = i;
		}
	}

	printf("Согласно принципу большинства следует рекомендовать набор стратегий а%d .", k+1);
	_getch();
}
