#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define BOY 100

char vorname[BOY][20];
char nachname[BOY][20];
char adresse[BOY][20];
char telefonnummer[BOY][20];

int menu();
void Kundenregistrierung();
void auflisten();
void kundenFinden();
void speichern();
void zuruckSpeichern();
void eingang(char*);

int count = 0;

int main()
{
    int wahl;

    do {
        wahl = menu();

        switch (wahl) {
        case 1: Kundenregistrierung(); break;
        case 2: kundenFinden(); break;
        case 3: auflisten(); break;
        case 4: speichern(); break;
        case 5: zuruckSpeichern(); break;
        }
    } while (wahl != 0);

    return 0;
}

int menu() {
    int wahl;

    printf("\n\n\nKundenregistrierungs-App\n\n");
    printf("[1] Neu Registrierung\n");
    printf("[2] Finden\n");
    printf("[3] Auflisten\n");
    printf("[4] Speichern\n");
    printf("[5] Zuruck Speichern\n");
    printf("[0] schliessen\n");

    do {
        printf("\nWählen Sie bitte [0-5] :\n");
        wahl = _getche() - '0'; // Düzgün bir şekilde işleniyor
    } while (wahl < 0 || wahl > 5);

    return wahl;
}

void Kundenregistrierung() {
    printf("\nVorname: "); eingang(vorname[count]);
    printf("Nachname: "); eingang(nachname[count]);
    printf("Adresse: "); eingang(adresse[count]);
    printf("Telefonnummer: "); eingang(telefonnummer[count]);

    count++;
    printf("\nFertig!\n");
}


void kundenFinden() {
    char suchenPerson[20];
    printf("\nVorname: "); eingang(suchenPerson);
    int i = 0;
    int abschluss = 0, schalter=0;
    while (i < count) {
        if (strcmp(suchenPerson, vorname[i]) == 0) {
            if(schalter ==0)
            printf("\n%-20s%-20s%-20s%-20s\n","Vorname","Nachname", "Adresse", "Telefonnummer");
            printf("\n%-20s%-20s%-20s%-20s\n", vorname[i], nachname[i], adresse[i], telefonnummer[i]);;
            schalter++;
        }
        i++;

    }
    if (schalter == 0) {
        printf("\n%s Keine Eintragung!\n", suchenPerson );
    }
    else
        printf("\n%d Datensätze gefunden",  schalter);
    // TODO: Bir müşteri bul
}

void auflisten() {
    if (count == 0) {
        printf("\nKeine Eintragungen vorhanden!\n");
        return;
    }

    printf("\n%-20s%-20s%-20s%-20s\n", "Vorname", "Nachname", "Adresse", "Telefonnummer");

    for (int i = 0; i < count; i++) {
        printf("%-20s%-20s%-20s%-20s\n", vorname[i], nachname[i], adresse[i], telefonnummer[i]);
    }

    printf("\n%d Datensätze gefunden\n", count);
}


void speichern() {
    FILE* ptr;
    if ((ptr = fopen("kunden.txt", "w")) == NULL) {
        printf("Error");
        exit(1);
    }
    else
        printf("\nFertig!\n");

    for (int i = 0; i < count; i++) {
        fprintf(ptr, "%-20s%-20s%-20s%-20s\n", vorname[i], nachname[i], adresse[i], telefonnummer[i]);
    }

    fclose(ptr);
}

void zuruckSpeichern() {
    FILE* ptr;
    if ((ptr = fopen("kunden.txt", "r")) == NULL) {
        printf("\nError\n");
        exit(1);
    }
    
    count = 0;
    while (count < BOY && fscanf(ptr, "%19s%19s%19s%19s", vorname[count], nachname[count], adresse[count], telefonnummer[count]) == 4) {
        count++;
    }

    fclose(ptr);

    if (count == 0) {
        printf("Error\n");
    }
    else {
        printf("\n\nDaten wurden zuruckgeladen.\n");
    }
}


void eingang(char* ptr) {
    fgets(ptr, 20, stdin);
    int n = strlen(ptr);
    ptr[n - 1] = '\0';
}
