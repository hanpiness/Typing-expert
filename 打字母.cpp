#include<stdio.h>
#include<stdlib.h>            // Sleep.h（）延迟函数
#include<graphics.h>          // 引用图形函数库头文件
#include<time.h>              // 随机函数
#include<conio.h>             // getch()响应按键
#include<Windows.h>           // 创建多线程
#include<mmsystem.h>          // 音乐 mciSendString()

#pragma comment(lib,"winmm.lib")  // 编译器指令,指定连接要使用的库
// 在vs2010以上需要用到，才可以进行音乐播放

#define bk_width 800		  // 背景的宽
#define bk_high  600          // 背景的高
#define text1_x  330          // 文本1的横坐标
#define text1_y  200		  // 文本1的纵坐标
#define	text2_x  330          // 文本2的横坐标  
#define text2_y  260          // 文本2的纵坐标
#define text3_x  330          // 文本3的横坐标
#define text3_y  320          // 文本3的纵坐标
#define text4_x  300          // 文本4的横坐标
#define text4_y  500          // 文本3的纵坐标
#define text_width 140        // 文本的宽
#define text_high 50          // 文本的高
#define speed 10              // 字母下降的速度
#define score_up_speed 10     // 分数增加的速度


//字母结构体
struct letter
{
	int x_letter;
	int y_letter;
	char target;
};

// 定义全局变量
struct letter letters[5];     // 每一次出现5个字符
int score = 0;                // 玩家的分数
int HP = 10;                  // 玩家的血量
int Delete = 0;               // 玩家消灭的字母
int level = 1;				  // 游戏的等级
clock_t begin, end;           // 记录游戏时间
char now_score[20];           // 实时分数变化
char now_HP[20];              // 实时血量变化
char now_delete[20];          // 实时消灭的字母
char now_Time[20];            // 实时游戏时间
char now_level[20];           // 实时游戏等级

IMAGE background1, background2, background3, background4, background5; // 背景
IMAGE kuang;                  // 字母所在的框
IMAGE background_help;        // 帮助背景
IMAGE background_gameove;     // 游戏结束背景
IMAGE qingt, huangj, zhuans, wangz, baiy;  // 段位图片

// 加载图片
void loadpicture()
{
	loadimage(&background1, _T("D:\\打字练习系统\\打字母\\背景1.png"), 800, 600);
	loadimage(&background2, _T("D:\\打字练习系统\\打字母\\背景2.png"), 800, 600);
	loadimage(&background3, _T("D:\\打字练习系统\\打字母\\背景3.png"), 800, 600);
	loadimage(&background4, _T("D:\\打字练习系统\\打字母\\背景4.png"), 800, 600);
	loadimage(&background5, _T("D:\\打字练习系统\\打字母\\背景5.png"), 800, 600);
	loadimage(&kuang, _T("D:\\打字练习系统\\打字母\\框.png"), 50, 50);
	loadimage(&background_help, _T("D:\\打字练习系统\\打字母\\帮助.jpg"), 800, 600);
	loadimage(&background_gameove, _T("D:\\打字练习系统\\打字母\\游戏结束.png"), 800, 600);
	loadimage(&huangj, _T("D:\\打字练习系统\\打字母\\黄金.png"));
	loadimage(&zhuans, _T("D:\\打字练习系统\\打字母\\钻石.png"));
	loadimage(&qingt, _T("D:\\打字练习系统\\打字母\\青铜.png"));
	loadimage(&wangz, _T("D:\\打字练习系统\\打字母\\王者.png"));
	loadimage(&baiy, _T("D:\\打字练习系统\\打字母\\白银.png"));
	loadimage(&background1, _T("D:\\打字练习系统\\打字母\\背景1.png"));
}

