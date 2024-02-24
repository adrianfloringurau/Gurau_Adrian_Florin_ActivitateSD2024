//C
#include <stdio.h>
#include <stdlib.h>

//Gurău Adrian-Florin -> G, A si F

enum Culoare {
	ALB, ROSU, ALBASTRU, GALBEN, MOV
};

struct Girofar {
	char* cod; //cod unic de identificare
	int nrCulori; //numarul culorilor din lista ordonata
	enum Culoare* culori; //culorile efective ce se vor afisa in ordinea mentionata
	double* timpAfisareCuloare; //timpul de afisare (in secunde) al fiecarei culori
	int* nivelIntensitateCuloare; //intensitatea (in procent) fiecarei culori
	float putere; //masurati in watti
	float rezistenta; //masurati in ohmi
	float voltaj; //masurat in volti
};

void initializeaza(struct Girofar* girofar) {
	(*girofar).cod = NULL;
	(*girofar).nrCulori = 0;
	(*girofar).culori = NULL;
	(*girofar).timpAfisareCuloare = NULL;
	(*girofar).nivelIntensitateCuloare = NULL;
	(*girofar).putere = 0;
	(*girofar).rezistenta = 0;
	(*girofar).voltaj = 0;
}

struct Girofar citeste() {
	struct Girofar obiect;

	char buffer[100] = "";
	do {
		printf("\nIntroduceti codul de identificare al girofarului (>2caractere): ");
		scanf_s(" %[^\n]s", &buffer, (unsigned int)sizeof(buffer)); //rezolva asta
	} while (strlen(buffer) <= 2);
	obiect.cod = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(obiect.cod, buffer);

	do {
		printf("\nIntroduceti nr de culori (>0): ");
		scanf_s("%d", &obiect.nrCulori);
	} while (obiect.nrCulori <= 0);

	obiect.culori = (enum Culoare*)malloc(sizeof(enum Culoare) * obiect.nrCulori);
	obiect.timpAfisareCuloare = (double*)malloc(sizeof(double) * obiect.nrCulori);
	obiect.nivelIntensitateCuloare = (int*)malloc(sizeof(int) * obiect.nrCulori);

	int alegere;
	for (int i = 0; i < obiect.nrCulori; i++) {
		do {
			printf("\nCuloarea %d (ALB = 0, ROSU = 1, ALBASTRU = 2, GALBEN = 3, MOV = 4): ", i + 1);
			scanf_s("%d", &alegere);
			switch (alegere) {
			case 0:
				obiect.culori[i] = ALB; break;
			case 1:
				obiect.culori[i] = ROSU; break;
			case 2:
				obiect.culori[i] = ALBASTRU; break;
			case 3:
				obiect.culori[i] = GALBEN; break;
			case 4:
				obiect.culori[i] = MOV; break;
			}
		} while (alegere != 0 && alegere != 1 && alegere != 2 && alegere != 3 && alegere != 4);
		do {
			printf("\nTimp %d (>0): ", i + 1);
			scanf_s("%lf", &obiect.timpAfisareCuloare[i]);
		} while (obiect.timpAfisareCuloare[i] <= 0);
		do {
			printf("\nIntensitate %d (0-100): ", i + 1);
			scanf_s("%d", &obiect.nivelIntensitateCuloare[i]);
		} while (obiect.nivelIntensitateCuloare[i] < 0 || obiect.nivelIntensitateCuloare[i] > 100);
	}
	do {
		printf("Putere: ");
		scanf_s("%f", &obiect.putere);
	} while (obiect.putere <= 0);
	do {
		printf("Rezistenta: ");
		scanf_s("%f", &obiect.rezistenta);
	} while (obiect.rezistenta <= 0);
	do {
		printf("Voltaj: ");
		scanf_s("%f", &obiect.voltaj);
	} while (obiect.voltaj <= 0);

	return obiect;
}

