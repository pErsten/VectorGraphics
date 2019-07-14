#include <iostream>
#include <cmath>
#include <vector>
#include <Windows.h>
using namespace std;

void kik(bool** arr, int& row1, int& column1, int& row2, int& column2) {
	double x;
	cout << "A( " << column1 << ", " << row1 << " ), B( " << column2 << ", " << row2 << " )" << endl;
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
	int rows = 44, columns = 100;
	bool** arr = new bool* [rows]();
	for (int count = 0; count < rows; ++count)
		arr[count] = new bool[columns]();

	int row1 = 40, column1 = 73, row2 = 12, column2 = 65;
	kik(arr, row1, column1, row2, column2);
	column2 = 20; row2 = 30;
	kik(arr, row1, column1, row2, column2);
	column1 = 2; row1 = 2;
	kik(arr, row1, column1, row2, column2);
	column2 = 65; row2 = 12;
	kik(arr, row1, column1, row2, column2);
	cout << "^ Y 44\n";
	for (int i = 43; i >= 0; i--) {
		cout << "|";
		for (int j = 0; j < 100; j++) {
			if (arr[i][j]) {
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