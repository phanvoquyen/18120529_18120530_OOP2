#include "pad.h"
#include "ball.h"
#include"ListItem.h"
#include"item.h"

ball::ball() {

}
ball::~ball() {

}
ball::ball(float xi, float yi, int wi, int hi, int i)// ham khoi tao ball
{
	x = xi;
	y = yi;
	xo = xi;
	yo = yi;
	vx = vy = 0;
	width = wi;
	height = hi;
	real = i;
	trangthai = i;
	p = 0;
}

void ball::drawball()// ham ve ball
{
	if (trangthai == 1) {
		HANDLE h;
		h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD p;

		//ve vi tri hien tai cua ball la khoang trang khi ball di chuyen
		p.X = int(xo);
		p.Y = int(yo);
		SetConsoleCursorPosition(h, p);
		cout << ' ';

		//ve vi tri pad di toi
		p.X = int(x);
		p.Y = int(y);
		SetConsoleCursorPosition(h, p);
		SetConsoleTextAttribute(h, 5 + real);// set mau cho ball
		cout << 'O';

		SetConsoleTextAttribute(h, 15);// set lai mau trang
		// dat lai vi tri hien tai cua pad
		xo = x;
		yo = y;
	}
}

void ball::resetpvp()// ham xu li ball khi ghi diem
{
	srand(time(NULL));

	// dat lai toa do cua ball
	x = float(width / 2 - 1);
	y = float(height / 2);

	// dat lai vx cua ball
	vx = rand() % 2 + 1;
	if (vx == 1)
		vx = 0.1;
	else
		vx = -0.1;

	// dat lai vy cua ball
	vy = rand() % 2 + 1;
	if (vy == 1)
		vy = 1;
	else
		vy = -1;
}

void ball::resetpve()// ham xu li ball khi ghi diem
{
	srand(time(NULL));

	// dat lai toa do cua ball
	x = float(width / 2 - 1);
	y = float(height / 2);

	// dat lai vx cua ball
	vx = rand() % 2 + 1;
	if (vx == 1)
		vx = 0.1;
	else
		vx = -0.1;

	// dat lai vy cua ball
	vy = 1;
}

void ball::startpvp()// ham set van toc cua ball ban dau
{
	// set vx cua ball
	vx = rand() % 2 + 1;
	if (vx == 1)
		vx = 0.1;
	else
		vx = -0.1;

	// set vy cua ball
	vy = rand() % 2 + 1;
	if (vy == 1)
		vy = 1;
	else
		vy = -1;
}

void ball::startpve()// ham set van toc cua ball ban dau
{
	// set vx cua ball
	vx = rand() % 2 + 1;
	if (vx == 1)
		vx = 0.1;
	else
		vx = -0.1;

	// set vy cua ball
	vy = 1;
}

void ball::ballmove()// ham di chuyen cua ball
{
	// cho x, y tien them doan bang vx, vy
	x += vx;
	y += vy;
}

void ball::balllimit()// ham xu li khi ball cham 2 bien
{
	// neu ball cham bien trai
	if (x <= 1)
	{
		vx *= -1;// doi chieu cua ball
		x = 1;
	}
	else if (x >= width - 3)// neu ball cham bien phai
	{
		vx *= -1;// doi chieu cua ball
		x = float(width - 3);
	}
}

int ball::ballscore()// ham tinh diem: return 1 thi player2 ghi dc 1 diem, return 2 thi player1 ghi dc 1 diem
{
	if (y >= height - 1)// neu player 1 ko bat duoc ball
		return 1;
	else if (y <= 1)// neu player 2 ko bat duoc ball
		return 2;
}

int ball::ballhitpad1(pad p)// ham xu li khi ball cham vao pad player1
{
	if (y >= p.y - 1 && y <= p.y + 1)
	{
		if (x > p.x - p.size && x < p.x + p.size)
		{
			vy *= -1;
			vx += float(x - p.x) / 3;
			y = p.y - 1;
			return 1;
		}
	}
	return 0;
}

