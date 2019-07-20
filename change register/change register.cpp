#include <iostream>
#include <cmath>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <cassert>
using namespace std;
class Point {
	int m_x;
	int m_y;
public:
	Point() { m_x = 0; m_y = 0; }
	void setValue(int x, int y) { m_x = x; m_y = y; }
	void incx() { if (m_x < 99) m_x++; }
	void incy() { if (m_y < 43) m_y++; }
	void decx() { if (m_x > 0) m_x--; }
	void decy() { if (m_y > 0) m_y--; }
	int getx() { return m_x; }
	int gety() { return m_y; }
};
void kik(bool** arr, Point& point1, Point& point2, bool index) {
	int column1 = point1.getx();
	int column2 = point2.getx();
	int row1 = point1.gety();
	int row2 = point2.gety();
	double x;
	cout << ((index) ? " -> " : "    ") << "A( " << column1 << ", " << row1 << " )" << endl;
	if(abs(column1-column2)>abs(row1-row2))
		for (int i = ((column1 > column2) ? column2 : column1); i <= ((column1 > column2) ? column1 : column2); i++) {
			x = (1.0 / (column2 - column1)) * (i - column1) * (row2 - row1) + row1;
				arr[static_cast<int>(round(x))][i] = true;
		}
	else
		for (int i = ((row1 >= row2) ? row2 : row1); i <= ((row1 >= row2) ? row1 : row2); i++) {
			x = (1.0 / (row2 - row1)) * (i - row1) * (column2 - column1) + column1;
			arr[i][static_cast<int>(round(x))] = true;
		}
}
int main() {
	Point point[4];
	point[0].setValue(73, 40);
	point[1].setValue(65, 12);
	point[2].setValue(20, 30);
	point[3].setValue(2, 2);
	int index = 0;
	while (_kbhit) {
		int rows = 44, columns = 100;
		bool** arr = new bool* [rows]();
		for (int count = 0; count < rows; ++count)
			arr[count] = new bool[columns]();
		char chur = _getch();
		switch (chur) {
		case '1': index = 0; break;
		case '2': index = 1; break;
		case '3': index = 2; break;
		case '4': index = 3; break;
		case 'w': point[index].incy(); break;
		case 'a': point[index].decx(); break;
		case 's': point[index].decy(); break;
		case 'd': point[index].incx(); break;
		case 'q': exit(0); break;
		default: continue;
		}
		system("cls");
		kik(arr, point[0], point[1], index == 0);
		kik(arr, point[1], point[2], index == 1);
		kik(arr, point[2], point[3], index == 2);
		kik(arr, point[3], point[0], index == 3);
		cout << "^ Y 44\n";
		for (int i = 43; i >= 0; i--) {
			cout << "|";
			for (int j = 0; j < 100; j++) {
				if (i == point[index].gety() && j == point[index].getx()) {
					cout << static_cast<char>(178);
					cout << static_cast<char>(178);
				}
				else if (arr[i][j]) {
					cout << static_cast<char>(177);
					cout << static_cast<char>(177);
				}
				else
					cout << "  ";
			}
			cout << endl;
		}
		cout << "+";
		for (int i = 0; i < 200; i++)
			cout << "-";
		cout << "> X 100";
		for (int count = 0; count < rows; ++count)
			delete[] arr[count];
		delete[] arr;
	}
}