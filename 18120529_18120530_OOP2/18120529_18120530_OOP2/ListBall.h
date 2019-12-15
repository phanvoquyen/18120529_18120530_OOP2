#pragma once
#include<iostream>
#include<Windows.h>
#include"ball.h"
#include<ctime>
#include <vector>
#include<vector>

extern int  MAX_BALL;//số quả bóng tối đa được tạo khi chơi game
class ball;
class ListBall
{
	vector<ball> LB; //danh sách bóng, bóng thứ 0 là bòng chính của trò chơi, từ 1 đến MAX_BALL là bóng nhằm tạo thêm thú vị cho game
	int width, height;//chiều rộng và chiều cao của khung chơi
public:
	ListBall();//khi tạo danh sẽ có 1 bóng chính của game được tạo
	~ListBall();
	ball Get_Ball(int i);
	//hàm tạo bóng chính để chơi
	void CreatMainBall(int w, int h);
	//hàm khởi tạo bóng giả 
	void CreatFakeBall();
	//hàm kiểm tra chúng vật phẩm của các bóng, tăng điểm khi chúng, cập nhập điểm lên console
	void UpDrawScore(int &p1s, int &p2s, ListItem &l);
	//hàm xóa bóng giả khi bóng đụng vào biên trên hay biên dưới, và thay đổi hướng bóng chính khi
	void DrawDeleteFakeBall();
	//hàm kiểm tra bóng chính đụng vào thanh và tạo bóng giả 
	void ImpactPACreateFB(pad p1, pad p2, int &p1s, int &p2s);
	//hàm kiểm tra còn bóng giả trên sân không
	int ISExistFakeBall();
	//hàm di chuyển danh sách bóng
	void MoveListBall();
	//hàm vẽ danh sách bóng
	void Draw();
	//hàm reset danh sách bóng
	void Reset();
	//hàm kiểm tra bóng chính bị ra ngoài biên,( thanh không đở được bóng)
	//hàm kiểm tra bóng chính bị ra ngoài biên,( thanh không đở được bóng)
	vector<ball> getLBall();
	void push_back(ball b);
	void clear();
};

