#include <iostream>
#include <clocale>
using namespace std;

int amount, counter, num_to_enter, amount_of_delit, max_value, min_value, div_num_five, power_two, top, check_num, first, second, third, difference;
float sum_num, middle_value;

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
		amount_of_delit = 0;
		if (num_to_enter % 2 != 0)
		{
			int core = sqrt(num_to_enter);
			for (int delit = 3; delit <= core; delit += 2)
			{
				if (num_to_enter % delit == 0)
				{
					amount_of_delit++;
					break;
				}
			}
		}
		else
			amount_of_delit++;
		if (amount_of_delit == 0 and num_to_enter != 1 or num_to_enter == 2)
		{
			if (isHuman)
				cout << num_to_enter << " - простое число" << endl;
			else
				cout << num_to_enter << endl;
		}
		else
		{
			if (isHuman)
				cout << num_to_enter << " - не простое число" << endl;
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
