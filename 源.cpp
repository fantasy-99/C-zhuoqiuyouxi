//头文件区
#include<graphics.h>		//图形库
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//全局量区
#define PI 3.1415926		//pi
IMAGE backimg1;			//背景图							多字节字符集莫忘
IMAGE backimg2;
IMAGE balltable;			//球桌
IMAGE choiceimg1;			//选项素材 开始游戏
IMAGE choiceimg2;			//游戏规则
IMAGE choiceimg3;			//重新开始
IMAGE choiceimg4;			//返回主页
IMAGE fen1;				//分数
IMAGE fen2;
IMAGE power1;			//力度
IMAGE power2;
IMAGE power3;
IMAGE ballhole1;			//球洞
IMAGE ballhole2;
IMAGE ballhole3;
IMAGE ballhole4;
IMAGE ballhole5;
IMAGE ballhole6;
IMAGE ballhole7;
IMAGE ballhole8;
IMAGE ballhole9;
IMAGE ball1;			//球
IMAGE ball2;
IMAGE ball3;
IMAGE ball4;
IMAGE ball5;
IMAGE ball6;
IMAGE ball7;
IMAGE ball8;
IMAGE ball9;
char score1[10];		//玩家分		//以下量均为游戏界面的变量
char score2[10];		//电脑分
int s1, s2;			//分数
int i;
int dx, dy;			//坐标差
double degree;			//角度
double cot;			//1.0
int spotx, spoty;		//虚线点的坐标。
int power;			//力的大小
int countball;			//球的次序
time_t tstart;		//获得初始时间
time_t tend;
struct MyStruct				//球和球洞位置坐标 结构体
{
	int x;
	int y;
	bool exist;
};
MyStruct ball[11];		//球的初始位置
MyStruct hole[11];			//球洞位置

//函数声名区
void game_console();		//游戏欢迎界面		
void game_rules();			//规则界面
void game_play();			//游戏界面paly
void game_play_Initia();	//初始化变量
void loadpictures();		//加载素材
void moveball();		//球的移动
void judge();		//判断输赢

//主函数
int main()
{
	SetConsoleTitle("台球小游戏");	//窗口标题
	initgraph(900, 600);		//窗口大小
	setbkmode(TRANSPARENT);			//透明
	loadpictures();			//素材函数
	game_console();			//进入欢迎界面函数
	return 0;
}

void loadpictures()			//加载素材
{
	loadimage(&backimg1, "./images/001.jpg", 900, 600);			//加载素材图片 
	loadimage(&backimg2, "./images/004.jpg", 900, 600);
	loadimage(&balltable, "./images/005.jpg", 750, 400);
	loadimage(&choiceimg1, "./images/002.jpg", 230, 70);
	loadimage(&choiceimg2, "./images/003.jpg", 230, 70);
	loadimage(&choiceimg3, "./images/006.jpg", 230, 70);
	loadimage(&choiceimg4, "./images/007.jpg", 230, 70);
	loadimage(&fen1, "./images/分1.jpg", 60, 175);
	loadimage(&fen2, "./images/分2.jpg", 60, 175);
	loadimage(&power1, "./images/力1.jpg", 175, 50);
	loadimage(&power2, "./images/力2.jpg", 175, 50);
	loadimage(&power3, "./images/力3.jpg", 175, 50);
	loadimage(&ballhole9, "./images/球9.gif", 25, 25);			//可做成掩码图
	loadimage(&ballhole1, "./images/球1.gif", 25, 25);
	loadimage(&ballhole2, "./images/球2.gif", 25, 25);
	loadimage(&ballhole3, "./images/球3.gif", 25, 25);
	loadimage(&ballhole4, "./images/球4.gif", 25, 25);
	loadimage(&ballhole5, "./images/球5.gif", 25, 25);
	loadimage(&ballhole6, "./images/球6.gif", 25, 25);
	loadimage(&ballhole7, "./images/球7.gif", 25, 25);
	loadimage(&ballhole8, "./images/球8.gif", 25, 25);
	loadimage(&ball9, "./images/球9.gif", 20, 20);
	loadimage(&ball1, "./images/球1.gif", 20, 20);
	loadimage(&ball2, "./images/球2.gif", 20, 20);
	loadimage(&ball3, "./images/球3.gif", 20, 20);
	loadimage(&ball4, "./images/球4.gif", 20, 20);
	loadimage(&ball5, "./images/球5.gif", 20, 20);
	loadimage(&ball6, "./images/球6.gif", 20, 20);
	loadimage(&ball7, "./images/球7.gif", 20, 20);
	loadimage(&ball8, "./images/球8.gif", 20, 20);
}

