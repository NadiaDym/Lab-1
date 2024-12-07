#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;



// Функция для создания динамической матрицы
double** createMatrix(int rows, int cols) {
	double** matrix = new double*[rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new double[cols];
	}
	return matrix;
}

// Функция для удаления динамической матрицы
void deleteMatrix(double** matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

// Функция для заполнения матрицы
void fillMatrix(double** matrix, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cin >> matrix[i][j];
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
	double** result = createMatrix(N, K);

	// Выполняем умножение
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < K; ++j) {
			result[i][j] = 0;
			for (int l = 0; l < M; ++l) {
				result[i][j] += A1[i][l] * A2[l][j];
			}
		}
	}

	return result;
}

// Функция для возведения матрицы в степень
double** powerMatrix(double** matrix, int rows, int cols, int x) {
	double** result = createMatrix(rows, cols);

	// инициализация результата единичной матрицей
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			result[i][j] = (i == j) ? 1 : 0;
		}
	}

	// Степенное возведение матрицы
	for (int k = 0; k < x; ++k) {
		double** temp = createMatrix(rows, cols);
		temp = multiplyMatrices(result, rows, cols, matrix, cols);
		deleteMatrix(result, rows);
		result = temp;
	}

	return result;
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
	cin >> N >> M;

	double** A1 = createMatrix(N, M);
	if (isHuman)
		cout << "Введите элементы матрицы построчно:\n";
	fillMatrix(A1, N, M);

	int command;
	while (true) {
		if (isHuman)
			cout << "Введите команду (0 - окончание, 1 - вывод, 2 - умножение, 3 - возведение в степень):\n";
		cin >> command;
		if (command == 0) break;
		else if (command == 1) {
			if (isHuman)
				cout << "Матрица:\n";
			printMatrix(A1, N, M);
		}
		else if (command == 2) {
			int K;
			if (isHuman)
				cout << "Введите количество столбцов K для матрицы A2:\n";
			cin >> K;

			if (N != K)
			{
				if (isHuman)
					cout << "Невозможно перемножить матрицы: количество столбцов первой матрицы не равно количеству строк второй.\n";
			}
			else {
				double** A2 = createMatrix(M, K);
				fillMatrix(A2, M, K);

				double** result = multiplyMatrices(A1, N, M, A2, K);
				if (result) {
					deleteMatrix(A1, N);
					A1 = result;
					M = K;
				}
				deleteMatrix(A2, M);
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
				cin >> x;
				double** result = powerMatrix(A1, N, M, x);
				if (result) {
					deleteMatrix(A1, N);
					A1 = result;
				}
			}
		}
		else {
			if (isHuman)
				cout << "Неверная команда, попробуйте снова.\n";
		}
	}

	deleteMatrix(A1, N);
	return 0;
}
