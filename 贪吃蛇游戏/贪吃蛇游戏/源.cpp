#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define height 28//����߶�
#define width 60//�����ȣ�������ż��


//--------------------------------------------------------
//��������
void GameStart();//��������
void GameOver();//��������
void draw_cube();//�����
void initialization();//��ʼ�����������
void gotoxy(int x, int y);//�ƶ�����
void move();//������������ƶ�
void p_move();//������ͷ�ƶ�������ָ����ƶ�
void food();//����ʳ��
void judge_head();//�ж���ͷ��λ��
void static_info();//��̬��Ϣ������Ϸ����������ʾ
void dynamic_info();//��̬��Ϣ������Ϸ�÷�
//--------------------------------------------------------
//ȫ�ֱ���
struct snake
{
	short x;//x����
	short y;//y����
	struct snake *next;//��һ���ֵ�ָ��
}*head=NULL,*scan=NULL,*pf=NULL,*pb=NULL;


int speed = 250;//���ƶ����ٶȣ����룩
short length = 4;//��ʼ��������
char direction = 'd';//��ͷ������w/a/s/d
short food_x, food_y, tail_x, tail_y;//ʳ�����꣬��β������
short snake_xy[1024];//�洢������ÿһ���ڵ�����꣬���ı�ṹ��ָ������ʹ��
short score = 0;//��Ϸ�÷�
short music = 1;//�Ե�ʳ����Ƿ����壬Ĭ����
//--------------------------------------------------------
//����������
void initialization()//��Ϸ��ʼ��ĳ�ʼ�������
{
	short i;
	draw_cube();//�����ܵķ�����
	for (i = 1; i <= length; i++)//��̰����
	{
		pb = (struct snake*)malloc(sizeof(struct snake));
		pb->y = 17;//��ʼλ��������y=17
		if (i == 1)//�������ͷ
		{
			head = scan = pf = pb;//������ͷ������
			pb->x = 28;//��ͷ�ĺ����긳ֵΪ28
			gotoxy(pb->x, pb->y);//�ƶ����
			printf("��");//������ͷ
		}
		else//����
		{
			pb->x = pf->x - 2;//���º�����
			gotoxy(pb->x, pb->y); printf("��");//����������
			pf->next = pb;//ָ����һ���ߵ�֫��
		}
		pf = pb;
		pf->next = NULL;
	}
}
void draw_cube()
{
	short i;
	for (i = 1; i <= height; i++)//���������з���
	{
		gotoxy(0, i); printf("��");
		gotoxy(width, i); printf("��");
	}
	for (i = 0; i <= width + 1; i+=2)//���������з���
	{
		gotoxy(i, 0); printf("��");
		gotoxy(i, height + 1); printf("��");
	}
}
void gotoxy(int x, int y)//�ƶ���꺯��
{
	COORD coord;//���������͵ı���
	coord.X = x;//�����긳ֵ
	coord.Y = y;//�����긳ֵ
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	//���ù��λ��
}
void GameStart()//��Ϸ����������ƺ���
{
	draw_cube();//�������ܵĿ��
	gotoxy(25, 10); printf("̰������Ϸ");
	gotoxy(21, 13); printf("Designed by ��ҹ");
	gotoxy(22, 17);
	system("pause");
}
void GameOver()//��Ϸ�����������
{
	system("cls");
	draw_cube();
	gotoxy(25, 10); printf("Game Over");
	gotoxy(25, 12); printf("�÷�:%d",score);
	gotoxy(22, 17);
	printf("�밴���������...");
	_getch();
	exit(0);
}
void static_info()//��̬��Ϣ���ƺ���
{
	gotoxy(width + 4,2); printf("%c %c %c %c����",24,25,26,27);
	gotoxy(width + 4,3); printf("���������ͣ");
	gotoxy(width + 4,4); printf("F1 ���٣�F2 ����");
	gotoxy(width + 4,5); printf("F3 ��������");
	gotoxy(width + 4,8); printf("�÷�:");
	gotoxy(width + 4,10); printf("��ͷλ��:");
	gotoxy(width + 4,12); printf("ʳ��λ��:");
	gotoxy(width + 4,14); printf("����:");
	gotoxy(width + 4, 16); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_RED | FOREGROUND_INTENSITY); printf("F4:��");//��ɫ
	gotoxy(width + 4, 18); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_GREEN | FOREGROUND_RED| FOREGROUND_INTENSITY); printf("F5:��");//��ɫ
	gotoxy(width + 4, 20); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("F6:��");//��ɫ
	gotoxy(width + 4, 22); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY); printf("F7:��");//��ɫ
	gotoxy(width + 4, 24); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED| FOREGROUND_INTENSITY); printf("F8:��");//����ɫ
	gotoxy(width + 4, 26); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED); printf("F9:��");//��ɫ
}
void dynamic_info()//��̬��Ϣ���ƺ���
{
	gotoxy(width+9 ,8); printf("%d",score);//����ɼ�
	gotoxy(width+13 ,10); printf("%2d,%2d",head->x,head->y);//�����ͷλ��
	gotoxy(width+13,12); printf("%2d,%2d", food_x, food_y);//�����ͷλ��
	gotoxy(width+9,14);music==1? printf("��"): printf("��");//���ֿ���
}
void move()//��Ϸ���ĺ���
{
	short a, b;//�����������Ҽ�
	char key_direction = 'd';//���ƶ�����
	while (!_kbhit())//�ж��Ƿ��а������룻�����ƶ�
	{
	loop://ѭ����ת��־
		gotoxy(food_x, food_y); printf("��");//����ʳ��
		switch (direction)//���ݷ����������������и��²���
		{
		case 'w':gotoxy(scan->x, scan->y - 1); printf("    ��    "); p_move();
			head->y = head->y - 1; break;
		case 'a':gotoxy(scan->x - 2, scan->y); printf("    ��    "); p_move();
			head->x = head->x - 2; break;
		case 's':gotoxy(scan->x, scan->y + 1); printf("    ��    "); p_move();
			head->y = head->y + 1; break;
		case 'd':gotoxy(scan->x + 2, scan->y); printf("    ��    "); p_move();
			head->x = head->x + 2;
		}
		dynamic_info();//��̬��Ϣ���
		scan = head;
		judge_head();//�ж���ͷ״̬
		Sleep(speed);//���˶��ٶȿ���
	}
	scan = head;
	a = _getch();
	b = _getch();
	switch (a)//���ݲ����������˶�����Ŀ���
	{
	case 224:switch (b)
	         {
	          case 72:key_direction = 'w'; if (direction == 's') key_direction = 0; break;
			  case 75:key_direction = 'a'; if (direction == 'd') key_direction = 0; break;
			  case 80:key_direction = 's'; if (direction == 'w') key_direction = 0; break;
			  case 77:key_direction = 'd'; if (direction == 'a') key_direction = 0;
	         }break;
	case 0:switch (b)//�����û���������˶��ٶ�
			{
			case 59:speed -= 20; break;
			case 60:speed += 20; break;
			case 61:music = music == 1 ? 0 : 1; break;
			case 62:system("color0C"); static_info(); SetConsoleTextAttribute
					(GetStdHandle(STD_OUTPUT_HANDLE),
						FOREGROUND_RED | FOREGROUND_INTENSITY); break;//��ɫ
			case 63:system("color0E"); static_info(); SetConsoleTextAttribute
					(GetStdHandle(STD_OUTPUT_HANDLE),
						FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); break;//��ɫ
			case 64:system("color0A"); static_info(); SetConsoleTextAttribute
					(GetStdHandle(STD_OUTPUT_HANDLE),
						FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;//��ɫ
			case 65:system("color0D"); static_info(); SetConsoleTextAttribute
					(GetStdHandle(STD_OUTPUT_HANDLE),
						FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY); break;//��ɫ
			case 66:system("color0F"); static_info(); SetConsoleTextAttribute
					(GetStdHandle(STD_OUTPUT_HANDLE),
						FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY); break;//����ɫ
			case 67:system("color08"); static_info(); SetConsoleTextAttribute
					(GetStdHandle(STD_OUTPUT_HANDLE),
						FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED); break;//��ɫ
	       }break;
	default: goto loop;
	}
	if (key_direction)
		direction = key_direction;
	else
		goto loop;
	goto loop;
}
void p_move()
{
	short i = 0;
	while (scan->next != NULL)
		scan = scan->next;//scan����ָ����β
	gotoxy(scan->x, scan->y); printf(" ");//��һ�������У���ӡ����ͷ��������ȥ����β
	scan = head;//scanָ��ԭ������ͷλ��
	while (scan->next != NULL)//�洢��ͷ����βǰһ���ڵ������
	{
		snake_xy[i] = scan->x;
		i++;
		snake_xy[i] = scan->y;
		i++;
		scan = scan->next;
	}
	tail_x = scan->x;
	tail_y = scan->y;//�洢��β���꣬Ϊ�����ڳԵ�ʳ��ʱ������������������
	i = 0;
	scan = head->next;
	while (scan->next != NULL)//�Ѵ洢�����������ֵ����ͷλ��֮��Ľڵ㣬ֱ��ɨ�赽��β����
	{
		scan->x = snake_xy[i];
		i++;
		scan->y = snake_xy[i];
		i++;
		scan = scan->next;
	}
	scan->x = snake_xy[i];
	i++;
	scan->y = snake_xy[i];
}
void food()//ʳ�����ɺ���
{
	short i = 0;
	srand((unsigned)time(NULL));//�����������
	do 
	{
		food_x = rand() % (width - 3) + 2;//ʳ��������������
	} while (food_x % 2);
	food_y = rand() % (height - 1) + 1;//ʳ���������������
	gotoxy(food_x, food_y);
	printf("��");//����ʳ��	
	scan = head;
}
void judge_head()//�ж���ͷ״̬����
{
	short i = 0;
	if (head->x == 0 || head->x == width || head->y == 0 || head->y == height + 1)
		//�����ж��ǲ���ײǽ��
		GameOver();
	while (scan->next != NULL)//�ж��ǲ���ҧ���Լ���
	{
		if (head->x == snake_xy[i])
			if (head->y == snake_xy[++i])
				GameOver();
			else
				i++;
		else
			i += 2;
		scan = scan->next;
	}
	if (head->x == snake_xy[i])
		if (head->y == snake_xy[++i])
			GameOver();
	if (head->x == food_x && head->y == food_y)//����Ե�ʳ���β�ͼ���һ��
	{
		if (music)
			putchar(7);//����
		score += 100;
		pb = (struct snake*)malloc(sizeof(struct snake));
		pf->next = pb;
		pb->next = NULL;
		pf = pb;
		pb->x = tail_x;
		pb->y = tail_y;
		gotoxy(pb->x, pb->y); printf("��");
		food();
	}
	scan = head;
}
//--------------------------------------------------------
//main����
int main()
{
	system("mode con: cols=100 lines=31");//���ó�80��30��
	GameStart();
	system("cls");
	initialization();
	food();
	static_info();
	move();
	system("pause");
	return 0;
}
