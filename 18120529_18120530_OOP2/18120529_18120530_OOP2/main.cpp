#include <windows.h>
#include <iostream>
#include<vector>
#include <ctime>
#include <queue>
#include<fstream>
#include <string>
#include "pad.h"
#include"ListBall.h"
#include"ListItem.h"
#include"item.h"
#include<conio.h>
using namespace std;
//game chinh
//thong so man hinh console
int width = 55;
int height = 35;
ofstream savefile;
//file luu danh sach diem

string FILENAMESCORE = "filenamescore.txt";
void resetPVP(pad &p1, pad &p2, ball &b, bool &run, int &p1s, int &p2s)									// ham reset khi ball qua vach dich
{
	p1.reset();
	p2.reset();
	b.resetpvp();
	run = false;

	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD p;

	// ve bang diem
	p.X = 0;
	p.Y = height;
	SetConsoleCursorPosition(h, p);
	cout << "\n    Player1 score: " << p1s << "\t\tPlayer2 score: " << p2s << '\n';
}

void resetPVE(pad &p1, pad &p2, ball &b, bool &run, int &p1s, int &p2s)									// ham reset khi ball qua vach dich
{
	p1.reset();
	p2.reset();
	b.resetpve();
	run = false;

	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD p;

	// ve bang diem
	p.X = 0;
	p.Y = height;
	SetConsoleCursorPosition(h, p);
	cout << "\n    Player score: " << p1s << "\t\tComputer score: " << p2s << '\n';
}

void drawborder() // ham ve khung
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);

	// ve vien tren
	SetConsoleTextAttribute(h, 15);
	for (int i = 0; i < width - 1; ++i)
		cout << '*';

	//ve 2 ben vien
	for (int i = 0; i < height - 1; ++i)
	{
		cout << "\n|";
		for (int i = 1; i < width - 2; ++i)
			cout << ' ';
		cout << '|';
	}
	cout << '\n';

	//ve vien duoi
	for (int i = 0; i < width - 1; ++i)
		cout << '*';
}

void hidecursor() // ham an con tro
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO info;
	info.dwSize = 10;
	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);
}

//đồ án 2
//viết điểm của người chơi vào file điểm
void WriteScore(string FileName, int p1s, int p2s) {
	ofstream File;
	File.open(FileName, ios::app);//mở file để viết tiếp
	if (File.fail()) {//nếu không tồn tại thì thoát
		return;
	}
	if (p1s > p2s) {//điểm nào lớn hơn sẽ viết vào file
		File << p1s << endl;
	}
	else {
		File << p2s << endl;;
	}
	File.close();
}

//hamf reset giữ liệu của game trước khi chơi mới
void ReSet(int &p1s, int &p2s, ListBall &Lb, ListItem &l, pad &p1, pad &p2) {
	Lb.Reset();//đặt lại bóng chính, và không có bóng giả
	l.DeleteANewItem();//tạo mới danh sách vật phẩm
	p1.reset();
	p2.reset();
	p1s = 0;
	p2s = 0;

}

//hàm xử lí sau khi kết thúc game
void EndGame(ListBall &Lb, ListItem &l, int &choose, bool &run) {
	Lb.DrawDeleteFakeBall();//xóa bóng giả còn trên sân
	l.deleteDraw();//xóa những vật phẩm còn trên sân
	choose = 0;
	run = 0;

}

//hàm vẽ bảng thành tích
void DrawAchBoard(priority_queue<int>Score) {
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD p;
	p.X = int(width / 2 - 10);
	p.Y = int(height / 4);
	SetConsoleCursorPosition(h, p);
	cout << "achievement boards" << endl;
	//xuất ra 30 điểm cao nhất
	int i;
	for (i = 0; i < 10; i++) {
		if (!Score.empty()) {
			if (Score.top() != 0) {
				p.X = int(width / 2);
				p.Y = int(height / 4 + i + 1);
				SetConsoleCursorPosition(h, p);
				cout << Score.top() << endl;;
				Score.pop();
			}
		}
	}
	p.X = int(width / 2 - 20);
	p.Y = int(height / 4 + i + 1);
	SetConsoleCursorPosition(h, p);
	system("pause");
}

