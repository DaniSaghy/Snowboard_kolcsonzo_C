#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
//#include <stdbool.h>

/*typedef enum bool {
	false = 0, true = 1
} bool;*/

/*typedef int bool;
#define true 1;
#define false 0;*/

typedef struct snowboard{
    char azonosito[6];
    int hossz;
    double szelesseg;
    int ev;
    int napok;
    struct snowboard *kov; //következõ snowboardra mutató pointer
    struct snowboard *berlo;  //A boardot kivérlő személyre mutató pointer
}snowboard;

// snowboard *head_board = NULL;

/* C tm:
tm_sec	int	seconds after the minute	0-60*
tm_min	int	minutes after the hour	0-59
tm_hour	int	hours since midnight	0-23
tm_mday	int	day of the month	1-31
tm_mon	int	months since January	0-11
tm_year	int	years since 1900
tm_wday	int	days since Sunday	0-6
tm_yday	int	days since January 1	0-365
tm_isdst int Daylight Saving Time flag */

typedef struct datum{
	int ev;
	int honap;
	int nap;
}datum;

typedef struct berles{
	datum kezdete;
	datum vege;
}berles;

typedef struct nev{
    char vezeteknev[20];
    char keresztnev[20];
}nev;

typedef struct berlo{
    nev neve;
	int testtomeg;
	int testmagassag;
	double labmeret;
	char szint[15];
	berles berles_idotartama;
	char azonosito[6];
	struct berlo *kovetkezo_berlo;
	struct berlo *kov_berles;
}berlo;

//berlo *head_berlo = NULL;

int bereles_idotartama(berles berles1)
{
    double diffsec = 0.0;
    int berelt_napok = 0;
	time_t tm1; 
	time_t tm2;
    //struct tm d1, d2
    time_t rawtime;
    //time ( &rawtime ); //Jelenlegi ido
    struct tm *timeinfo1 = localtime ( &rawtime ); //Convert time_t to tm as local time
    struct tm *timeinfo2 = localtime ( &rawtime ); //Convert time_t to tm as local time
	time ( &rawtime );
    timeinfo1->tm_year = berles1.kezdete.ev - 1900;
    timeinfo1->tm_mon = berles1.kezdete.honap - 1;
    timeinfo1->tm_mday = berles1.kezdete.nap;
    tm1 = mktime(timeinfo1 ); //Convert tm structure to time_t
    //printf("time_t tm1 : %ld\n", tm1);

    timeinfo2->tm_year = berles1.vege.ev - 1900;
    timeinfo2->tm_mon = berles1.vege.honap - 1;
    timeinfo2->tm_mday = berles1.vege.nap;
    tm2 = mktime(timeinfo1 ); //Convert tm structure to time_t
    //printf("time_t tm2 : %ld\n", tm2);

    diffsec = difftime(tm2, tm1);
    //printf("diffsec B : %lf\n", diffsec);
    berelt_napok = (int)((diffsec/24.0)/3600.0);
    //printf("eltelt napok : %d\n", berelt_napok);
    return berelt_napok;
}

snowboard* board_beolvas()
{
    char azonosito[6];
    int hossz;
    double szelesseg;
    int ev;
    int napok;
    snowboard *board, *elozo;
    snowboard *head_board = NULL;
    FILE *f;
	//f = fopen("C:\\temp\\board.txt","r");
	f = fopen("board.txt","r");
	while(fscanf(f," %s %d %lf %d %d",azonosito ,&hossz, &szelesseg, &ev, &napok) != EOF)
    {
	//fscanf(f,"%s %d %lf %d %d",azonosito ,&hossz, &szelesseg, &ev, &napok);
        board = (snowboard*)malloc(sizeof(snowboard));
        strcpy(board->azonosito,azonosito);
        board->hossz=hossz;
        board->szelesseg=szelesseg;
        board->ev=ev;
        board->napok=napok;
        board->kov=NULL;
        board->berlo=NULL;
        if(head_board == NULL )
        {
            head_board = board;
        }
        else
        {
            elozo->kov=board;
        }
        elozo = board;
    }
    return head_board;
}

