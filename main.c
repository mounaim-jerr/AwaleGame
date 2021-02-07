#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
struct player
{
    char firstName [20];
    int scorePlayer;
    int position ;
};
struct game
{
    struct player next;
    struct player current ;
    int scoreFinalHigh;
    int scoreFinalLow;
    struct player playerHigh;
    struct player playerLow;
};
struct cases
{
    int lignes;
    int collones;
};
int verFin (int lignes,int collones, int tab[lignes][collones]);
bool verGrain (int lignes,int collones, int tab[lignes][collones]);
int collect ( int ligne, int lastCase,int tab[2][6]);
struct cases moveGrain ( int ligne, int firstCase, int tab[2][6]);
struct game turnFun (struct game);
int display (int lignes, int collones,int tab[lignes][collones] );
int init(int lignes,int collones,int tab[lignes][collones]);
main ()
{
    int playOrWatch =0;
    int lignes=2;
    int collones=6;
    int tab [lignes][collones];
    int playCase=0;
    int totalGrain =1;
    struct player playerHigh = {playerHigh.firstName,playerHigh.position,0};
    struct game gameAwale   = { gameAwale.next,gameAwale.current, gameAwale.scoreFinalHigh,gameAwale.scoreFinalLow,playerHigh, gameAwale.playerLow };
    struct cases awaleCases = {awaleCases.lignes,awaleCases.collones};
    printf("\n press 1 to watch the last game \n ");
    scanf("%d",&playOrWatch);
    if (playOrWatch==0){
      printf ("player high : please write your name\n");
    scanf ("%s", &gameAwale.playerHigh.firstName);
    printf ("\n");
    printf ("player low : please write your name\n");
    scanf ("%s", &gameAwale.playerLow.firstName);
    }
    gameAwale.playerHigh.position=0;
    gameAwale.playerLow.position=1;
    gameAwale.current=gameAwale.playerHigh;
    gameAwale.next=gameAwale.playerLow;
    gameAwale.playerHigh.scorePlayer=0;
    gameAwale.playerLow.scorePlayer=0;
    init(lignes,collones,tab);
    display(lignes,collones,tab);
    int i=0;
    FILE *lowFile ;
    FILE *highFile ;
    if(playOrWatch==0)
    {

    lowFile = fopen("lowFile.txt","w") ;
    if (lowFile==NULL)
    {
        printf("error\n") ;
        exit(1) ;
    }
    highFile = fopen ("highFile.txt","w") ;
    if (highFile== NULL)
    {
        printf("error\n") ;
        exit(1) ;
    }
    }
    else{
    lowFile = fopen("lowFile.txt","r") ;
    if (lowFile==NULL)
    {
        printf("error\n") ;
        exit(1) ;
    }
    highFile = fopen ("highFile.txt","r") ;
    if (highFile== NULL)
    {
        printf("error\n") ;
        exit(1) ;
    }
    }
     while (gameAwale.playerHigh.scorePlayer+gameAwale.playerLow.scorePlayer!=48)
    // while (i!=10)
    {
        i++;
        gameAwale = turnFun (gameAwale);
       // printf (" \n %s choose a case please \n", gameAwale.current.firstName);
        if(playOrWatch!=0)
            {
                if(gameAwale.current.position==1)
                {
                 fscanf(lowFile,"%d",&playCase);
                 fseek(lowFile, +1, SEEK_CUR);
                 printf("\n player low play case :%d\n",playCase);
                 Sleep(1000);
                }
                if(gameAwale.current.position==0)
                {
                   fscanf(highFile,"%d",&playCase);
                   fseek(highFile, +1, SEEK_CUR);
                   printf("\n player high play case :%d\n",playCase);
                   Sleep(1000);
                }
            }
            else{
                printf (" \n %s choose a case please \n", gameAwale.current.firstName);
                scanf ("%d", &playCase);
            }
        while (playCase<0 || playCase>5)
        {
            printf("you must choose a case between 0 and 5 : \n");
            scanf("%d",&playCase);
        }
        while (tab[gameAwale.current.position][playCase]==0)
        {
            printf("you cant choose an empty case \n try again please :\n");
            scanf("%d",&playCase);
        }
        if (gameAwale.current.position==0)
        {
            fprintf(highFile,"%d\n",playCase);
        }
        if (gameAwale.current.position==1)
        {
            fprintf(lowFile,"%d\n",playCase);
        }
        struct cases awaleCases=moveGrain(gameAwale.current.position,playCase,tab);
        if (awaleCases.lignes==gameAwale.next.position)
        {
            int nbrGraines = collect( awaleCases.lignes,awaleCases.collones,tab);
            if (gameAwale.current.position==0)
            {
                gameAwale.playerHigh.scorePlayer+=nbrGraines;
            }
            if (gameAwale.current.position==1)
            {
                gameAwale.playerLow.scorePlayer+=nbrGraines;
            }
        }
        if (verGrain(gameAwale.current.position,collones,tab)==true )
        {
            int restScore = verFin (gameAwale.next.position,collones,tab);
            printf("GAME OVER\n");
            if (restScore!=0)
            {
                if (gameAwale.next.position==0)
                {
                    gameAwale.playerHigh.scorePlayer+=restScore;
                }
                if(gameAwale.next.position==1)
                {
                    gameAwale.playerLow.scorePlayer+=restScore;
                }
            }

        }
        printf("player high score: %d\n",gameAwale.playerHigh.scorePlayer);
        printf("player low score: %d\n",gameAwale.playerLow.scorePlayer);
        display(lignes,collones,tab);

    }

    fclose(lowFile);
    fclose(highFile);
}
int collect ( int ligne,  int lastCase,int tab[2][6]  )
{
    int cllt;
    int nbrGraines=0;
    cllt = ligne ==0 ? 1 :-1 ;
    if (ligne==0)
    {
        for (int i=lastCase ; i<6 ; i=i+cllt)
        {
            if ((tab[ligne][i]==2) || (tab[ligne][i]==3))
            {
                nbrGraines+=tab[ligne][i];
                tab[ligne][i]=0;
            }
            else
            {
                i=6;
            }
        }
    }
    if (ligne==1)
    {
        for (int i = lastCase;  i>=0 ; i=i+cllt)
        {
            if ((tab [ligne][i]==2) || (tab[ligne][i]==3))
            {
                nbrGraines+=tab[ligne][i];
                tab[ligne][i]=0;
            }
            else
            {
                i=-1;
            }
        }
    }
    return  nbrGraines ;
}
struct cases moveGrain ( int ligne, int firstCase,int tab [2][6] )
{
    struct cases awaleCases ;
    int nombreDeGraines ;
    nombreDeGraines=tab[ligne][firstCase];
    tab[ligne][firstCase]=0;
    int incr;
    incr = ligne ==0 ? 1 :-1 ;
    for (int j=0 ; j<nombreDeGraines; j++)
    {
        firstCase=firstCase-incr;
        if (firstCase<0)
        {
            ligne=1;
            incr=-1;
            firstCase=0;
        }
        if (firstCase>5)
        {
            ligne=0;
            incr=1;
            firstCase=5;
        }
        tab[ligne][firstCase]++;
        awaleCases.collones=firstCase;
        awaleCases.lignes=ligne;
    }
    return awaleCases;
}
int init(int lignes,int collones,int tab[lignes][collones])
{
    for (int i=0 ; i<lignes ; i++)
    {
        for(int j=0 ; j<collones ; j++)
        {
            if (i==0)
            {
                if (j==0)
                {
                    tab[i][j]=4;
                }
                else
                {
                    tab[i][j]=4;
                }
            }
            else
            {
                if (j==5)
                {
                    tab[i][j]=4;
                }
                else
                {
                    tab[i][j]=4;
                }
            }
        }
    }
}
int display (int lignes, int collones,int tab[lignes][collones] )
{
    for (int i=0 ; i<lignes ; i++)
    {
        for (int j =0 ; j<collones ; j++)
        {
            printf("| %d ",tab[i][j]);
        }
        if (i==0)
        {
            printf("\n");
            printf("_______________________\n");
        }
    }
}
struct game turnFun (struct game gameA )
{
    struct player temp = gameA.current;
    gameA.current=gameA.next;
    gameA.next=temp;
    return gameA;
}
// TODO  (return bool)
bool verGrain (int lignes,int collones, int tab[lignes][collones])
{
    int totalGrain=0;
//if (gameA.playerHigh.scorePlayer>24||gameA.playerLow.scorePlayer>24)
    for (int i =0 ; i<6 ; i++)
    {
        totalGrain+=tab[lignes][i];
    }
    if (totalGrain==0)
    {
        return true ;
    }
    else
    {
        return (false);
    }
}
int verFin (int lignes,int collones, int tab[lignes][collones])
{
    int score =0;
    int j=0;
    if (lignes==0)
    {
        for (int i=0 ; i<6 ; i++)
        {
            if (tab[lignes][i]<=i)
            {
                j++;
            }
        }
        if (j==6)
        {
            for(int i =0 ; i<6; i++)
            {
                score+=tab[lignes][i];
                tab[lignes][i]=0;
            }
        }
    }
    if (lignes==1)
    {
        for (int i=0 ; i<6 ; i++)
        {
            if (tab[lignes][i]<6-i)
            {
                j++;
            }
        }
        if (j==6)
        {
            for(int i =0 ; i<6; i++)
            {
                score+=tab[lignes][i];
                tab[lignes][i]=0;
            }
        }
    }
    return score ;
}

/*int getCaseToPlay ( int ligne, int tab[2][6])
{
    int caseIndex=-1 ;
    if (ligne ==0)
    {
        for (int i=0 ; i<6 ; i++)
        {
            int var = ligne==0 ? i+1 : 6-i ;
            if (tab[ligne][i]>var)
            {
                caseIndex=i;
            }
        }
    }
    return caseIndex ;
}
*/




