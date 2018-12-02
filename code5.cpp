#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>
#include <cstring> 
#include <windows.h>
#include <errno.h>

struct Book
{
	char* author;
	char* title;
	int year;
	int countOfPages;
	int neW;
};
int menu()
{
	int punkt = 0;
	printf("Выберите пункт меню\n");
	printf("___________________\n\n");
	//_________________________________________________________________________

	printf("1. Добавление книги\n");
	printf("2. Удаление книги\n");
	printf("3. Вывод информации о книгах\n");
	printf("4. Сортировка информации о книгах\n");
	printf("5. Записать данные в файл\n");
	printf("6. Выход\n");

	//_________________________________________________________________________
	printf("___________________\n\n");
	do
	{
		char c = '\0';
		while (scanf_s("%d%c", &punkt, &c, 1) != 2 || c != '\n')
		{
			printf("The entered value is invalid. Please try again.\n");
			while (getchar() != '\n');
		}
	} while ((punkt < 1) || (punkt > 6));
	return punkt;
}
char * InputString()
{
	char string = '\0';
	scanf_s("%c", &string, 1);

	int leng = 1;

	char* str = new char[1];
	if (string != ';')
	{
		str[0] = string;
	}

	while (string != '\0')
	{
		scanf_s("%c", &string, 1);
		if (string == ';')
		{
			continue;
		}
		char* tmpStr = new char[leng + 1];
		for (int i = 0; i < leng; i++)
		{
			tmpStr[i] = str[i];
		}

		if (string == '\n')
		{
			tmpStr[leng] = '\0';
			string = '\0';
		}
		else
		{
			tmpStr[leng] = string;
		}
		delete[] str;
		str = tmpStr;
		leng++;
	}
	return str;
}
int newNew(int leng, Book** tmp)
{
	if (tmp[leng]->year == 2018)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void AddArray(Book** &books, int &leng)
{
	Book** tmp = new Book*[leng + 1];
	for (int i = 0; i < leng; i++)
	{
	//	tmp[i] = new Book;
		tmp[i] = books[i];
	}
	delete books;
	
	//---------------------------------------------------------------------------------
	printf("Книга №%d\n", leng+1);
	tmp[leng] = new Book;
	printf("Автор: ");
	tmp[leng]->author = InputString();
	printf("Название: ");
	tmp[leng]->title = InputString();

	do
	{
		printf("Год издания: ");
		char c = '\0';
		while (scanf_s("%d%c", &tmp[leng]->year, &c, 1) != 2 || c != '\n')
		{
			printf("Год издания: ");
			while (getchar() != '\n');
		}
	} while ((tmp[leng]->year < 1) || (tmp[leng]->year > 2018));
	
	do
	{
		printf("Количество страниц: ");
		char c = '\0';
		while (scanf_s("%d%c", &tmp[leng]->countOfPages, &c, 1) != 2 || c != '\n')
		{
			printf("Количество страниц: ");
			while (getchar() != '\n');
		}
	} while ((tmp[leng]->countOfPages < 1) || (tmp[leng]->countOfPages > 20000));
	tmp[leng]->neW = newNew(leng, tmp);
	//---------------------------------------------------------------------------------
	books = tmp;
	leng++;
//	delete[] tmp;

}
void deletE(Book** &books, int &leng)
{
	Book** tmp = new Book*[leng - 1];
	int p = 0;
	int del = 0;
	do
	{
		printf("Имеется информация о %d книгах. Какую из них по счету вы хотите удалить?\n", leng);
		char c = '\0';
		while (scanf_s("%d%c", &del, &c, 1) != 2 || c != '\n')
		{
			printf("Имеется информация о %d книгах. Какую из них по счету вы хотите удалить?\n", leng);
			while (getchar() != '\n');
		}
	} while ((del < 1) || (del > leng));
	del--;
	for (int i = 0; i < leng; i++)
	{
		if (i == del)
		{
			delete[] books[del]->author;
			delete[] books[del]->title;
			delete[] books[del];
			printf("Информация о книге удалена");
		//	i++;
		}
		else
		{
			tmp[p] = books[i];
			p++;
		}
		
	}
	leng--;
	delete[] books;
	books = tmp;
//	delete[] tmp;
}
void printList(Book** books, int leng)
{
	for (int i = 0; i < leng; i++)
	{
		printf("Книга №%d\n", i + 1);
		printf("Автор: %s\nНазвание: %s\nГод издания: %d\nКоличество страниц: %d\n", books[i]->author, books[i]->title, books[i]->year, books[i]->countOfPages);
		printf("Новинка: ");
		if (books[i]->neW == 1)
		{
			printf("да\n\n\n");
		}
		else
		{
			printf("нет\n\n\n");
		}
		
	}
}
void swap(Book** &books, int i, int j)
{
	Book* tmp  = books[i];
	books[i] = books[j];
	books[j] = tmp;
}

void printToFile(FILE* file, Book** books, int leng)
{
	for (int i = 0; i < leng; i++)
	{
		fprintf(file, "%s;%s;%d;%d;\n", books[i]->author, books[i]->title, books[i]->year, books[i]->countOfPages);
	}
}

char* readStringFromFile(FILE* file)
{
	char* string = new char[1];
	char symbol = '\0';
	int symbolCount = 0;
	while (symbol != ';')
	{
		fscanf(file, "%c", &symbol);
		if (symbol == ';')
		{
			break;
		}

		char* tmpString = new char[symbolCount + 2];
		for (int i = 0; i < symbolCount; i++)
		{
			tmpString[i] = string[i];
		}
		tmpString[symbolCount] = symbol;
		delete[] string;
		string = tmpString;
		symbolCount++;
	}
	string[symbolCount] = '\0';
	return string;
}
Book* readBookFromFile(FILE* file)
{
	Book* tmpBook = new Book;
	tmpBook->author = readStringFromFile(file);
	tmpBook->title = readStringFromFile(file);
	fscanf(file, "%d;\n", &tmpBook->year);
	fscanf(file, "%d;\n", &tmpBook->countOfPages);
	if (tmpBook->year == 2018)
	{
		tmpBook->neW = 1;
	}
	else
	{
		tmpBook->neW = 0;
	}
	return tmpBook;
}
Book** readFromFile(FILE* file, int& leng)
{
	int size = 0;
	Book** readBooks = NULL;
	while (!feof(file))
	{
		Book** tmpArr = new Book*[size + 1];
		for (int i = 0; i < size; i++)
		{
			tmpArr[i] = readBooks[i];
		}
		tmpArr[size] = readBookFromFile(file);
		delete[] readBooks;
		readBooks = tmpArr;
		size++;
	}

	leng = size;
	return readBooks;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Book** books = NULL;
//	Book** readBooks = NULL;
	int leng = 0;

	int punkt = 0;
	int punkt1 = 0;
	int punkt3 = 0;


	do
	{
		punkt = menu();

		switch (punkt)
		{

		case 1: //Добавление элемента структуры
			system("cls");
			printf("1. Ввести данные с клавиатуры\n");
			printf("2. Считать данные из файла\n");
			printf("3. Вернуться в главное меню\n");
			do
			{
				char c = '\0';
				while (scanf_s("%d%c", &punkt1, &c, 1) != 2 || c != '\n')
				{
					printf("The entered value is invalid. Please try again.\n");
					while (getchar() != '\n');
				}
			} while ((punkt1 < 1) || (punkt1 > 3));
			if (punkt1 == 3)
			{
				system("cls");
				break;
			}
			else if (punkt1 == 1)
			{
				system("cls");
				AddArray(books, leng);
			}
			else if (punkt1 == 2)
			{
				system("cls");
				if (leng > 0)
				{
					for (int i = 0; i < leng; i++)
					{
						delete[] books[i]->author;
						delete[] books[i]->title;
						delete[] books[i];
					}
					delete[] books;
				}
				FILE*  file = fopen("C:\\Users\\Asus\\source\\repos\\res\\data.txt", "r");
				books = readFromFile(file, leng);
				fclose(file);
				printf("Данные были успешно считаны\n");
			}
			getchar();
			system("cls");
			break;

		case 2: //Удаление элемента структуры
			system("cls");
			if (leng == 0)
			{
				printf("Пожалуйста, для начала добавьте данные о книгах");
				getchar();
				system("cls");
				break;
			}
			else
			{
				deletE(books, leng); 
				getchar();
				system("cls");
				break;
			}
		case 3: //Вывод данных на экран
			system("cls");
			if (leng == 0)
			{
				printf("Пожалуйста, для начала добавьте данные о книгах");
				getchar();
				system("cls");
				break;
			}
			else
			{
				printList(books, leng); 
				getchar();
				system("cls");
				break;
			}
		case 4: //Сортировка
			system("cls");
			if (leng == 0)
			{
				printf("Пожалуйста, для начала добавьте данные о книгах");
				getchar();
				system("cls");
				break;
			}
			else if (leng == 1)
			{
				printf("Недостаточное количество книг для сортировки");
				getchar();
				system("cls");
				break;
			}
			else
			{
				printf("Выберите, по какому полю сортировать\n");
				printf("1. Автор\n");
				printf("2. Название\n");
				printf("3. Год издания\n");
				printf("4. Количество страниц\n");
				printf("5. Новинка\n");
				printf("6. Вернуться в главное меню\n");
				do
				{
					char c = '\0';
					while (scanf_s("%d%c", &punkt3, &c, 1) != 2 || c != '\n')
					{
						printf("The entered value is invalid. Please try again.\n");
						while (getchar() != '\n');
					}
				} while ((punkt3 < 1) || (punkt3 > 6));
				if (punkt3 == 6)
				{
				//	getchar();
					system("cls");
					break;
				}
				system("cls");
				for (int i = 0; i < leng - 1; i++)
				{
					for (int j = i + 1; j < leng; j++)
					{
						if (punkt3 == 1)
						{
							if (strcmp(books[i]->author, books[j]->author) > 0)
							{
								swap(books, i, j);
							}
						}
						if (punkt3 == 2)
						{
							if (strcmp(books[i]->title, books[j]->title) > 0)
							{
								swap(books, i, j);
							}
						}
						if (punkt3 == 3)
						{
							if (books[i]->year < books[j]->year)
							{
								swap(books, i, j);
							}
						}
						if (punkt3 == 4)
						{
							if (books[i]->countOfPages < books[j]->countOfPages)
							{
								swap(books, i, j);
							}
						}
						if (punkt3 == 5)
						{
							if (books[i]->neW < books[j]->neW)
							{
								swap(books, i, j);
							}
						}
					}
				}
				printf("Информация о книгах отсортирована");
				getchar();
				system("cls");
				break;
			}
		case 5: //Записать данные в файл
			system("cls");
			if (leng == 0)
			{
				printf("Пожалуйста, для начала добавьте данные о книгах");
				getchar();
				system("cls");
				break;
			}
			else
			{

				FILE* file = fopen("C:\\Users\\Asus\\source\\repos\\res\\data.txt", "w");
				printToFile(file, books, leng);
				fclose(file);
				printf("Данные были успешно записаны в файл");
				getchar();
				system("cls");
				break;
			}
		case 6:
			break;
		}

	} while (punkt != 6);


	for (int i = 0; i < leng; i++)
	{
		delete[] books[i]->author;
		delete[] books[i]->title;
		delete[] books[i];
	}
	delete[] books;
	_CrtDumpMemoryLeaks();

}
