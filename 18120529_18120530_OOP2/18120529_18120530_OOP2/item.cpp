#include "item.h"
int MAX_TYPEITEM = 5;


item::item()
{
}

item::~item()
{
}

void item::Draw() {
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD p;

	p.X = int(x);
	p.Y = int(y);
	SetConsoleCursorPosition(h, p);
	SetConsoleTextAttribute(h, 3);// set mau cho vật phẩm
	switch (i) {
	case 1: cout << "$"; break;
	case 2:cout << "@"; break;
	case 3:cout << "2"; break;
	case 4:cout << "*"; break;
	case 5: {
		SetConsoleTextAttribute(h, 16);
		cout << " "; }
			break;
	}

	SetConsoleTextAttribute(h, 15);// set lai mau trang
	// dat lai vi tri hien tai cua vật phẩm
	xo = x;
	yo = y;
}

void item::MoveItem() {
	if (x >= width - 5 || x <= 2) {//kiểm tra vật phẩm có chạm biên 
		vx *= -1;//đổi hướng đi của vật phẩm
	}
	x += vx;

}

void item::RandSore() {
	if (i < 5) {//nếu vật phẩm không là vật cản
		switch ((int)i) {//tùy thuộc vào số random mà vật phẩm có điểm khác nhau
		case 1: diem = 10; break;//điểm là +10
		case 2: diem = 5; break;//điểm là +5
		case 3: diem = 2; break;//điểm là x2
		case 4: diem = 0.5; break;//điểm là x0.5
		}
	}
	else {
		diem = 1;
	}
}

void item::RandCoord(int w, int h) {//chuyen vao chieu cao, va chieu rong man hinh concole
	x = rand() % (w - 5) + 3;//tạo ngẫu nhiên tọa độ hoành cho vật phẩm
	y = rand() % (h / 2) + h / 4;//tạo ngẫu nhiên tọa độ tung cho vật phẩm
	xo = x;
	yo = y;
	trangthai = 1;//hien tren man hinh con so le
	i = rand() % 5 + 1;//chọn ngẫu nhiên hình dáng của vật phẩm
	RandSore();
	vx = 2;//khởi tạo vận tốc ban đầu bằng 1
	width = w;
	height = h;
}

int item::IsLimit(int w, int h) {
	if (y == h - 1) {
		return 1;
	}
	return 0;
}

int item::Get_TrangThai() {
	return trangthai;
}

double item::Get_Score() {
	return diem;
}

void item::DrawDeleteItem() {
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD p;


	p.X = int(x);
	p.Y = int(y);
	SetConsoleCursorPosition(h, p);
	SetConsoleTextAttribute(h, 15);
	cout << ' ';
}
// lấy hình dáng của vật phẩm theo mã acsii
int item::getShape() { return this->i; }
// lấy trạng thái của vật phẩm
int item::getState() { return this->trangthai; }
// lấy điểm của vật phẩm
double item::getScore() { return this->diem; }
// lấy tọa độ
float item::getX() { return this->x; }
float item::getY() { return this->y; }
// lấy tọa độ trước đó
float item::getX0() { return this->xo; }
float item::getY0() { return this->yo; }
// lấy vận tốc
int item::getVX() { return this->vx; }


//set
void item::setShape(int x) { i = x; }
void item::setState(int x) { trangthai = x; }
void item::setScore(float x) { diem = x; }
void item::setX(float x) { this->x = x; }
void item::setY(float x) { y = x; }
void item::setX0(float x) { xo = x; }
void item::setY0(float x) { yo = x; }
void item::setVX(int x) { vx = x; }
void item::setWidth(int w) { width = w; }
void item::setHeight(int h) { height = h; }