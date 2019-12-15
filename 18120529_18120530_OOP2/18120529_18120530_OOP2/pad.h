#include<iostream>
#include<Windows.h>
#include<ctime>
using namespace std;

class pad //tao class pad
{
private:
	int size; // kick thuoc cua pad
	float xo, yo, x, y; // xo, yo: vi tri hien tai cua pad. x, y: vi tri den cua pad
	float vx; // van toc cua pad
	int width, height; // chieu dai, chieu rong cua man hinh console
public:
	friend class ball;
	pad(float x, float y, int size, int wi, int hi); // ham khoi tao pad
	void drawpar();// ham ve pad len man hinh
	void runleft();// ham di chuyen ve trai pad
	void runright();// ham di chuyen ve phai pad
	void limit();// ham xu li khi pad cham 2 bien
	void reset();// ham reset lai pad khi ghi diem
	int getsize();
	float getX0();
	float getY0();
	float getX();
	float getY();
	float getVX();
	void setSize(int);
	void setX0(float);
	void setY0(float);
	void setX(float);
	void setY(float);
	void setVX(float);
};