//hàm đọc bangr thành tích thừ file
void ReadScore(string FileName) {
	ifstream File;
	File.open(FileName);//mở file để đọc
	if (File.fail()) {//không có file thì thoát
		return;
	}
	//danh sách điểm người chơi
	priority_queue<int>Score;
	int a;//
	char temp[255];
	while (!File.eof()) {//cho chạy từ đầu đến cuối file
		File >> a;//lấy điếm sô
		File.getline(temp, 255);
		Score.push(a);//lưu vào hàng đợi ưu tiên
	}
	File.close();//đóng file
	//xuất ra 30 điểm cao nhất
	DrawAchBoard(Score);
}

//hàm xóa bảng thành tích
void DrawDeleteAchBoard() {
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD p;
	for (int i = 0; i < height - 10; i++) {
		p.X = int(width / 2 - 20);
		p.Y = int(height / 4 + i);
		SetConsoleCursorPosition(h, p);
		cout << "                                  " << endl;
	}
}

//hàm vẽ lại game và điểm của game
void DrawTypeASocre(int choose, int p1s, int p2s) {
	if (choose == 1) {
		HANDLE h;
		h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD p;

		// ve bang diem
		p.X = 0;
		p.Y = height;
		SetConsoleCursorPosition(h, p);
		cout << "\n    Player1 score: " << p1s << "   " << "\t\tPlayer2 score: " << p2s << "     \n";
		return;
	}
	if (choose == 2) {
		HANDLE h;
		h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD p;

		// ve bang diem
		p.X = 0;
		p.Y = height;
		SetConsoleCursorPosition(h, p);
		cout << "\n    Player score: " << p1s << "   " << "\t\tComputer score: " << p2s << "       \n";
	}
}

//hàm lưu game
void saveGameLogic(string filename, pad p1, pad p2, ListBall lb, bool &run, int p1s, int p2s, ListItem litem, int choose)
{

	savefile.open(filename); // biến toàn cục
	if (!savefile) return;
	// lưu thông số của quả bóng
	int n = lb.getLBall().size();
	vector<ball> m = lb.getLBall();
	savefile << n << endl;
	for (int i = 0; i < n; i++)
	{
		savefile << m[i].getBallX() << " ";
		savefile << m[i].getBallY() << " ";
		savefile << m[i].getBallX0() << " ";
		savefile << m[i].getBallY0() << " ";
		savefile << m[i].getBallVX() << " ";
		savefile << m[i].getBallVY() << " ";
		savefile << m[i].getState() << " ";
		savefile << m[i].getp() << " ";
		savefile << endl;
	}

	// lưu thống số của chương ngại vật và vật phẩm
	vector<item> list = litem.getLI();
	n = litem.getLI().size();
	// lưu số vật phẩm còn lại
	savefile << n << endl;
	for (int i = 0; i < n; i++)
	{
		savefile << list[i].getShape() << " ";
		savefile << list[i].Get_TrangThai() << " ";
		savefile << list[i].getScore() << " ";
		savefile << list[i].getX() << " ";
		savefile << list[i].getY() << " ";
		savefile << list[i].getX0() << " ";
		savefile << list[i].getY0() << " ";
		savefile << list[i].getVX() << " ";
		savefile << endl;
	}

	// lưu thông số của pad1
	savefile << p1.getsize() << " ";
	savefile << p1.getX() << " ";
	savefile << p1.getY() << " ";
	savefile << p1.getX0() << " ";
	savefile << p1.getY0() << " ";
	savefile << p1.getVX() << " ";
	savefile << endl;
	// lưu thông số pad2
	savefile << p2.getsize() << " ";
	savefile << p2.getX() << " ";
	savefile << p2.getY() << " ";
	savefile << p2.getX0() << " ";
	savefile << p2.getY0() << " ";
	savefile << p2.getVX() << " ";
	savefile << endl;
	// lưu điểm
	savefile << p1s << " ";
	savefile << p2s << " ";
	savefile << endl;
	// lưu chế độ chơi 
	savefile << run << endl;
	savefile << choose << endl;
}

