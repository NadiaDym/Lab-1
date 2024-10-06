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
	while (x != 0 || y != 0)
	{
		if (isHuman) 
		{
			cout << "Введите координаты х и у: " << endl;
		}
		cin >> x;
		cin >> y;
		if (x == 0 && y == 0)
		{
			break;
		}
		if ((x <= 3 && x >= 0) & (y <= 4 && y >= 0))
		{
			double func = 0;
			func = -4.0 / 3 * x + 4;
			if (y <= func && y >= 0)
			{
				cout << "YES" << endl;
				if (isHuman)
				{
					string ans;
					cout << "Вы хотите продолжить?\n";
					cin >> ans;
					if (ans == ("YES"))
					{
						continue;
					}
					else
					{
						break;
					}
				}
				else
				{
					continue;
				}
			}
			else
			{
				cout << "NO" << endl;
				if (isHuman)
				{
					string ans;
					cout << "Вы хотите продолжить?\n";
					cin >> ans;
					if (ans == ("YES"))
					{
						continue;
					}
					else
					{
						break;
					}
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			cout << "NO" << endl;
			if (isHuman) 
			{
				string ans2;
				cout << "Упс, кажется эта точка не попала в треугольник. Вы хотите продолжить?\n";
				cin >> ans2;
				if (ans2 == ("YES"))
				{
					continue;
				}
				else
				{
					break;
				}
			}
			else
			{
				continue;
			}
		}
	}
}