void game_console()			//游戏窗口
{
	putimage(0, 0, &backimg1);			//放置图片素材
	putimage(320, 150, &choiceimg1);
	putimage(320, 350, &choiceimg2);
	setcolor(BLACK);			//字体颜色
	settextstyle(70, 0, "华文行楷");
	outtextxy(230, 250, "台 球 小 游 戏");
	settextstyle(30, 0, "微软雅黑");		//字体样式
	MOUSEMSG m;		//保存鼠标消息
	while (1) {		
		FlushMouseMsgBuffer();
		m = GetMouseMsg();		//获取鼠标消息
		if (m.uMsg == WM_LBUTTONDOWN)			//按下鼠标左键
		{
			if (m.x >= 320 && m.x <= 550 && m.y >= 150 && m.y <= 220)		//开始游戏的位置
			{
				game_play();
				break;				//防止冲突
			}
			if (m.x >= 320 && m.x <= 550 && m.y >= 350 && m.y <= 420)		//规则选项的位置
			{
				game_rules();
				break;
			}
		}
	}
}

void game_play()			//游戏开始
{
	game_play_Initia();		//初始化变量
	cleardevice();			// 清屏
	putimage(0, 0, &balltable);			//素材图		初始化素材
	putimage(50, 500, &choiceimg3);			
	putimage(400, 500, &choiceimg4);
	putimage(800, 15, &fen1);
	putimage(800, 235, &fen2);
	putimage(200, 182, &ball1);
	putimage(580, 58, &ballhole1);
	putimage(580, 88, &ballhole2);
	putimage(580, 118, &ballhole3);
	putimage(580, 148, &ballhole4);
	putimage(580, 178, &ballhole5);
	putimage(580, 208, &ballhole6);
	putimage(580, 238, &ballhole7);
	putimage(580, 268, &ballhole8);
	putimage(580, 298, &ballhole9);
	putimage(25, 425, &power1);
	putimage(300, 425, &power2);
	putimage(575, 425, &power3);
	outtextxy(810, 115, "000");			//显示得分
	outtextxy(810, 335, "000");
	Sleep(300);
	while (1) {			//不断更新
		cleardevice();			//清屏
		putimage(0, 0, &balltable);			//素材图
		putimage(50, 500, &choiceimg3);
		putimage(400, 500, &choiceimg4);
		putimage(800, 15, &fen1);
		putimage(800, 235, &fen2);
		putimage(25, 425, &power1);
		putimage(300, 425, &power2);
		putimage(575, 425, &power3);
		putimage(hole[1].x, hole[1].y, &ballhole1);
		putimage(hole[2].x, hole[2].y, &ballhole2);
		putimage(hole[3].x, hole[3].y, &ballhole3);
		putimage(hole[4].x, hole[4].y, &ballhole4);
		putimage(hole[5].x, hole[5].y, &ballhole5);
		putimage(hole[6].x, hole[6].y, &ballhole6);
		putimage(hole[7].x, hole[7].y, &ballhole7);
		putimage(hole[8].x, hole[8].y, &ballhole8);
		putimage(hole[9].x, hole[9].y, &ballhole9);
		sprintf_s(score1, "%03d", s1);			//得分转为字符串
		sprintf_s(score2, "%03d", s2);
		outtextxy(810, 115, score1);			//显示得分
		outtextxy(810, 335, score2);
		if (ball[countball].exist==0) {			//桌面上已经没有球了，更新下一颗球
			countball++;
			switch (countball) {
			case 1:putimage(200, 182, &ball1); break;
			case 2:putimage(200, 182, &ball2); break;
			case 3:putimage(200, 182, &ball3); break;
			case 4:putimage(200, 182, &ball4); break;
			case 5:putimage(200, 182, &ball5); break;
			case 6:putimage(200, 182, &ball6); break;
			case 7:putimage(200, 182, &ball7); break;
			case 8:putimage(200, 182, &ball8); break;
			case 9:putimage(200, 182, &ball9); break;
			default:break;
			}
		}
		else {					//桌子上仍有球，保持现有位置
			switch (countball) {
			case 1:putimage(ball[countball].x, ball[countball].y, &ball1); break;
			case 2:putimage(ball[countball].x, ball[countball].y, &ball2); break;
			case 3:putimage(ball[countball].x, ball[countball].y, &ball3); break;
			case 4:putimage(ball[countball].x, ball[countball].y, &ball4); break;
			case 5:putimage(ball[countball].x, ball[countball].y, &ball5); break;
			case 6:putimage(ball[countball].x, ball[countball].y, &ball6); break;
			case 7:putimage(ball[countball].x, ball[countball].y, &ball7); break;
			case 8:putimage(ball[countball].x, ball[countball].y, &ball8); break;
			case 9:putimage(ball[countball].x, ball[countball].y, &ball9); break;
			default:break;
			}
		}
		tend = time(NULL);
		if (tend - tstart >= 1) {
			tstart = tend;
			for (i = 1; i <= 9; i++) {					//球洞位置变化
				if (hole[i].y == 58) hole[i].y = 298;
				else hole[i].y -= 30;
			}
		}
		POINT m;			//鼠标名
		GetCursorPos(&m);
		HWND hwnd = GetHWnd();			//句柄
		ScreenToClient(hwnd, &m);		//转为屏幕坐标
		if (m.x >= 44 && m.x <= 710 && m.y >= 39 && m.y <= 358)			//画虚线
		{
			dx = m.x - ball[countball].x;		//求弧度
			dy = m.y - ball[countball].y;
			degree = atan((cot * m.y - cot * ball[countball].y) / (cot * m.x - cot * ball[countball].x));
			if (dx == 0 && dy > 0)	degree = PI / 2;
			if (dx == 0 && dy < 0) degree = -(PI / 2);
			if (dy == 0 && dx > 0) degree = 0;
			if (dy == 0 && dx < 0) degree = PI;
			if (dx < 0) degree = PI + degree;
			spotx = ball[countball].x+8;
			spoty = ball[countball].y-6;
			for (i = 1; i <= 10; i++)
			{
				outtextxy(spotx, spoty, "·"); 
				spotx += 10 * cos(degree);
				spoty += 10 * sin(degree);
			}
		}
		if (GetKeyState(VK_LBUTTON) < 0)		//左键按下
		{
			if (m.x >= 25 && m.x <= 200 && m.y >= 425 && m.y <= 475) power = 1;		//力度大小
			if (m.x >= 300 && m.x <= 475 && m.y >= 425 && m.y <= 475) power = 2;
			if (m.x >= 575 && m.x <= 750 && m.y >= 425 && m.y <= 475) power = 3;
			if (m.x >= 44 && m.x <= 710 && m.y >= 39 && m.y <= 358)
			{
				moveball();		//球移动
				if (ball[countball].exist == 1) s2 += 10;	//电脑得分
				if (ball[9].exist == 0)	judge();	//球没了 判断输赢
			}
			if (m.x >= 50 && m.x <= 280 && m.y >= 500 && m.y <= 570)		//重新游戏的位置
			{
				game_play();
				break;				//防止冲突
			}
			if (m.x >= 400 && m.x <= 630 && m.y >= 500 && m.y <= 570)		//返回主页的位置
			{
				game_console();
				break;
			}
		}
		Sleep(100);
	}
}

