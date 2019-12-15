#pragma once
#include<iostream>
#include<Windows.h>
#include<ctime>
using namespace std;
extern int MAX_TYPEITEM;
class item
{
	int i;//hinh dang cua hinh
	int trangthai;//hinh con hien hay khong
	double diem;//so diem co duoc neu danh chung vat pham
	float x;//toa do hoanh cua vat pham
	float y;//toa do tung cua vat pham
	float xo;//vi tri hoanh cua item luc truoc
	float yo;//vi tri tung cua item luc truoc
	int vx;//vận tốc ngang của vật phẩm 
	int width, height;// chieu dai, chieu rong cua man hinh console
public:
	friend class ListItem;
	friend class ball;
	//ham gán giá trị vật phẩm
	void RandSore();
	//ham tao ngau nhieu toa do cua vat pham
	void RandCoord(int w, int h);
	//ham ve vat pham
	void Draw();
	////hàm di chuyển 
	void MoveItem();
	//ham xuat ra xuat ra trang thai cua vat pham
	int Get_TrangThai();
	//ham xuat ra gia tri diem cua vat pham
	double Get_Score();
	//ham kiem tra vat pham cham bien;
	int IsLimit(int, int);
	//Hàm xóa vật phẩm trên màn hình console
	void DrawDeleteItem();
	item();
	~item();
	// lấy hình dáng của vật phẩm theo mã acsii
	int getShape();
	// lấy trạng thái của vật phẩm
	int getState();
	// lấy điểm của vật phẩm
	double getScore();
	// lấy tọa độ
	float getX();
	float getY();
	// lấy tọa độ trước đó
	float getX0();
	float getY0();
	// lấy vận tốc
	int getVX();

	// set
	void setShape(int);
	void setState(int);
	void setScore(float);
	void setX(float);
	void setY(float);
	void setX0(float);
	void setY0(float);
	void setVX(int);
	void setWidth(int);
	void setHeight(int);
};