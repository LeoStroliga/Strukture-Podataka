
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


struct _element;
typedef struct _element* pozicija;
typedef struct _element
{
    int broj;
    pozicija lijevo;
    pozicija desno;

}element;


int dodaj(int n, pozicija prvi)
{

    pozicija novi = NULL;
    novi = (pozicija)malloc(sizeof(element));
    novi->broj = n;
    novi->desno = NULL;
    novi->lijevo = NULL;
    if (prvi == NULL)
    {
        prvi = novi;
        return 0;
    }
    pozicija temp = prvi;

    while (1 == 1)
    {
        if (n > temp->broj)
        {
            if (temp->desno == NULL)
            {
                temp->desno = novi;
                return 0;
            }
            temp = temp->desno;
        }

        else if (n < temp->broj)
        {
            if (temp->lijevo == NULL)
            {
                temp->lijevo = novi;
                return 0;
            }
            temp = temp->lijevo;
        }

        else
        {
            printf("Taj broj vec postoji");
            return 0;
        }
    }
}


int pronadi(int n, pozicija prvi)
{
    pozicija temp = prvi;

    while (temp != NULL)
    {
        if (temp->broj == n)
        {
            printf("Broj pronaden");
            return 0;
        }
        else if (n > temp->broj)
        {
            temp = temp->desno;
        }
        else
            temp = temp->lijevo;
    }
    printf("Broj ne postoji");
    return 0;
}


int izbrisi(int n, pozicija prvi)
{
    pozicija temp = prvi;
    pozicija prije = NULL;
    int a = 0;
    while (temp != NULL && temp->broj != n)
    {

        if (n > temp->broj)
        {
            prije = temp;
            temp = temp->desno;
            a = 1;
        }
        else
        {
            prije = temp;
            temp = temp->lijevo;
            a = 2;
        }
        printf("DOUT");
    }
    if (temp == NULL)
        return 0;
    if (temp->desno != NULL)
    {
        pozicija temp2 = temp->desno;
        pozicija prije2 = temp;
        while (temp2->lijevo != NULL)
        {
            prije2 = temp2;
            temp2 = temp2->lijevo;
        }
        if (a == 1)
            prije->desno = temp2;
        else
            prije->lijevo = temp2;
        temp2->lijevo = temp->lijevo;
        if (prije2 != temp)
        {
            prije2->lijevo = temp2->desno;
            temp2->desno = temp->desno;
        }
        free(temp);
        return 0;
    }
    else
    {
        if (a == 1)
            prije->desno = temp->lijevo;
        else if (a == 2)
            prije->lijevo = temp->lijevo;
        else
            prvi = prvi->lijevo;
        return 0;
    }

}

int ispisr(pozicija ele)
{

    if (ele != NULL)
    {
        ispisr(ele->lijevo);
        printf("%d", ele->broj);
        ispisr(ele->desno);
    }
    return 0;
}



int main()
{

    int n;
    n = 7;
    element prvi = { .broj = n,.desno = NULL,.lijevo = NULL };
    dodaj(3, &prvi);
    dodaj(11, &prvi);
    dodaj(2, &prvi);
    dodaj(6, &prvi);
    dodaj(9, &prvi);
    dodaj(13, &prvi);
    dodaj(14, &prvi);
    izbrisi(14, &prvi);
    pronadi(13, &prvi);
    ispisr(&prvi);

    return 0;
}