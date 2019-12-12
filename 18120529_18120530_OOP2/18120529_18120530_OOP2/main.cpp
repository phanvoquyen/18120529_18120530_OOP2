#include <windows.h>
#include <iostream>
#include<vector>
#include <ctime>
#include <fstream>
#include "ball.h"
#include "pad.h"
#include"ListItem.h"
#include"item.h"
using namespace std;

//thong so man hinh console
int width = 55;
int height = 35;
ofstream savefile;

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
//thay đổi tí số, khi có bóng đánh chúng vật phẩm
void DrawUpScore(int p1s, int p2s) {
	HANDLE k;
	k = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD p;

	// ve bang diem
	p.X = 0;
	p.Y = height;
	SetConsoleCursorPosition(k, p);
	cout << "\n    Player score: " << "\t\tComputer score: " << '\n';
	p.X = 19;
	p.Y = height + 1;
	SetConsoleCursorPosition(k, p);
	cout << p1s;
	p.X = 49;
	p.Y = height + 1;
	SetConsoleCursorPosition(k, p);
	cout << p2s;
}

// hàm save game
void saveGameLogic(string filename, pad &p1, pad &p2, ball &b, bool &run, int &p1s, int &p2s, ListItem litem)
{
	filename.insert(0, "..\\");
	savefile.open(filename.c_str());

	// lưu thông số của bóng
	savefile << b.getBallX() << endl;
	savefile << b.getBallY() << endl;
	savefile << b.getBallVX() << endl;
	savefile << b.getBallVY() << endl;

	// lưu thống số của chương ngại vật và vật phẩm
	vector<item> list = litem.getLI();
	int n = litem.getLI().size();
	for (int i = 0; i < n; i++)
	{
		savefile << list[i].getShape << endl;
		savefile << list[i].Get_TrangThai() << endl;
		savefile << list[i].getScore() << endl;
		savefile << list[i].getX() << endl;
		savefile << list[i].getY() << endl;
		savefile << list[i].getX0() << endl;
		savefile << list[i].getY0() << endl;
		savefile << list[i].getVX() << endl;
	}

	// 

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
	ball b(width / 2 - 1, height / 2, width, height);
	ListItem l(width, height);

	//khai bao bien diem cua 2 player
	int p1s = 0;
	int p2s = 0;

	//ve player1 player2 ball
	p1.drawpar();
	//p2.drawpar();
	b.drawball();
	//vẽ tỉ số của hai thanh 
	DrawUpScore(p1s, p2s);
	//dat van toc cho ball
	b.startpvp();
	//biên lưu giá trị vật phẩm vừa bắn chúng.
	double value = 1;

	while (1)
	{
		if (!run && choose == 0)
		{
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
			cout << "PLAYER VS PLAYER:	PRESS 1";

			//ve lua chon player vs computer
			p.X = int(width / 2 - 15);
			p.Y = int(height / 1.5f + 1);
			SetConsoleCursorPosition(h, p);
			cout << "PLAYER VS COMPUTER: PRESS 2";

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

				// dat van toc cho ball pvp
				b.startpvp();

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

				// dat van toc cho ball pve
				b.startpve();

				//cho game bat dau chay player vs computer
				choose = 2;
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
			//kiểm tra ball có va chạm với vật phẩm không
			value = b.IsImpactItem(l);
			//nếu giá trị vật phẩm trả về bằng 1 tức là không có vật phẩm được đánh chúng
			if (value != 1) {
				//hàm thay đổi điểm của người chơi
				b.UpScore(value, p1s, p2s);
				//hàm vẽ lại điểm người chơi
				DrawUpScore(p1s, p2s);
				//hàm vẽ lại vật phẩm
			}

			//kiem tra ball dung pad
			b.ballhitpad1(p1);
			b.ballhitpad2(p2);

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

			//ball di chuyen
			b.ballmove();


			//kiem tra ball ra 2 bien
			b.balllimit();


			// thiếu hàm tăng tốc độ ở đây
		}

		//chơi với computer
		if (run && choose == 2)
		{


			//kiểm tra ball có va chạm với vật phẩm không
			value = b.IsImpactItem(l);
			//kiểm tra giá trị của vật phẩm, nếu bằng 1 là không có vật phẩm bị đánh chúng
			if (value != 1) {//nếu khác 1 có vật phẩm bị đánh chúng
				b.UpScore(value, p1s, p2s);// thay đổi điểm của người chơi phụ thược vào giá trị của vật phẩm bị đánh chúng
				DrawUpScore(p1s, p2s);//vẽ lại điểm của người chơi
			}
			//kiem tra ball dung pad
			b.ballhitpad1(p1);
			b.ballhitpad2(p2);
			//player di chuyen
			if (GetAsyncKeyState(VK_LEFT))										// nhan mui ten trai
				p1.runleft();													//pad player di chuyen sang trai
			else if (GetAsyncKeyState(VK_RIGHT))								// nhan mui ten sang phai
				p1.runright();													//pad player di chuyen sang phai
			//computer di chuyen
			b.padcompmove(p2);//xem lại hàm này
			//kiem tra pad toi duong bien
			p1.limit();
			p2.limit();
			//ball di chuyen
			b.ballmove();
			//kiem tra ball ra 2 bien
			b.balllimit();
		}
		//nếu điểm hai người chơi chênh lệch bội số 10 thì cho vật phẩm di chuyển, và một trong hai điểm số phải khác 0
		if (((p1s - p2s) % 10) == 0 && (p1s != 0 || p2s != 0)) {
			l.MoveListItem();//di chuyển danh sách vật phẩm

		}
		//ve player1 player2 ball
		b.drawball();
		p1.drawpar();
		p2.drawpar();


		if ((l.IsState() && p1s > p2s) || b.ballscore() == 2)
		{
			l.deleteDraw();//xóa các vật phẩm để màn hình nhìn đẹp
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

				break;
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

				break;
			}
		}
		else if ((l.IsState() && p1s < p2s) || b.ballscore() == 1)
		{
			l.deleteDraw();//xóa các vật phẩm để màn hình nhìn đẹp
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

				break;
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

				break;
			}
		}
		else if (l.IsState()) {//khi hết vật phẩm thì game kết thúc, mà điểm số hai người chơi bằng nhau màn hình sẽ hiện qual score
			l.deleteDraw();//xóa các vật phẩm để màn hình nhìn đẹp
			COORD p;

			p.X = int(width / 2 - 10);
			p.Y = int(height / 1.5f - 3);
			SetConsoleCursorPosition(h, p);
			cout << "   equal score    ";

			p.X = int(width / 2 - 13);
			p.Y = int(height / 1.5f - 1);
			SetConsoleCursorPosition(h, p);

			break;
		}


		//delay
		Sleep(100);
	}

	Sleep(3000);
	system("pause");
	return 0;


}