snowboard board_beker()
{
    snowboard ujboard;
    printf("Azonosito: ");
    scanf("%s", ujboard.azonosito);
    printf("Hossz: ");
    scanf("%d", &ujboard.hossz);
    printf("Szelesseg: ");
    scanf("%lf", &ujboard.szelesseg);
    printf("Ev: ");
    scanf("%d", &ujboard.ev);
    printf("Napok: ");
    scanf("%d", &ujboard.napok);
    return ujboard;
}

void board_hozzaad(snowboard *head_board, snowboard uj_board)
{
    snowboard *board, *p_uj_board;
    for(board = head_board; board->kov != NULL; board=board->kov);
    p_uj_board = (snowboard*)malloc(sizeof(snowboard));
    board->kov = p_uj_board;
    strcpy(p_uj_board->azonosito,uj_board.azonosito);
    p_uj_board->hossz=uj_board.hossz;
    p_uj_board->szelesseg=uj_board.szelesseg;
    p_uj_board->ev=uj_board.ev;
    p_uj_board->napok=uj_board.napok;
    p_uj_board->kov=NULL;
    p_uj_board->berlo=NULL;
}

snowboard* board_torol(snowboard *head_board, char *azonosito)
{
	char *azon;
    snowboard *board, *elozo, *kovetkezo;
    if(strcmp(head_board->azonosito,azonosito)==0)
    {
        elozo =head_board;
        head_board = head_board->kov;
        free(elozo);
        printf("Sikeres torles: %s\n",azonosito);
        return head_board;
    }
    for(board = head_board; board->kov != NULL; board=board->kov)
    {
        kovetkezo = board->kov;  //B
        azon=kovetkezo->azonosito;
        if(strcmp(azon,azonosito)==0)
        {
            //kovetkezo =board->kov;
            board->kov = kovetkezo->kov; //B to C
            free(kovetkezo);
            printf("Sikeres torles: %s\n",azonosito);
            break;
        }
    }

    return head_board;
}
void board_kiir(snowboard *board)
{
    printf("%s %4d %5.1lf %5d %4d \n",board->azonosito,board->hossz,board->szelesseg,board->ev,board->napok);
}

void board_listaz(snowboard *head_board)
{
    //printf("%s\n",head->azonosito);
    //board_beolvas();
    //printf("%p\n",head_board);
    snowboard *board;
    for(board = head_board; board != NULL; board=board->kov)
    {
        board_kiir(board);
    }
}

void felszabadit()
{
    //todo
}

berlo* berlo_beolvas()
{
    nev neve;
	int testtomeg;
	int testmagassag;
	double labmeret;
	char szint[15];
	//char veznev[20];
	//char kernev[20];
	berles berles_idotartama;
	char azonosito[6];
    berlo *berlo1, *elozo_berlo;
    berlo *head_berlo = NULL;
    FILE *f;
	//f = fopen("C:\\temp\\berlok.txt","r");
	f = fopen("berlok.txt","r");
	while(fscanf(f," %s %s %d %d %lf %s %d %d %d %d %d %d %s",
               neve.vezeteknev,
               neve.keresztnev,
               &testtomeg,
               &testmagassag,
               &labmeret,
               szint,
               &berles_idotartama.kezdete.ev, &berles_idotartama.kezdete.honap, &berles_idotartama.kezdete.nap,
               &berles_idotartama.vege.ev, &berles_idotartama.vege.honap, &berles_idotartama.vege.nap,
               azonosito)
              != EOF)
    {
        berlo1 = (berlo*)malloc(sizeof(berlo));
        //printf("vezeteknev: %s\n",veznev);
        strcpy(berlo1->neve.vezeteknev,neve.vezeteknev);
        strcpy(berlo1->neve.keresztnev,neve.keresztnev);
        berlo1->testtomeg=testtomeg;
        berlo1->testmagassag=testmagassag;
        berlo1->labmeret=labmeret;
        strcpy(berlo1->szint,szint);
        berlo1->berles_idotartama=berles_idotartama;
        strcpy(berlo1->azonosito,azonosito);
        berlo1->kovetkezo_berlo=NULL;
        berlo1->kov_berles=NULL;
        //berlo_listaz(berlo1);
        if(head_berlo == NULL )
        {
            head_berlo = berlo1;
        }
        else
        {
            elozo_berlo->kovetkezo_berlo=berlo1;            //megkerdezni!!
        }
        elozo_berlo = berlo1;
    }
    return head_berlo;
}

