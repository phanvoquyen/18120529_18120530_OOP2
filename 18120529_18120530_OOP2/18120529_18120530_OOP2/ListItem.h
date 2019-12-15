#pragma once
#include<iostream>
#include<Windows.h>
#include<ctime>
#include"item.h"
#include<vector>
extern int MAX_ITEM;
class item;
class ListItem
{
	vector<item> LI;//danh sach các vật phẩm
	int width, height;// chieu dai, chieu rong cua man hinh console
public:
	friend class ball;
	//hàm khởi tạo các item cho danh sách item, hàm tạo các item, rồi cho lưu vào mảng danh sach
	void CreatList();
	//hàm khởi tạo 2 tham biến, khởi tạo giá trị cho biến width, height, và goị hàm CreatList để khởi tạo giá trị cho vật phẩm
	ListItem(int w, int h);
	//hàm vẽ danh sách các vật phẩm
	void Draw();
	//hàm di chuyển các vật phẩm của danh sach
	void MoveListItem();
	//hàm kiểm tra các vật phẩm cho bị va chạm với bóng hết chưa
	bool IsState();
	//Hàm xóa các vật phẩm hiện có trên màn hình console
	void deleteDraw();
	//hàm xóa toàn bộ vật phẩm có trong danh sách, và tạo mới
	void DeleteANewItem();
	vector<item> getLI();
	void push_back(item it);
	ListItem();
	~ListItem();
	void CreatEmty();
};