void game_rules()			//得分规则
{
	cleardevice();			//清屏
	putimage(0, 0, &backimg2);
	putimage(100, 450, &choiceimg1);
	putimage(500, 450, &choiceimg4);
	outtextxy(50, 50, "1.九个彩色球洞，九颗对应颜色且稍小的彩球。");
	outtextxy(50, 85, "2.每局游戏开始时，左侧固定位置生成一颗彩球，球洞以一定频率移动位置，");
	outtextxy(50, 120, "	玩家需要将球击入相应颜色的球洞。");
	outtextxy(50, 155, "3.每击入一颗球，左侧固定位置生成一颗彩球，九颗球全入洞后，游戏结束。");
	outtextxy(50, 190, "4.玩家得分规则：击入一颗球时，得10分。");
	outtextxy(50, 225, "5.电脑得分规则：玩家未击入球时，得10分。");
	outtextxy(50, 260, "6.游戏结束时，得分高者获胜。");
	outtextxy(50, 295, "PS：击球前需要选择力度大小。");
	outtextxy(50, 330, "力的大小有三种，游戏开始时，默认为第一种");
	MOUSEMSG m;		//保存鼠标消息
	while (1) {		
		FlushMouseMsgBuffer();
		m = GetMouseMsg();		//获取鼠标消息
		if (m.uMsg == WM_LBUTTONDOWN)			//按下鼠标左键
		{
			if (m.x >= 100 && m.x <= 330 && m.y >= 450 && m.y <= 520)		//开始游戏的位置
			{
				game_play();
				break;
			}
			if (m.x >= 500 && m.x <= 730 && m.y >= 450 && m.y <= 520)		//返回主页的位置
			{
				game_console();
				break;
			}
		}
	}
}

void game_play_Initia()
{		
	s1 = 0;
	s2 = 0;
	degree = 0;			
	power = 1;		
	countball = 1;	
	cot = 1.0;
	tstart = time(NULL);
	ball[0] = { 0,0,1 };
	ball[1] = { 200,182,1 };
	ball[2] = { 200,182,1 };
	ball[3] = { 200,182,1 };
	ball[4] = { 200,182,1 };
	ball[5] = { 200,182,1 };
	ball[6] = { 200,182,1 };
	ball[7] = { 200,182,1 };
	ball[8] = { 200,182,1 };
	ball[9] = { 200,182,1 };
	hole[0] = { 0,0,1 };
	hole[1] = { 580,58,1 };
	hole[2] = { 580,88,1 };
	hole[3] = { 580,118,1 };
	hole[4] = { 580,148,1 };
	hole[5] = { 580,178,1 };
	hole[6] = { 580,208,1 };
	hole[7] = { 580,238,1 };
	hole[8] = { 580,268,1 };
	hole[9] = { 580,298,1 };
}

