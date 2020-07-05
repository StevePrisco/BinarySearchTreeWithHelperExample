struct Player
{
 char * name;
 int wins;
 int losses;
} Player;

typedef struct node
{
 struct Player * player;
 struct node *left;
 struct node *right;
} node;

node * findNode(char * name);

void addNode(char *name, int result);

void updateNode(char *name, int result);

void insert(char *player1, int score1, char *player2, int score2);

void printHelper(node * tempNode);

void printTree();

void deallocateHelper(node *tempNode);

void deallocate();
