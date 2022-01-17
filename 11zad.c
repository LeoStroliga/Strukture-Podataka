
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

//a)

struct _elementliste;
struct _elementstabla;
typedef struct _elementstabla* pokstabla;
typedef struct _elementliste* pokliste;
typedef struct _elementliste
{
    char imedrzave[100];
    pokliste sljedeci;
    pokstabla stablo;
}elementliste;
typedef struct _elementstabla
{
    char imegrada[100];
    int broj;
    pokstabla lijevo;
    pokstabla desno;
}elementstabla;

pokstabla novielementstabla(char* ime, int broj)
{
    pokstabla novi = NULL;
    novi = (pokstabla)malloc(sizeof(elementstabla));
    novi->broj = broj;
    strcpy(novi->imegrada, ime);
    novi->desno = NULL;
    novi->lijevo = NULL;
    return novi;
}
pokliste novielementliste(char* ime)
{
    pokliste novi = NULL;
    novi = (pokliste)malloc(sizeof(elementliste));
    strcpy(novi->imedrzave, ime);
    novi->sljedeci = NULL;
    novi->stablo = NULL;
    return novi;

}

int dodajulistu(pokliste head, pokliste novi)
{
    if (head->sljedeci == NULL)
    {
        head->sljedeci = novi;
        return 0;
    }

    pokliste temp = head->sljedeci;
    pokliste tempprije = NULL;


    while (temp != NULL && strcmp(temp->imedrzave, novi->imedrzave) < 0)
    {
        tempprije = temp;
        temp = temp->sljedeci;
    }
    novi->sljedeci = temp;
    tempprije->sljedeci = novi;
    return 0;
}


int dodajustablo(pokstabla prvi, pokstabla novi)
{


    pokstabla temp = prvi;
    pokstabla tempprije = NULL;
    int a = 0;


    while (temp != NULL)
    {

        if (temp->broj > novi->broj)
        {
            a = 1;
            tempprije = temp;
            temp = temp->lijevo;
        }
        else
        {
            a = 2;
            tempprije = temp;
            temp = temp->desno;
        }
    }
    if (a == 0)
        prvi = novi;
    else if (a == 1)
        tempprije->lijevo = novi;
    else if (a == 2)
        tempprije->desno = novi;

    return 0;

}
int ucitajustablo(char* imedat, pokliste drzava)
{

    pokstabla temp = NULL;


    FILE* f = fopen(imedat, "r");
    char imegrada[50];
    int brojstan;
    if (feof(f) == 0)
    {
        fscanf(f, " %s %d", imegrada, &brojstan);
        drzava->stablo = novielementstabla(imegrada, brojstan);
    }
    while (feof(f) == 0)
    {
        fscanf(f, " %s %d", imegrada, &brojstan);
        temp = novielementstabla(imegrada, brojstan);

        dodajustablo(drzava->stablo, temp);
    }
    fclose(f);
    return 0;
}

int ucitaj(char* imedat, pokliste hash)
{
    FILE* f = fopen(imedat, "r");
    char imedrzave[50];
    char imedatg[50];
    pokliste temp = NULL;
    int q = 0;
    int i = 0;


    while (feof(f) == 0)
    {
        q = 0;
        fscanf(f, " %s %s", imedrzave, imedatg);
        temp = novielementliste(imedrzave);
        ucitajustablo(imedatg, temp);
        while (imedrzave[i] != '\0')
        {
            q += (int)(imedrzave[i]);

            i++;
        }
        q = q % 11;
        dodajulistu(&hash[q], temp);
    }
    fclose(f);
    return 0;
}
int ispisistablo(pokstabla prvi)
{

    if (prvi != NULL)
    {
        ispisistablo(prvi->lijevo);
        printf("%s %d ", prvi->imegrada, prvi->broj);
        ispisistablo(prvi->desno);
    }

    return 0;
}

int ispisi(pokliste head)
{
    pokliste temp = head->sljedeci;
    while (temp != NULL)
    {
        printf("%s : ", temp->imedrzave);

        ispisistablo(temp->stablo);
        printf("\n");
        temp = temp->sljedeci;

    }
    return 0;
}

int nadibrojuhashu(pokliste hash, char* ime)
{
    int q = 0;
    int i = 0;
    while (ime[i] != '\0')
    {
        q += (int)(ime[i]);
        i++;
    }
    q = q % 11;
    return q;
}

pokliste nadidrzavu(pokliste head, char* ime)
{

    pokliste temp = head->sljedeci;

    while (temp != NULL)
    {
        if (strcmp(ime, temp->imedrzave) == 0)
            return temp;
        temp = temp->sljedeci;
    }
    printf("Nije pronadeno");
    return NULL;

}

int ispisigradove(pokstabla prvi, int broj)
{
    if (prvi != NULL)
    {
        if (prvi->broj > broj)
        {
            ispisigradove(prvi->lijevo, broj);
            printf("%s %d ", prvi->imegrada, prvi->broj);
        }
        ispisigradove(prvi->desno, broj);
    }
    return 0;
}


int main()
{
    int i = 0;
    elementliste hash[11];
    for (i = 0; i < 11; i++)
    {
        strcpy(hash[i].imedrzave, "");
        hash[i].sljedeci = NULL;
        hash[i].stablo = NULL;
    }
    elementliste head = { .imedrzave = NULL,.sljedeci = NULL,.stablo = NULL };
    ucitaj("Drzave.txt", hash);


    char imedrzave[] = "Hrvatska";
    pokliste pokdrzave = NULL;

    int a = 0;
    a = nadibrojuhashu(hash, imedrzave);

    pokdrzave = nadidrzavu(&hash[a], imedrzave);

    ispisigradove(pokdrzave->stablo, 101);

    return 0;
}


