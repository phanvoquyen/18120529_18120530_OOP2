#include "ListItem.h"
#include"item.h"
int MAX_ITEM = 20;


ListItem::ListItem()
{

}
void ListItem::CreatEmty() {
	LI.resize(0);
}
ListItem::ListItem(int w, int h) {
	width = w;
	height = h;
	CreatList();
}

ListItem::~ListItem()
{
}

void ListItem::CreatList() {
	item a;//một vật phẩm tạm để tạo ra các vật để lưu vào mảng danh sách các vật phậm
	for (int i = 0; i < MAX_ITEM; i++) {
		a.RandCoord(width, height);
		LI.push_back(a);
	}
}

void ListItem::Draw() {
	//duyệt từ đầu đến cuối danh sach vật phẩm
	for (int i = 0; i < LI.size(); i++) {
		if (LI[i].Get_TrangThai()) {//Kiểm tra vật phẩm thứ i đã bị bóng đụng hay chưa, nếu chưa thực hiện lệnh trong if
			LI[i].Draw();//vẽ vật phẩm chưa bị đụng ra khỏi màn hình console;
		}
	}
}

void ListItem::MoveListItem() {
	for (int i = 0; i < LI.size(); i++) {//duyệt từ đầu đến cuối danh sách vật phẩm
		if (LI[i].trangthai == 1) {//nếu vật phẩm không bị ẩn
			LI[i].DrawDeleteItem();//xóa vật phẩm ở vị trí hiện tại
			LI[i].MoveItem();//di chuyển vật phẩm
			LI[i].Draw();//vẽ lại vật phẩm ở vị trí mới
		}
	}
}

bool ListItem::IsState() {
	//duyệt từ đầu đến cuối cây
	for (int i = 0; i < LI.size(); i++) {
		if (LI[i].Get_TrangThai())//kiểm tra vật phẩm có bị bóng chạm chưa
			return false;//nếu tồn tại một vật phẩm chưa bị bóng chạm thì trả về false là danh sách vật phẩm chưa bị chạm hết
	}
	return true;//danh sách các vật phẩm đã bị chạm hết.
}

void ListItem::deleteDraw() {
	for (int i = 0; i < LI.size(); i++) {//duyeẹt từ đầu đến cuối danh sach vật phẩm
		if (LI[i].Get_TrangThai()) {//nếu trạng thái bằng 1 là còn hiện trên màn hình console thì xóa
			LI[i].DrawDeleteItem();//xóa vật phẩm trên màn hình console
		}
	}
}
void ListItem::DeleteANewItem() {
	LI.resize(0);//tạo trống danh sách
	CreatList();//tạo mới danh sach
}
vector<item> ListItem::getLI() { return LI; }

void ListItem::push_back(item it)
{
	it.setHeight(height);
	it.setWidth(width);
	LI.push_back(it);
}
