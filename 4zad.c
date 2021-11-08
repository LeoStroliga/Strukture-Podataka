#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct _polinom;
typedef struct _polinom* pozicija;

typedef struct _polinom
{
    int koef;
    int eks;
    pozicija pok;

}polinom;

int umnozak(pozicija, pozicija);
int izbrisi(pozicija, pozicija);
int dodajiza(pozicija, pozicija);
int dodajprije(pozicija, pozicija, pozicija);
int dodajisort(pozicija, pozicija);
int brojredaka(char*);
int ucitavanjeizstringa(pozicija, char*);
int ucitavanjeizliste(pozicija*, char*);
pozicija stvori(int, int);
int ispisilistu(pozicija);
int zbroj(pozicija, pozicija);
int umnozak(pozicija, pozicija);

int main()
{
    int brred = 0;
    FILE* f = NULL;
    char imedat[] = "datoteka.txt";
    brred = brojredaka(imedat);


    polinom* head = NULL;
    head = (polinom*)malloc(sizeof(polinom) * (brred));
    int i = 0;

    for (; i < brred; i++)
    {

        head[i].koef = 0;
        head[i].eks = 0;
        head[i].pok = NULL;
    }

    /*ucitavanjizliste(head,imedat);*/

    char buffer[1024] = { NULL };
    int n = 1024;
    i = 0;
    f = fopen(imedat, "r");
    while (feof(f) == 0)
    {
        fgets(buffer, n, f);
        ucitavanjeizstringa(&head[i], buffer);
        i++;
    }
    fclose(f);

    for (i = 0; i < brred; i++)
    {
        ispisilistu(&head[i]);
    }



    polinom headzbroja = { .koef = 0, .eks = 0, .pok = NULL };
    for (i = 0; i < brred; i++)
        zbroj(&headzbroja, &head[i]);
    ispisilistu(&headzbroja);
    polinom headumnoska = { .koef = 0, .eks = 0, .pok = NULL };
    for (i = 0; i < brred; i++)
    {
        umnozak(&headumnoska, &head[i]);
        ispisilistu(&headumnoska);

    }
    ispisilistu(&headumnoska);
    return 0;
}


pozicija stvori(int k, int e)
{
    pozicija novi = NULL;
    novi = (pozicija)malloc(sizeof(polinom));
    novi->koef = k;
    novi->eks = e;
    novi->pok = NULL;

    return novi;
}

int izbrisi(pozicija head, pozicija taj)
{
    pozicija temp = head;
    for (; temp->pok != taj; temp = temp->pok)
    {
    }
    temp->pok = taj->pok;
    free(taj);

    return 0;
}


int dodajiza(pozicija novi, pozicija prije)
{
    novi->pok = prije->pok;
    prije->pok = novi;
    return 0;
}
int dodajprije(pozicija novi, pozicija iza, pozicija head)
{
    pozicija temp = head;
    for (; temp->pok != iza; temp = temp->pok)
    {
    }

    dodajiza(novi, temp);
    return 0;
}
int dodajisort(pozicija head, pozicija novi)
{


    pozicija temp = head->pok;

    if (temp == NULL)
    {
        dodajiza(novi, head);
        return 0;
    }

    for (; (temp->pok != NULL) && (novi->eks < temp->eks); temp = temp->pok)
    {
    }

    if (novi->eks == temp->eks)
    {
        temp->koef += novi->koef;
        if (temp->koef == 0)
        {
            izbrisi(head, temp);
        }

        free(novi);
        return 0;
    }
    if (novi->eks > temp->eks)
    {
        dodajprije(novi, temp, head);
        return 0;
    }
    dodajiza(novi, temp);
    return 0;
}

int brojredaka(char* imedat)
{
    FILE* f = NULL;
    f = fopen(imedat, "r");
    char buffer[1024] = { NULL };
    int n = 1024;
    int i = 0;


    if (f == NULL)
        return 0;

    while (feof(f) == 0)
    {
        fgets(buffer, n, f);

        i++;

    }
    rewind(f);
    return i;
}

int ucitavanjeizstringa(pozicija head, char* red)
{
    int n = 0;
    int eks = 0;
    int koef = 0;
    pozicija novi = NULL;
    while (sscanf(red, "%d %d %n", &koef, &eks, &n) == 2)
    {
        novi = stvori(koef, eks);
        dodajisort(head, novi);
        red = red + n;
    }
    return 0;
}

int ucitavanjeizliste(pozicija* head, char* imedat)
{
    FILE* f = NULL;
    printf("%s", imedat);
    f = fopen(imedat, "r");

    char buffer[1024] = { NULL };
    int n = 1024;
    int i = 0;
    while (feof(f) == 0)
    {
        fgets(buffer, n, f);
        ucitavanjeizstringa(&head[i], buffer);
        pozicija tt = &head[i];
        tt = tt->pok;
        printf("prvi koef %d \n", tt->koef);
        i++;
    }

    fclose(f);
}

int ispisilistu(pozicija head)
{
    pozicija temp = head->pok;

    while (temp != NULL)
    {
        printf("%d %d ", temp->koef, temp->eks);
        temp = temp->pok;
    }

    printf("\n");

    return 0;
}

int zbroj(pozicija headzbroja, pozicija head)
{
    pozicija tempz = headzbroja->pok;
    pozicija temp = head;
    pozicija novi = NULL;

    do
    {
        temp = temp->pok;

        novi = stvori(temp->koef, temp->eks);
        dodajisort(headzbroja, novi);


    } while (temp->pok != NULL);

    return 0;
}

int umnozak(pozicija headumnoska, pozicija head)
{
    pozicija tempm = headumnoska->pok;
    pozicija temp = head->pok;
    pozicija novi = NULL;
    polinom novihead = { .koef = 0,.eks = 0,.pok = NULL };
    pozicija tempnovi = NULL;
    if (tempm == NULL)
    {
        while (temp != NULL)
        {
            novi = stvori(temp->koef, temp->eks);
            dodajisort(headumnoska, novi);
            temp = temp->pok;
        }
        return 0;
    }
    prebaci(headumnoska, &novihead);

    for (; temp != NULL; temp = temp->pok)
    {
        if (temp == head->pok)
            for (tempm = headumnoska->pok; tempm != NULL; tempm = tempm->pok)
            {
                tempm->koef = (temp->koef) * (tempm->koef);
                tempm->eks += temp->eks;
            }
        else
            for (tempnovi = novihead.pok; tempnovi != NULL; tempnovi = tempnovi->pok)
            {
                novi = stvori(temp->koef * tempnovi->koef, tempnovi->eks + temp->eks);
                dodajisort(headumnoska, novi);

            }
    }

    return 0;
}
int prebaci(pozicija headstari, pozicija headnovi)
{
    pozicija tempstari = headstari->pok;
    pozicija list = NULL;
    for (; tempstari != NULL; tempstari = tempstari->pok)
    {
        list = stvori(tempstari->koef, tempstari->eks);
        dodajisort(headnovi, list);
    }
    return 0;
}