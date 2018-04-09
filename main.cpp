#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <Windows.h>
#include "snake.h"

void Pos(int i, int j)
{
	COORD pos;
	pos.X = i;
	pos.Y = j;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);           //set the position of cursor
}

void CreateMap()
{
	for(int i=0; i<58; i=i+2)
	{
		Pos(i, 0);
		printf("■");
		Pos(i, 26);
		printf("■");
	}
	for(int j=1; j<26; j++)
	{
		Pos(0, j);
		printf("■");
		Pos(56, j);
		printf("■");
	}
}

void InitSnake()
{
	food_n = (snake *)malloc(sizeof(snake));
	if(!(tail=(snake *)malloc(sizeof(snake))))
	{
		printf("don't have enough space\n");
		exit(1);
	}
	tail->next = NULL;
	tail->x = 24;
	tail->y = 5;

	for(int i=1; i<=4; i++)
	{
		if(!(head=(snake *)malloc(sizeof(snake))))
		{
			printf("don't have enough space\n");
			exit(1);
		}
		head->next = tail;
		head->x = tail->x + 2;
		head->y = tail->y;
		tail = head;
	}

	while(tail!=NULL)
	{
		Pos(tail->x, tail->y);
		printf("■");
		tail = tail->next;
	}
}

void CreateFood()
{
	snake *food = (snake *)malloc(sizeof(snake));
	snake *p = (snake *)malloc(sizeof(snake));
	srand((unsigned)time(NULL));
	food->x = rand()%52+2;          //the food should not be created out of the space
	while((food->x)%2!=0)             //The abscissa of food is even
		food->x = rand()%52+2;
	food->y = rand()%24+1;

	p = head;
	while(p!=NULL)
	{
		if(food->x==p->x && food->y==p->y)
		{
			food->x = rand()%52+2;
			food->y = rand()%24+1;
		}
		p = p->next;
	}

	food_n->x = food->x;
	food_n->y = food->y;
	Pos(food_n->x, food_n->y);
	printf("■");
	free(food);
	free(p);
}

bool BiteSelf()
{
	snake *self = (snake *)malloc(sizeof(snake));
	self = head->next;
	while(self!=NULL)
	{
		if(head->x==self->x && head->y==self->y)
		{
			free(self);
			return true;
		}
		self = self->next;
	}
	free(self);
	return false;
}

void HittheWall()
{
	if(head->x==0||head->x==56||head->y==0||head->y==26)
	{
		endgamestatus = 1;
		Endgame();
	}
}

void SnakeMove()//蛇前进,上U,下D,左L,右R
{
	snake * nexthead;
    HittheWall();
    nexthead=(snake*)malloc(sizeof(snake));
	switch(status)
	{
    case U:
    {
        nexthead->x=head->x;
        nexthead->y=head->y-1;
        if(nexthead->x==food_n->x && nexthead->y==food_n->y)//如果下一个有食物//
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            score=score+add;
            CreateFood();
        }
        else                                               //如果没有食物//
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            Pos(q->next->x,q->next->y);
            printf("  ");
            free(q->next);
            q->next=NULL;
        }
		break;
    }
    case D:
    {
        nexthead->x=head->x;
        nexthead->y=head->y+1;
        if(nexthead->x==food_n->x && nexthead->y==food_n->y)  
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            score=score+add;
            CreateFood();
        }
        else                               
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            Pos(q->next->x,q->next->y);
            printf("  ");
            free(q->next);
            q->next=NULL;
        }
		break;
    }
    case L:
    {
        nexthead->x=head->x-2;
        nexthead->y=head->y;
        if(nexthead->x==food_n->x && nexthead->y==food_n->y)
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            score=score+add;
            CreateFood();
        }
        else                                
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            Pos(q->next->x,q->next->y);
            printf("  ");
            free(q->next);
            q->next=NULL;
        }
		break;
    }
    case R:
    {
        nexthead->x=head->x+2;
        nexthead->y=head->y;
        if(nexthead->x==food_n->x && nexthead->y==food_n->y)
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            score=score+add;
            CreateFood();
        }
        else                                         
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            Pos(q->next->x,q->next->y);
            printf("  ");
            free(q->next);
            q->next=NULL;
        }
		break;
    }
	}
	Pos(60, 24);

    if(BiteSelf()==true)   
    {
        endgamestatus=2;
        Endgame();
    }
}

void Endgame()
{
	system("cls");
	Pos(13, 12);
	if(endgamestatus==1) printf("对不起，您撞到墙了。游戏结束");
	else if(endgamestatus==2) printf("对不起，您咬到自己了。游戏结束");
	else if(endgamestatus==3) printf("游戏结束");
	Pos(24, 13);
	printf("%s,您的得分是: %d\n", name, score);
	system("pause");
	exit(0);
}

void Pause()
{
	while(1)
	{
		Sleep(300);
		if(GetAsyncKeyState(VK_SPACE))
			break;
	}
}

void StartGame()
{
	system("cls");
	Pos(24, 8);
	printf("请输入名字：");
	scanf("%s", name);
	system("cls");
	Pos(20, 8);
	printf("欢迎来到贪吃蛇游戏：%s", name);
	Pos(20, 10);
	printf("用↑.↓.←.→分别控制蛇的移动， F1 为加速，2 为减速\n");
	Pos(20, 11);
	printf("加速能获得更高的分数\n");

	Pos(58, 26);
	system("pause");
	system("cls");
}

void GameCircle()
{
	CreateMap();
	InitSnake();

    Pos(64,15);
    printf("不能穿墙，不能咬到自己\n");
    Pos(64,16);
    printf("用↑.↓.←.→分别控制蛇的移动.");
    Pos(64,17);
    printf("F1 为加速，F2 为减速\n");
    Pos(64,18);
    printf("ESC ：退出游戏");
	Pos(64,19);
	printf("space：暂停游戏/继续游戏");
    Pos(64,20);
	CreateFood();

	while(1)
	{
		Pos(64,10);
        printf("得分：%d  ",score);
        Pos(64,11);
        printf("每个食物得分：%d分",add);

		if(GetAsyncKeyState(VK_UP) && status!=D) status = U;
		else if(GetAsyncKeyState(VK_DOWN) && status!=U) status = D;
		else if(GetAsyncKeyState(VK_LEFT) && status!=R) status = L;
		else if(GetAsyncKeyState(VK_RIGHT) && status!=L) status = R;
		else if(GetAsyncKeyState(VK_SPACE)) Pause();
		else if(GetAsyncKeyState(VK_ESCAPE))
		{
			endgamestatus = 3;
			break;
		}
		else if(GetAsyncKeyState(VK_F1))
		{
			add += 2;
			SLEEPTIME -= 30;
		}
		else if(GetAsyncKeyState(VK_F2))
		{
			add -= 2;
			SLEEPTIME += 30;
		}
		SnakeMove();
		Sleep(SLEEPTIME);
	}
}

void main()
{
	StartGame();
	//CreateMap();
	//InitSnake();
	//system("pause");

	GameCircle();
	Endgame();
	system("pause");
}
