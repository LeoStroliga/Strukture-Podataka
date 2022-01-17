#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

//a)
/*
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
        pokstabla novi=NULL;
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
        pokliste tempprije=NULL;
        while (temp != NULL && strcmp(temp->imedrzave, novi->imedrzave)< 0)
        {
            tempprije = temp;
            temp = temp->sljedeci;
        }
        novi->sljedeci=temp;
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
    int ucitajustablo(char* imedat,pokliste drzava)
    {
        pokstabla temp=NULL;
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
    int ucitaj(char* imedat, pokliste head)
    {
        FILE* f = fopen(imedat, "r");
        char imedrzave[50];
        char imedatg[50];
        pokliste temp = NULL;
        while (feof(f) == 0)
        {
            fscanf(f, " %s %s", imedrzave, imedatg);
            temp = novielementliste(imedrzave);
            ucitajustablo(imedatg,temp);
            dodajulistu(head,temp);
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
    
    }
    int main()
    {
        elementliste head = { .imedrzave = NULL,.sljedeci = NULL,.stablo = NULL };
        ucitaj("Drzave.txt", &head);
       ispisi(&head);
       char imedrzave[50];
       pokliste pokdrzave=NULL;
       scanf(" %s", imedrzave);
       pokdrzave = nadidrzavu(&head, imedrzave);
       int broj;
       scanf("%d", &broj);
       ispisigradove(pokdrzave->stablo, broj);
        return 0;
    }
    */
    //b

struct _elementstabla;
struct _elementliste;
typedef struct _elementstabla* pokstabla;
typedef struct _elementliste* pokliste;
typedef struct _elementstabla
{
    char ime[50];
    pokstabla lijevo;
    pokstabla desno;
    pokliste lista;

}elementstabla;

typedef struct _elementliste
{
    char ime[50];
    int broj;
    pokliste sljedeci;

}elementliste;

pokstabla dodajelestabla(char* ime, pokstabla prvi)
{
    pokstabla novi = NULL;
    pokliste novihead = NULL;
    novihead = (pokliste)malloc(sizeof(elementliste));
    novihead->broj = 0;
    strcpy(novihead->ime, " ");
    novihead->sljedeci = NULL;

    novi = (pokstabla)malloc(sizeof(elementstabla));
    strcpy(novi->ime, ime);
    novi->lista = novihead;
    novi->lijevo = NULL;
    novi->desno = NULL;

    pokstabla temp = prvi;
    pokstabla tempprije = NULL;

    int a = 0;
    while (temp != NULL)
    {
        if (strcmp(temp->ime, novi->ime) > 0)
        {
            tempprije = temp;
            temp = temp->lijevo;
            a = 1;
        }
        else
        {
            tempprije = temp;
            temp = temp->desno;
            a = 2;
        }
    }
    if (a == 0)
    {
        prvi = novi;

        return novi;
    }
    else if (a == 1)
    {
        tempprije->lijevo = novi;

        return novi;
    }

    tempprije->desno = novi;


    return novi;

}
pokliste stvorieleliste(char* imegrada, int broj)
{
    pokliste novi = NULL;
    novi = (pokliste)malloc(sizeof(elementliste));
    novi->broj = broj;
    strcpy(novi->ime, imegrada);
    novi->sljedeci = NULL;
    return novi;
}
int dodajulistu(pokliste novi, pokliste head)
{
    pokliste temp = head->sljedeci;
    pokliste tempprije = NULL;
    // printf("%s", temp->ime);
    while (temp != NULL && novi->broj > temp->broj)
    {
        tempprije = temp;
        temp = temp->sljedeci;
    }

    if (tempprije == NULL)
    {
        head->sljedeci = novi;
        novi->sljedeci = temp;
        // printf("%s",head->sljedeci);
        return 0;
    }
    //  printf("%s ",novi->ime);
    tempprije->sljedeci = novi;
    novi->sljedeci = temp;
    return 0;
}