//hàm lưu game
void savegame(pad p1, pad p2, ListBall lb, bool &run, int p1s, int p2s, ListItem litem, int choose)
{

	system("cls");
	string filename;
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	cout << "Nhap ten file save: ";
	cin >> filename;
	saveGameLogic(filename, p1, p2, lb, run, p1s, p2s, litem, choose);
	system("pause");
	system("cls");
	drawborder();
	litem.Draw();
	return;
}

//hàm tải game
void loadgame(pad &p1, pad &p2, ListBall &lb, bool &run, int &p1s, int &p2s, ListItem &litem, int &choose) {
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	system("cls");
	string filename;
	cout << "Nhap ten game: ";
	do {
		cin >> filename;
	} while (filename == "");


	fstream file(filename, ios::in);
	if (file.fail()) {
		return;//khong co game ten do;
	}
	int n;
	//ListBall lb;
	lb.clear();

	file >> n;
	float ballX, ballY, ballX0, ballY0;
	float ballVX, ballVY;
	int ispad;//biến lưu giá trị do thanh nào đạp lên
	int state;
	for (int i = 0; i < n; i++) {
		ball b;
		file >> ballX >> ballY >> ballX0 >> ballY0 >> ballVX >> ballVY >> state >> ispad;
		//chuyen toa do thanh lb
		b.setBallX(ballX);
		b.setBallY(ballY);
		b.setX0(ballX0);
		b.setY0(ballY0);
		b.setBallVX(ballVX);
		b.setBallVY(ballVY);
		b.setState(state);
		b.setp(ispad);
		lb.push_back(b);
	}


	// đọc số vật phẩm còn lại
	int m;
	file >> m;
	int hinh, trangthai, itemVX;
	float score, itemX, itemY, itemX0, itemY0;
	litem.CreatEmty();
	//ListItem litem;
	for (int i = 0; i < m; i++)
	{
		item it;
		file >> hinh >> trangthai >> score >> itemX >> itemY >> itemX0 >> itemY0 >> itemVX;
		it.setShape(hinh);
		it.setState(trangthai);
		it.setScore(score);
		it.setX(itemX);
		it.setY(itemY);
		it.setX0(itemX0);
		it.setY0(itemY0);
		it.setVX(itemVX);
		litem.push_back(it);
	}


	// đcọ thông số của pad1
	int psize1;
	float pad1X, pad1Y, pad1X0, pad1Y0, pad1VX;
	file >> psize1 >> pad1X >> pad1Y >> pad1X0 >> pad1Y0 >> pad1VX;
	p1.setSize(psize1);
	p1.setX(pad1X);
	p1.setY(pad1Y);
	p1.setX0(pad1X0);
	p1.setY0(pad1Y0);
	p1.setVX(pad1VX);

	// đcọ thông số pad2
	int psize2;
	float pad2X, pad2Y, pad2X0, pad2Y0, pad2VX;
	file >> psize2 >> pad2X >> pad2Y >> pad2X0 >> pad2Y0 >> pad2VX;
	p2.setSize(psize2);
	p2.setX(pad2X);
	p2.setY(pad2Y);
	p2.setX0(pad2X0);
	p2.setY0(pad2Y0);
	p2.setVX(pad2VX);

	// đọc điểm
	file >> p1s >> p2s;

	// đọc chế độ chơi
	file >> run >> choose;

	// vẽ lại màn hình chơi
	system("cls");
	drawborder();
	lb.Draw();
	p1.drawpar();
	p2.drawpar();
	litem.Draw();


}

