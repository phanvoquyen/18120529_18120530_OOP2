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
	float xo, yo, x, y;// xo, yo: vi tri hien tai cua ball. x, y: vi tri den cua ball
	float vx, vy;// vx, vy: van toc cua ball
	int width, height;// chieu dai, chieu rong cua man hinh console
	int real;//là bóng thật hay bóng giả
	int trangthai;//là còn hiện trên màn hình console hay không
	int p;//bóng do pad nào đánh lên;
public:
	friend class ListBall;
	ball();
	~ball();
	ball(float xi, float yi, int w, int h, int i);// ham khoi tao ball
	void drawball();// ham ve ball
	void startpvp();// ham set van toc cua ball ban dau pvp
	void startpve();// ham set van toc cua ball ban dau pve
	void ballmove();// ham di chuyen cua ball
	void balllimit();// ham xu li khi ball cham 2 bien
	int ballscore();// ham tinh diem: return 1 thi player2 ghi dc 1 diem, return 2 thi player1 ghi dc 1 diem
	int ballhitpad1(pad p);// ham xu li khi ball cham vao pad player1, nếu có va chạm thì trả về 1
	int ballhitpad2(pad p);// ham xu li khi ball cham vao pad player2,  nếu có va chạm thì trả về 1
	void  padcompmove(pad &p);// ham di chuyen cua pad comp
	void resetpvp();// ham xu li ball khi ghi diem pvp
	void resetpve();// ham xu li ball khi ghi diem pve
	//Đồ án 2
	//hàm kiểm tra bóng có đụng chúng vật phẩm nào trong danh sach, nếu có thì đổi trạng thái vật phẩm sang 0(ẩn)
	double IsImpactItem(ListItem &a);
	//hàm tăng điểm khi va chạm với vật phẩm
	void UpScore(double &value, int &ps1, int &ps2);
	//hàm xóa bóng trên màn hình console
	void DrawDeleteBall();
	//hàm lấy vị trí của bóng này gán cho bóng kia
	void CopyCoord(ball b, int i);
	float getBallX();
	float getBallY();
	float getBallX0();
	float getBallY0();
	float getBallVX();
	float getBallVY();
	int getState();
	int getp();
	void setBallX(float);
	void setBallY(float);
	void setX0(float);
	void setY0(float);
	void setBallVX(float);
	void setBallVY(float);
	void setState(int);
	void setWidth(int);
	void setHeight(int);
	void setReal(int);
	void setp(int);
};