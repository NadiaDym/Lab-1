#include <iostream>
#include <fstream>

using namespace std;

// Функция для ввода матрицы из консоли
void inputMtx(int** matrix, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			cin >> matrix[i][j];
		}
	}
}

// Функция для вывода матрицы
void printMtx(int** matrix, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

// Функция для записи матрицы в файл
void writeMtxToFile(int** matrix, int size, const string& filename) {
	ofstream file(filename);
	if (file.is_open()) {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				file << matrix[i][j] << " ";
			}
			file << endl;
		}
		file.close();
	}
	else {
		cout << "Ошибка открытия файла!" << endl;
	}
}

// Функция для чтения матрицы из файла
void readMtxFromFile(int** matrix, int size, const string& filename) {
	ifstream file(filename);
	if (file.is_open()) {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				file >> matrix[i][j];
			}
		}
		file.close();
	}
	else {
		cout << "Ошибка открытия файла!" << endl;
	}
}

// Функция для редактирования элементов матрицы
void editMtx(int** matrixA, int** matrixB, int size) {
	int row, col, value, numMtx;
	cout << "Введите номер матрицы, которую хотите редактировать:\n";
	cin >> numMtx;
	if (numMtx == 1)
	{
		cout << "Введите изменения в матрице A - номер строки, столбца и новое значение (через пробел):\n";
		cin >> row >> col >> value;
		if (row > 0 && row <= size && col > 0 && col <= size) { 
			matrixA[row-1][col-1] = value;
		}
	}
	else if (numMtx == 2)
	{
		cout << "Введите изменения в матрице B - номер строки, столбца и новое значение (через пробел):\n";
		cin >> row >> col >> value;
		if (row > 0 && row <= size && col > 0 && col <= size) { 
			matrixB[row-1][col-1] = value;
		}
	}
	else {
		cout << "Некорректные индексы!" << endl;
	}
}

// Функция для подсчета столбцов матрицы А, которые встречаются более одного раза в матрице B
int countRepeatCol(int** A, int** B, int size) {
	int count = 0;

	for (int j = 0; j < size; ++j) {
		int rpt = 0;
		for (int i = 0; i < size; ++i) {
			if (A[i][j] == B[i][j]) {
				rpt++;
			}
		}
		if (rpt > 1) {
			count++;
		}
	}
	return count;
}


int main() {
	setlocale(LC_ALL, "RU");
	int size;
	cout << "Введите размерность квадратных матриц одним числом: ";
	cin >> size;
	cout << "Меню:\n";
	cout << "1. Ввод матриц A и B\n";
	cout << "2. Вывод матриц A и B\n";
	cout << "3. Запись матриц в файл\n";
	cout << "4. Чтение матриц из файла\n";
	cout << "5. Редактирование матрицы\n";
	cout << "6. Подсчет столбцов матрицы A, встречающихся в матрице B более одного раза\n";
	cout << "7. Вызов меню\n";
	cout << "0. Выход из программы\n";

	// Динамическое выделение памяти для матриц
	int** A = new int*[size];
	int** B = new int*[size];
	for (int i = 0; i < size; i++) {
		A[i] = new int[size];
		B[i] = new int[size];
	}

	int choice;
	do {

		cout << "Выберите опцию: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Введите элементы матрицы A размером " << size << "x" << size << " построчно:\n";
			inputMtx(A, size);
			cout << "Введите элементы матрицы B размером " << size << "x" << size << " построчно:\n";
			inputMtx(B, size);
			break;
		case 2:
			cout << "Матрица A:\n";
			printMtx(A, size);
			cout << "Матрица B:\n";
			printMtx(B, size);
			break;
		case 3:
			writeMtxToFile(A, size, "matrix_A.txt");
			writeMtxToFile(B, size, "matrix_B.txt");
			cout << "Матрицы записаны в файл.\n";
			break;
		case 4:
			readMtxFromFile(A, size, "matrix_A.txt");
			readMtxFromFile(B, size, "matrix_B.txt");
			cout << "Матрицы считаны из файла.\n";
			break;
		case 5:
			editMtx(A, B, size);
			break;
		case 6:
			cout << "Количество столбцов матрицы A, встречающихся в матрице B более одного раза: " << countRepeatCol(A, B, size) << endl;
			break;
		case 7:
		{
			cout << "Меню:\n";
			cout << "1. Ввод матриц A и B\n";
			cout << "2. Вывод матриц A и B\n";
			cout << "3. Запись матриц в файл\n";
			cout << "4. Чтение матриц из файла\n";
			cout << "5. Редактирование матрицы\n";
			cout << "6. Подсчет столбцов матрицы A, встречающихся в матрице B более одного раза\n";
			cout << "7. Вызов меню\n";
			cout << "0. Выход из программы\n";
		}
			break;
		case 0:
			cout << "Вы завершили работу программы!\n";
			break;
		default:
			cout << "Некорректный ввод, попробуйте снова.\n";
			break;
		}
	} while (choice != 0);

	// Освобождение памяти
	for (int i = 0; i < size; i++) {
		delete[] A[i];
		delete[] B[i];
	}
	delete[] A;
	delete[] B;

	return 0;
}