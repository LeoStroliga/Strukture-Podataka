#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include<time.h>


struct _element;
typedef struct _element* pozicija;
typedef struct _element
{
    int broj;
    pozicija lijevo;
    pozicija desno;

}element;

struct _elementliste;
typedef struct _elementliste* pozicijae;
typedef struct _elementliste
{
    int broj;
    pozicijae sljedeci;

}elementliste;



pozicija dodaj(int n, pozicija prvi)
{

    pozicija novi = NULL;
    novi = (pozicija)malloc(sizeof(element));
    novi->broj = n;
    novi->desno = NULL;
    novi->lijevo = NULL;
    if (prvi == NULL)
    {
        prvi = novi;
        return prvi;
    }
    pozicija temp = prvi;

    while (1 == 1)
    {
        if (n > temp->broj || n == temp->broj)
        {
            if (temp->lijevo == NULL)
            {
                temp->lijevo = novi;
                return prvi;
            }
            temp = temp->lijevo;
        }

        else if (n < temp->broj)
        {
            if (temp->desno == NULL)
            {
                temp->desno = novi;
                return prvi;
            }
            temp = temp->desno;
        }
    }
    return prvi;
}


int replace(pozicija ele)
{
    if (ele == NULL)
        return 0;
    int n = ele->broj;
    ele->broj = replace(ele->lijevo) + replace(ele->desno);
    return(n + ele->broj);
}


int ispisr(pozicija ele)
{

    if (ele != NULL)
    {
        ispisr(ele->desno);
        printf("%d ", ele->broj);
        ispisr(ele->lijevo);

    }
    return 0;
}
pozicijae stvori(int n)
{
    pozicijae novi = NULL;
    novi = (pozicijae)malloc(sizeof(elementliste));
    novi->broj = n;
    novi->sljedeci = NULL;
    return novi;

}
int izbrisilistu(pozicijae head)
{
    pozicijae temp = NULL;
    while (head->sljedeci != NULL)
    {
        temp = head->sljedeci;
        head->sljedeci = temp->sljedeci;
        free(temp);
    }
    return 0;
}

int sort(pozicijae head, int n)
{
    pozicijae novi = stvori(n);
    if (head->sljedeci == NULL)
    {
        head->sljedeci = novi;
        return 0;
    }
    pozicijae temp = head->sljedeci;
    pozicijae tempprije = head;
    while (temp != NULL && temp->broj < novi->broj)
    {
        tempprije = temp;
        temp = temp->sljedeci;
    }
    tempprije->sljedeci = novi;
    novi->sljedeci = temp;
    return 0;
}


int unosulistu(pozicija ele, pozicijae head)
{

    if (ele != NULL)
    {
        unosulistu(ele->lijevo, head);
        sort(head, ele->broj);
        unosulistu(ele->desno, head);
    }
    return 0;
}



int unosudatoteku(pozicija prvi, char* ime)
{

    elementliste head = { .broj = 0,.sljedeci = NULL };
    unosulistu(prvi, &head);
    FILE* f = fopen(ime, "w");
    pozicijae temp = head.sljedeci;
    while (temp != NULL)
    {
        fprintf(f, "%d ", temp->broj);
        temp = temp->sljedeci;
    }
    fprintf(f, "\n");
    izbrisilistu(&head);
    replace(prvi);
    unosulistu(prvi, &head);
    temp = head.sljedeci;
    while (temp != NULL)
    {
        fprintf(f, "%d ", temp->broj);
        temp = temp->sljedeci;
    }

    fclose(f);

    return 0;
}



int main()
{

    int n;
    n = rand() % 80 + 10;
    element prvi = { .broj = n,.desno = NULL,.lijevo = NULL };
    srand(time(0));

    dodaj(rand() % 80 + 10, &prvi);
    dodaj(rand() % 80 + 10, &prvi);
    dodaj(rand() % 80 + 10, &prvi);
    dodaj(rand() % 80 + 10, &prvi);
    dodaj(rand() % 80 + 10, &prvi);
    dodaj(rand() % 80 + 10, &prvi);
    dodaj(rand() % 80 + 10, &prvi);
    dodaj(rand() % 80 + 10, &prvi);
    dodaj(rand() % 80 + 10, &prvi);
    ispisr(&prvi);
    printf("\n");
    char ime[] = "ndat.txt";
    unosudatoteku(&prvi, ime);
    //replace(&prvi);
    ispisr(&prvi);



    // ispisr(&prvi);




    return 0;
}