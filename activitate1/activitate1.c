/*Acest folder de activitate cuprinde doar partea de cod pe care am scris-o personal
in cadrul seminarului 3. Pentru codul complet, accesati folderul seminar3.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Locuinta {
	int id;
	char* strada;
	int numar;
};

void citesteFisier(const char* nume_fisier, struct Locuinta** vector,
	int* dim) {
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
				//...
			}
			fclose(f);
		}
	}
}

void main() {
	//...
}