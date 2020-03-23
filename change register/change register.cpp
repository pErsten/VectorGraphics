#include <iostream>
#include <conio.h>
#include <windows.h>
#define WIDTH 211
#define HEIGHT 54

HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

COORD dwBufferSize = { WIDTH,HEIGHT };
COORD dwBufferCoord = { 0, 0 };
SMALL_RECT rcRegion = { 0, 0, WIDTH - 1, HEIGHT - 1 };

CHAR_INFO space[HEIGHT][WIDTH];

using namespace std;
class Point {
	int m_x;
	int m_y;
public:
	Point() { m_x = 0; m_y = 0; }
	void setValue(int x, int y) { m_x = x; m_y = y; }
	void incx() { if (m_x < WIDTH - 1) m_x++; }
	void incy() { if (m_y < HEIGHT- 5) m_y++; }
	void decx() { if (m_x > 1) m_x--; }
	void decy() { if (m_y > 1) m_y--; }
	int  getx() { return m_x; }
	int  gety() { return m_y; }
};
void kik(Point point1, Point point2, const char &symbol) {
	const int column1 = point1.getx();
	const int column2 = point2.getx();
	const int row1 = point1.gety();
	const int row2 = point2.gety();
	double x;
	if(abs(column1-column2)>abs(row1-row2))
		for (int i = ((column1 > column2) ? column2 : column1); i <= ((column1 > column2) ? column1 : column2); i++) {
			x = (1.0 / (column2 - column1)) * (i - column1) * (row2 - row1) + row1;
			space[(int)(ceil(x))][i].Attributes = symbol;
		}
	else if(row1 != row2 || column1 != column2)
		for (int i = ((row1 >= row2) ? row2 : row1); i <= ((row1 >= row2) ? row1 : row2); i++) {
			x = (1.0 / (row2 - row1)) * (i - row1) * (column2 - column1) + column1;
			space[i][(int)(ceil(x))].Attributes = symbol;
		}
}
void ses(CHAR_INFO space[HEIGHT][WIDTH], Point *point, const char &symbol) {
	kik(point[0], point[1], symbol);
	kik(point[1], point[2], symbol);
	kik(point[2], point[3], symbol);
	kik(point[3], point[0], symbol);

}
int main() {
	Point point[4];
	point[0].setValue(73, 40);
	point[1].setValue(65, 12);
	point[2].setValue(20, 30);
	point[3].setValue(3 , 3 );
	int index = 1;

	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	ReadConsoleOutput(hOutput, (CHAR_INFO*)space, dwBufferSize,
		dwBufferCoord, &rcRegion);
	char symbol = 255;
	ses(space, point, symbol);
	while (_kbhit) {
		WriteConsoleOutput(hOutput, (CHAR_INFO*)space, dwBufferSize,
			dwBufferCoord, &rcRegion);
		char chur = _getch();
		char sombol = 0;
		switch (chur) {
		case '1': index = 0; break;
		case '2': index = 1; break;
		case '3': index = 2; break;
		case '4': index = 3; break;
		case 'w': ses(space, point, sombol); point[index].decy(); ses(space, point, symbol); break;
		case 'a': ses(space, point, sombol); point[index].decx(); ses(space, point, symbol); break;
		case 's': ses(space, point, sombol); point[index].incy(); ses(space, point, symbol); break;
		case 'd': ses(space, point, sombol); point[index].incx(); ses(space, point, symbol); break;
		case 'q': exit(0); break;
		default: continue;
		}
	}
}