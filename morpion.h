struct Joueur{
	unsigned long long int Num;
	char Nom[100];
	char Prenom[100];
	char Pown;
};
typedef struct Joueur Joueur;

struct joueurStat{
	unsigned long long num;
	char Nom[100];
	char Prenom[100];
	int g;
	struct joueurStat *suivant; 
};
typedef struct joueurStat joueurStat;

int   couleurs = 15, restedupage = 15;
char board[3][3];
Joueur J1, J2;

unsigned long long int rechercher(char TmpNomChercher[], char TmpPrenomChercher[]);
Joueur ajouterJoueur();
void gotoxy1(int x ,int y);
void delay(int NbrDeSeconds);
void resetBoard();
void printBoard();
int checkFreeSpaces();
unsigned long long int printWinner(char winner,int i);
char checkWinner();
int* CheckWin();
void Recup(unsigned long long int J1NUM, unsigned long long int J2NUM, int type);
void Sauvegarder(char pown, int etat);
void playerMove(char PLAYER);
void computerMove1();
void computerMove2();
int MethodeFacile();
int MethodeMoyenne();
void ModeDuJeuSolo();
void ModeDuJeuMulti();
void ModeDuJeuMultijoueurs();
joueurStat*  inserer(unsigned long long n , char no[] , char p[] , int g);
joueurStat* ajouter(joueurStat *liste, joueurStat *vol);
void stat();
int gag(unsigned long long int num);
void stat_G();
void statistiques();
void MenuColor();
void aide();
void header();
void menu();