void setValori(struct Girofar* obiect, const char* cod, int nrCulori, enum Culoare* culori,
	double* timpAfisareCuloare, int* nivelIntensitateCuloare,
	float putere, float rezistenta, float voltaj)
{
	if ((*obiect).cod != NULL) {
		free((*obiect).cod);
		(*obiect).cod = NULL;
	}

	if (cod != NULL && strlen(cod) > 0) {	
		(*obiect).cod = (char*)malloc(sizeof(char) * strlen(cod) + 1);
		strcpy((*obiect).cod, cod);
	}

	if (nrCulori > 0 && culori != NULL && timpAfisareCuloare != NULL
		&& nivelIntensitateCuloare != NULL) {
		(*obiect).nrCulori = nrCulori;
		if ((*obiect).culori != NULL) {
			free(obiect->culori);
			(*obiect).culori = NULL;
		}
		if ((*obiect).timpAfisareCuloare != NULL) {
			free((*obiect).timpAfisareCuloare);
			(*obiect).timpAfisareCuloare = NULL;
		}
		if ((*obiect).nivelIntensitateCuloare != NULL) {
			free((*obiect).nivelIntensitateCuloare);
			(*obiect).nivelIntensitateCuloare = NULL;
		}
		(*obiect).culori = (enum Culoare*)malloc(sizeof(enum Culoare) * (*obiect).nrCulori);
		(*obiect).timpAfisareCuloare = (double*)malloc(sizeof(double) * (*obiect).nrCulori);
		(*obiect).nivelIntensitateCuloare = (int*)malloc(sizeof(int) * (*obiect).nrCulori);
		for (int i = 0; i < (*obiect).nrCulori; i++) {
			(*obiect).culori[i] = culori[i];
			(*obiect).timpAfisareCuloare[i] = timpAfisareCuloare[i];
			(*obiect).nivelIntensitateCuloare[i] = nivelIntensitateCuloare[i];
		}
	}
	else (*obiect).nrCulori = 0;

	if (putere > 0) (*obiect).putere = putere;
	else (*obiect).putere = 0;

	if (rezistenta > 0) (*obiect).rezistenta = rezistenta;
	else (*obiect).rezistenta = 0;

	if (voltaj > 0) (*obiect).voltaj = voltaj;
	else (*obiect).voltaj = 0;
}

double calculeazaTimpTotalCuloare(const struct Girofar* girofar, enum Culoare culoare) {
	if ((*girofar).nrCulori > 0 && (*girofar).culori != NULL && (*girofar).timpAfisareCuloare != NULL) {
		double timpTotal = 0;
		for (int i = 0; i < (*girofar).nrCulori; i++)
			if ((*girofar).culori[i] == culoare)
				timpTotal += (*girofar).timpAfisareCuloare[i];
		return timpTotal;
	}
	else return 0;
}

void setCuloriGirofar(struct Girofar* girofar, int nrCulori,
	enum Culoare* culori, double* timpAfisareCuloare,
	int* nivelIntensitateCuloare)
{
	if (nrCulori > 0 && culori != NULL && timpAfisareCuloare != NULL
		&& nivelIntensitateCuloare != NULL) {
		(*girofar).nrCulori = nrCulori;
		if ((*girofar).culori != NULL) {
			free((*girofar).culori);
			(*girofar).culori = NULL;
		}
		if ((*girofar).timpAfisareCuloare != NULL) {
			free((*girofar).timpAfisareCuloare);
			(*girofar).timpAfisareCuloare = NULL;
		}
		if ((*girofar).nivelIntensitateCuloare != NULL) {
			free((*girofar).nivelIntensitateCuloare);
			(*girofar).nivelIntensitateCuloare = NULL;
		}
		(*girofar).culori = (enum Culoare*)malloc(sizeof(enum Culoare) * (*girofar).nrCulori);
		(*girofar).timpAfisareCuloare = (double*)malloc(sizeof(double) * (*girofar).nrCulori);
		(*girofar).nivelIntensitateCuloare = (int*)malloc(sizeof(int) * (*girofar).nrCulori);
		for (int i = 0; i < (*girofar).nrCulori; i++) {
			(*girofar).culori[i] = culori[i];
			(*girofar).timpAfisareCuloare[i] = timpAfisareCuloare[i];
			(*girofar).nivelIntensitateCuloare[i] = nivelIntensitateCuloare[i];
		}
	}
	else (*girofar).nrCulori = 0;
}