void moveball()
{
	time_t mid = time(NULL);		//决定球运动的时间
	time_t te = time(NULL);
	int s;
	while (1) {
		if (te - mid >= 4) return;		//时间到了 返回
		if (ball[countball].x <= 45)	//碰壁 弧度变化，反弹
		{
			ball[countball].x = 46;
			degree = PI - degree;
		}
		if (ball[countball].x >= 687)
		{
			ball[countball].x = 686;
			degree = PI - degree;
		}
		if (ball[countball].y <= 40)
		{
			ball[countball].y = 41;
			degree = -degree;
		}
		if (ball[countball].y >= 337)
		{
			ball[countball].y = 336;
			degree = -degree;
		}
		if (power == 1) {
			ball[countball].x += 9 * cos(degree);
			ball[countball].y += 9 * sin(degree);
		}
		if (power == 2) {
			ball[countball].x += 12 * cos(degree);
			ball[countball].y += 12 * sin(degree);
		}
		if (power == 3) {
			ball[countball].x += 14 * cos(degree);
			ball[countball].y += 14 * sin(degree);
		}
		cleardevice();
		putimage(0, 0, &balltable);
		putimage(50, 500, &choiceimg3);
		putimage(400, 500, &choiceimg4);
		putimage(800, 15, &fen1);
		putimage(800, 235, &fen2);
		putimage(hole[1].x, hole[1].y, &ballhole1);
		putimage(hole[2].x, hole[2].y, &ballhole2);
		putimage(hole[3].x, hole[3].y, &ballhole3);
		putimage(hole[4].x, hole[4].y, &ballhole4);
		putimage(hole[5].x, hole[5].y, &ballhole5);
		putimage(hole[6].x, hole[6].y, &ballhole6);
		putimage(hole[7].x, hole[7].y, &ballhole7);
		putimage(hole[8].x, hole[8].y, &ballhole8);
		putimage(hole[9].x, hole[9].y, &ballhole9);
		outtextxy(810, 115, score1);
		outtextxy(810, 335, score2);
		switch (countball) {
		case 1:putimage(ball[countball].x, ball[countball].y, &ball1); break;
		case 2:putimage(ball[countball].x, ball[countball].y, &ball2); break;
		case 3:putimage(ball[countball].x, ball[countball].y, &ball3); break;
		case 4:putimage(ball[countball].x, ball[countball].y, &ball4); break;
		case 5:putimage(ball[countball].x, ball[countball].y, &ball5); break;
		case 6:putimage(ball[countball].x, ball[countball].y, &ball6); break;
		case 7:putimage(ball[countball].x, ball[countball].y, &ball7); break;
		case 8:putimage(ball[countball].x, ball[countball].y, &ball8); break;
		case 9:putimage(ball[countball].x, ball[countball].y, &ball9); break;
		default:break;
		}
		if (ball[countball].x >= 567 && ball[countball].x <= 597) {	//球进，得分，返回
			s = hole[countball].y - ball[countball].y;
			if (s <= 12 && s >= -12) {
				s1 += 10;
				ball[countball].exist = 0;
				return;
			}
		}
		tend = time(NULL);
		if (tend - tstart >= 1) {
			tstart = tend;
			for (i = 1; i <= 9; i++) {
				if (hole[i].y == 58) hole[i].y = 298;
				else hole[i].y -= 30;
			}
		}
		te = time(NULL);
		if (power == 1)	Sleep(70);
		if (power == 2) Sleep(60);
		if (power == 3) Sleep(40);
	}
}

void judge()
{
	settextstyle(70, 20, "华文行楷");
	setcolor(RED);
	if (s1 > s2) outtextxy(230, 160, "玩 家 获 胜！");
	if (s1 < s2) outtextxy(230, 160, "电 脑 获 胜！");
	if (s1 == s2) outtextxy(230, 160, "恭 喜 平 局！");
	setcolor(BLACK);		//回到之前的颜色
	settextstyle(30, 0, "微软雅黑");	
	MOUSEMSG m;		
	while (1) {
		FlushMouseMsgBuffer();
		m = GetMouseMsg();		
		if (m.uMsg == WM_LBUTTONDOWN)			
		{
			if (m.x >= 50 && m.x <= 280 && m.y >= 500 && m.y <= 570)		
			{
				game_play();
				break;				
			}
			if (m.x >= 400 && m.x <= 630 && m.y >= 500 && m.y <= 570)		
			{
				game_console();
				break;
			}
		}
	}
}