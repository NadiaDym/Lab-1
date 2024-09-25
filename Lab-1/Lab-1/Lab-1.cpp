#include <iostream>
#include <clocale>
#include <cmath>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RU");
	double x = 1;
	double y = 1;
	bool isHuman = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0)
	{
		isHuman = true;
	}
	if (isHuman)
	{
		while ((x != 0 || y != 0))
		{
			cout << "Введите координаты х и у: " << endl;
			cin >> x;
			cin >> y;
			if (x == 0 && y == 0)
			{
				return 0;
			}
			if ((x <= 3 && x >= 0) & (y <= 4 && y >= 0))
			{
				double func = 0;
				func = -4.0 / 3 * x + 4;
				if (y <= func && y >= 0)
				{
					cout << "YES" << endl;
					std::string ans;
					std::cout << "Вы хотите продолжить?\n";
					std::cin >> ans;
					if (ans == ("YES"))
					{
						continue;
					}
					else
					{
						break;
					}
				}

			}
			else
			{
				cout << "NO" << endl;
				std::string ans2;
				std::cout << "Упс, кажется эта точка не попала в треугольник. Вы хотите продолжить?\n";
				std::cin >> ans2;
				if (ans2 == ("YES"))
				{
					continue;
				}
				else
				{
					break;
				}
			}
		}
	}
	else
	{
		while ((x != 0 || y != 0))
		{
			cin >> x;
			cin >> y;
			if (x <= 3 && x >= 0)
			{
				double func = 0;
				func = -4.0 / 3 * x + 4;
				if (y <= func && y >= 0)
				{
					cout << "YES" << endl;
				}
				else
				{
					cout << "NO" << endl;
				}
			}
			else
			{
				cout << "NO" << endl;
			}
		}
	}
}