DWORD WINAPI playMusic(LPVOID lpParame)  // LPVOID是一个void*的类型用于作为参数传回线程，线程声明方式
{
	mciSendString(_T("open D:\\打字练习系统\\打字母\\爆炸声.mp3 alias music2"), 0, 0, 0); // 打开多媒体文件
	mciSendString(_T("play music2 wait"), 0, 0, 0); // 播放完函数才返回
	mciSendString(_T("close music2"), 0, 0, 0);     // 关闭音乐
	return 0;
}
// DWORD由 4 字节长（32 位整数）的数字表示的数据

// 输出字母
void put_mao(int x, int y, char target)
{        
	putimage(x, y, &kuang);
	settextcolor(WHITE);
	settextstyle(30, 0,_T("ebrimabd"));
	outtextxy(x + 17, y + 8, target);
}



// 画菜单
void draw_mune()
{
	// 图形布局
	setbkcolor(WHITE);                        // 把背景设置为白色
	cleardevice();					          // 刷新显示，如果没有则背景不会改变
	setfillcolor(LIGHTBLUE);                  // 设置填充颜色为淡蓝色
	fillrectangle(text1_x, text1_y, text1_x + text_width, text1_y + text_high);   // 画第一个矩形
	fillrectangle(text2_x, text2_y, text2_x + text_width, text2_y + text_high);   // 画第二个矩形
	fillrectangle(text3_x, text3_y, text3_x + text_width, text3_y + text_high);   // 画第三个矩形
	
	// 文字布局              
	setbkmode(TRANSPARENT);                // 设置文字背景,TRANSPARENT是使用透明的输出
	settextcolor(BLACK);
	settextstyle(50, 0, _T("FZSTK"));      // windos可以查看电脑拥有的字体
	outtextxy(300,100,_T("打字专家"));     // 为图形输出设置当前的文本属性
	settextstyle(25, 0, _T("STXINGKA"));
	settextcolor(WHITE);
	outtextxy(text1_x + 20, text1_y + 13, _T("开始游戏"));  // _T让程序支持Unicode编码
	outtextxy(text2_x + 20, text2_y + 13, _T("  帮助"));    // 包含在graphics.h中
	outtextxy(text3_x + 20, text3_y + 13, _T("退出游戏"));

	// 版权信息                             
	settextcolor(BLACK);                      // 设置文本颜色
	outtextxy(330, 550, _T("马原晟制作"));    // _T让程序支持Unicode编码
}

// 菜单操作
void mouse_move()
{
	void playgame();
	void draw_help();
	initgraph(bk_width, bk_high);
	draw_mune();
	MOUSEMSG m;               // 存储鼠标消息的变量
	while (1)
	{
		m = GetMouseMsg();     // 获取鼠标消息

		if (m.x >= text1_x && m.x <= text1_x + text_width && m.y >= text1_y && m.y <= text1_y + text_high)
		{
			// 开始游戏菜单中
			setlinecolor(RED);  // 设置当前画线宽度和类型
			rectangle(text1_x - 5, text1_y - 5, text1_x + text_width + 5, text1_y + text_high + 5);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				// 进入游戏
				HP = 10;              // 重新设定游戏数据
				score = 0;
				Delete = 0;
				level = 1;
				begin = clock();
				break;
			}
		}
		else if (m.x >= text2_x && m.x <= text2_x + text_width && m.y >= text2_y && m.y <= text2_y + text_high)
		{
			// 在帮助菜单中
			setlinecolor(RED);
			rectangle(text2_x - 5, text2_y - 5, text2_x + text_width + 5, text2_y + text_high + 5);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				closegraph();
				draw_help();
			}
		}
		else if (m.x >= text3_x && m.x <= text3_x + text_width && m.y >= text3_y && m.y <= text3_y + text_high)
		{
			// 在退出菜单中
			setlinecolor(RED);
			rectangle(text3_x - 5, text3_y - 5, text3_x + text_width + 5, text3_y + text_high + 5);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				// 退出游戏
				exit(0);    // exit((0) 正常退出游戏
			}
		}
		else
		{
			//不在菜单中
			setlinecolor(WHITE);
			rectangle(text2_x - 5, text1_y - 5, text1_x + text_width + 5, text1_y + text_high + 5);
			rectangle(text1_x - 5, text2_y - 5, text2_x + text_width + 5, text2_y + text_high + 5);
			rectangle(text3_x - 5, text3_y - 5, text3_x + text_width + 5, text3_y + text_high + 5);
		}
		FlushBatchDraw();
	}
	playgame();
	closegraph();
}

