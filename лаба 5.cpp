﻿#include <iostream>
#include <cstring>
#include <iomanip>
#include <windows.h>
#include <sstream>

using namespace std;

const int MAX_NAME_LENGTH = 100;
const int GRADES_COUNT = 5;

struct STUDENT {
	char full_name[MAX_NAME_LENGTH];
	int group_number;
	int grades[GRADES_COUNT];
	float averageGrade() const {
		int sum = 0;
		for (int i = 0; i < 5; ++i)
			sum += grades[i];
		return static_cast<float>(sum) / 5;
	}
};


// Устойчивый алгоритм сортировки по номеру группы по возрастанию
void stable_sort_by_group(STUDENT students[], int N) {
	for (int i = 0; i < N - 1; ++i) {
		for (int j = 0; j < N - 1 - i; ++j) {
			if (students[j].group_number > students[j + 1].group_number) {
				STUDENT temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
		}
	}
}
// Функция для вывода информации о студентах
void print_students(const STUDENT students[], int N) {
	for (int i = 0; i < N; i++) {
		cout << students[i].group_number << " - " << students[i].full_name << ": ";
		for (int j = 0; j < GRADES_COUNT; j++) {
			cout << students[i].grades[j];
			if (j < GRADES_COUNT - 1) {
				cout << ", ";
			}
		}
		cout << endl;
	}
}
// Сортировка по среднему значению (по убыванию)
void stableSortByAverageGrade(STUDENT* students, int n) {
	for (int i = 1; i < n; ++i) {
		STUDENT key = students[i];
		int j = i - 1;
		while (j >= 0 && students[j].averageGrade() < key.averageGrade()) {
			students[j + 1] = students[j];
			--j;
		}
		students[j + 1] = key;
	}
}
// Печать средних значений (по убыванию)
void printHighAverageStudents(const STUDENT* students, int n) {
	for (int i = 0; i < n; ++i) {
		float avg = students[i].averageGrade();
		cout << students[i].group_number << ", " << students[i].full_name << " - " << avg << endl;
	}
}

// Функция для фильтрации студентов со средним баллом выше 4.0
int filterHighAverageStudents(const STUDENT* students, int n, STUDENT* filteredStudents) {
	int M = 0;
	for (int i = 0; i < n; ++i) {
		if (students[i].averageGrade() > 4.0) {
			filteredStudents[M++] = students[i];
		}
	}
	return M;
}

// Функция для группировки и агрегации данных по номеру группы
struct GroupStats {
	int group_number;
	int student_count;
	int bad_student_count;
};

// Функция для центровки текста в заданной ширине
string center(const string& str, int width) {
	int padding = width - str.length();
	int pad_left = padding / 2; // Левый отступ
	int pad_right = padding - pad_left; // Правый отступ
	return string(pad_left, ' ') + str + string(pad_right, ' ');
}

// Функция для оформления таблицы
void head(const GroupStats group_stats[], int unique_groups) {
	cout << "Группировка по номерам групп:\n";
	cout << "|" << setw(15) << center("Номер группы", 30) << "|"
		<< setw(15) << center("Кол-во студентов", 30) << "|"
		<< setw(15) << center("С плохими оценками", 30) << "|\n";
	cout << "----------------------------------------------------------------------------------------------\n";

	for (int i = 0; i < unique_groups; i++) {
		cout << "|" << setw(15) << center(to_string(group_stats[i].group_number), 30) << "|"
			<< setw(15) << center(to_string(group_stats[i].student_count), 30) << "|"
			<< setw(15) << center(to_string(group_stats[i].bad_student_count), 30) << "|\n";
	}
}

// Функция для поиска группы
int findGroupIndex(GroupStats group_stats[], int unique_groups, int group_number) {
	for (int j = 0; j < unique_groups; j++) {
		if (group_stats[j].group_number == group_number) {
			return j; // Возвращаем индекс группы
		}
	}
	return -1; // Если группа не найдена
}

// Функция для сортировки групп по количеству двоечников
void sortGroupStats(GroupStats group_stats[], int unique_groups) {
	for (int i = 0; i < unique_groups - 1; ++i) {
		for (int j = 0; j < unique_groups - 1 - i; ++j) {
			if (group_stats[j].bad_student_count < group_stats[j + 1].bad_student_count ||
				(group_stats[j].bad_student_count == group_stats[j + 1].bad_student_count &&
					group_stats[j].group_number > group_stats[j + 1].group_number)) {
				swap(group_stats[j], group_stats[j + 1]);
			}
		}
	}
}

// Функция для высчета уникальных групп и кол-ва двоечников
void group_students(const STUDENT students[], int N, bool isHuman) {
	GroupStats* group_stats = new GroupStats[N];
	int unique_groups = 0;

	// Сбор данных по группам
	for (int i = 0; i < N; i++) {
		int group_index = findGroupIndex(group_stats, unique_groups, students[i].group_number);

		if (group_index == -1) {
			group_stats[unique_groups++] = { students[i].group_number, 1, 0 };
			group_index = unique_groups - 1;
		}
		else {
			group_stats[group_index].student_count++;
		}

		// Проверяем на наличие двоек
		for (int j = 0; j < GRADES_COUNT; j++) {
			if (students[i].grades[j] == 2) {
				group_stats[group_index].bad_student_count++;
				break;  // Если есть хотя бы одна двойка, выходим из цикла
			}
		}
	}

	// Сортируем группы
	sortGroupStats(group_stats, unique_groups);

	// Выводим результаты
	if (isHuman)
	{
		head(group_stats, unique_groups);
	}
	else
	{
		for (int i = 0; i < unique_groups; i++)
			cout << group_stats[i].group_number << " - " << group_stats[i].student_count << " - " << group_stats[i].bad_student_count << endl;
	}

	delete[] group_stats; // Освобождаем память
}

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	bool isHuman = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0)
	{
		isHuman = true;
	}
	setlocale(LC_ALL, "RU");
	int N;

	// Ввод количества студентов
	if (isHuman)
		cout << "Введите количество студентов: ";
	cin >> N;
	cin.ignore(); // Игнорируем оставшийся символ новой строки

	STUDENT* students = new STUDENT[N]; //

	// Ввод информации о студентах
	for (int i = 0; i < N; i++) {
		if (isHuman)
			cout << "Введите ФИО студента " << (i + 1) << ": ";
		cin.getline(students[i].full_name, MAX_NAME_LENGTH);
		if (isHuman)
			cout << "Введите номер группы: ";
		cin >> students[i].group_number;
		if (isHuman)
			cout << "Введите успеваемость (5 оценок): ";
		for (int j = 0; j < GRADES_COUNT; j++) {
			cin >> students[i].grades[j];
		}
		cin.ignore(); // Игнорируем оставшийся символ новой строки
	}

	// 1. Упорядочивание информации по возрастанию номера группы
	stable_sort_by_group(students, N);

	// 2. Вывод информации о студентах
	print_students(students, N);

	// 3. Фильтрация по среднему балу
	STUDENT* filteredStudents = new STUDENT[N]; // Массив для отфильтрованных студентов
	int M = filterHighAverageStudents(students, N, filteredStudents);

	stableSortByAverageGrade(filteredStudents, M);

	if (M > 0) {
		if (isHuman) {
			cout << endl << "Студенты со средним баллом > 4.0, упорядоченные по убыванию среднего балла:" << endl;
		}
		printHighAverageStudents(filteredStudents, M);
	}
	else {
		cout << "NO" << endl;
	}
	// 4. Группировка по номерам групп и агрегация
	group_students(students, N, isHuman);

	// 5. Освобождение памяти
	delete[] students; // Освобождение памяти для массива студентов
	delete[] filteredStudents;
	return 0;
}