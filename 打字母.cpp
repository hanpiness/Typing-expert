#include<stdio.h>
#include<stdlib.h>            // Sleep.h�����ӳٺ���
#include<graphics.h>          // ����ͼ�κ�����ͷ�ļ�
#include<time.h>              // �������
#include<conio.h>             // getch()��Ӧ����
#include<Windows.h>           // �������߳�
#include<mmsystem.h>          // ���� mciSendString()

#pragma comment(lib,"winmm.lib")  // ������ָ��,ָ������Ҫʹ�õĿ�
// ��vs2010������Ҫ�õ����ſ��Խ������ֲ���

#define bk_width 800		  // �����Ŀ�
#define bk_high  600          // �����ĸ�
#define text1_x  330          // �ı�1�ĺ�����
#define text1_y  200		  // �ı�1��������
#define	text2_x  330          // �ı�2�ĺ�����  
#define text2_y  260          // �ı�2��������
#define text3_x  330          // �ı�3�ĺ�����
#define text3_y  320          // �ı�3��������
#define text4_x  300          // �ı�4�ĺ�����
#define text4_y  500          // �ı�3��������
#define text_width 140        // �ı��Ŀ�
#define text_high 50          // �ı��ĸ�
#define speed 10              // ��ĸ�½����ٶ�
#define score_up_speed 10     // �������ӵ��ٶ�


//��ĸ�ṹ��
struct letter
{
	int x_letter;
	int y_letter;
	char target;
};

// ����ȫ�ֱ���
struct letter letters[5];     // ÿһ�γ���5���ַ�
int score = 0;                // ��ҵķ���
int HP = 10;                  // ��ҵ�Ѫ��
int Delete = 0;               // ����������ĸ
int level = 1;				  // ��Ϸ�ĵȼ�
clock_t begin, end;           // ��¼��Ϸʱ��
char now_score[20];           // ʵʱ�����仯
char now_HP[20];              // ʵʱѪ���仯
char now_delete[20];          // ʵʱ�������ĸ
char now_Time[20];            // ʵʱ��Ϸʱ��
char now_level[20];           // ʵʱ��Ϸ�ȼ�

IMAGE background1, background2, background3, background4, background5; // ����
IMAGE kuang;                  // ��ĸ���ڵĿ�
IMAGE background_help;        // ��������
IMAGE background_gameove;     // ��Ϸ��������
IMAGE qingt, huangj, zhuans, wangz, baiy;  // ��λͼƬ

// ����ͼƬ
void loadpicture()
{
	loadimage(&background1, _T("D:\\������ϰϵͳ\\����ĸ\\����1.png"), 800, 600);
	loadimage(&background2, _T("D:\\������ϰϵͳ\\����ĸ\\����2.png"), 800, 600);
	loadimage(&background3, _T("D:\\������ϰϵͳ\\����ĸ\\����3.png"), 800, 600);
	loadimage(&background4, _T("D:\\������ϰϵͳ\\����ĸ\\����4.png"), 800, 600);
	loadimage(&background5, _T("D:\\������ϰϵͳ\\����ĸ\\����5.png"), 800, 600);
	loadimage(&kuang, _T("D:\\������ϰϵͳ\\����ĸ\\��.png"), 50, 50);
	loadimage(&background_help, _T("D:\\������ϰϵͳ\\����ĸ\\����.jpg"), 800, 600);
	loadimage(&background_gameove, _T("D:\\������ϰϵͳ\\����ĸ\\��Ϸ����.png"), 800, 600);
	loadimage(&huangj, _T("D:\\������ϰϵͳ\\����ĸ\\�ƽ�.png"));
	loadimage(&zhuans, _T("D:\\������ϰϵͳ\\����ĸ\\��ʯ.png"));
	loadimage(&qingt, _T("D:\\������ϰϵͳ\\����ĸ\\��ͭ.png"));
	loadimage(&wangz, _T("D:\\������ϰϵͳ\\����ĸ\\����.png"));
	loadimage(&baiy, _T("D:\\������ϰϵͳ\\����ĸ\\����.png"));
	loadimage(&background1, _T("D:\\������ϰϵͳ\\����ĸ\\����1.png"));
}

DWORD WINAPI playMusic(LPVOID lpParame)  // LPVOID��һ��void*������������Ϊ���������̣߳��߳�������ʽ
{
	mciSendString(_T("open D:\\������ϰϵͳ\\����ĸ\\��ը��.mp3 alias music2"), 0, 0, 0); // �򿪶�ý���ļ�
	mciSendString(_T("play music2 wait"), 0, 0, 0); // �����꺯���ŷ���
	mciSendString(_T("close music2"), 0, 0, 0);     // �ر�����
	return 0;
}
// DWORD�� 4 �ֽڳ���32 λ�����������ֱ�ʾ������

// �����ĸ
void put_mao(int x, int y, char target)
{        
	putimage(x, y, &kuang);
	settextcolor(WHITE);
	settextstyle(30, 0,_T("ebrimabd"));
	outtextxy(x + 17, y + 8, target);
}