int main()
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);

	srand(time(NULL));

	//thu nho man hinh console
	SMALL_RECT display = { 0, 0, width, height + 3 };//tang kich co co cosole
	SetConsoleWindowInfo(h, TRUE, &display);

	//an con tro tren man hinh console
	hidecursor();

	// ve khung vien
	drawborder();

	//cho bien bat dau game
	bool run = false;
	int choose = 0;//lua chon choi, 1 choi voi nguoi, 2 choi voi may

	//khai bao player1 player2 ball danh sach các vật phẩm.
	pad p1(width / 2, height - 2, 4, width, height);
	pad p2(width / 2, 2, 4, width, height);
	//khai báo danh sach bóng
	ListBall Lb;
	//tạo bóng chính để game chơi
	Lb.CreatMainBall(width, height);
	//tạo danh sách vật phẩm
	ListItem l(width, height);

	//khai bao bien diem cua 2 player
	int p1s = 0;
	int p2s = 0;


	//ve player1 player2 ball
	p1.drawpar();

	//ham ve danh sach bong
	Lb.Draw();
	//dat van toc cho ball
	Lb.Reset();
	//biên lưu giá trị vật phẩm vừa bắn chúng.
	double value = 1;

	while (1)
	{
		if (!run && choose == 0)
		{
			ReSet(p1s, p2s, Lb, l, p1, p2);//hàm reset lại game trước khi chơi
			COORD p;

			//ve intro
			p.X = int(width / 2 - 10);
			p.Y = int(height / 1.5f - 3);
			SetConsoleCursorPosition(h, p);
			cout << "   PING PONG GAME   ";

			//ve lua chon player vs player
			p.X = int(width / 2 - 15);
			p.Y = int(height / 1.5f - 1);
			SetConsoleCursorPosition(h, p);
			cout << "PLAYER VS PLAYER:	PRESS 1         ";

			//ve lua chon player vs computer
			p.X = int(width / 2 - 15);
			p.Y = int(height / 1.5f + 1);
			SetConsoleCursorPosition(h, p);
			cout << "PLAYER VS COMPUTER: PRESS 2           ";

			//ve lua cho mo bang thanh tich
			p.X = int(width / 2 - 15);
			p.Y = int(height / 1.5f + 3);
			SetConsoleCursorPosition(h, p);
			cout << "ACHIEVEMENT BOARDS:PRESS 3          ";

			// ve lua chon load game
			p.X = int(width / 2 - 15);
			p.Y = int(height / 1.5f + 5);
			SetConsoleCursorPosition(h, p);
			cout << "LOAD GAME:PRESS 4          ";
			if (GetAsyncKeyState(VK_NUMPAD1))//getAsyncKeyState là hàm bắt fhim, VK_NUMPAP1 là bắt phim số 1, VK_NUMPAP0-VKNUMPAP9 tuong duong tu 1-9
			{
				COORD p;

				//xoa intro
				p.X = int(width / 2 - 10);
				p.Y = int(height / 1.5f - 3);
				SetConsoleCursorPosition(h, p);
				cout << "                    ";

				//xoa lua chon player vs player
				p.X = int(width / 2 - 20);
				p.Y = int(height / 1.5f - 1);
				SetConsoleCursorPosition(h, p);
				cout << "                                  ";

				//xoa lua chon player vs computer
				p.X = int(width / 2 - 20);
				p.Y = int(height / 1.5f + 1);
				SetConsoleCursorPosition(h, p);
				cout << "                                  ";

				//xóa intro mà bảng thành tích
				p.X = int(width / 2 - 20);
				p.Y = int(height / 1.5f + 3);
				SetConsoleCursorPosition(h, p);
				cout << "                                  ";
				// xóa load game
				p.X = int(width / 2 - 20);
				p.Y = int(height / 1.5f + 5);
				SetConsoleCursorPosition(h, p);
				cout << "                                  ";

				//cho game bat dau chay player vs player
				choose = 1;
			}


			if (GetAsyncKeyState(VK_NUMPAD2))
			{
				COORD p;

				//xoa intro
				p.X = int(width / 2 - 10);
				p.Y = int(height / 1.5f - 3);
				SetConsoleCursorPosition(h, p);
				cout << "                    ";

				//xoa lua chon player vs player
				p.X = int(width / 2 - 20);
				p.Y = int(height / 1.5f - 1);
				SetConsoleCursorPosition(h, p);
				cout << "                                  ";

				//xoa lua chon player vs computer
				p.X = int(width / 2 - 20);
				p.Y = int(height / 1.5f + 1);
				SetConsoleCursorPosition(h, p);
				cout << "                                  ";

				//xóa intro mà bảng thành tích
				p.X = int(width / 2 - 20);
				p.Y = int(height / 1.5f + 3);
				SetConsoleCursorPosition(h, p);
				cout << "                                  ";
				// xóa load game
				p.X = int(width / 2 - 20);
				p.Y = int(height / 1.5f + 5);
				SetConsoleCursorPosition(h, p);
				cout << "                                  ";

				//cho game bat dau chay player vs computer
				choose = 2;
			}

			if (GetAsyncKeyState(VK_NUMPAD3)) {
				DrawDeleteAchBoard();
				ReadScore(FILENAMESCORE);
				DrawDeleteAchBoard();
			}
			if (GetAsyncKeyState(VK_NUMPAD4))
			{
				loadgame(p1, p2, Lb, run, p1s, p2s, l, choose);

			}

		}

		// hien intro player vs player
		if (!run && choose == 1)
		{
			//hien chu man hinh cho
			COORD p;

			//ve intro
			p.X = int(width / 2 - 10);
			p.Y = int(height / 1.5f - 3);
			SetConsoleCursorPosition(h, p);
			cout << "PRESS SPACE TO START";

			//ve huong dan choi player 1
			p.X = int(width / 2 - 20);
			p.Y = int(height / 1.5f - 1);
			SetConsoleCursorPosition(h, p);
			cout << "PLAYER 1	BOTTOM		left: <- right: ->";

			//ve huong dan choi player 2
			p.X = int(width / 2 - 20);
			p.Y = int(height / 1.5f + 1);
			SetConsoleCursorPosition(h, p);
			cout << "PLAYER 2	TOP		left: 4	 right: 6 ";

			// ve bang diem
			DrawTypeASocre(choose, p1s, p2s);
			if (GetAsyncKeyState(VK_SPACE))										//khi nguoi dung nhan spacebar
			{
				COORD p;

				//xoa intro
				p.X = int(width / 2 - 10);
				p.Y = int(height / 1.5f - 3);
				SetConsoleCursorPosition(h, p);
				cout << "                    ";

				//xoa huong dan choi player 1
				p.X = int(width / 2 - 20);
				p.Y = int(height / 1.5f - 1);
				SetConsoleCursorPosition(h, p);
				cout << "                                             ";

				//xoa huong dan choi player 2
				p.X = int(width / 2 - 20);
				p.Y = int(height / 1.5f + 1);
				SetConsoleCursorPosition(h, p);
				cout << "                                             ";

				//cho game bat dau chay
				run = true;
				//vẽ vật phẩm để khi chơi thấy được
				l.Draw();
			}
		}

		// hien intro player vs computer
		if (!run && choose == 2)
		{

			//hien chu man hinh cho
			COORD p;

			//ve intro
			p.X = int(width / 2 - 10);
			p.Y = int(height / 1.5f - 3);
			SetConsoleCursorPosition(h, p);
			cout << "PRESS SPACE TO START";

			//ve huong dan choi player 1
			p.X = int(width / 2 - 20);
			p.Y = int(height / 1.5f - 1);
			SetConsoleCursorPosition(h, p);
			cout << "PLAYER    BOTTOM		left: <- right: ->";

			//ve huong dan choi player 2
			p.X = int(width / 2 - 20);
			p.Y = int(height / 1.5f + 1);
			SetConsoleCursorPosition(h, p);
			cout << "COMPUTER  TOP";

			// ve bang diem
			DrawTypeASocre(choose, p1s, p2s);
			if (GetAsyncKeyState(VK_SPACE))										//khi nguoi dung nhan spacebar
			{
				COORD p;

				//xoa intro
				p.X = int(width / 2 - 10);
				p.Y = int(height / 1.5f - 3);
				SetConsoleCursorPosition(h, p);
				cout << "                    ";

				//xoa huong dan choi player 1
				p.X = int(width / 2 - 20);
				p.Y = int(height / 1.5f - 1);
				SetConsoleCursorPosition(h, p);
				cout << "                                             ";

				//xoa huong dan choi player 2
				p.X = int(width / 2 - 20);
				p.Y = int(height / 1.5f + 1);
				SetConsoleCursorPosition(h, p);
				cout << "                                          ";

				//cho game bat dau chay
				run = true;
				//vẽ vật phẩm để chơi
				l.Draw();
			}
		}

		//player chơi với player
		if (run && choose == 1)
		{
			//hàm kiểm tra bóng đụng vật phẩm, thay điểm người chơi
			Lb.UpDrawScore(p1s, p2s, l);

			//hàm vẽ điểm của người chơi
			DrawTypeASocre(choose, p1s, p2s);

			//hàm xóa những bóng giả bị đụng biên trên và dưới
			Lb.DrawDeleteFakeBall();

			//hàm xu li khi bong dung thanh, va tao bong gia
			Lb.ImpactPACreateFB(p1, p2, p1s, p2s);


			if (GetAsyncKeyState(0x53) & 0x8000) {
				savegame(p1, p2, Lb, run, p1s, p2s, l, choose);
			}
			//player 1 di chuyen
			if (GetAsyncKeyState(VK_LEFT))										// nhan mui ten trai
				p1.runleft();													//pad player 1 di chuyen sang trai
			else if (GetAsyncKeyState(VK_RIGHT))								// nhan mui ten sang phai
				p1.runright();													//pad player 1 di chuyen sang phai

			//player 2 di chuyen
			if (GetAsyncKeyState(VK_NUMPAD4))									// nhan nut so 4
				p2.runleft();													//pad player 2 di chuyen sang trai
			else if (GetAsyncKeyState(VK_NUMPAD6))								// nhan nut so 6
				p2.runright();													//pad player 2 di chuyen sang phai

			//kiem tra pad toi duong bien
			p1.limit();
			p2.limit();

			//hàm di chuyển bóng
			Lb.MoveListBall();

			// thiếu hàm tăng tốc độ ở đây
		}

		//chơi với computer
		if (run && choose == 2)
		{
			//hàm kiểm tra bóng đụng vật phẩm, thay điểm người chơi
			Lb.UpDrawScore(p1s, p2s, l);

			//hàm vẽ điểm của người chơi
			DrawTypeASocre(choose, p1s, p2s);

			//hàm xóa những bóng giả bị đụng biên trên và dưới
			Lb.DrawDeleteFakeBall();

			//hàm xu li khi bong dung thanh, va tao bong gia
			Lb.ImpactPACreateFB(p1, p2, p1s, p2s);

			if (GetAsyncKeyState(0x53) & 0x8000) {
				savegame(p1, p2, Lb, run, p1s, p2s, l, choose);
			}
			if (GetAsyncKeyState(VK_LEFT))										// nhan mui ten trai
				p1.runleft();													//pad player di chuyen sang trai
			else if (GetAsyncKeyState(VK_RIGHT))								// nhan mui ten sang phai
				p1.runright();													//pad player di chuyen sang phai

			 //computer di chuyen
			Lb.Get_Ball(0).padcompmove(p2);//xem lại hàm này

			//kiem tra pad toi duong bien
			p1.limit();
			p2.limit();

			//hàm di chuyển bóng
			Lb.MoveListBall();
		}
		//nếu điểm hai người chơi chênh lệch bội số 10 thì cho vật phẩm di chuyển, và một trong hai điểm số phải khác 0
		if (((p1s - p2s) % 10) == 0 && (p1s !=p2s)) {
			l.MoveListItem();//di chuyển danh sách vật phẩm

		}

		//ve player1 player2 ball
		Lb.Draw();
		p1.drawpar();
		p2.drawpar();

		if ((l.IsState() && p1s > p2s) || Lb.Get_Ball(0).ballscore() == 2)
		{

			if (choose == 1)
			{
				COORD p;

				p.X = int(width / 2 - 10);
				p.Y = int(height / 1.5f - 3);
				SetConsoleCursorPosition(h, p);
				cout << "    PLAYER 1 WIN    ";

				p.X = int(width / 2 - 13);
				p.Y = int(height / 1.5f - 1);
				SetConsoleCursorPosition(h, p);

				system("pause");
			}
			else if (choose == 2)
			{
				COORD p;

				p.X = int(width / 2 - 10);
				p.Y = int(height / 1.5f - 3);
				SetConsoleCursorPosition(h, p);
				cout << "       YOU WIN      ";

				p.X = int(width / 2 - 13);
				p.Y = int(height / 1.5f - 1);
				SetConsoleCursorPosition(h, p);

				system("pause");
			}
			EndGame(Lb, l, choose, run);//hàm xử lí kết thúc game
			WriteScore(FILENAMESCORE, p1s, p2s);//ghi điểm vào danh sách điểm
		}
		else if ((l.IsState() && p1s < p2s) || Lb.Get_Ball(0).ballscore() == 1)
		{


			if (choose == 1)
			{
				COORD p;

				p.X = int(width / 2 - 10);
				p.Y = int(height / 1.5f - 3);
				SetConsoleCursorPosition(h, p);
				cout << "    PLAYER 2 WIN    ";

				p.X = int(width / 2 - 13);
				p.Y = int(height / 1.5f - 1);
				SetConsoleCursorPosition(h, p);

				system("pause");
			}
			else if (choose == 2)
			{
				COORD p;

				p.X = int(width / 2 - 10);
				p.Y = int(height / 1.5f - 3);
				SetConsoleCursorPosition(h, p);
				cout << "    COMPUTER WIN    ";

				p.X = int(width / 2 - 13);
				p.Y = int(height / 1.5f - 1);
				SetConsoleCursorPosition(h, p);

				system("pause");
			}
			EndGame(Lb, l, choose, run);//hàm xử lí kết thúc game
			WriteScore(FILENAMESCORE, p1s, p2s);//ghi điểm vào danh sách điểm
		}
		else if (l.IsState()) {//khi hết vật phẩm thì game kết thúc, mà điểm số hai người chơi bằng nhau màn hình sẽ hiện qual score
			EndGame(Lb, l, choose, run);//hàm xử lí kết thúc game
			WriteScore(FILENAMESCORE, p1s, p2s);//ghi điểm vào danh sách điểm
			COORD p;

			p.X = int(width / 2 - 10);
			p.Y = int(height / 1.5f - 3);
			SetConsoleCursorPosition(h, p);
			cout << "   equal score    ";

			p.X = int(width / 2 - 13);
			p.Y = int(height / 1.5f - 1);
			SetConsoleCursorPosition(h, p);
			system("pause");

		}


		//delay
		Sleep(100);
	}

	Sleep(3000);
	system("pause");
	return 0;


}