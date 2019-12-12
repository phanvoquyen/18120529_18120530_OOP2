#include<iostream>
#include<Windows.h>
#include<ctime>
using namespace std;

class pad;
class item;
class ListItem;
class ball//tao class ball
{
private:
	float  xo, yo, x, y;// xo, yo: vi tri hien tai cua ball. x, y: vi tri den cua ball
	float vx, vy;// vx, vy: van toc cua ball
	int width, height;// chieu dai, chieu rong cua man hinh console
public:
	ball(float xi, float yi, int w, int h);// ham khoi tao ball
	void drawball();// ham ve ball
	void startpvp();// ham set van toc cua ball ban dau pvp
	void startpve();// ham set van toc cua ball ban dau pve
	void ballmove();// ham di chuyen cua ball
	void balllimit();// ham xu li khi ball cham 2 bien
	int ballscore();// ham tinh diem: return 1 thi player2 ghi dc 1 diem, return 2 thi player1 ghi dc 1 diem
	void ballhitpad1(pad p);// ham xu li khi ball cham vao pad player1
	void ballhitpad2(pad p);// ham xu li khi ball cham vao pad player2
	void padcompmove(pad &p);// ham di chuyen cua pad comp
	void resetpvp();// ham xu li ball khi ghi diem pvp
	void resetpve();// ham xu li ball khi ghi diem pve
	//Đồ án 2
	//hàm kiểm tra bóng có đụng chúng vật phẩm nào trong danh sach, nếu có thì đổi trạng thái vật phẩm sang 0(ẩn)
	double IsImpactItem(ListItem &a);
	//hàm xét xem bóng đang đi lên hay xuống
	int IsUpDown();
	//hàm tăng điểm khi va chạm với vật phẩm
	void UpScore(double &value, int &ps1, int &ps2);
	float getBallX();
	float getBallY();
	float getBallVX();
	float getBallVY();
};