// ���˵�
void draw_mune()
{
	// ͼ�β���
	setbkcolor(WHITE);                        // �ѱ�������Ϊ��ɫ
	cleardevice();					          // ˢ����ʾ�����û���򱳾�����ı�
	setfillcolor(LIGHTBLUE);                  // ���������ɫΪ����ɫ
	fillrectangle(text1_x, text1_y, text1_x + text_width, text1_y + text_high);   // ����һ������
	fillrectangle(text2_x, text2_y, text2_x + text_width, text2_y + text_high);   // ���ڶ�������
	fillrectangle(text3_x, text3_y, text3_x + text_width, text3_y + text_high);   // ������������
	
	// ���ֲ���              
	setbkmode(TRANSPARENT);                // �������ֱ���,TRANSPARENT��ʹ��͸�������
	settextcolor(BLACK);
	settextstyle(50, 0, _T("FZSTK"));      // windos���Բ鿴����ӵ�е�����
	outtextxy(300,100,_T("����ר��"));     // Ϊͼ��������õ�ǰ���ı�����
	settextstyle(25, 0, _T("STXINGKA"));
	settextcolor(WHITE);
	outtextxy(text1_x + 20, text1_y + 13, _T("��ʼ��Ϸ"));  // _T�ó���֧��Unicode����
	outtextxy(text2_x + 20, text2_y + 13, _T("  ����"));    // ������graphics.h��
	outtextxy(text3_x + 20, text3_y + 13, _T("�˳���Ϸ"));

	// ��Ȩ��Ϣ                             
	settextcolor(BLACK);                      // �����ı���ɫ
	outtextxy(330, 550, _T("��ԭ������"));    // _T�ó���֧��Unicode����
}

