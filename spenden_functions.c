#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spenden_functions.h"

 void create_spende(void)
{
    //Konto
    static struct Spende tSpende;

    clear();

    /*
    Seitenkopf
    */
    printNTimes('*', 33);
    printf("\n*Neue Spende anlegen\t\t*\n");
    printNTimes('*', 33);

    /*
    Eingabe von allen nötigen Daten
    */
    printf("\n\nBitte geben sie den Vornamen ein: ");
    scanf("%s", tSpende.vorname);
    fflush(stdin);

    printf("Bitte geben sie den Nachnamen ein: ");
    scanf("%s", tSpende.nachname);
    fflush(stdin);

    printf("Bitte geben sie den zu spendenden Beitrag ein: ");
    scanf("%lf", &tSpende.betrag);
    fflush(stdin);

    /*
    Abspeichern der Informationen in die Datei
    */
    show_spende(&tSpende);

    if(save_spende(&tSpende) == EXIT_FAILURE)
    {
        printf("Die Spende konnte nicht erstellt werden.\n");
    }
}



/**
* Diese Funktion gibt ein bestimmtes Zeichen X Mal aus. Es wird kein Zeilenumbruch ausgegeben.
* @ param - const char - Das Zeichen, was ausgegeben werden soll
* @ param - const int - Die Anzahl
*/
void printNTimes(const char cZeichen, const int iTimes)
{
    //Laufvariable
    int iX;

    for(iX=0; iX<iTimes; iX++)
    {
        printf("%c", cZeichen);
    }
}



int save_spende(struct Spende *tSpende)
{
    //Streampointer
    FILE *pFile;

    //Datei wird zum bearbeiten geöffnet
    pFile = fopen (SPENDEN_DATEI, "a");

    /*
    Schreiben des Datensatzes in die Datei
    */
    fprintf(pFile,"%s", tSpende->vorname);
    fprintf(pFile, " %s", tSpende->nachname);
    fprintf(pFile, " %.2lf", tSpende->betrag);
    fprintf(pFile, "\n");

    //Datei wird geschlossen
    fclose(pFile);

    return EXIT_SUCCESS;
}

void show_spende(struct Spende *tSpende)
{
    clear();
    printf("Vielen Dank %s %s fuer Ihre Spende in hoehe von %.2lf Euro.\n", tSpende->vorname, tSpende->nachname, tSpende->betrag);
    system("PAUSE");
}

void display_all_spende()
{
    //Laufvariable
    int iX=0;
    //Rechenvariable für die Navigation
    int iY=0;
    //Für die ermittlung der Anzahl der Konten
    int iAnzahl=0;
    //Das dynamische Konto-Array
    struct Spende *tAlleSpenden;
    //Für die formatierte Ausgabe. ([Nachname], [Vorname])
    char szNachVorname[60];
    //Steuervariable für die Navigation
    char cAuswahl;

    /*
    Dynamische Speicherallocierung der tAlleKonten - Variable.
    */
    tAlleSpenden=load_all_spenden(&iAnzahl);
    tAlleSpenden=(struct Konto *) malloc(iAnzahl * sizeof(struct Spende));
    tAlleSpenden=load_all_spenden(&iAnzahl);

    do
    {
        clear();

        /*
        Ausgabe des Headers
        */
        printNTimes('*', 33);
        printf("\n*Alle Spenden anzeigen:\t\t*\n");
        printNTimes('*', 33);

        /*
        Ausgabe der Seitennavigation
        */
        if(iY+10 > iAnzahl)
        {
            printf("\n\nEintraege %d-%d von %d\n\n", iY+1, iAnzahl, iAnzahl);
        }
        else
        {
            printf("\n\nEintraege %d-%d von %d\n\n", iY+1, 10+iY, iAnzahl);
        }

        /*
        Ausgabe des Tabellenkopfes
        */
        printf("|%-25s|%-15s|\n", "Name", "Betrag");
        printNTimes('-', 59);
        printf("\n");

        /*
        Ausgabe der einzelnen Datensätze mit Zusammenführung von Vor- und Nachname
        */
        for(iX=0; iX<10 && (iX+iY)<iAnzahl; iX++)
        {
            szNachVorname[0]=0;
            strcat(szNachVorname, tAlleSpenden[iX+iY].nachname);
            strcat(szNachVorname, ", ");
            strcat(szNachVorname, tAlleSpenden[iX+iY].vorname);

            printf("|%-25s|%15.2lf|\n", szNachVorname, tAlleSpenden[(iX+iY)].betrag);
        }

        /*
        Ausgabe des Tabellenfußes
        */
        printNTimes('-', 59);
        printf("\n\n\n%-30s%-30s%-30s\n", "[z]urueck", "[b]eenden", "[v]or");

        //Einlesen der Steuervariable (Navigation)
        cAuswahl=getchar();
        fflush(stdin);

        //Algorithmus zur berechnung der Rechenvariable für die Navigation
        if(cAuswahl == 'v' && (iX+iY)<iAnzahl)
        {
            iY+=10;
        }
        else if(cAuswahl == 'z' && iY>9)
        {
            iY-=10;
        }
        else
        {
            ;
        }
    }
    while(cAuswahl != 'b'); //Programm wird bei eingabe von 'b' beendet
}

struct Konto *load_all_spenden(int *iAnzahl)
{
    //Dummy-Konto-Structur zum zwischenspeichern
    struct Spende tDummy;
    //Dynamisches Array für alle Konten
    static struct Spende *tAlleSpenden=NULL;
    FILE *pFile;

    //iAnzahl wird auf 0 gesetzt
    *iAnzahl=0;

    //Öffnen der Datei im Lesemodus
    pFile = fopen (SPENDEN_DATEI, "r");

    /*
    Wenn die Datei nicht vorhanden ist wir NULL zurück gegeben.
    */
    if(pFile == NULL)
    {
        printf("Die Datei konnte nicht geoeffnet werden!");
        return NULL;
    }
    /*
    Die Anzahl der Datensätze wird ermittelt
    */
    else
    {

        while(fscanf(pFile,"%s %s %lf", tDummy.vorname, tDummy.nachname, &tDummy.betrag) != EOF)
        {
            (*iAnzahl)++;
        }
    }

    //Allociert den benötigten Speicher
    tAlleSpenden = (struct Spende *) malloc((*iAnzahl)*sizeof(struct Spende));

    //Setzt den Streampointer wieder an den Anfang der Datei
    rewind(pFile);

    /*
    Liest alle Datensätze in das dynamische Array ein
    */
    *iAnzahl=0;
    while(fscanf(pFile,"%s %s %lf", tAlleSpenden[*iAnzahl].vorname, tAlleSpenden[*iAnzahl].nachname, &tAlleSpenden[*iAnzahl].betrag) != EOF)
    {
        (*iAnzahl)++;
    }

    //Schließt die Datei
    fclose(pFile);

    return tAlleSpenden;
}

void clear(void)
{
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif
}
