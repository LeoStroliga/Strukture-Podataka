#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
struct _stogelement;
typedef struct _stogelement* pozicija;

typedef struct _stogelement
{
    double broj;
    pozicija pok;

}stogelement;

pozicija stvori(int broj);
int dodajnakon(pozicija prije, pozicija novi);
int dodajustog(pozicija head, double broj);
int izracun(pozicija head, char znak);
int izbrisinakon(pozicija element);
int ucitajizdatoteke(char* imedatoteke, pozicija head);
int ucitajizstringa(char* buffer, pozicija head);
int ispisi(pozicija head);
int izbrisilistu(pozicija head);


int main()
{
    stogelement stog = { .broj = 0, .pok = NULL };
    int n = 1024;
    char imedat[] = "datoteka.txt";
    if (ucitajizdatoteke(imedat, &stog) < 0)
        return 0;
    printf("Rezultat: ");
    ispisi(&stog);
    izbrisilistu(&stog);
    return 0;
}


pozicija stvori(double broj)
{
    stogelement* novi = NULL;
    novi = (pozicija)malloc(sizeof(stogelement));

    if (!novi)
    {
        printf("Nema memorije");
        return NULL;
    }

    novi->broj = broj;
    novi->pok = NULL;

    return novi;
}

int dodajnakon(pozicija prije, pozicija novi)
{
    novi->pok = prije->pok;
    prije->pok = novi;
    return EXIT_SUCCESS;
}

int dodajustog(pozicija head, double broj)
{
    stogelement* novi;
    novi = stvori(broj);
    dodajnakon(head, novi);
    return EXIT_SUCCESS;
}

int izbrisinakon(pozicija element)
{

    pozicija temp = element->pok;
    if (temp == NULL)
        return EXIT_SUCCESS;
    element->pok = temp->pok;
    free(temp);
    return EXIT_SUCCESS;
}

int izracun(pozicija head, char znak)
{
    pozicija temp = head->pok;
    if (!temp)
    {
        printf("Nema brojeva prije znaka");
        return -1;
    }
    double prvi = 0;
    double drugi = 0;
    drugi = temp->broj;
    temp = temp->pok;
    if (!temp)
    {
        printf("Fali broj prije znaka");
        return -1;
    }
    prvi = temp->broj;
    if (znak == '+')
    {
        izbrisinakon(head);
        temp->broj = drugi + prvi;
    }
    else if (znak == '-')
    {
        izbrisinakon(head);
        temp->broj = prvi - drugi;
    }
    else if (znak == '*')
    {
        izbrisinakon(head);
        temp->broj = drugi * prvi;
    }
    else if (znak == '/')
    {
        if (prvi == 0)
        {
            printf("Nema dijeljena sa nulon");
            return -1;
        }
        izbrisinakon(head);
        temp->broj = prvi / drugi;
    }
    else
    {
        printf("%c - sta je ovo", znak);
        return -1;
    }
    return EXIT_SUCCESS;
}
int ucitajizdatoteke(char* imedatoteke, pozicija head)
{
    FILE* f = NULL;
    char buffer[1024] = { NULL };
    int a = 1024;
    f = fopen(imedatoteke, "r");
    if (!f)
    {
        printf("Nema datoteke");
        fclose(f);
        return -2;
    }
    if (feof(f) != 0)
    {
        printf("Prazna datoteka");
        fclose(f);
        return -1;
    }
    fgets(buffer, a, f);
    fclose(f);
    if (ucitajizstringa(buffer, head) < 0)
        return -1;
    return EXIT_SUCCESS;
}
int ucitajizstringa(char* buffer, pozicija head)
{
    double br = 0;
    int n = 0;
    int q = 0;
    while (strlen(buffer) != 0)
    {
        if (sscanf(buffer, "%lf %n", &br, &n) == 1)
        {
            if (dodajustog(head, br) < 0)
                return -1;
            q = 0;

        }
        else
        {
            if (izracun(head, buffer[0]) < 0)
                return -1;
            q = 1;
        }
        buffer = buffer + n;
    }
    if (q == 0)
    {
        printf("Nema operacija nakon %d", &br);
        return -1;
    }

    return EXIT_SUCCESS;

}
int ispisi(pozicija head)
{
    pozicija temp = head->pok;
    if (temp == NULL)
    {
        printf("Prazano\n");
        return -1;
    }
    for (; temp != NULL; temp = temp->pok)
        printf("%lf ", temp->broj);
    return 0;
}
int izbrisilistu(pozicija head)
{
    while (head->pok != NULL)
        izbrisinakon(head);
    return EXIT_SUCCESS;
}