// �˵�����
void mouse_move()
{
	void playgame();
	void draw_help();
	initgraph(bk_width, bk_high);
	draw_mune();
	MOUSEMSG m;               // �洢�����Ϣ�ı���
	while (1)
	{
		m = GetMouseMsg();     // ��ȡ�����Ϣ

		if (m.x >= text1_x && m.x <= text1_x + text_width && m.y >= text1_y && m.y <= text1_y + text_high)
		{
			// ��ʼ��Ϸ�˵���
			setlinecolor(RED);  // ���õ�ǰ���߿�Ⱥ�����
			rectangle(text1_x - 5, text1_y - 5, text1_x + text_width + 5, text1_y + text_high + 5);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				// ������Ϸ
				HP = 10;              // �����趨��Ϸ����
				score = 0;
				Delete = 0;
				level = 1;
				begin = clock();
				break;
			}
		}
		else if (m.x >= text2_x && m.x <= text2_x + text_width && m.y >= text2_y && m.y <= text2_y + text_high)
		{
			// �ڰ����˵���
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
			// ���˳��˵���
			setlinecolor(RED);
			rectangle(text3_x - 5, text3_y - 5, text3_x + text_width + 5, text3_y + text_high + 5);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				// �˳���Ϸ
				exit(0);    // exit((0) �����˳���Ϸ
			}
		}
		else
		{
			//���ڲ˵���
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

//����������
void draw_help()
{
	void playgame();
	initgraph(bk_width, bk_high);
	MOUSEMSG n;
	settextstyle(25, 0, _T("STXINGKA"));
	setbkmode(TRANSPARENT);                // �������ֱ���,TRANSPARENT��ʹ��͸�������
	// ͼ�β���
	outtextxy(text4_x + 10, text4_y + 13, _T("�������˵�"));
	loadpicture();
	putimage(0, 0, &background_help);
	while (1)
	{
		n = GetMouseMsg();
		// ���ֲ���
		settextcolor(BLACK);
		outtextxy(100, 50, _T("��Ҫ��Ϊһ������ר�ң���ͱ���ѧ�����׼ȷ�Ĵ���"));
		outtextxy(100, 100, _T("ֻ�о������ϵ���ϰ���ܹ�ʵ�֣�һ������ս�ɡ�"));
		outtextxy(100, 150, _T("1���ó���ȷ����ĸ���������е���ĸ"));
		outtextxy(100, 200, _T("2���ڿ�ʼ��Ϸ֮ǰ���л�Ϊ��дģʽ"));
		outtextxy(100, 250, _T("3������Ϸ��ʼ������԰���Esc���˳���Ϸ"));
		outtextxy(100, 300, _T("���ڷ��ز˵������ʼ��Ϸ��ʼ��ս��"));
		outtextxy(text4_x + 10, text4_y + 13, _T("�������˵�"));
		// ������Ӧ
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

// ��ȡ�����ĸ
void initchar(struct letter array[], int i)
{
	// ��д��ĸ
	srand((unsigned int)time(NULL));    // ����ϵͳʱ�䷵��һ�������
	array[i].target = rand() % 26 + 'A';
	while (array[i].target == array[(i + 1) % 5].target || array[i].target == array[(i + 2) % 5].target || array[i].target == array[(i + 3) % 5].target || array[i].target == array[(i + 4) % 5].target)
	{
		array[i].target = rand() % 26 + 'A';
	}

	array[i].x_letter = rand() % 14 * 50 + 100;  // ʹ��ĸ����һ����Χ�ҳ��ֵ�λ�ò�ͬ
	array[i].y_letter = rand() % 51 - 100;
}

void playgame()
{
	void draw_gameover();
	loadpicture();                // ����ͼƬ
	for (int i = 0; i < 5; i++)
	{
		initchar(letters, i);     // ��������ĸ
	}
	initgraph(bk_width, bk_high); // ������ʾ����
	while (1)
	{
		BeginBatchDraw();         // �Ȼ�ͼ�����ʾ�����Ա�����˸
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
		//��ĸ���ƶ�
		for (int i = 0; i < 5; i++)
		{
			letters[i].y_letter += speed  *0.8 * level;   // ��ĸ�½����ٶ�
			if (letters[i].y_letter >= bk_high)     // �����ĸ����������
			{ 
				initchar(letters, i);               // �����һ���µ���ĸ
				HP = HP - 1;
				if (HP == 0)
				{
					end = clock();
					draw_gameover();
					goto out;
				}
			}
		}
		// ��ĸ����ʾ
		for (int i = 0; i < 5; i++)
		{
			put_mao(letters[i].x_letter, letters[i].y_letter, letters[i].target);
		}

		// ����һ��Ҫ���ж��Ƿ���ڰ���
		if (_kbhit())
		{
			char userKey = _getch();  // ��ȡ��������Ϣ
			for (int i = 0; i < 5; i++)
			{
				if (letters[i].target == userKey || letters[i].target == userKey - ('a' - 'A'))
				{
					score += score_up_speed * level;
					Delete += 1;
					level = score / 500 + 1;
					initchar(letters, i); // ����һ���µ���ĸ
					CreateThread(NULL, 0, playMusic, NULL, NULL, NULL); // ���µ��߳�����ʾ��ը��

					break;
				}
				if (userKey == 27)    // �˳���Ϸ����
				{
					end = clock();
					draw_gameover();
					goto out;
				}
			}
		}
		settextstyle(20, 0, _T("STXINGKA"));
		_stprintf_s(now_score, _T("������%d"), score);
		_stprintf_s(now_HP, _T("HP��%d"), HP);
		_stprintf_s(now_level, _T("�ؿ��� %d"), level);
		setbkmode(TRANSPARENT);
		outtextxy(700, 20, now_score);
		outtextxy(50, 20, now_HP);
		outtextxy(350, 20, now_level);
		Sleep(100);
		FlushBatchDraw();
	}
	out:
	_getch();          //����ʹ����פ������һ������������˳���Ч��
	closegraph();
}

void draw_gameover()
{
	MOUSEMSG n;
	loadpicture();                // ����ͼƬ
	initgraph(bk_width, bk_high);
	putimage(0, 0, &background_gameove);
	while (1)
	{
		n = GetMouseMsg();
		//���ֲ���
		settextcolor(WHITE);
		settextstyle(25, 0, _T("STXINGKA"));
		_stprintf_s(now_delete, _T("���������ĸ��%d��"), Delete);
		_stprintf_s(now_Time, _T("��Ϸʱ�䣺%.2fs"), ((double)end - begin) / CLK_TCK);
		_stprintf_s(now_score, _T("������%d"), score);
		if (level == 1)
		{
			putimage(50, 100, &qingt);
			outtextxy(200, 100, _T("��ϲ������� ��ǿ��ͭ �ƺ�"));
		}
		if (level == 2)
		{
			putimage(50, 100, &baiy);
			outtextxy(200, 100, _T("��ϲ������� ������� �ƺ�"));
		}
		if (level == 3)
		{
			putimage(50, 100, &huangj);
			outtextxy(200, 100, _T("��ϲ������� ��ҫ�ƽ� �ƺ�"));
		}
		if (level == 4)
		{
			putimage(50, 100, &zhuans);
			outtextxy(200, 100, _T("��ϲ������� ������ʯ �ƺ�"));
		}
		if (level >= 5)
		{
			putimage(50, 100, &wangz);
			outtextxy(200, 100, _T("��ϲ������� ��ǿ���� �ƺ�"));
		}
		outtextxy(350, 50, now_Time);
		outtextxy(50,50,now_delete);
		outtextxy(650, 50, now_score);
		outtextxy(300, 400, _T("�������˵�"));
		outtextxy(300, 450, _T(" �˳���Ϸ"));
		// �����Ӧ
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
	mciSendString(_T("open D:\\������ϰϵͳ\\����ĸ\\С����.mp3 alias music"), 0, 0, 0);
	mciSendString(_T("play music repeat"),0,0,0);       // ����ѭ������
	mouse_move();
	return 0;
}