berlo* berlo_beker()
{
    berlo *uj_berlo;
    uj_berlo = (berlo*)malloc(sizeof(berlo));
    printf("Vezeteknev:   ");
    scanf("%s",  uj_berlo->neve.vezeteknev);
    printf("Keresztnev:   ");
    scanf("%s",  uj_berlo->neve.keresztnev);
    printf("Testtomeg:    ");
    scanf("%d", &uj_berlo->testtomeg);
    printf("Testmagassag: ");
    scanf("%d", &uj_berlo->testmagassag);
    printf("Labmeret:     ");
    scanf("%lf",&uj_berlo->labmeret);
    printf("Szint:        ");
    scanf("%s",  uj_berlo->szint);
    printf("Berles idotartama (Formatum EEEE HH NN):\n");
    printf("  Kezdete:    ");
    scanf("%d %d %d",&uj_berlo->berles_idotartama.kezdete.ev, &uj_berlo->berles_idotartama.kezdete.honap, &uj_berlo->berles_idotartama.kezdete.nap);
    printf("  Vege:       ");
    scanf("%d %d %d",&uj_berlo->berles_idotartama.vege.ev, &uj_berlo->berles_idotartama.vege.honap, &uj_berlo->berles_idotartama.vege.nap);
    strcpy(uj_berlo->azonosito,"");
    uj_berlo->kovetkezo_berlo=NULL;
    uj_berlo->kov_berles=NULL;
    return uj_berlo;
}

void berlo_hozzaad(berlo *head_berlo, berlo *uj_berlo)
{
    berlo *berlo1;
    for(berlo1 = head_berlo; berlo1->kovetkezo_berlo != NULL; berlo1=berlo1->kovetkezo_berlo);
    berlo1->kovetkezo_berlo=uj_berlo;
}

berlo* berlo_torol(berlo *head_berlo, nev neve)
{
    //todo kov_berles
	nev nev1;
    berlo *berlo1, *elozo_berlo, *kovetkezo;
    if(strcmp(head_berlo->neve.vezeteknev,neve.vezeteknev)==0 &&strcmp(head_berlo->neve.keresztnev,neve.keresztnev)==0)
    {
        elozo_berlo = head_berlo;
        head_berlo = head_berlo->kovetkezo_berlo;
        free(elozo_berlo);
        return head_berlo;
    }
    for(berlo1 = head_berlo; berlo1->kovetkezo_berlo != NULL; berlo1=berlo1->kovetkezo_berlo)
    {
        kovetkezo = berlo1->kovetkezo_berlo;  //B
        
        strcpy(nev1.vezeteknev,kovetkezo->neve.vezeteknev);
        strcpy(nev1.keresztnev,kovetkezo->neve.keresztnev);
        if(strcmp(nev1.vezeteknev,neve.vezeteknev)==0 &&strcmp(nev1.keresztnev,neve.keresztnev)==0 )
        {
            berlo1->kovetkezo_berlo = kovetkezo->kovetkezo_berlo; //B to C
            free(kovetkezo);
            break;
        }
    }
    //todo freee
    return head_berlo;
}

