#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include "morpion.h"
#include "conio.h"
#include "conio.c"


//////////////////////////////////////////////////
//////////////////////////////////////////////////
unsigned long long int rechercher(char TmpNomChercher[], char TmpPrenomChercher[]){
	Joueur JTmp, J;
	strcpy(J.Nom, TmpNomChercher);
	strcpy(J.Prenom, TmpPrenomChercher);
	FILE *F = fopen("Joueurs.txt", "r");
	if (F == NULL) printf("   erreur\n");
	else{
		while (!feof(F)){
			fscanf(F,"%llu %s %s\n", &JTmp.Num, JTmp.Nom, JTmp.Prenom);
			fflush(stdin);
			if (strcmp(JTmp.Nom, J.Nom) == 0 && strcmp(JTmp.Prenom, J.Prenom) == 0){
				J.Num = JTmp.Num;
				fclose(F);
				return J.Num;
			}
		}
		fclose(F);
		return 0;
	}
} // check

Joueur ajouterJoueur(){
	system("cls");
	Joueur joueur;
	printf("   Entrez le nom et prenom du joueur: ");
	scanf("%s %s", joueur.Nom, joueur.Prenom);
	fflush(stdin);
	unsigned long long int IdTmp = rechercher(joueur.Nom, joueur.Prenom);
	if(IdTmp == 0){
		FILE *F = fopen("Joueurs.txt", "a+");
		if (F == NULL) printf("   erreur\n");
		else{
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			joueur.Num = (pow(10, 10) * (tm.tm_year + 1900)) + (pow(10, 8) * (tm.tm_mon + 1)) + (pow(10, 6) * tm.tm_mday) + (pow(10, 4) * tm.tm_hour) + (pow(10, 2) * tm.tm_min) + tm.tm_sec;
			fprintf(F, "%llu %s %s\n", joueur.Num, joueur.Nom, joueur.Prenom);
			fclose(F);
		}
	}else{
		joueur.Num = IdTmp;	
	}
	return joueur;
} // check

//////////////////////////////////////////////////
//////////////////////////////////////////////////
void gotoxy1(int x ,int y){
 	COORD crd;
 	crd.X=x;
 	crd.Y=y;
 	SetConsoleCursorPosition(GetStdHandle (STD_OUTPUT_HANDLE),crd);
}

void resetBoard(){
	int i, j;
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			board[i][j] = ' ';
		}
	}
} // check

void printBoard(){
	gotoxy1(39 ,3); textcolor(restedupage); printf("1   2   3");
	gotoxy1(35 ,5); printf("1"); textcolor(couleurs); gotoxy1(39 ,5); printf("%c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
	gotoxy1(38 ,6); printf("---|---|---\n");textcolor(restedupage);
	gotoxy1(35 ,7); printf("2");textcolor(couleurs);gotoxy1(39 ,7);printf("%c | %c | %c \n ", board[1][0], board[1][1], board[1][2]);
	gotoxy1(38 ,8); printf("---|---|---\n");textcolor(restedupage);
	gotoxy1(35 ,9); printf("3");textcolor(couleurs); gotoxy1(39 ,9);printf("%c | %c | %c ", board[2][0], board[2][1], board[2][2]); printf("\n");
	textcolor(restedupage);
	gotoxy1(0,11);
}

int checkFreeSpaces(){
	// elle retourne 0 ya pas de place vide dans la matrice cad fin de jeu
	int i, j, freeSpaces = 9;
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			if (board[i][j] != ' '){
				freeSpaces--;
			}
		}
	}
	return freeSpaces;
} // check

unsigned long long int printWinner(char winner,int i){
	if (winner == ' '){
		printf("   IT'S A TIE!\n"); 
		return 0;
	}
	if(i == 0){
		if (winner == J1.Pown){
			printf("   Tu as gagne!\n");
			return J1.Num;
		}else{
			printf("   Tu as perdu!\n");
			return J2.Num;
		}
	}else{
		if (winner == J1.Pown){
			printf("   %s %s a gagne le match!\n", J1.Nom, J1.Prenom);
			return J1.Num;
		}else{
			printf("   %s %s a gagne le match!\n", J2.Nom, J2.Prenom);
			return J2.Num;
		}
	}
}

char checkWinner(){
	int i;
	for (i = 0; i < 3; i++){
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) return board[i][0];
	}
	for (i = 0; i < 3; i++){
		if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) return board[0][i];
	}
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) return board[0][0];
	if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) return board[0][2];
	return ' ';
}

