#include "ListBall.h"
#include"ListItem.h"
#include"pad.h"
int MAX_BALL = 2;
ListBall::ListBall()
{

}
ListBall::~ListBall()
{
}
ball ListBall::Get_Ball(int i) {
	return LB[i];
}
//hàm tạo bóng chính để chơi game
void ListBall::CreatMainBall(int w, int h) {
	width = w;//gán chiều rộng màn hình
	height = h;//gán chiều cao màn hình
	ball b(width / 2 - 1, height / 2, width, height, 1);//bóng chính của game
	LB.push_back(b);//thêm bóng chính vào danh sach bóng
}
//hàm tạo bóng giả để game thêm phần khó
void ListBall::CreatFakeBall() {
	int i = rand() % MAX_BALL + 1;//tạo ngẫu nhiêu số bóng
	for (int j = 0; j < MAX_BALL; j++) {//duyệt từ đầu đến số bóng muốn tạo
		ball  b(width / 2 - 1, height / 2, width, height, 0);//tạo bóng
		LB.push_back(b);//thêm bóng vào danh sách
	}
}
void ListBall::UpDrawScore(int &p1s, int &p2s, ListItem &l) {
	double value;
	for (int i = 0; i < LB.size(); i++) {
		if (LB[i].trangthai == 1) {//bóng vẫn còn đang hiện trên màn hình console
			//kiểm tra ball có va chạm với vật phẩm không
			value = LB[i].IsImpactItem(l);
			//kiểm tra giá trị của vật phẩm, nếu bằng 1 là không có vật phẩm bị đánh chúng
			if (value != 1) {//nếu khác 1 có vật phẩm bị đánh chúng
				LB[i].UpScore(value, p1s, p2s);// thay đổi điểm của người chơi phụ thược vào giá trị của vật phẩm bị đánh chúng
			}
		}
	}
}
void ListBall::DrawDeleteFakeBall() {
	for (int i = 1; i < LB.size(); i++) {//duyệt từ phần từ bóng giả đầu tiên là 1 đến cuối
		if (LB[i].trangthai == 1) {//bóng vẫn còn đang hiện trên màn hình console
			if (LB[i].ballscore() == 1 || LB[i].ballscore() == 2) {//nếu bóng đụng thành sẽ trả về giá trị bằng 1, và 2
				LB[i].DrawDeleteBall();//xóa bóng bị đụng
			}
		}
	}
}
int ListBall::ISExistFakeBall() {
	if (LB.size() == 1)//nếu trong danh sách chỉ có một bóng thật
		return 0;
	for (int i = 1; i < LB.size(); i++) {//duyệt bóng giả
		if (LB[i].trangthai == 1)//nếu tồn tại bóng giả đang trên sân thì trả về 1
			return 1;
	}
	return 0;//duyệt hết không có trả về bằng 0
}
void ListBall::ImpactPACreateFB(pad p1, pad p2, int &p1s, int &p2s) {
	for (int i = 1; i < LB.size(); i++) {//duyệt từ bóng giả
		if (LB[i].ballhitpad1(p1) == 1) {
			LB[i].setp(1);
		}//kiểm tra bóng giả đụng thanh người chơi 1, thay đổi hướng bóng
		if (LB[i].ballhitpad2(p2)==1) {
			LB[i].setp(2);
		}//kiểm tra bóng giả đụng thanh người chơi 2, thay đổi hướng bóng
	}
	int a = LB[0].ballhitpad1(p1);
	int b = LB[0].ballhitpad2(p2);
	if (a == 1) {
		LB[0].setp(1);
		p1s++;
	}
	if (b == 1) {
		p2s++;
		LB[0].setp(2);
	}
	if (a == 1 || b == 1) {//nếu bóng chín đụng vào một trong 2 thanh chơi
		if (((p1s - p2s) % 15) == 0 && (p1s != p2s)) {//nếu độ chên lệch điểm là bội số của 5 thì tạo bóng gỉa
			if (ISExistFakeBall() == 0) {//nếu không tồn tại bóng giả trể sân thì tạo
				LB.resize(1);
				CreatFakeBall();//tạo danh sách bóng giả
				for (int i = 1; i < LB.size(); i++) {//duyệt bóng giả
					LB[i].CopyCoord(LB[0], i);//tạo tọa độ cho bóng giả
				}
			}

		}
	}
	
}
void ListBall::MoveListBall() {
	for (int i = 0; i < LB.size(); i++) {//duyệt từ đầu đến cuối danh sách bóng
		if (LB[i].trangthai == 1) {//nếu bóng còn trên sân thì cho di chuyển
			LB[i].ballmove();//di chuyển bóng
			LB[i].balllimit();//kiểm tra đụng 2 biên 
		}
	}
}
void ListBall::Draw() {
	for (int i = 0; i < LB.size(); i++) {//duyệt từ đầu đến cuối danh sách bóng
		if (LB[i].trangthai == 1) {//nếu bóng còn trên sân thì vẽ
			LB[i].drawball();//vẽ bóng
		}
	}
}
void ListBall::Reset() {
	LB.resize(1);
	LB[0].resetpvp();
}
vector<ball> ListBall::getLBall() { return LB; }

void ListBall::push_back(ball b)
{
	if (LB.empty()) {
		b.setReal(1);
	}
	else {
		b.setReal(0);
	}
	b.setWidth(width);
	b.setHeight(height);
	LB.push_back(b);
}

void ListBall::clear()
{
	LB.clear();
}