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
    char ime[100];
    pozicija sin;
    pozicija brat;
}element;



int md(pozicija pokazivac, char* ime)
{
    pozicija novi;
    pozicija temp;
    temp = pokazivac->sin;
    strcpy(novi->ime, ime);
    pokazivac->sin = novi;
    novi->brat = temp;
    return 0;
}

pozicija find(pozicija pokazivac, char* ime)
{
    if (pokazivac == NULL)
    {
        printf("Nije pronadeno\n");
        return pokazivac;
    }
    else if (strcmp(pokazivac, ime) == 0)
    {

        return pokazivac;
    }
    pokazivac = find(pokazivac->brat, ime);
    return pokazivac;

}



int cd(pozicija pokazivac, char* ime)
{
    pokazivac = find(pokazivac->sin, ime);

    return 0;
}

int ispis(pozicija tata)
{
    printf("%s::~n", tata->ime);
    pozicija temp = tata->sin;
    while (temp != NULL)
    {
        printf("%s:\n", temp->ime);
        temp = temp->brat;
    }
    return 0;
}


int main()
{
    element c = { .ime = "C",.sin = NULL,.brat = NULL };
    char naredba[100];
    pozicija pokazivac;
    pokazivac = &c;

    ispis(pokazivac);
    while (strcmp(naredba, "izlaz") != 0)
    {
        if (strcmp(naredba, "md") == 0)
        {
            char ime[100];
            scanf(" %s", ime);
            md(pokazivac, ime);
        }
        else if (strcmp(naredba, "cd") == 0)
        {
            char ime[100];
            scanf(" %s", ime);
            cd(pokazivac, ime);
        }
        ispis(pokazivac);
        scanf(" %s", naredba);
    }

    return 0;
}