void berlo_kiir(berlo *berlo1)
{
    datum kezdet = berlo1->berles_idotartama.kezdete;
    datum veg = berlo1->berles_idotartama.vege;
    printf("%20s %20s", berlo1->neve.vezeteknev,berlo1->neve.keresztnev);
    //printf("%s\n", berlo1->neve.vezeteknev);
    printf("%3d ", berlo1->testtomeg);
    printf("%3d ", berlo1->testmagassag);
    printf("%3.1lf ", berlo1->labmeret);
    printf("%15s ", berlo1->szint);
    printf("%4d.%2d.%2d - %4d.%2d.%2d",kezdet.ev, kezdet.honap, kezdet.nap, veg.ev, veg.honap, veg.nap);
    printf("%6s\n", berlo1->azonosito);
}

void berlok_listaz(berlo *head_berlo)
{
    berlo *berlo1;
    for(berlo1 = head_berlo; berlo1 != NULL; berlo1=berlo1->kovetkezo_berlo)
    {
        berlo_kiir(berlo1);
    }
}

int napi_egysegar(snowboard board1)
{
    int ar;
    ar = 5000-((2016-board1.ev)*board1.napok);
    if(ar<1500)
        return 1500;
    else
        return ar;
}

datum datum_beolvas()
{
    datum datum1;
    int ev;
    int honap;
    int nap;
    scanf("%d %d %d", &datum1.ev, &datum1.honap, &datum1.nap);
    return datum1;
}

double labmeret_atvalto(double meret)
{
    double meret1;
    double cm;
    FILE *f;
    //f = fopen("C:\\temp\\labmeretek.txt","r");
    f = fopen("labmeretek.txt","r");
    while(fscanf(f,"%lf %lf",&meret1, &cm) != EOF)
    {
        if(meret == meret1)
        {
            fclose(f);
            return cm;
        }
    }
    return 0;
}

void leselejtezendo(snowboard *head_board)
{
    int x;
    snowboard *board;
    printf("Adja meg milyen evet irunk!\n");
    scanf("%d",&x);
    for(board = head_board; board->kov != NULL; board=board->kov)
    {
        if(board->ev <= x-10)
                printf("%s %d %lf %d %d \n",board->azonosito,board->hossz,board->szelesseg,board->ev,board->napok);
    }
}

snowboard* legtobbet_berelt_deszka(snowboard *head_board)
{
    int max = 0;
    snowboard *board;
    snowboard *maxboard;
    printf("A legtobbet berelt deszka\n");
    for(board = head_board; board->kov != NULL; board=board->kov)
    /*{
        if(board->napok > max)
            maxboard = board;
    }*/
    {
        if(board->napok > max)
        {
            max = board->napok;
            maxboard = board;
        }
    }
    return maxboard;
}

