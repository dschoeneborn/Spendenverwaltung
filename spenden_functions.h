#ifndef SPENDEN_FUNCTIONS_H_INCLUDED
#define SPENDEN_FUNCTIONS_H_INCLUDED
#define SPENDEN_DATEI "spenden.txt"

struct Spende{
    char vorname[50];
    char nachname[50];
    double betrag;
};

void create_spende(void);
int save_spende(struct Spende *tSpende);
void show_spende(struct Spende *tSpende);
struct Konto *load_all_spenden(int *iAnzahl);
void display_all_spende();
void printNTimes(const char cZeichen, const int iTimes);
void clear(void);


#endif // SPENDEN_FUNCTIONS_H_INCLUDED
