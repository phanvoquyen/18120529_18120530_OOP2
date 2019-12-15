#include "pad.h"

pad::pad(float xi, float yi, int sizei, int wi, int hi)// ham khoi tao pad
{
	x = xi;
	y = yi;
	xo = xi;
	yo = yi;
	size = sizei;
	width = wi;
	height = hi;
	vx = 0;
}

void pad::drawpar()// ham ve pad
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD p;

	//ve vi tri hien tai cua pad la khoang trang khi pad di chuyen
	p.X = int(xo) - size;
	p.Y = int(yo);
	SetConsoleCursorPosition(h, p);
	for (int i = -size; i < size; i++)
		cout << ' ';

	//ve vi tri pad di toi
	p.X = int(x) - size;
	p.Y = int(y);
	SetConsoleCursorPosition(h, p);
	SetConsoleTextAttribute(h, 12);// set mau cho pad
	for (int i = -size; i < size; i++)
		cout << '=';

	SetConsoleTextAttribute(h, 15);// set lai mau trang
	// dat lai vi tri hien tai cua pad
	xo = x;
	yo = y;
}

void pad::reset()// ham reset lai pad khi ghi diem
{
	x = float(width / 2);// dat lai vi tri x cua pad
}

void pad::runleft()// ham di chuyen ve trai pad
{
	x -= 2;
}

void pad::runright()// ham di chuyen ve phai pad
{
	x += 2;
}

void pad::limit()// ham xu li khi pad cham 2 bien
{
	if (x < size + 1)
		x = float(size + 1);
	else if (x > width - size - 2)
		x = float(width - size - 2);
}
int pad::getsize()
{
	return size;
}
float pad::getX0() { return xo; }
float pad::getY0() { return yo; }
float pad::getX() { return x; }
float pad::getY() { return y; }
float pad::getVX() { return vx; }
void pad::setSize(int x) { size = x; }
void pad::setX0(float x) { xo = x; }
void pad::setY0(float x) { yo = x; }
void pad::setX(float x) { this->x = x; }
void pad::setY(float x) { y = x; }
void pad::setVX(float x) { vx = x; }