int board_szabad(snowboard *board, berlo *berlo2)
{
    //bool ret = false;
    //berlo *berlo1 = board->berlo;
	berlo *berlo1;
    datum kezd2 = berlo2->berles_idotartama.kezdete;
    datum veg2 = berlo2->berles_idotartama.vege;
	datum kezd1 = berlo1->berles_idotartama.kezdete;
    datum veg1 = berlo1->berles_idotartama.vege;
    for(berlo1 = board->berlo; board->berlo != NULL; berlo1 = berlo1->kovetkezo_berlo)
    {
        
        if(veg2.ev < kezd1.ev || veg2.honap < kezd1.honap || veg2.nap < kezd1.nap)
        {
            //return true;
        }
        else if(veg1.ev < kezd2.ev || veg1.honap < kezd2.honap || veg1.nap < kezd2.nap)
        {
            //return true;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

int fesus_lista_befuzes(snowboard *head_board, berlo *berlo1)
{
	snowboard *board1;
    berlo *fesu_fog;
    for(board1 = head_board; board1 != NULL; board1 = board1->kov)
    {
        if(strcmp(berlo1->azonosito,board1->azonosito)==0)
        {
            fesu_fog = board1->berlo;
            board1->berlo = berlo1;
            berlo1->kov_berles = fesu_fog;
            //printf("%s %s\n", board1->azonosito, berlo1->neve.vezeteknev);
            return 1;
        }
    }
    return 0;
}

void fesus_lista_inditas(snowboard *head_board, berlo *head_berlo)
{
	berlo *berlo1;
    berlo *fesu_fog;
    for(berlo1 = head_berlo; berlo1 != NULL; berlo1 = berlo1->kovetkezo_berlo)
    {
        if (!fesus_lista_befuzes(head_board, berlo1))
        {
           printf("Nem talalhato a megadott snowboard azonosito : %s\n", berlo1->azonosito);
        }
    }
}

void fesus_lista_listazas(snowboard *head_board)
{
	snowboard *board1;
	berlo *berlo1;
    berlo *fesu_fog;
    for(board1= head_board; board1!= NULL; board1 = board1->kov)
    {
        board_kiir(board1);
        for(berlo1 = board1->berlo; berlo1 != NULL; berlo1 = berlo1->kov_berles)
        {
            berlo_kiir(berlo1);
        }
    }
}

void berles_ara(snowboard *head_board, berlo *head_berlo)
{
    typedef enum
    {
        kezdo=1,
        kozephalado = 2,
        halado = 3
    }ugyessegi_szint;

    int ok;
    int k=0;
    int db=0;
    int i;
    int idotartam;
    char azonosito[6];
    snowboard *board;
    berlo *berlo2;
    double labmeret;
    snowboard *megfelelo_boardok;
    berlo2 = berlo_beker();
    berlo_hozzaad(head_berlo, berlo2);
    labmeret = labmeret_atvalto(berlo2->labmeret);
    printf("labmeret: %lf\n", labmeret);
    idotartam = bereles_idotartama(berlo2->berles_idotartama);
    printf("idotartam: %d\n", idotartam);
    for(board = head_board; board->kov != NULL; board = board->kov)
    {
        if((int)(((double)(berlo2->testmagassag))*0.8) < board->hossz && (berlo2->testmagassag)*0.9 > board->hossz && labmeret < (board->szelesseg)*1.2)
        {
            if(board_szabad(board,berlo2))
            {
                db++;
            }
        }
    }
    megfelelo_boardok = (snowboard*)malloc(db*sizeof(snowboard));
    for(board = head_board; board->kov != NULL; board = board->kov)
    {
        if((berlo2->testmagassag)*0.8 < board->hossz && (berlo2->testmagassag)*0.9 > board->hossz && labmeret < (board->szelesseg)*1.2)
        {
            if(board_szabad(board, berlo2))
            {
                megfelelo_boardok[k++] = *board;
            }
        }
    }
    for(i=0;i<k;i++)
    {
        snowboard board = megfelelo_boardok[i];
        int ar = idotartam*(napi_egysegar(board));
        printf("%s %3d %4.1lf %d %4d - ", board.azonosito, board.hossz, board.szelesseg, board.ev, board.napok);
        printf("%6d Ft\n", ar);
    }
    printf("Kerem a valasztott snowboard azonositojat: ");
    scanf("%s",berlo2->azonosito);
    ok = fesus_lista_befuzes(head_board, berlo2);
    if (ok)
    {
        printf("Sikeresen hozzafuzve\n");
    }
    else
    {
       printf("Nem talalhato a megadott snowboard azonosito : %s\n", berlo2->azonosito);
       free(berlo2);
    }
}

void boardok_fajlba_irasa(snowboard *head_board)
{
	snowboard *board1;
    snowboard *elozo;
    FILE *f;
    //f = fopen("C:\\temp\\board.txt","w");
    f = fopen("board.txt","w");
    for(board1 = head_board; board1 != NULL;)
   {
       fprintf(f,"%5s %4d %3.1lf %4d %4d \n", board1->azonosito,board1->hossz,board1->szelesseg, board1->ev, board1->napok);
       elozo = board1;
       board1 = board1->kov;
       board_kiir(elozo);
       free(elozo);
   }
   fclose(f);
}

void berlok_fajlba_irasa(berlo *head_berlo)
{
	datum kezdet; //= berlo1->berles_idotartama.kezdete;
    datum veg; //= berlo1->berles_idotartama.vege;
	berlo *berlo1;
    berlo *elozo;
    FILE *f;
    //f = fopen("C:\\temp\\berlok.txt","w");
    f = fopen("berlok.txt","w");
    for(berlo1 = head_berlo; berlo1 != NULL; )
    {
		kezdet = berlo1->berles_idotartama.kezdete;
        veg = berlo1->berles_idotartama.vege;
        fprintf(f,"%20s %20s", berlo1->neve.vezeteknev,berlo1->neve.keresztnev);
        fprintf(f,"%3d ", berlo1->testtomeg);
        fprintf(f,"%3d ", berlo1->testmagassag);
        fprintf(f,"%3.1lf ", berlo1->labmeret);
        fprintf(f,"%15s ", berlo1->szint);
        fprintf(f,"%4d %2d %2d  %4d %2d %2d ",kezdet.ev, kezdet.honap, kezdet.nap, veg.ev, veg.honap, veg.nap);
        fprintf(f,"%6s\n", berlo1->azonosito);
        elozo = berlo1;
        berlo1 = berlo1->kovetkezo_berlo;
        berlo_kiir(elozo);
        free(elozo);
    }
     fclose(f);
}

void kilepes(snowboard *head_board, berlo *head_berlo)
{
    //todo
    printf("Program bezarasa\n");


}

void menu()
{
    //printf("ok1\n");
    berlo berlo1;
    int nap;
    nev nev1;
    int k;
    int i;
    char *boards;
    int *sum;
    char azonosito1[6];
	int menupont = 0;
	snowboard *board1;
	snowboard *head_board;
	berlo *berlo2;
	berlo *head_berlo;
	head_board = board_beolvas();
	//printf("ok2\n");
	head_berlo = berlo_beolvas();
	//printf("ok3\n");
	fesus_lista_inditas(head_board, head_berlo);
	//printf("ok4\n");
	do {
        printf("A menuk kozotti navigalashoz hasznalja a szamokat.\n");
        printf(
            "0. Osszes berles listazasa.\n"
            "1. A berles ara.\n"
            "2. Berles vege, a berlo visszahozta a berelt termeket.\n"
            "3. A legtobbet berelet deszka.\n"
            "4. Szezon vegen leselejtezendo deszkak.\n"
            "5. Snowboard hozzadasa.\n"
            "6. Snowboard torlese.\n"
            "7. Berlok listazasa.\n"
            "8. Boardok listazasa.\n"
            "9. Kilepes.\n"
            "\n");
        scanf("%d", &menupont);
        switch (menupont) {
            case 0: fesus_lista_listazas(head_board); break;

            case 1: berles_ara(head_board, head_berlo);
                    break;

            case 2: printf("Adja meg a berlot (vezeteknev keresztnev): ");
                    scanf("%s %s", nev1.vezeteknev, nev1.keresztnev);
                    head_berlo = berlo_torol(head_berlo,nev1);
                    break;

            case 3: board1 = legtobbet_berelt_deszka(head_board);
                    printf("%s %d %lf %d %d \n",board1->azonosito,board1->hossz,board1->szelesseg,board1->ev,board1->napok); break;

            case 4:  leselejtezendo(head_board);
                     break;

            case 5: board_hozzaad(head_board,board_beker());
                    board_listaz(head_board);
                    break;

            case 6: board_listaz(head_board);
                    printf("Adja meg a torolni kivant snowboard azonositojat (5karakter): ");
                    scanf("%s",azonosito1);
                    head_board = board_torol(head_board,azonosito1);
                    break;

            case 7:  berlok_listaz(head_berlo);
                     break;

            case 8:  board_listaz(head_board);
                     break;

            case 9: //kilepes(head_board, head_berlo);
                    boardok_fajlba_irasa(head_board);
                    berlok_fajlba_irasa(head_berlo); //todo
                    printf("Program bezarasa\n");
                    return;

            default: printf("A megadott szamok kozul valasszon!\n"); break;
        }
        printf("\n");
    }
    while (menupont != 9);
}

int main ()
{
    //bereles_idotartama()
    menu ();
    return 0;
}