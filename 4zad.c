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

int umnozak(pozicija , pozicija );
int izbrisi(pozicija , pozicija );
int dodajiza(pozicija , pozicija );
int dodajprije(pozicija , pozicija , pozicija );
int dodajisort(pozicija , pozicija );
int brojredaka(char* );
int ucitavanjeizstringa(pozicija , char* );
int ucitavanjeizliste(pozicija* , char* );
pozicija stvori(int , int );
int ispisilistu(pozicija );
int zbroj(pozicija , pozicija );
int umnozak(pozicija , pozicija );

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
    char buffer[1024] = {NULL};
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
    int n=0;
    int eks = 0;
    int koef = 0;
    pozicija novi = NULL;
    while (sscanf(red, "%d %d %n", &koef, &eks, &n)==2)
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
    f = fopen(imedat,"r");

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

    while(temp!=NULL)
    {
        printf("%d %d ",temp->koef,temp->eks);
        temp = temp->pok;
    }

    printf("\n");

   return 0;
}

int zbroj(pozicija headzbroja, pozicija head)
{
    pozicija tempz = headzbroja->pok;
    pozicija temp =head;
    pozicija novi = NULL;

    do
    {   temp = temp->pok;
       
        novi = stvori(temp->koef, temp->eks);  
        dodajisort(headzbroja,novi);
       

    } while (temp->pok != NULL);
   
    return 0;
}