void afiseaza(const struct Girofar* girofar) {
	printf("\n--------------------GIROFAR--------------------");
	printf("\nCod: ");
	if ((*girofar).cod != NULL && strlen((*girofar).cod) > 0)
		printf((*girofar).cod);
	else printf("-");
	printf("\nNr culori: %d" , (*girofar).nrCulori);
	if ((*girofar).nrCulori > 0 && (*girofar).culori != NULL &&
		(*girofar).timpAfisareCuloare != NULL &&
		(*girofar).nivelIntensitateCuloare != NULL) {
		printf("\nCulori: ");
		for (int i = 0; i < (*girofar).nrCulori; i++) {
			printf("\n  ");
			switch ((*girofar).culori[i]) {
			case ALB:
				printf("Alb"); break;
			case ROSU:
				printf("Rosu"); break;
			case ALBASTRU:
				printf("Albastru"); break;
			case GALBEN:
				printf("Galben"); break;
			case MOV:
				printf("Mov"); break;
			}
			printf(" - %5.2lf secunde | ", (*girofar).timpAfisareCuloare[i]);
			printf("Intensitate: %d%%", (*girofar).nivelIntensitateCuloare[i]);
		}
	}
	printf("\nPutere: %5.2fW", (*girofar).putere);
	printf("\nRezistenta: %5.2fohm", (*girofar).rezistenta);
	printf("\nVoltaj: %5.2fV", (*girofar).voltaj);
	printf("\n-----------------------------------------------");
}

void dezalocare(struct Girofar* girofar) {
	(*girofar).nrCulori = 0;
	if ((*girofar).cod != NULL) {
		free((*girofar).cod);
		(*girofar).cod = NULL;
	}
	if ((*girofar).culori != NULL) {
		free((*girofar).culori);
		(*girofar).culori = NULL;
	}
	if ((*girofar).timpAfisareCuloare != NULL) {
		free((*girofar).timpAfisareCuloare);
		(*girofar).timpAfisareCuloare = NULL;
	}
	if ((*girofar).nivelIntensitateCuloare != NULL) {
		free((*girofar).nivelIntensitateCuloare);
		(*girofar).nivelIntensitateCuloare = NULL;
	}
}

void main() {
	enum Culoare culori[3] = { ALB, ROSU, ALB };
	double timp[3] = { 3.47, 8.84, 1.12 };
	int intensitate[3] = { 30, 60, 90 };
	struct Girofar girofar;
	initializeaza(&girofar);

	afiseaza(&girofar); //girofar neinitializat

	setValori(&girofar, "XA-20 .24", 3, culori, timp, intensitate, 16, 36, 12);

	afiseaza(&girofar); //girofar cu valori date ca parametri

	double timpTotal = calculeazaTimpTotalCuloare(&girofar, ALB);
	printf("\n\nTimpul total de afisare al culorii \"ALB\" in g1 este: %5.2lf secunde.\n", timpTotal);

	enum Culoare new_culori[6] = { ALB, ROSU, ALBASTRU, MOV, ALB, ROSU };
	double new_timp[6] = { 5.67, 3.23, 1.29, 8.88, 3.41, 9.21 };
	int new_intensitate[6] = { 100, 90, 60, 80, 70, 100 };

	setCuloriGirofar(&girofar, 6, new_culori, new_timp, new_intensitate);

	afiseaza(&girofar); //girofar cu valori modificate prin parametri

	struct Girofar new_girofar = citeste();

	afiseaza(&new_girofar); //girofar cu valori citite de la tastatura

	dezalocare(&girofar);
	dezalocare(&new_girofar);

	//testam afisarea celor 2 obiecte dupa dezalocare
	afiseaza(&girofar);
	afiseaza(&new_girofar);
}