int ball::ballhitpad2(pad p)// ham xu li khi ball cham vao pad player2
{
	if (y <= p.y + 1 && y >= p.y - 1) {
		if (x > p.x - p.size && x < p.x + p.size)
		{
			vy *= -1;
			vx += float(x - p.x) / 3;
			y = p.y + 1;
			return 1;
		}
	}
	return 0;
}

void ball::padcompmove(pad &p)
{

	p.vx -= float(p.x - x) / 10.0f;
	p.vx *= 0.83f;
	p.x += p.vx;
}

double ball::IsImpactItem(ListItem &a) {
	int i = 0;
	int is = 0;//biến kiểm tra có phần tử bị chạm hay không
	int temp = i; //biến lưu vật phẩm thư i bị đụng
	//duyệt từ đầu đến cuối của danh sách các vật phẩm
	for (; i < a.LI.size(); i++) {
		//kiểm tra coi tọa độ của bóng có chùng với tọa độ của vật phẩm nào hay không
		if ((int)x == (int)a.LI[i].x && (int)y == (int)a.LI[i].y&&a.LI[i].trangthai == 1) {
			//nếu có thì trạng thái của vật phẩm bằng 0(ẩn)
			a.LI[i].trangthai = 0;
			if (a.LI[i].i == 5) {//nếu đụng chúng vật cản thì vận tốc thay đổi
				vy *= -1;//đổi hướng chạy của bóng;
			}

			is = 1;
			temp = i;
		}
	}
	if (is) {
		//trả về giá trị của vật phẩm;
		return a.LI[temp].diem;
	}
	else {
		//nếu không có va chạm thì giá trị chả về là 1;
		return 1;
	}
}



void ball::UpScore(double &value, int &p1s, int &p2s) {
	if (p == 2) {//kiểm tra bóng do thanh đánh lên chúng vật phẩm, rồi cộng điểm cho thanh đó
		if (value <= 2) {//nếu giá trị vật phẩm dưới hai, thì là nhân lên x2 ,x0.5
			p2s *= value;
		}
		else {//nếu giá trị vật phẩm dưới hai, thì là nhân lên x2 ,x0.5
			p2s += value;
		}
		value = 1;//đưa về giá trị ban đầu
	}
	else if (p == 1) {
		if (value <= 2) {//nếu giá trị vật phẩm dưới hai, thì là nhân lên x2 ,x0.5
			p1s *= value;
		}
		else {//nếu giá trị vật phẩm dưới hai, thì là nhân lên x2 ,x0.5
			p1s += value;
		}
		value = 1;//đưa về giá trị ban đầu
	}
	else {
		value = 1;
	}
}

void ball::DrawDeleteBall() {
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD p;

	//ve vi tri hien tai cua ball la khoang trang khi ball di chuyen
	p.X = int(xo);
	p.Y = int(yo);
	SetConsoleCursorPosition(h, p);
	cout << ' ';
	trangthai = 0;
}

void ball::CopyCoord(ball b, int i) {
	if (trangthai == 0) {
		x = b.x;
		y = b.y;
		xo = b.xo;
		yo = b.yo;
		vx = -1 * (b.vx + i); //sẽ đi ngược hướng với bóng thật
		vy = b.vy;
		trangthai = 1;
	}
}
float ball::getBallX() { return this->x; }
float ball::getBallY() { return y; }
float ball::getBallX0() { return xo; }
float ball::getBallY0() { return yo; }
float ball::getBallVX() { return vx; }
float ball::getBallVY() { return vy; }
int ball::getState() { return trangthai; }
int ball::getp() { return p; }
void ball::setBallX(float x) { this->x = x; }
void ball::setBallY(float y) { this->y = y; }
void ball::setBallVX(float x) { vx = x; }
void ball::setBallVY(float y) { vy = y; }
void ball::setState(int x) { trangthai = x; }
void ball::setX0(float x) { xo = x; }
void ball::setY0(float y) { yo = y; }
void ball::setWidth(int w) { width = w; }
void ball::setHeight(int h) { height = h; }
void ball::setReal(int i) { real = i; }
void ball::setp(int a) { p = a; }