int umnozak(pozicija headumnoska,pozicija head)
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
            dodajisort(headumnoska,novi);
            temp = temp->pok;
        }
        return 0;
    }
    prebaci(headumnoska, &novihead);

    for (; temp != NULL; temp = temp->pok)
    { if (temp == head->pok)
        for (tempm = headumnoska->pok; tempm != NULL; tempm = tempm->pok)
        {
            tempm->koef = (temp->koef) * (tempm->koef);
            tempm->eks += temp->eks;
        }
    else
        for (tempnovi= novihead.pok; tempnovi != NULL; tempnovi = tempnovi->pok)
        {
            novi = stvori(temp->koef*tempnovi->koef,tempnovi->eks+temp->eks);
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
/*
int main()
{
    int brred = 0;
    FILE* f = NULL;
    char imedat[] = "datoteka.txt";
    brred = brojredaka(imedat);
   
   
    polinom* head=NULL;
    head = (polinom*)malloc(sizeof(polinom) * (brred));
    int i = 0;

    for (; i < brred; i++)
    {
       
        head[i].koef = 0;
        head[i].eks = 0;
        head[i].pok = NULL;
    }

ucitavanjizliste(head,imedat);

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
    
    

    polinom headzbroja = { .koef = 0, .eks = 0, .pok=NULL };
for (i = 0; i < brred; i++)
        zbroj(&headzbroja,&head[i]);
ispisilistu(&headzbroja);
     polinom headumnoska = { .koef = 0, .eks = 0, .pok = NULL };
     for (i = 0; i < brred; i++)
     {
         umnozak(&headumnoska, &head[i]);
         
     }
ispisilistu(&headumnoska);
    return 0;
}

*/





















/*
struct _osoba;
typedef struct _osoba* pozicija;
typedef struct _osoba
{
    char ime[128];
    char prezime[128];
    int godina;
    pozicija pok;
}osoba;

int dodajnapocetak(osoba* pok) //pok heada
{
    
    osoba nova;
    nova.pok = pok;
    pok = &nova;
     scanf(" %s", nova.ime);
     scanf(" %s", nova.prezime);
     scanf("%d", &nova.godina);
    return 0;
}

int ispisi(osoba* poz)
{
   
    if (poz->pok == NULL)
        return -1;
 printf("dotu");
    osoba* a;
    a = poz->pok;
    printf("%s %s %d", a->ime, a->prezime, a->godina);
    for (; a != NULL; a = a->pok)
        printf("%s %s %d", a->ime, a->prezime, a->godina);
    return 0;
}

int dodajnakraj(osoba* pokprije)
{
    osoba nova;
    nova.pok = pokprije;
    pokprije = &nova;

    return 0;
}
int izbrisi(int a, osoba* poz)
{
    int i;
    osoba* pozposlije;
    for (i = 0; i < a - 1; i++)
    {
        poz = poz->pok;
    }
    pozposlije = poz->pok;
    free(poz->pok);
    poz->pok = pozposlije->pok;
    return 0;

}

int dodajiza(char* trazeni, osoba* prije)
{
    osoba* iza;
    for (iza = prije->pok; strcmp(prije->prezime, trazeni) != 0 && iza->pok != NULL; prije = iza, iza = prije->pok)

        if (!strcmp(trazeni, prije->pok))
        {
            osoba novi;
            novi.pok = iza;
            prije->pok = &novi;
            scanf(" %s", novi.ime);
            scanf(" %s", novi.prezime);
            scanf("%d", &novi.godina);
            return 0;
        }
    if (!strcmp(trazeni, iza->pok))
    {
        osoba novi;
        novi.pok = NULL;
        iza->pok = &novi;
        return 0;
    }
    printf("Nije pronađeno");
    return -1;
}


int dodajispred(char* trazeni, osoba* prije)
{
    osoba* iza;
    for (iza = prije->pok; strcmp(iza->prezime, trazeni) != 0 && iza->pok != NULL; prije = iza, iza = prije->pok)

        if (!strcmp(iza->prezime, trazeni))
        {
            osoba novi;
            novi.pok = iza;
            prije->pok = &novi;
            scanf(" %s", novi.ime);
            scanf(" %s", novi.prezime);
            scanf("%d", &novi.godina);
            return 0;
        }
    printf("Nije pronadeno");
    return -1;
}

int mjehuric(osoba* prije, osoba* unesena) // u prije upisojemo pok heda
{
    if (prije == NULL)
    {
        prije = unesena;
        printf("DOUT");
        return 0;
    }
    
    for (; strcmp(prije->prezime, unesena->prezime) < 0 && prije->pok != NULL; prije = prije->pok)

        if (strcmp(prije->prezime, unesena->prezime) == 0)
        {
            for (; strcmp(prije->ime, unesena->ime) < 0 && prije->pok != NULL; prije = prije->pok)

                unesena->pok = prije->pok;
            prije->pok = unesena;
            return 0;
        }
    unesena->pok = prije->pok;
    prije->pok = unesena;
    return 0;
}

int unosisort(osoba* poz)
{
   // osoba novi;
    pozicija novi=NULL;
    novi = (pozicija)malloc(sizeof(osoba));
    char ime[128];
    char prezime[128];
    int godina;

    printf("Ime: ");
    scanf(" %s",ime);
    strcpy(novi->ime, ime);
    printf("Prezime: ");
    scanf(" %s",prezime);
    strcpy(novi->prezime, prezime);
    printf("Godina: ");
    scanf("%d", &godina);
    novi->godina = godina;
   // mjehuric(poz, novi);
    
    return 0;
}

int unososoba(int n, osoba* poz)//poz je pok heada
{
    int i;
    for (i = 0; i < n; i++)
        unosisort(poz);
}

int citanjeisort(char* imedatoteke, osoba* pokheada)
{
    FILE* f;
    f = fopen(imedatoteke, "r");
    if (f == NULL)
        return -1;
    if (pokheada == NULL)
        return -2;
    char time[128];
    char tprezime[128];
    int tgodina;
    char buffer[1024] = { NULL };
    for (; feof(f) == 0; fgets(buffer, 1024, f))
    {
        if (sscanf(buffer, " %s %s %d", time, tprezime, &tgodina) == 3)
        {
            osoba novi;
            strcpy(novi.ime, time);
            strcpy(novi.prezime, tprezime);
            novi.godina = tgodina;
            mjehuric(pokheada, &novi);
        }

    }
    return 0;
}

int upsijelistudat(char* imedat, osoba* pokheada)
{
    FILE* f;
    f = fopen(imedat, "w");
    if (f == NULL)
        return -1;
    osoba* s;
    s = pokheada;
    if (s == NULL)
        return -2;
    for (; s->pok != NULL; s = s->pok)
        fprintf(imedat, "%s %s %d \n", s->ime, s->prezime, &s->godina);

    fprintf(imedat, "%s %s %d", s->ime, s->prezime, &s->godina);
    return 0;
}


int main()
{
    osoba lista;
    *lista.ime = NULL;
    *lista.prezime = NULL;
    lista.godina = NULL;
    lista.pok = NULL;
    pozicija p = &lista;
    unososoba(1, lista.pok);
    ispisi(&lista);
    return 0;
}
*/

/*
struct _osoba;
typedef struct _osoba* pozicija;
typedef struct _osoba
{
    char ime[64];
    char prezime[64];
    int godina;
    pozicija pok;
}osoba;


pozicija napraviosobu(char *ime,char *prezime,int godina)
{
    pozicija nova=NULL;
    nova = (pozicija)malloc(sizeof(osoba));
    if (!nova)
        return -1;
    
    strcpy(nova->ime, ime);
    strcpy(nova->prezime, prezime);
    nova->godina = godina;
    nova->pok = NULL;
    return nova;
}

int dodajnapocetak(pozicija b,pozicija head)
{
    
    b->pok = head->pok;
    head->pok = b;
    return 0;
}

int dodajnakraj(pozicija b, pozicija head)
{
    pozicija temp=NULL;
    
    for (temp = head->pok; temp->pok != NULL; temp = temp->pok)
    {
    }
     temp->pok = b;
       b->pok = NULL;
   return 0;
}

int ispisilistu(pozicija head)
{
    pozicija temp=NULL;
    temp = head->pok;
    while (temp!= NULL)
    {
        printf("%s %s %d \n", temp->ime, temp->prezime, temp->godina);
        temp = temp->pok;
    }
    return 0;
}

pozicija pronadi(char* trazena, pozicija head)
{
    pozicija temp=NULL;
    for (temp = head->pok; strcmp(trazena, temp->prezime) != 0 && temp != NULL; temp = temp->pok)
    {
        if (temp->pok == NULL)
    {
        printf("Nije pronaden element");
        return NULL;
    }
    }
    
       return temp;
}

int obrisi(pozicija head, pozicija nezeljena)
{
    pozicija temp = NULL;
    temp = head;
    pozicija temppok;
    for (; temp->pok != nezeljena; temp = temp->pok)
    {
        temppok = temp->pok;
        if (temppok->pok == NULL)
        {
            printf("Nije pronaden element");
                return -1;
        }
    }
    temp->pok = nezeljena->pok;
      free(nezeljena);
    
      return 0;
}

int dodajiza(pozicija b,pozicija a)
{
    b->pok = a->pok;
    a->pok = b;
    return 0;
}
int dodajprije(pozicija a, pozicija b,pozicija head)
{
    pozicija temp=NULL;
       for (temp = head; temp->pok != b; temp = temp->pok)
       {
       }
       dodajiza(a, temp);
       
    return 0;
}

int mjehuric(pozicija head, pozicija novi)
{
    pozicija temp = head->pok;

    for (; strcmp(temp->prezime, novi->prezime)<0 && temp != NULL; temp = temp->pok)
    {
    }
    dodajprije(novi, temp, head);

    return 0;
}

int upisisort(pozicija head,char* ime,char *prezime, int godina)
{
    pozicija nova = NULL;
    nova = napraviosobu(ime, prezime, godina);
    return 0;
}

int ucitizdat(char* imedat,pozicija head)
{
    FILE* f=NULL;
    f = fopen(imedat, "r");
    char ime[128];
    char prezime[128];
    int godina;
    char buffer[1024];
    for (; feof(f) == 0; fgets(buffer, 1024, f))
    {
        if (sscanf(buffer, " %s %s %d", ime, prezime, &godina) == 3)
            upisisort(head, ime, prezime, godina);
    }
    return 0;
}


int upisudat(char* imedat, pozicija head)
{
    FILE* f = NULL;
    f = fopen(imedat, "w");
    pozicija temp;
    for (temp = head->pok; temp != NULL; temp = temp->pok)
    {
        fprintf(f, "%s %s %d \n", temp->ime, temp->prezime, temp->godina);
    }

    return 0;
}

int main()
    {
    osoba head = { .pok = NULL, .ime = {0}, .prezime = {0}, .godina = 0 };
    pozicija heada = NULL;
    heada=&head;
    pozicija a, b, c;
    a = napraviosobu("prva", "aaa", 12);
    b = napraviosobu("druga", "bbb", 13);
    c = napraviosobu("treca", "ccc", 11);
    dodajnapocetak(b, heada);
    dodajnapocetak(a, heada);
    dodajnakraj(c, heada);
    ispisilistu(heada);
    pozicija ne=NULL;
    ne = pronadi("aa", heada);
    obrisi(heada, ne);
    ispisilistu(heada);
    
    return 0;
    }


    */


/*
  #include<stdio.h>
  int main()
  {
      int a;
      scanf_s("%d", &a);
    printf("OK");
    return 0;
  }

struct _osoba;
typedef struct _osoba* pozicija;
typedef struct _osoba
{
    char ime[64];
    char prezime[64];
    int godina;
    pozicija sljedeci;
}osoba;


pozicija napraviosobu()
{
    pozicija nova = NULL;
    nova = (pozicija)malloc(sizeof(osoba));
    char ime[64];
    char prezime[64];
    int godina;
    scanf(" %s %s %s", ime, prezime, &godina);
    strcpy(nova->ime, ime);
    strcpy(nova->prezime, prezime);
    nova->godina = godina;
    nova->sljedeci = NULL;
    return nova;
}


int dodajnapocetak(pozicija head) //prima head
{
    pozicija nova = NULL;
    nova = (pozicija)malloc(sizeof(osoba));
    head->sljedeci = nova;

}

int dodajnakraj(pozicija prije) //prima head
{
    pozicija nova = NULL;
    pozicija temp;
    temp = prije->sljedeci;
    nova = (pozicija)malloc(sizeof(osoba));
    for(;temp!=NULL;prije = temp,temp=prije->sljedeci)
    temp= nova;
    return 0;
}

pozicija pronadi(pozicija head, char* prezime)
{
    pozicija temp=head->sljedeci;

    for (; temp != NULL; strcmp(temp->prezime, prezime) != 0, head = temp, temp = head->sljedeci)

        return temp;

}

int obrisi(pozicija head, char* prezime)
{
    pozicija odredeni;
    odredeni = pronadi(head, prezime);
    pozicija temp;
    temp = head->sljedeci;
    for (; temp->sljedeci != odredeni; head = temp, temp = head->sljedeci)

        temp->sljedeci = odredeni->sljedeci;
    free(odredeni);
    return 0;

}

int dodajiza(pozicija head, char* koga)
{
    pozicija novi;
    pozicija prije;
    pozicija temp;
    temp = head;
    prije= pronadi(head, koga);
    novi = napraviosobu();
    temp = head->sljedeci;
    for (; temp->sljedeci != prije; head = temp, temp = head->sljedeci);
    novi->sljedeci = prije->sljedeci;
    prije->sljedeci = novi;
}
int dodajprije(pozicija head, char* koga)
{
    pozicija novi;
    pozicija iza;
    pozicija temp;
    novi = napraviosobu();
    iza = pronadi(head, koga);
    for (; temp->sljedeci != iza; head = temp, temp = head->sljedeci)
       
    dodajiza(head, iza->prezime);

}

int sortiunos(pozicija head)
{
    pozicija novi = NULL;
    pozicija temp = head;
    novi = napraviosobu();


    while (temp->sljedeci != NULL && strcmp(temp->sljedeci->prezime, novi->prezime < 0)
        temp = temp->sljedeci;
    novi->sljedeci = temp->sljedeci;
    temp->sljedeci = novi;

    return 0;
}

int ucitavanjeiz(pozicija head, char* imedatoteke)
{
    char buffer[1024];
    char ime[50];
    char prezime[50];
    int godina;
    pozicija nova = NULL;
    pozicija temp = head;
    FILE* f = NULL;
    f = fopen(imedatoteke, "r");
    while (feof(f) == 0)
    {        
        fgets(buffer, 1024, f);
        if (ssscanf(buffer, " %s %s %d", ime, prezime, &godina) == 3)
        {
            nova = (pozicija) malloc(sizeof(osoba));
            strcpy(nova->ime, ime);
            strcpy(nova->prezime, prezime);
            nova->godina = godina;
            temp = temp->sljedeci;
        }
}
    return 0;

}

int unosudat(pozicija head, char* ime)
{
    FILE* f=NULL;
    pozicija temp = NULL;
    temp = head;
    f = fopen(ime, "w");
    while (temp->sljedeci != NULL)
    {
        fprintf(f, "%s %s %d", temp->next->ime, temp->next->prezime, temp->next->godina);
        temp = temp->sljedeci;
    }
    return 0;
}

int main()
{
    osoba head = { .sljedeci = NULL, .ime = {0}, .prezime = {0}, .godina = 0 };
    pozicija p = &head;
    pozicija a, b, c;
        a = napraviosobu();
        b = napraviosobu();
        c = napraviosobu(); 


}


*/