int stvoriidodajulistu(char* imedatdr, pokstabla stablo)
{
    FILE* d = fopen(imedatdr, "r");
    pokliste novitemp = NULL;
    char grad[50];
    int brojst;
    /*   pokliste head = NULL;
       head = (pokliste)malloc(sizeof(elementliste));
       head->broj = 0;
       strcpy(head->ime, "0");
       head->sljedeci = NULL;
       stablo->lista = head;*/

    while (feof(d) == 0)
    {
        fscanf(d, " %s %d", grad, &brojst);
        novitemp = stvorieleliste(grad, brojst);
        //printf("%s", novitemp->ime);

        dodajulistu(novitemp, stablo->lista);
        //  printf("%s", stablo->lista->sljedeci->ime);
    }
    // printf("%s ",stablo->lista->sljedeci->ime);
    fclose(d);
    return 0;
}


int ucitaj(char* imedat, pokstabla prvi)
{
    FILE* f = fopen(imedat, "r");
    pokstabla novi = NULL;
    char imedr[50];
    char imedrdat[50];
    while (feof(f) == 0)
    {

        if (strcmp("0", prvi->ime) == 0)
        {
            fscanf(f, " %s %s", imedr, imedrdat);
            strcpy(prvi->ime, imedr);
            stvoriidodajulistu(imedrdat, prvi);
        }
        /*
        while (!feof(f))
        {
            fscanf(" %s %s", imedr, imedat);
            strcpy(prvi->ime, imedr);
        }
       */

        else
        {

            fscanf(f, " %s %s", imedr, imedrdat);
            novi = dodajelestabla(imedr, prvi);
            stvoriidodajulistu(imedrdat, novi);
        }

    }
    fclose(f);
    return 0;
}

int ispisilistu(pokliste head)
{
    if (head->sljedeci == NULL)
        return 0;
    pokliste temp = head->sljedeci;
    while (temp != NULL)
    {
        //     printf("DOTU2");
        printf("%s %d ", temp->ime, temp->broj);
        temp = temp->sljedeci;
        // printf("%s ", temp->sljedeci->ime);
    }
    return 0;
}

int ispisisve(pokstabla elestabla)
{
    if (elestabla != NULL)
    {
        //printf("DOTU ");
      //  printf("prije %s : ", elestabla->ime);
       // printf("levo");
        ispisisve(elestabla->lijevo);
        printf("%s : ", elestabla->ime);

        ispisilistu(elestabla->lista);
        //   printf("desno");
        ispisisve(elestabla->desno);

    }
    return 0;
}

pokstabla nadidrzavu(char* car, pokliste prvi)
{
    pokstabla temp = prvi;
    while (temp != NULL && strcmp(car, temp->ime) != 0)
    {
        if (strcmp(car, temp->ime) < 0)
        {
            temp = temp->lijevo;
        }
        else
            temp = temp->desno;
    }
    if (temp == NULL)
        printf("Nemad grada");

    return temp;

}
int ispisigradove(int n, pokliste head)
{
    pokliste temp = head->sljedeci;
    while (temp != NULL && n > temp->broj)
        temp = temp->sljedeci;

    while (temp != NULL)
    {
        printf("%s %d ", temp->ime, temp->broj);
        temp = temp->sljedeci;
    }
    return 0;

}

int main()
{
    elementstabla prvi = { .desno = NULL,.ime = "0",.lijevo = NULL,.lista = NULL };
    elementliste head = { .broj = 0,.ime = " ",.sljedeci = NULL };
    prvi.lista = &head;

    ucitaj("Drzave.txt", &prvi);
    //  ispisisve(&prvi);
   //  if (prvi.desno != NULL)
      //  printf("%s",prvi.desno->ime);
    char a[] = "Hrvatska";
    int n = 10001;
    pokstabla drz;
    drz = nadidrzavu(a, &prvi);
    printf("%s: ", drz->ime);
    ispisigradove(n, drz->lista);



    return 0;
}