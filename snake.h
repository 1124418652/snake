#define U 1
#define D 2
#define L 3
#define R 4

typedef struct snake
{
	int x, y;
	snake *next;
}snake;

int score=0, add=10;
int status=D;
int endgamestatus;
int SLEEPTIME = 300;
snake *tail, *head, *p, *food_n, *q;
char name[50];

void Pos(int, int);
void CreateMap(void);
void InitSnake();
void CreateFood();
bool BiteSelf();
void HittheWall();
void SnakeMove();
void Endgame();
void Pause();
void StartGame();
void GameCircle();