int* CheckWin(){
    int *tab = (int*)malloc(2*sizeof(int));
    char pown = 'O';
    int i, j, counterPown = 0, counterVoid = 0;
    for (  j = 0; j < 2; j++){
        //1
        for (i = 0; i < 3; i++){
            if (board[0][i] == pown) counterPown++;
            if (board[0][i] == ' ') counterVoid++;
        }
        if (counterPown == 2 && counterVoid == 1){
            for (i = 0; i < 3; i++){
                if (board[0][i] == ' '){
                    tab[0] = 0; tab[1] = i;
                    break;
                }
            }
            return tab;
        }
        //2
        counterPown = 0; counterVoid = 0;
        for (i = 0; i < 3; i++){
            if (board[i][0] == pown) counterPown++;
            if (board[i][0] == ' ') counterVoid++;
        }
        if (counterPown == 2 && counterVoid == 1){
            for (i = 0; i < 3; i++){
                if (board[i][0] == ' '){
                    tab[0] = i; tab[1] = 0;
                    break;
                }
            }
            return tab;
        }
        //3
        counterPown = 0; counterVoid = 0;
        for (i = 0; i < 3; i++){
            if (board[i][i] == pown) counterPown++;
            if (board[i][i] == ' ') counterVoid++;
        }
        if (counterPown == 2 && counterVoid == 1){
            for (i = 0; i < 3; i++){
                if (board[i][i] == ' '){
                    tab[0] = i; tab[1] = i;
                    break;
                }
            }
            return tab;
        }
        //4
        counterPown = 0; counterVoid = 0;
        for (i = 0; i < 3; i++){
            if (board[2][i] == pown) counterPown++;
            if (board[2][i] == ' ') counterVoid++;
        }
        if (counterPown == 2 && counterVoid == 1){
            for (i = 0; i < 3; i++){
                if (board[2][i] == ' '){
                    tab[0] = 2; tab[1] = i;
                    break;
                }
            }
            return tab;
        }
        //5
        counterPown = 0; counterVoid = 0;
        for (i = 0; i < 3; i++){
            if (board[i][2] == pown) counterPown++;
            if (board[i][2] == ' ') counterVoid++;
        }
        if (counterPown == 2 && counterVoid == 1){
            for (i = 0; i < 3; i++){
                if (board[i][2] == ' '){
                    tab[0] = i; tab[1] = 2;
                    break;
                }
            }
            return tab;
        }
        //6
        counterPown = 0; counterVoid = 0;
        for (i = 0; i < 3; i++){
            if (board[i][1] == pown) counterPown++;
            if (board[i][1] == ' ') counterVoid++;
        }
        if (counterPown == 2 && counterVoid == 1){
            for (i = 0; i < 3; i++){
                if (board[i][1] == ' '){
                    tab[0] = i; tab[1] = 1;
                    break;
                }
            }
            return tab;
        }
        //7
        counterPown = 0; counterVoid = 0;
        for (i = 0; i < 3; i++){
            if (board[1][i] == pown) counterPown++;
            if (board[1][i] == ' ') counterVoid++;
        }
        if (counterPown == 2 && counterVoid == 1){
            for (i = 0; i < 3; i++){
                if (board[1][i] == ' '){
                    tab[0] = 1; tab[1] = i;
                    break;
                }
            }
            return tab;
        }
        //8
        counterPown = 0; counterVoid = 0;
        for (i = 0; i < 3; i++){
            if (board[i][2-i] == pown) counterPown++;
            if (board[i][2-i] == ' ') counterVoid++;
        }
        if (counterPown == 2 && counterVoid == 1){
            for (i = 0; i < 3; i++){
                if (board[i][2-i] == ' '){
                    tab[0] = i; tab[1] = 2-i;
                    break;
                }
            }
            return tab;
        }
        pown = 'X';
    }
    free(tab);
    return NULL;
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
void Recup(unsigned long long int J1NUM, unsigned long long int J2NUM, int type){
	unsigned long long int NTmp1,NTmp2, Num = 0;
	char M[3][3];
	int Etatdepartie, i, j, x = 0, o = 0;
	Joueur joueur;
	FILE *F = fopen("FichierRecuperation.txt","r+");
	while(fscanf(F, "%llu %llu {{%c%c%c},{%c%c%c},{%c%c%c}} %d", &NTmp1,  &NTmp2,
			&M[0][0], &M[0][1], &M[0][2],
			&M[1][0], &M[1][1], &M[1][2],
			&M[2][0], &M[2][1], &M[2][2],
			&Etatdepartie) == 12){
			
		if(((J1NUM == NTmp1) || (J2NUM == NTmp1)) && ((J1NUM == NTmp2) || (J2NUM == NTmp2))){
			if(Etatdepartie == 0){
				Num = NTmp1;
				for(i = 0; i < 3; i++){
					for(j = 0; j < 3; j++){
						board[i][j] = M[i][j];
					}
				}
			}
			if(Etatdepartie == 1) Num=0;
		}
	}
	if(Num == 0){
		resetBoard();
		J1.Pown = 'X'; J2.Pown = 'O';
		switch (type){
			case 1: // mode facile
				MethodeFacile();
				break;
			case 2: // mode moyen
				MethodeMoyenne();
				break;
			case 3: // mode difficile
				break;
			case 4: // mode difficile
				ModeDuJeuMulti();
				break;
		}
	}else{
		int choix;
		printf("   1- Continuer le jeu \n");
		printf("   2- Commencer une nouvelle partie \n");
		do{
			printf("   Entrer votre choix: ");
			scanf("%d", &choix);
		} while (choix < 1 || choix > 2);
		//printf("type: %d | Id: %llu | choix: %d\n", type, Num, choix);
		system("cls");
		switch (choix){
		case 1:
			switch (type){
				case 1: // mode facile
					J1.Pown = 'X'; J2.Pown = 'O';
					MethodeFacile();
					break;
				case 2: // mode moyen
					J1.Pown = 'X'; J2.Pown = 'O';
					MethodeMoyenne();
					break;
				case 3: // mode difficile
					break;
				case 4: // mode duo
					for(i = 0; i < 3; i++){
						for(j = 0; j < 3; j++){
							if(board[i][j] == 'X') x++;
							if(board[i][j] == 'O') o++;
						}
					}
					if (x == o){
						if (Num == J1.Num){}
						else{
							joueur = J1;
							J1 = J2;
							J2 = joueur;
						}
						J1.Pown = 'X'; J2.Pown = 'O';
					}else{
						if (Num == J2.Num){
							joueur = J1;
							J1 = J2;
							J2 = joueur;
						}
						J1.Pown = 'O'; J2.Pown = 'X';
					}
					printf("   Le joueur qui va commencer est %s %s avec le caractere %c\n", J1.Nom, J1.Prenom, J1.Pown);
					ModeDuJeuMulti();
					break;
			}
			break;
		case 2:
			resetBoard();
			J1.Pown = 'X'; J2.Pown = 'O';
			switch (type){
				case 1: // mode facile
					MethodeFacile();
					break;
				case 2: // mode moyen
					MethodeMoyenne();
					break;
				case 3: // mode difficile
					break;
				case 4: // mode duo
					ModeDuJeuMulti();
					break;
			}
			break;
	}
	}
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
// quelque chose qui cloche !!!
void Sauvegarder(char pown, int etat){
	FILE *f =fopen("FichierRecuperation.txt","a+");
	if (pown == J1.Pown){
		fprintf(f,"%llu %llu {{%c%c%c},{%c%c%c},{%c%c%c}} %d\n", J1.Num, J2.Num, board[0][0] , board[0][1] ,board[0][2] ,
		board[1][0] ,board[1][1] ,board[1][2] ,board[2][0] ,board[2][1] ,board[2][2], etat);
	}else{
		fprintf(f,"%llu %llu {{%c%c%c},{%c%c%c},{%c%c%c}} %d\n", J2.Num, J1.Num, board[0][0] , board[0][1] ,board[0][2] ,
		board[1][0] ,board[1][1] ,board[1][2] ,board[2][0] ,board[2][1] ,board[2][2], etat);
	}
	fclose(f);
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
//A optimiser
void playerMove(char PLAYER){
	int x, y, i = 0;
	char response;
	do{
		printf("   Entrez le numero de la ligne #(1-3): ");
		scanf("%d", &x);
		x--;
		printf("   Entrez le numero du colonne #(1-3): ");
		scanf("%d", &y);
		y--;
		if((x >= 0 && x <= 2) && (y >= 0 && y <= 2) && (board[x][y] == ' ')){
			i = 1;
			board[x][y] = PLAYER;
			break;
		}else if(x == -1 && y == -1){
			printf("   Voulez-vous quitter le match ? (O/N): ");
			scanf("%c");
			scanf("%c",&response);
			if(toupper(response) == 'O'){
				if(PLAYER == J1.Pown) Sauvegarder(J1.Pown, 0);
				else  Sauvegarder(J2.Pown, 0);
				menu();
			} else{
				continue;
			}
		}
		else printf("   Deplacement invalide!\n");
	}while ( i == 0 );
}
	
void computerMove1(){
	// avant de generer des nombres aleatoires on va verifier sil ya encore des espaces vides
	srand(time(0));
	int x, y;
	if (checkFreeSpaces() > 0){
		do{
			x = rand() % 3;
			y = rand() % 3;
		} while (board[x][y] != ' ');
		board[x][y] = 'O';
	}else{
		printWinner(' ', 0);
	}
}

void computerMove2(){
	// avant de generer des nombres aleatoires on va verifier sil ya encore des espaces vides
	srand(time(0));
	int x, y;
    int *t;
	if (checkFreeSpaces() > 0){
        t = CheckWin();
        if (t != NULL){
            board[t[0]][t[1]] = 'O';
        }else{
            do{
                x = rand() % 3;
                y = rand() % 3;
            } while (board[x][y] != ' ');
            board[x][y] = 'O';
        }
	}else{
		printWinner(' ', 0);
	}
}

int MethodeFacile(){
	char winner, response;
	unsigned long long int NTmp;
	do{
		winner = ' ';
		response = ' ';
		while (winner == ' ' && checkFreeSpaces() != 0){
			system("cls");
			printBoard();
			playerMove(J1.Pown);
			winner = checkWinner();
			if (winner != ' ' || checkFreeSpaces() == 0) break;
			computerMove1();
			winner = checkWinner();
			if (winner != ' ' || checkFreeSpaces() == 0) break;
		}
		system("cls");
		printBoard();
		
		NTmp = printWinner(winner, 0);
		if(NTmp == 0) Sauvegarder(winner,2);
		else Sauvegarder(winner,1);

		printf("   Voulez-vous rejouer ? (O/N): ");
		scanf("%c");
		scanf("%c", &response);
		response = toupper(response);
		resetBoard();
	} while (response == 'O');
	printf("   Merci d'avoir joue !\n");
	return 0;
}

int MethodeMoyenne(){
	char winner, response;
	unsigned long long int NTmp;
    int ft = 0, x, y;
	do{
		winner = ' ';
		response = ' ';
		while (winner == ' ' && checkFreeSpaces() != 0){
			system("cls");
			printBoard();
			playerMove(J1.Pown);
			winner = checkWinner();
			if (winner != ' ' || checkFreeSpaces() == 0) break;
            if (ft == 0){
                if ( board[1][1] == 'X' ){
                    x = rand() % 3;
                    y = rand() % 3;
                    if (x == 1) x--;
                    if (y == 1) y--;
                    board[x][y] = 'O';
                }else{
                    board[1][1] = 'O';
                }
                ft = 1;
            } else {
			    computerMove2();
            }
			winner = checkWinner();
			if (winner != ' ' || checkFreeSpaces() == 0) break;
		}
		system("cls");
		printBoard();
		
		NTmp = printWinner(winner, 0);
		if(NTmp == 0) Sauvegarder(winner,2);
		else Sauvegarder(winner,1);

		printf("   Voulez-vous rejouer ? (O/N): ");
		scanf("%c");
		scanf("%c", &response);
		response = toupper(response);
		resetBoard();
	} while (response == 'O');
	printf("   Merci d'avoir joue !\n");
	return 0;
}

void ModeDuJeuSolo(){
	int niveau;
	do{
		system("cls");

		textcolor(couleurs); printf("  +");
		textcolor(restedupage);	printf(" ------------------------------------------------------------------------------------- ");
		textcolor(couleurs); printf("+\n\n");
		header();
		printf("\n\n\t\t\t\t******MODE DE JEU SOLO****** \n\n\t\t\t\t1- Niveau facile\n\n\t\t\t\t2- Niveau moyen\n\n\t\t\t\t3- Retour au menu\n\n");
		textcolor(couleurs); printf("  +");
		textcolor(restedupage);	printf(" ------------------------------------------------------------------------------------- ");
		textcolor(couleurs); printf("+\n\n");
		printf("   Saisir votre choix: ");
		scanf("%d", &niveau);
	} while (niveau < 0 || niveau > 3);
	switch (niveau){
		case 1:
			J2.Num = 1; strcpy(J2.Nom, "Computer"); strcpy(J2.Prenom, "Easy");
			J1 = ajouterJoueur();
			Recup(J1.Num, J2.Num, 1);
			break;
		case 2:
			J2.Num = 2; strcpy(J2.Nom, "Computer"); strcpy(J2.Prenom, "Medium");
			J1 = ajouterJoueur();
			Recup(J1.Num, J2.Num, 2);
			break;
		case 3:
			break;
	}
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
void ModeDuJeuMulti(){
	char winner, response;
	int i;
	unsigned long long int NTmp;
	do{
		winner = ' ';
		response = ' ';
		i = 0;
		while (winner == ' ' && checkFreeSpaces() != 0){
			system("cls");
			printBoard();
			if (i == 0){
            	printf("   C'est le tour du joueur(se) %s %s: \n ", J1.Nom, J1.Prenom);
				playerMove(J1.Pown);
				i = 1;
			}else{
            	printf("   C'est le tour du joueur(se) %s %s: \n ", J2.Nom, J2.Prenom);
				playerMove(J2.Pown);
				i = 0;
			}
			winner = checkWinner();
			if (winner != ' ' || checkFreeSpaces() == 0) break;
		}
		system("cls");
		printBoard();
		// pourquoi ne pas combiner les deux fonctions en une seule ?
		NTmp = printWinner(winner, 1);
		if(NTmp == 0) Sauvegarder(winner,2);
		else Sauvegarder(winner,1);
		printf("   Voulez-vous rejouer ? (O/N): ");
		scanf("%c");
		scanf("%c",&response);
		response = toupper(response);
		resetBoard();
	} while (response == 'O');
	printf("   Merci d'avoir joue !\n");
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
void ModeDuJeuMultijoueurs(){
	system("cls");
	J1 = ajouterJoueur(); J2 = ajouterJoueur();
    Recup(J1.Num, J2.Num, 4);
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
joueurStat*  inserer(unsigned long long n , char no[] , char p[] , int g){
	joueurStat *j1 = (joueurStat *)malloc(sizeof(joueurStat));
	j1->num = n;
	j1->g = g;
	strcpy(j1->Nom , no);
	strcpy(j1->Prenom , p);
	j1->suivant = NULL ; 
	return j1;
}

joueurStat* ajouter(joueurStat *liste, joueurStat* JS){
	joueurStat *actuel = liste, *precedent = NULL;
	if (liste){
		while (actuel != NULL && actuel->g > JS->g){
		precedent = actuel;
		actuel = actuel->suivant;
		}
		if (actuel == NULL){
			precedent->suivant = JS;
		} else {
			JS->suivant = actuel;
			if (precedent){
				precedent->suivant = JS;
			} else {
				liste = JS;
			}
		}	
	} else {
		liste = JS;
	}
	return liste;
}

void stat(){
	Joueur joueur ; 
	int gagner = 0, perdre=0, egalite=0, etat=0 ; 
	unsigned long long int Num1 , Num2 ; 
	FILE *F;
	char a, M[3][3];
	
	printf("   Veuillez entrer le nom complet : ");
	scanf("%s %s",joueur.Nom , joueur.Prenom);
	joueur.Num = rechercher(joueur.Nom, joueur.Prenom);
	if(joueur.Num!=0){
		F=fopen("FichierRecuperation.txt","r");
		while(!feof(F)){
			fscanf(F, "%llu %llu {{%c%c%c},{%c%c%c},{%c%c%c}} %d", &Num1,  &Num2, 
			&M[0][0], &M[0][1], &M[0][2],
			&M[1][0], &M[1][1], &M[1][2],
			&M[2][0], &M[2][1], &M[2][2],
			&etat);		
		if((joueur.Num == Num1 || joueur.Num ==Num2) && etat == 1){
			if(joueur.Num == Num1)gagner++;
			if(joueur.Num == Num2)perdre++;
		}
	}
	system("cls");
	
	gotoxy1(2,0); textcolor(couleurs); printf("+");
	textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
	textcolor(couleurs); printf("+");

	gotoxy1(2,1); textcolor(restedupage); printf("|"); textcolor(couleurs); printf(" %s %s", joueur.Nom, joueur.Prenom); gotoxy1(90,1); textcolor(restedupage); printf("|");
	gotoxy1(2,2); textcolor(couleurs); printf("+");
	textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
	textcolor(couleurs); printf("+");
	gotoxy1(2,3); textcolor(restedupage); printf("|"); textcolor(couleurs); printf(" Gagne"); gotoxy1(32,3); textcolor(restedupage); printf("|"); textcolor(couleurs); printf(" Perte"); gotoxy1(62,3); textcolor(restedupage); printf("|"); textcolor(couleurs); printf(" Egalite"); gotoxy1(90,3); textcolor(restedupage); printf("|");
	gotoxy1(2,4); textcolor(couleurs); printf("+");
	textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
	textcolor(couleurs); printf("+");
	gotoxy1(2,5); textcolor(restedupage); printf("|"); textcolor(couleurs); printf(" %d", gagner); gotoxy1(32,5); textcolor(restedupage); printf("|"); textcolor(couleurs); printf(" %d", perdre); gotoxy1(62,5); textcolor(restedupage); printf("|"); textcolor(couleurs); printf(" %d", egalite); gotoxy1(90,5); textcolor(restedupage); printf("|");
	gotoxy1(2,6); textcolor(couleurs); printf("+");
	textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
	textcolor(couleurs); printf("+");

	}else{
		printf("   Ce joueur n'existe pas \n"); 
		stat();
	}
 
	do{
		printf("\n   Voulez vous selectionnez un autre joueur? (1 pour oui 0 pour retourner au menu): ");
		scanf("%c",&a);
		if(a== '1')	stat();
		if(a=='0')	menu();
	}while(a != '1' && a != '0');
	
	fclose(F);
}

int gag(unsigned long long int num){
    FILE *f = fopen("FichierRecuperation.txt","r+");
    unsigned long long int num1 , num2 ;
    int etatj , gagner =0 ; 
    char M[3][3];
    while(!feof(f)){
    	fscanf(f, "%llu %llu {{%c%c%c},{%c%c%c},{%c%c%c}} %d", &num1,  &num2, // fscanf & la sensibilisation a l'espace
			&M[0][0], &M[0][1], &M[0][2],
			&M[1][0], &M[1][1], &M[1][2],
			&M[2][0], &M[2][1], &M[2][2],
			&etatj);
			
			if(num == num1 && etatj ==1 ){
				gagner++;
			}
	}
	fclose(f);
	return gagner ;	
}

void stat_G(){
	joueurStat *j = NULL ; 
	FILE *fp;
	int i = 1 ;
	
	int gagnant;
	char nom[100] ,  prenom[100];
	unsigned long long nume;
	fp = fopen("Joueurs.txt","r+");
		while(fscanf( fp , "%llu %s %s" ,&nume ,nom,prenom) == 3){
		gagnant = gag(nume);
		j = ajouter(j,inserer(nume,nom,prenom,gagnant)) ;
	}
	gotoxy1(2,0); textcolor(couleurs); printf("+");
	textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
	textcolor(couleurs); printf("+");
	textcolor(restedupage); gotoxy1(2,1); printf("|"); textcolor(couleurs); printf(" Rang"); gotoxy1(11,1); textcolor(restedupage); printf("|"); textcolor(couleurs); printf(" Nom complet"); gotoxy1(61,1); textcolor(restedupage); printf("|"); textcolor(couleurs); printf(" Match remporte"); textcolor(restedupage); gotoxy1(90,1); printf("|");
	gotoxy1(2,2); textcolor(couleurs); printf("+");
	textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
	textcolor(couleurs); printf("+");

	while (j!=NULL){
		textcolor(restedupage); gotoxy1(2,i*2+1); printf("|"); textcolor(couleurs); printf(" %d", i); gotoxy1(11,i*2+1); textcolor(restedupage); printf("|"); textcolor(couleurs); printf("%s %s", j->Nom , j->Prenom); gotoxy1(61,i*2+1); textcolor(restedupage); printf("|"); textcolor(couleurs); printf("%d", j->g); textcolor(restedupage); gotoxy1(90,i*2+1); printf("|");
		textcolor(couleurs); gotoxy1(2,i*2+2); printf("+");
		textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
		textcolor(couleurs); printf("+");
		i++;
		j=j->suivant;
	}
	
    char a ;
	printf("\n   Tapez 0 pour retourner: ");
	do{
		scanf("%c",&a);
		if(a=='0'){
			statistiques();
		}
	}while(a != '1' && a != '0');
}

void statistiques(){
	int Choix;	
	do{
		system("cls");
		textcolor(couleurs); printf("  +");
		textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
		textcolor(couleurs); printf("+\n\n");
		header();
		printf("\n\n\t\t\t\t*********STATISTIQUES********* \n\n\t\t\t\t1- Statistiques personnelles\n\n\t\t\t\t2- Statistiques globales\n\n\t\t\t\t3- Retour\n\n");
		textcolor(couleurs); printf("  +");
		textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
		textcolor(couleurs); printf("+\n\n");
		printf("   Saisir votre choix: ");
		scanf("%d", &Choix);
	} while (Choix < 1 || Choix > 3);
	system("cls");
	switch (Choix){
		case 1:
			stat();
			break;
		case 2:
		    stat_G();
			break;
		case 3:
			break;
	}
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
void aide(){
	system("cls");
	textcolor(couleurs); printf("  +");
	textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
	textcolor(couleurs); printf("+\n\n");
	header();
	printf("\n\n");
	textcolor(couleurs); printf("    Le Tic-Tac-Toe en general:\n");
	textcolor(restedupage);printf("      Le tic-tac-toe, aussi appele « morpion » est un jeu de reflexion se pratiquant\n");
	printf("        a deux joueurs, tour par tour, dont le but est de creer le premier un alignement.\n\n");
    textcolor(couleurs); printf("    Les regles:\n");
	textcolor(restedupage);printf("      Deux joueurs s'affrontent. Ils doivent remplir chacun a leur tour une case\n");
	printf("        de la grille de taille (3X3) avec le symbole qui leur est attribue : O ou X.\n");
	printf("      Le gagnant est celui qui arrive a aligner trois symboles identiques, horizontalement,\n");
	printf("        verticalement ou en diagonale. Il est coutume de laisser le joueur jouant X\n");
	printf("        effectuer le premier coup de la partie.\n\n");
	textcolor(couleurs); printf("    Options disponibles, Ce jeu offre diverses options aux joueurs:\n");
	textcolor(restedupage);printf("      I- Jouer en mode solo : Ce mode permet aux joueurs de jouer contre l'ordinateur.\n");
	printf("        Il y a deux niveaux (facile et moyen) et le joueur choisit le niveau qui \n");
	printf("        lui convient le mieux. \n");
	printf("      II- Jouer en mode multijoueur : Ce mode permet a deux joueurs de jouer l'un contre\n");
	printf("        l'autre.\n");
	printf("      III- Statistiques : Le jeu fournit des statistiques sur le joueur, et il peut\n");
	printf("        egalement connaître son rang.\n");
	printf("      IV- Modification de l'apparence : Le jeu propose de choisir entre l'une des quatre\n");
	printf("        apparences disponibles pour assurer le confort du joueur.\n\n");
    textcolor(couleurs); printf("    Mode de jeu:\n");
	textcolor(restedupage);printf("      Le jeu demande aux joueurs de se presenter en premier.\n");
	printf("      La position dans laquelle le joueur placera son jeton est determinee en entrant\n");
	printf("        le numero de ligne puis le numero de colonne.\n");
	printf("      Si le joueur n'a pas termine son dernier match, la prochaine fois, le jeu proposera\n");
	printf("        de le continuer ou de commencer un nouveau match.\n");
	printf("      Pour quitter le match avant qu'il ne se termine, le joueur doit entrer 0\n");
	printf("        dans le champ des lignes et aussi dans le champ des colonnes.\n");
	textcolor(couleurs); printf("  +");
	textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
	textcolor(couleurs); printf("+\n");
	textcolor(restedupage); printf("      Ce jeu a ete programme et developpe par SOUD Kaoutar, BASLIH Anas, OULEMHOUR\n");
	printf("        Reda et sous la supervision de M. GAROUANI Moncef dans le cadre de la realisation\n");
	printf("        du projet C - EILCO 2022-2023\n");
	textcolor(couleurs); printf("  +");
	textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
	textcolor(couleurs); printf("+\n\n");

	printf("      Tapez n'importe quelle touche pour revenir au menu: ");
	char b;
	scanf("%c");
	scanf("%c", &b);
}

void MenuColor(){
	int theme;
	do{
		system("cls");
		textcolor(couleurs); printf("  +");
		textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
		textcolor(couleurs); printf("+\n\n");
		header();
		printf("\n\n\t\t\t\t***PARAMETRE DE GRAPHIQUE*** \n\n\t\t\t\t1- Premier theme (par defaut)\n\n\t\t\t\t2- Deuxieme heme\n\n\t\t\t\t3- Troixieme theme\n\n\t\t\t\t4- Quatrieme theme\n\n\t\t\t\t5- Retour\n\n");
		textcolor(couleurs); printf("  +");
		textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
		textcolor(couleurs); printf("+\n\n");
		printf("   Saisir votre choix: ");
		scanf("%d", &theme);
	} while (theme < 0 || theme > 5);
	switch (theme){
		case 1:
			system("COLOR 0F");
			couleurs=15;
			textcolor(15);
			restedupage=15;
			textcolor(15);
			break;
		case 2:
			system("COLOR E3"); 
			couleurs=8;
			textcolor(8);
			restedupage=227;
			textcolor(227);
			break;
		case 3:
			system("COLOR F6"); 
			couleurs=5;
			textcolor(5);
			restedupage=246;
			textcolor(246);
			break;
		case 4:
			system("COLOR D0");
			couleurs=14;
			textcolor(14);
			restedupage=208;
			textcolor(208);
			break;
		case 5:
			break;
	}
}

void header(){
	textcolor(couleurs);
	printf("\t   /$$      /$$  /$$$$$$ ");textcolor(couleurs);printf("  /$$$$$$$  ");textcolor(restedupage);printf("/$$$$$$$ /$$$$$$  /$$$$$$  /$$   /$$\n");
	textcolor(couleurs);
	printf("\t  | $$$    /$$$ /$$__  $$|");textcolor(couleurs);printf(" $$__  $$| $$_");textcolor(restedupage);printf("_  $$ |_ $$_/ /$$__  $$| $$$ | $$\n");
	textcolor(couleurs);
	printf("\t  | $$$$  /$$$$| $$  \\ $$|");textcolor(couleurs);printf(" $$  \\ $$| $$");textcolor(restedupage);printf("  \\ $$  | $$  | $$  \\ $$| $$$$| $$\n");
	textcolor(couleurs);
	printf("\t  | $$ $$/$$ $$| $$  | $$|");textcolor(couleurs);printf(" $$$$$$$/| $$$$$$$/");textcolor(restedupage);printf("  | $$  | $$  | $$| $$ $$ $$\n");
	textcolor(couleurs);
	printf("\t  | $$  $$$| $$| $$  | $$|");textcolor(couleurs);printf(" $$__  $$| $$____/ ");textcolor(restedupage);printf("  | $$  | $$  | $$| $$  $$$$\n");
	textcolor(couleurs);
	printf("\t  | $$\\  $ | $$| $$  | $$|");textcolor(couleurs);printf(" $$  \\ $$| $$");textcolor(restedupage);printf("        | $$  | $$  | $$| $$\\  $$$\n");
	textcolor(couleurs);
	printf("\t  | $$ \\/  | $$|  $$$$$$/ ");textcolor(couleurs);printf("|$$  | $$| $$");textcolor(restedupage);printf("       /$$$$$$|  $$$$$$/| $$ \\  $$\n");
	textcolor(couleurs);
	printf("\t  |__/     |__/ \\______/");textcolor(couleurs);printf("|__/  |__/|__/");textcolor(restedupage);printf("       |______/ \\______/ |__/  \\__/\n");
}

void menu(){

	int Choix;
	// nettoyer tout ce qui est ecrit dans la console
	resetBoard();
	do{
		system("cls");
		textcolor(couleurs); printf("  +");
		textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
		textcolor(couleurs); printf("+\n\n");
		header();
		printf("\n\n\t\t\t\t************MENU************\n\n\t\t\t\t1- Mode de jeu solo\n\n\t\t\t\t2- Mode de jeu multijoueur\n\n\t\t\t\t3- Statistiques\n\n\t\t\t\t4- Parametre de graphique\n\n\t\t\t\t5- Aide\n\n\t\t\t\t6- Quitter le jeu\n\n");
		textcolor(couleurs); printf("  +");
		textcolor(restedupage); printf(" ------------------------------------------------------------------------------------- ");
		textcolor(couleurs); printf("+\n\n");
		printf("   Saisir votre choix: ");
		scanf("%d", &Choix);
	} while (Choix < 1 || Choix > 6);
	switch (Choix){
		case 1:
			ModeDuJeuSolo();
			break;
		case 2:
			ModeDuJeuMultijoueurs();
			break;
		case 3:
			statistiques();
			break;
		case 4:
			MenuColor();
			break;
		case 5:
			aide();
			break;
		case 6:
			exit(1);
			break;
	}
	menu();
}
