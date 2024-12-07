#include <iostream>
#include <iomanip> // для std::setprecision
#include <cmath> // для std::pow

using namespace std;



// Функция для создания динамической матрицы
double** createMatrix(int rows, int cols) {
	double** matrix = new double*[rows]; // выделяем память для строк
	for (int i = 0; i < rows; i++) {
		matrix[i] = new double[cols]; // выделяем память для каждого столбца
	}
	return matrix;
}

// Функция для удаления динамической матрицы
void deleteMatrix(double** matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i]; // освобождаем память для каждой строки
	}
	delete[] matrix; // освобождаем память для массива строк
}

// Функция для заполнения матрицы
void fillMatrix(double** matrix, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cin >> matrix[i][j]; // ввод элементов матрицы
		}
	}
}

// Функция для вывода матрицы
void printMatrix(double** matrix, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cout << fixed << setprecision(0) << matrix[i][j];
			if (j < cols - 1)
				cout << " ";
		}
		cout << endl;
	}
}

// Функция для умножения матриц
double** multiplyMatrices(double** A1, int N, int M, double** A2, int K) {
	double** result = createMatrix(N, K); // создаем матрицу результата

	// Выполняем умножение
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < K; ++j) {
			result[i][j] = 0; // инициализация элемента
			for (int l = 0; l < M; ++l) {
				result[i][j] += A1[i][l] * A2[l][j]; // суммируем произведение
			}
		}
	}

	return result; // возвращаем результат
}

// Функция для возведения матрицы в степень
double** powerMatrix(double** matrix, int rows, int cols, int x) {
	double** result = createMatrix(rows, cols);

	// инициализация результата единичной матрицей
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			result[i][j] = (i == j) ? 1 : 0; // единичная матрица
		}
	}

	// Степенное возведение матрицы
	for (int k = 0; k < x; ++k) {
		double** temp = createMatrix(rows, cols); // временная матрица для умножения
		temp = multiplyMatrices(result, rows, cols, matrix, cols);
		deleteMatrix(result, rows); // освобождение памяти старой матрицы
		result = temp; // обновление матрицы результата
	}

	return result; // возвращаем результат
}

int main(int argc, char* argv[])
{
	bool isHuman = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0)
	{
		isHuman = true;
	}
	setlocale(LC_ALL, "RU");
	int N, M;
	if (isHuman)
		cout << "Введите размеры матрицы A1, N и M:\n";
	cin >> N >> M; // ввод размеров матрицы

	// Создаем и заполняем матрицу A1
	double** A1 = createMatrix(N, M);
	if (isHuman)
		cout << "Введите элементы матрицы построчно:\n";
	fillMatrix(A1, N, M);

	int command;
	while (true) {
		if (isHuman)
			cout << "Введите команду (0 - окончание, 1 - вывод, 2 - умножение, 3 - возведение в степень):\n";
		cin >> command; // ввод команды
		if (command == 0) break; // выход из цикла
		else if (command == 1) {
			if (isHuman)
				cout << "Матрица:\n";
			printMatrix(A1, N, M); // вывод матрицы
		}
		else if (command == 2) {
			int K;
			if (isHuman)
				cout << "Введите количество столбцов K для матрицы A2:\n";
			cin >> K; // ввод размеров новой матрицы

			if (N != K)
			{
				if (isHuman)
					cout << "Невозможно перемножить матрицы: количество столбцов первой матрицы не равно количеству строк второй.\n";
			}
			else {
				double** A2 = createMatrix(M, K); // создаем матрицу A2
				fillMatrix(A2, M, K); // заполняем ее

				double** result = multiplyMatrices(A1, N, M, A2, K); // перемножаем матрицы
				if (result) {
					deleteMatrix(A1, N); // освобождение старой матрицы
					A1 = result; // обновление A1
					M = K; // обновление размера M
				}
				deleteMatrix(A2, M); // освобождение матрицы A2
			}
		}
		else if (command == 3) {
			if (N != M) {
				if (isHuman)
					cout << "Невозможно возвести матрицу в степень: матрица должна быть квадратной.\n";
				else
					cout << "NO\n";
			}
			else {
				int x;
				if (isHuman)
					cout << "Введите показатель степени x:\n";
				cin >> x; // ввод степени
				double** result = powerMatrix(A1, N, M, x); // возведение в степень
				if (result) {
					deleteMatrix(A1, N); // освобождение матрицы A1
					A1 = result; // обновление A1
				}
			}
		}
		else {
			if (isHuman)
				cout << "Неверная команда, попробуйте снова.\n"; // обработка неверных команд
		}
	}

	deleteMatrix(A1, N); // освобождение памяти перед выходом
	return 0; // завершение программы
}