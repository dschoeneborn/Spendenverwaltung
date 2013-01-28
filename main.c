#include <stdio.h>
#include <stdlib.h>
#include "spenden_functions.h"

int main()
{
    int iAuswahl;

    do{
    printf("*********************************\n");
    printf("*Spendenverwaltung v0.1\t\t*\n*by Dennis Schoeneborn\t\t*\n");
    printf("*********************************\n\n");

    printf("Aktionen: \n[1] Spende eingeben\n[2] Spendenliste ansehen\n[0] Schliessen\n\n\n");

    scanf("%d",&iAuswahl);
    fflush(stdin);

    switch(iAuswahl)
    {
        case 1: create_spende(); break;
        case 2: display_all_spende(); break;
        /*case 5: invalidate_account(); break;
        default: */
        case 0: return 0; break;
    }
    system("cls");
    }while (iAuswahl != 0); //Wird so lange ausgeführt bis der Anwender 0 eingibt
    return 0;
}


