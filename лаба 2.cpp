#include <iostream>
#include <clocale>
using namespace std;

int amount, counter, num_to_enter, max_value, min_value, div_num_five, power_two, top, check_num, first, second, third, difference;
float sum_num, middle_value;

bool isPrime(int n)
{
	if (n > 1)
	{
		for (int i = 2; i < n; i += 1)
			if (n % i == 0) // проверка на четность числа, если условие выполняется, то число четное, а значит составное
				return false;
		return true; // если число прошло проверку цикла фор (у него нет делителей в диапазоне от 2 до самого числа не включительно), то оно простое
	}
	else // число не простое (1) или не натуральное (0 и отрицательные)
		return false;
}

int main(int argc, char* argv[])
{
	bool isHuman = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0)
	{
		isHuman = true;
	}
	if (isHuman)
	{
		setlocale(LC_ALL, "RU");
		cout << "Введите количество чисел последовательности: " << endl;
	}
	cin >> amount;
	for (counter = 0; counter < amount; counter++)
	{
		if (isHuman)
		{
			cout << counter + 1 << " число:" << endl;
		}
		cin >> num_to_enter;
		if (isHuman)
		{
			if (isPrime(num_to_enter))
				cout << num_to_enter << " - простое число" << endl;
			else
				cout << num_to_enter << " - не простое число" << endl;
		}
		else
		{
			if (isPrime(num_to_enter))
				cout << num_to_enter << endl;
		}
		if (counter == 0)
		{
			min_value = num_to_enter;
		}
		sum_num += num_to_enter;
		if (min_value > num_to_enter)
			min_value = num_to_enter;
		if (max_value < num_to_enter)
			max_value = num_to_enter;
		if (num_to_enter % 5 == 0)
			div_num_five += 1;
		check_num = num_to_enter;
		while (check_num % 2 == 0)
		{
			check_num = check_num / 2;
		}
		if (check_num == 1)
		{
			power_two += 1;
		}
		first = second;
		second = third;
		third = num_to_enter;
		if (counter >= 2)
		{
			if ((first + second) < third)
			{
				top++;
			}
		}
	}
	middle_value = round((sum_num / amount) * 100) / 100;
	difference = max_value - min_value;
	if (isHuman)
		cout << "Среднее арифметическое чисел: " << endl;
	cout << middle_value << endl;
	if (isHuman)
		cout << "Разность между максимумом и минимумом последовательности: " << endl;
	cout << difference << endl;
	if (isHuman)
		cout << "Количество чисел кратных числу 5: " << endl;
	cout << div_num_five << endl;
	if (isHuman)
		cout << "Количество чисел, которые являются степенью двойки: " << endl;
	cout << power_two << endl;
	if (isHuman)
		cout << "Количество чисел, которые превышают сумму двух предыдущих чисел последовательности: " << endl;
	cout << top << endl;
}
