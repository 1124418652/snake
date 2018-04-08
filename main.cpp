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
		printf("��");
		Pos(i, 26);
		printf("��");
	}
	for(int j=1; j<26; j++)
	{
		Pos(0, j);
		printf("��");
		Pos(56, j);
		printf("��");
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
		printf("��");
		tail = tail->next;
	}
}

void CreateFood()
{
	snake *food = (snake *)malloc(sizeof(snake));
	snake *p = (snake *)malloc(sizeof(snake));
	srand((unsigned)time(NULL));
	food->x = rand()%52+2;          //the food should not be created out of the space
	while(food->x%2!=0)             //The abscissa of food is even
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
	printf("��");
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

void SnakeMove()
{
	snake *nexthead = (snake *)malloc(sizeof(snake));
	p = (snake *)malloc(sizeof(snake));
	HittheWall();
	switch(status)
	{
	case U:
		{
		nexthead->x = head->x;
		nexthead->y = (head->y)-1;
		nexthead->next = head;
		head = nexthead;
		p = head;
		if(p->x==food_n->x && p->y==food_n->y)   //if the next square is food
		{
			while(p!=NULL)
			{
				Pos(p->x, p->y);
				printf("��");
				p = p->next;
			}
			score += add;
			CreateFood();
			free(p);
		}else
		{
			while(p->next->next!=NULL)
			{
				Pos(p->x, p->y);
				printf("��");
				p = p->next;
			}
			Pos(p->next->x, p->next->y);
			printf(" ");
			p->next = NULL;
			free(p->next);
		}
		}
	case D:
		{
		nexthead->x = head->x;
		nexthead->y = (head->y)+1;
		nexthead->next = head;
		head = nexthead;
		p = head;
		if(p->x==food_n->x && p->y==food_n->y)   //if the next square is food
		{
			while(p!=NULL)
			{
				Pos(p->x, p->y);
				printf("��");
				p = p->next;
			}
			score += add;
			CreateFood();
			free(p);
		}else
		{
			while(p->next->next!=NULL)
			{
				Pos(p->x, p->y);
				printf("��");
				p = p->next;
			}
			p = p->next;
			Pos(p->x, p->y);
			printf("  ");
			p = NULL;
			free(p);
		}
		}
	case L:
		{
		nexthead->x = (head->x)-2;
		nexthead->y = head->y;
		nexthead->next = head;
		head = nexthead;
		p = head;
		if(p->x==food_n->x && p->y==food_n->y)   //if the next square is food
		{
			while(p!=NULL)
			{
				Pos(p->x, p->y);
				printf("��");
				p = p->next;
			}
			score += add;
			CreateFood();
			free(p);
		}else
		{
			while(p->next!=NULL)
			{
				Pos(p->x, p->y);
				printf("��");
				p = p->next;
			}
			Pos(p->x, p->y);
			printf("  ");
			p = NULL;
			free(p);
		}
		}
	}
}

void Endgame()
{

}

void main()
{
	CreateMap();
	InitSnake();
	
	CreateFood();
	SnakeMove();
	SnakeMove();
	
	Pos(60,29);
	printf("%d,%d",food_n->x,food_n->y);
	system("pause");
}
