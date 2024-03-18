/*Acest folder de activitate cuprinde doar partea de cod pe care am scris-o personal
in cadrul seminarului 4. Pentru codul complet, accesati folderul seminar4.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Locuinta {
	int id;
	char* strada;
	int numar;
};

void inserareLocuinta(struct Locuinta** vector, int* dim,
	struct Locuinta l)
{
	struct Locuinta* copie;
	copie = malloc(sizeof(struct Locuinta) *
		(++(*dim)));
	for (int i = 0; i < (*dim) - 1; i++)
	{
		copie[i] = (*vector)[i];
	}
	copie[(*dim) - 1] = l;
	if ((*vector) != NULL)
	{
		free((*vector));
	}
	(*vector) = copie;
}

void citesteMatriceFisier(const char* nume_fisier, struct Locuinta** matrice, int nr_linii, int* nr_coloane) {
	if (nume_fisier != NULL && strlen(nume_fisier) > 0) {
		FILE* f = fopen(nume_fisier, "r");
		if (f != NULL) {
			char buffer[100];
			char delimitator[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {
				char* token;
				token = strtok(buffer, delimitator);
				struct Locuinta locuinta;
				locuinta.id = atoi(token);
				token = strtok(NULL, delimitator);
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);
				token = strtok(NULL, delimitator);
				locuinta.numar = atoi(token);
				int pozitie = locuinta.numar % 2;
				inserareLocuinta(&(matrice[pozitie]), &(nr_coloane[pozitie]), locuinta);
			}
			fclose(f);
		}
	}
}

void main() {
	int nr_linii;
	int* nr_coloane;
	struct Locuinta** matrice;

	nr_linii = 2;
	nr_coloane = (int*)malloc(sizeof(int) * nr_linii);
	matrice = (struct Locuinta**)malloc(sizeof(struct Locuinta*) * nr_linii);
	for (int i = 0; i < nr_linii; i++) {
		matrice[i] = NULL;
		nr_coloane[i] = 0;
	}
}