//画帮助界面
void draw_help()
{
	void playgame();
	initgraph(bk_width, bk_high);
	MOUSEMSG n;
	settextstyle(25, 0, _T("STXINGKA"));
	setbkmode(TRANSPARENT);                // 设置文字背景,TRANSPARENT是使用透明的输出
	// 图形布局
	outtextxy(text4_x + 10, text4_y + 13, _T("返回主菜单"));
	loadpicture();
	putimage(0, 0, &background_help);
	while (1)
	{
		n = GetMouseMsg();
		// 文字布局
		settextcolor(BLACK);
		outtextxy(100, 50, _T("想要成为一个打字专家，你就必须学会快速准确的打字"));
		outtextxy(100, 100, _T("只有经过不断的练习才能够实现，一起来挑战吧。"));
		outtextxy(100, 150, _T("1、敲出正确的字母并消灭所有的字母"));
		outtextxy(100, 200, _T("2、在开始游戏之前请切换为大写模式"));
		outtextxy(100, 250, _T("3、在游戏开始后你可以按下Esc键退出游戏"));
		outtextxy(100, 300, _T("现在返回菜单点击开始游戏开始挑战吧"));
		outtextxy(text4_x + 10, text4_y + 13, _T("返回主菜单"));
		// 键盘响应
		if (n.x >= text4_x && n.x <= text4_x + text_width && n.y >= text4_y && n.y <= text4_y + text_high) {
			if (n.uMsg == WM_LBUTTONDOWN)
			{
				break;
			}
		}
		FlushBatchDraw();
	}
	closegraph();
	mouse_move();
	playgame();
}

// 获取随机字母
void initchar(struct letter array[], int i)
{
	// 大写字母
	srand((unsigned int)time(NULL));    // 利用系统时间返回一个随机数
	array[i].target = rand() % 26 + 'A';
	while (array[i].target == array[(i + 1) % 5].target || array[i].target == array[(i + 2) % 5].target || array[i].target == array[(i + 3) % 5].target || array[i].target == array[(i + 4) % 5].target)
	{
		array[i].target = rand() % 26 + 'A';
	}

	array[i].x_letter = rand() % 14 * 50 + 100;  // 使字母出现一定范围且出现的位置不同
	array[i].y_letter = rand() % 51 - 100;
}

void playgame()
{
	void draw_gameover();
	loadpicture();                // 加载图片
	for (int i = 0; i < 5; i++)
	{
		initchar(letters, i);     // 获得随机字母
	}
	initgraph(bk_width, bk_high); // 加载显示窗口
	while (1)
	{
		BeginBatchDraw();         // 先绘图最后显示，可以避免闪烁
		putimage(0, 0, &background1); 
		if (level == 2)
		{
			BeginBatchDraw();
			putimage(0, 0, &background2);
		}
			if (level == 3)
			{
				BeginBatchDraw();
				putimage(0, 0, &background3);
			}
			if (level == 4)
			{
				BeginBatchDraw();
				putimage(0, 0, &background4);
			}
			if (level >= 5)
			{
				BeginBatchDraw();
				putimage(0, 0, &background5);
			}
		//字母的移动
		for (int i = 0; i < 5; i++)
		{
			letters[i].y_letter += speed  *0.8 * level;   // 字母下降的速度
			if (letters[i].y_letter >= bk_high)     // 如果字母触碰到底线
			{ 
				initchar(letters, i);               // 则加载一个新的字母
				HP = HP - 1;
				if (HP == 0)
				{
					end = clock();
					draw_gameover();
					goto out;
				}
			}
		}
		// 字母的显示
		for (int i = 0; i < 5; i++)
		{
			put_mao(letters[i].x_letter, letters[i].y_letter, letters[i].target);
		}

		// 按键一定要先判断是否存在按键
		if (_kbhit())
		{
			char userKey = _getch();  // 获取按键的信息
			for (int i = 0; i < 5; i++)
			{
				if (letters[i].target == userKey || letters[i].target == userKey - ('a' - 'A'))
				{
					score += score_up_speed * level;
					Delete += 1;
					level = score / 500 + 1;
					initchar(letters, i); // 产生一个新的字母
					CreateThread(NULL, 0, playMusic, NULL, NULL, NULL); // 在新的线程中显示爆炸声

					break;
				}
				if (userKey == 27)    // 退出游戏界面
				{
					end = clock();
					draw_gameover();
					goto out;
				}
			}
		}
		settextstyle(20, 0, _T("STXINGKA"));
		_stprintf_s(now_score, _T("分数：%d"), score);
		_stprintf_s(now_HP, _T("HP：%d"), HP);
		_stprintf_s(now_level, _T("关卡： %d"), level);
		setbkmode(TRANSPARENT);
		outtextxy(700, 20, now_score);
		outtextxy(50, 20, now_HP);
		outtextxy(350, 20, now_level);
		Sleep(100);
		FlushBatchDraw();
	}
	out:
	_getch();          //可以使窗口驻留，起到一个按任意键再退出的效果
	closegraph();
}

void draw_gameover()
{
	MOUSEMSG n;
	loadpicture();                // 加载图片
	initgraph(bk_width, bk_high);
	putimage(0, 0, &background_gameove);
	while (1)
	{
		n = GetMouseMsg();
		//文字布局
		settextcolor(WHITE);
		settextstyle(25, 0, _T("STXINGKA"));
		_stprintf_s(now_delete, _T("共消灭的字母：%d个"), Delete);
		_stprintf_s(now_Time, _T("游戏时间：%.2fs"), ((double)end - begin) / CLK_TCK);
		_stprintf_s(now_score, _T("分数：%d"), score);
		if (level == 1)
		{
			putimage(50, 100, &qingt);
			outtextxy(200, 100, _T("恭喜您，获得 倔强青铜 称号"));
		}
		if (level == 2)
		{
			putimage(50, 100, &baiy);
			outtextxy(200, 100, _T("恭喜您，获得 秩序白银 称号"));
		}
		if (level == 3)
		{
			putimage(50, 100, &huangj);
			outtextxy(200, 100, _T("恭喜您，获得 荣耀黄金 称号"));
		}
		if (level == 4)
		{
			putimage(50, 100, &zhuans);
			outtextxy(200, 100, _T("恭喜您，获得 永恒钻石 称号"));
		}
		if (level >= 5)
		{
			putimage(50, 100, &wangz);
			outtextxy(200, 100, _T("恭喜您，获得 最强王者 称号"));
		}
		outtextxy(350, 50, now_Time);
		outtextxy(50,50,now_delete);
		outtextxy(650, 50, now_score);
		outtextxy(300, 400, _T("返回主菜单"));
		outtextxy(300, 450, _T(" 退出游戏"));
		// 鼠标响应
		if (n.x >= 300 && n.x <= 300 + text_width && n.y >= 400 && n.y <= 400 + text_high)
		{
			if (n.uMsg == WM_LBUTTONDOWN)
			{
				mouse_move();
				break;
			}
		}
		if (n.x >= 300 && n.x <= 300 + text_width && n.y >= 450 && n.y <= 450 + text_high)
		{
			if (n.uMsg == WM_LBUTTONDOWN)
			{
				exit(0);
			}
		}
		FlushBatchDraw();
	}
	closegraph();
}

int main()
{
	mciSendString(_T("open D:\\打字练习系统\\打字母\\小提琴.mp3 alias music"), 0, 0, 0);
	mciSendString(_T("play music repeat"),0,0,0);       // 音乐循环播放
	mouse_move();
	return 0;
}
