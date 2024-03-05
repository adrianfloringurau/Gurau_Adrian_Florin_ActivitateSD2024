//C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		scanf_s(" %[^\n]s", &buffer, (unsigned int)sizeof(buffer));
	} while (strlen(buffer) <= 2);
	obiect.cod = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy_s(obiect.cod, strlen(buffer) + 1, buffer);

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
		strcpy_s((*obiect).cod, strlen(cod) + 1, cod);
	}

	if (nrCulori > 0 && culori != NULL && timpAfisareCuloare != NULL
		&& nivelIntensitateCuloare != NULL) {
		(*obiect).nrCulori = nrCulori;
		if ((*obiect).culori != NULL) {
			free((*obiect).culori);
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
			if (obiect->culori != NULL)
				(*obiect).culori[i] = culori[i];
			if (obiect->timpAfisareCuloare != NULL)
				(*obiect).timpAfisareCuloare[i] = timpAfisareCuloare[i];
			if (obiect->nivelIntensitateCuloare != NULL)
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
			if (girofar->culori != NULL)
				(*girofar).culori[i] = culori[i];
			if (girofar->timpAfisareCuloare != NULL)
				(*girofar).timpAfisareCuloare[i] = timpAfisareCuloare[i];
			if (girofar->nivelIntensitateCuloare != NULL)
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
	printf("\nNr culori: %d", (*girofar).nrCulori);
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

void dezalocare_vector(struct Girofar** vector, int dim) {
	if (*vector != NULL) {
		for (int i = 0; i < dim; i++)
			dezalocare(&((*vector)[i]));
		free(*vector);
		*vector = NULL;
	}
}

void restrictTimp(const struct Girofar* input, int dim_input, struct Girofar** output, int* dim_output, double timp_minim, double timp_maxim) {
	dezalocare_vector(&*output, *dim_output);
	*dim_output = 0;
	if (dim_input > 0 && input != NULL) {
		if (timp_maxim < timp_minim) {
			double aux = timp_maxim;
			timp_maxim = timp_minim;
			timp_minim = aux;
		}
		int ok;
		for (int i = 0; i < dim_input; i++) {
			ok = 1;
			for (int j = 0; j < input[i].nrCulori && ok; j++)
				if (!(input[i].timpAfisareCuloare[j] >= timp_minim && input[i].timpAfisareCuloare[j] <= timp_maxim)) ok = 0;
			if (ok == 1) (*dim_output)++;
		}

		*output = (struct Girofar*)malloc(sizeof(struct Girofar) * (*dim_output));
		if (*output != NULL) {
			int k = 0;
			for (int i = 0; i < dim_input; i++) {
				ok = 1;
				for (int j = 0; j < input[i].nrCulori && ok; j++)
					if (!(input[i].timpAfisareCuloare[j] >= timp_minim && input[i].timpAfisareCuloare[j] <= timp_maxim)) ok = 0;
				if (ok == 1 && k < *dim_output) {
					initializeaza(&((*output)[k]));
					setValori(&((*output)[k++]), input[i].cod, input[i].nrCulori, input[i].culori, input[i].timpAfisareCuloare, input[i].nivelIntensitateCuloare, input[i].putere, input[i].rezistenta, input[i].voltaj);
					//(*output)[k++] = input[i];
				}
			}
		}
	}
}

void restrictIntensitate(const struct Girofar* input, int dim_input, struct Girofar** output, int* dim_output, double intensitate_minima, double intensitate_maxima) {
	dezalocare_vector(&*output, *dim_output);
	*dim_output = 0;
	if (dim_input > 0 && input != NULL) {
		if (intensitate_maxima < intensitate_minima) {
			double aux = intensitate_maxima;
			intensitate_maxima = intensitate_minima;
			intensitate_minima = aux;
		}
		if (intensitate_maxima > 100) intensitate_maxima = 100;
		if (intensitate_minima < 0) intensitate_minima = 0;
		int ok;
		for (int i = 0; i < dim_input; i++) {
			ok = 1;
			for (int j = 0; j < input[i].nrCulori && ok; j++)
				if (!(input[i].nivelIntensitateCuloare[j] >= intensitate_minima && input[i].nivelIntensitateCuloare[j] <= intensitate_maxima)) ok = 0;
			if (ok == 1) (*dim_output)++;
		}
		*output = (struct Girofar*)malloc(sizeof(struct Girofar) * (*dim_output));
		if (*output != NULL) {
			int k = 0;
			for (int i = 0; i < dim_input; i++) {
				ok = 1;
				for (int j = 0; j < input[i].nrCulori && ok; j++)
					if (!(input[i].nivelIntensitateCuloare[j] >= intensitate_minima && input[i].nivelIntensitateCuloare[j] <= intensitate_maxima)) ok = 0;
				if (ok == 1 && k < *dim_output) {
					initializeaza(&((*output)[k]));
					setValori(&((*output)[k++]), input[i].cod, input[i].nrCulori, input[i].culori, input[i].timpAfisareCuloare, input[i].nivelIntensitateCuloare, input[i].putere, input[i].rezistenta, input[i].voltaj);
					//(*output)[k++] = input[i];
				}
			}
		}
	}
}

void afiseaza_vector(const struct Girofar* vector, int dim) {
	if (dim > 0) {
		for (int i = 0; i < dim; i++)
			afiseaza(&vector[i]);
	}
	else printf("-");
}

char equals_girofar(const struct Girofar* g1, const struct Girofar* g2) {
	if (g1 != g2) {
		if (g1->cod != NULL && g2->cod == NULL) return 0;
		if (g1->cod == NULL && g2->cod != NULL) return 0;
		if (g1->cod != NULL && g2->cod != NULL && strcmp(g1->cod, g2->cod) != 0) return 0;
		if (g1->nrCulori != NULL && g2->nrCulori == NULL) return 0;
		if (g1->nrCulori == NULL && g2->nrCulori != NULL) return 0;
		if (g1->nrCulori != NULL && g2->nrCulori != NULL && g1->nrCulori != g2->nrCulori) return 0;
		if (g1->nrCulori != NULL && g2->nrCulori != NULL && g1->culori != NULL && g2->culori != NULL &&
			g1->timpAfisareCuloare != NULL && g2->timpAfisareCuloare != NULL &&
			g1->nivelIntensitateCuloare != NULL && g2->nivelIntensitateCuloare != NULL) {
			for (int i = 0; i < g1->nrCulori; i++) {
				if (g1->culori[i] != g2->culori[i]) return 0;
				if (g1->timpAfisareCuloare[i] != g2->timpAfisareCuloare[i]) return 0;
				if (g1->nivelIntensitateCuloare[i] != g2->nivelIntensitateCuloare[i]) return 0;
			}
		}
		if (g1->putere != g2->putere) return 0;
		if (g1->rezistenta != g2->rezistenta) return 0;
		if (g1->voltaj != g2->voltaj) return 0;

		return 1;
	}
	return 1;
}

void concat_vectori(const struct Girofar* input1, int dim1, const struct Girofar* input2, int dim2, struct Girofar** output, int* dim_output) {
	dezalocare_vector(output, *dim_output);
	*dim_output = 0;

	*output = (struct Girofar*)malloc(sizeof(struct Girofar) * (dim1 + dim2));
	if (*output == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}

	for (int i = 0; i < dim1; i++) {
		int ok = 1;
		for (int k = 0; k < *dim_output; k++) {
			if (equals_girofar(&input1[i], &(*output)[k])) {
				ok = 0;
				break;
			}
		}
		if (ok) {
			initializeaza(&((*output)[*dim_output]));
			setValori(&((*output)[(*dim_output)++]), input1[i].cod, input1[i].nrCulori, input1[i].culori, input1[i].timpAfisareCuloare, input1[i].nivelIntensitateCuloare, input1[i].putere, input1[i].rezistenta, input1[i].voltaj);
		}
	}

	for (int j = 0; j < dim2; j++) {
		int ok = 1;
		for (int k = 0; k < *dim_output; k++) {
			if (equals_girofar(&input2[j], &(*output)[k])) {
				ok = 0;
				break;
			}
		}
		if (ok) {
			initializeaza(&((*output)[*dim_output]));
			setValori(&((*output)[(*dim_output)++]), input2[j].cod, input2[j].nrCulori, input2[j].culori, input2[j].timpAfisareCuloare, input2[j].nivelIntensitateCuloare, input2[j].putere, input2[j].rezistenta, input2[j].voltaj);
		}
	}
}

void readVectorFromFile(const char* nume_fisier, struct Girofar** v_out, int* dim_out) {
	dezalocare_vector(&*v_out, *dim_out);
	*dim_out = 0;
	if (nume_fisier != NULL && strlen(nume_fisier) > 0) {
		FILE* f = fopen(nume_fisier, "r");
		if (f != NULL) {
			int rez;
			rez = fscanf_s(f, " %d \n", &(*dim_out));
			if (rez == 1) {
				*v_out = (struct Girofar*)malloc(sizeof(struct Girofar) * (*dim_out));
				for (int i = 0; i < *dim_out; i++) {
					char buffer[100] = "";
					rez = fscanf_s(f, " %[^,]s ", buffer, (unsigned int)sizeof(buffer));
					if (rez == 1) {
						(*v_out)[i].cod = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
						strcpy_s((*v_out)[i].cod, strlen(buffer) + 1, buffer);
					}
					rez = fscanf_s(f, ", %d \n", &(*v_out)[i].nrCulori);
					if (rez == 1) {
						(*v_out)[i].culori = (enum Culoare*)malloc(sizeof(enum Culoare) * ((*v_out)[i].nrCulori));
						(*v_out)[i].timpAfisareCuloare = (double*)malloc(sizeof(double) * ((*v_out)[i].nrCulori));
						(*v_out)[i].nivelIntensitateCuloare = (int*)malloc(sizeof(int) * ((*v_out)[i].nrCulori));
						if ((*v_out)[i].nrCulori > 0) {
							for (int j = 0; j < (*v_out)[i].nrCulori - 1; j++) {
								char buffer[100] = "";
								rez = fscanf_s(f, " %[^,]s ", buffer, (unsigned int)sizeof(buffer));
								if (rez == 1) {
									if (strcmp(buffer, "alb") == 0)
										(*v_out)[i].culori[j] = ALB;
									else if (strcmp(buffer, "rosu") == 0)
										(*v_out)[i].culori[j] = ROSU;
									else if (strcmp(buffer, "albastru") == 0)
										(*v_out)[i].culori[j] = ALBASTRU;
									else if (strcmp(buffer, "galben") == 0)
										(*v_out)[i].culori[j] = GALBEN;
									else if (strcmp(buffer, "mov") == 0)
										(*v_out)[i].culori[j] = MOV;
									else
										(*v_out)[i].culori[j] = ALB;
								}
								rez = fscanf_s(f, ", %lf , %d ,", &(*v_out)[i].timpAfisareCuloare[j], &(*v_out)[i].nivelIntensitateCuloare[j]);
							}
							rez = fscanf_s(f, " %[^,]s ", buffer, (unsigned int)sizeof(buffer));
							if (rez == 1) {
								if (strcmp(buffer, "alb") == 0)
									(*v_out)[i].culori[(*v_out)[i].nrCulori - 1] = ALB;
								else if (strcmp(buffer, "rosu") == 0)
									(*v_out)[i].culori[(*v_out)[i].nrCulori - 1] = ROSU;
								else if (strcmp(buffer, "albastru") == 0)
									(*v_out)[i].culori[(*v_out)[i].nrCulori - 1] = ALBASTRU;
								else if (strcmp(buffer, "galben") == 0)
									(*v_out)[i].culori[(*v_out)[i].nrCulori - 1] = GALBEN;
								else if (strcmp(buffer, "mov") == 0)
									(*v_out)[i].culori[(*v_out)[i].nrCulori - 1] = MOV;
								else
									(*v_out)[i].culori[(*v_out)[i].nrCulori - 1] = ALB;
							}
						}
						rez = fscanf_s(f, ", %lf , %d \n", &(*v_out)[i].timpAfisareCuloare[(*v_out)[i].nrCulori - 1], &(*v_out)[i].nivelIntensitateCuloare[(*v_out)[i].nrCulori - 1]);
						rez = fscanf_s(f, " %f , %f , %f ", &(*v_out)[i].putere, &(*v_out)[i].rezistenta, &(*v_out)[i].voltaj);
					}
				}
				fclose(f);
			}
		}
	}
}

int writeGirofarToFile(const char* nume_fisier, const struct Girofar* g) {
	if (nume_fisier != NULL && strlen(nume_fisier) > 0 && g != NULL) {
		FILE* f = fopen(nume_fisier, "w");
		if (f != NULL) {
			if (g->cod != NULL && strlen(g->cod) > 0)
				fprintf(f, "%s, ", g->cod);
			else fprintf(f, "N/A, ");
			fprintf(f, "%d\n", g->nrCulori);
			if (g->nrCulori > 0 && g->culori != NULL && g->timpAfisareCuloare != NULL && g->nivelIntensitateCuloare != NULL) {
				for (int i = 0; i < g->nrCulori - 1; i++) {
					switch (g->culori[i]) {
					case ALB: fprintf(f, "alb,"); break;
					case ROSU: fprintf(f, "rosu,"); break;
					case ALBASTRU: fprintf(f, "albastru,"); break;
					case GALBEN: fprintf(f, "galben,"); break;
					case MOV: fprintf(f, "mov,"); break;
					}
					fprintf(f, "%5.2lf, %i, ", g->timpAfisareCuloare[i], g->nivelIntensitateCuloare[i]);
				}
				switch (g->culori[g->nrCulori - 1]) {
				case ALB: fprintf(f, "alb,"); break;
				case ROSU: fprintf(f, "rosu,"); break;
				case ALBASTRU: fprintf(f, "albastru,"); break;
				case GALBEN: fprintf(f, "galben,"); break;
				case MOV: fprintf(f, "mov,"); break;
				}
				fprintf(f, "%5.2lf, %i\n", g->timpAfisareCuloare[g->nrCulori - 1], g->nivelIntensitateCuloare[g->nrCulori - 1]);
			}
			fprintf(f, "%5.2f, %5.2f, %5.2f", g->putere, g->rezistenta, g->voltaj);
			fclose(f);
			return 1;
		}
		else return 0;
	}
	else return 0;
}

int writeVectorToFile(const char* nume_fisier, const struct Girofar* vector, int dim) {
	if (nume_fisier != NULL && strlen(nume_fisier) > 0 && vector != NULL && dim > 0) {
		FILE* f = fopen(nume_fisier, "w");
		if (f != NULL) {
			fprintf(f, "%d\n", dim);
			for (int k = 0; k < dim; k++) {
				if (vector[k].cod != NULL && strlen(vector[k].cod) > 0)
					fprintf(f, "%s, ", vector[k].cod);
				else fprintf(f, "N/A, ");
				fprintf(f, "%d\n", vector[k].nrCulori);
				if (vector[k].nrCulori > 0 && vector[k].culori != NULL && vector[k].timpAfisareCuloare != NULL && vector[k].nivelIntensitateCuloare != NULL) {
					for (int i = 0; i < vector[k].nrCulori - 1; i++) {
						switch (vector[k].culori[i]) {
						case ALB: fprintf(f, "alb,"); break;
						case ROSU: fprintf(f, "rosu,"); break;
						case ALBASTRU: fprintf(f, "albastru,"); break;
						case GALBEN: fprintf(f, "galben,"); break;
						case MOV: fprintf(f, "mov,"); break;
						}
						fprintf(f, "%5.2lf, %i, ", vector[k].timpAfisareCuloare[i], vector[k].nivelIntensitateCuloare[i]);
					}
					switch (vector[k].culori[vector[k].nrCulori - 1]) {
					case ALB: fprintf(f, "alb,"); break;
					case ROSU: fprintf(f, "rosu,"); break;
					case ALBASTRU: fprintf(f, "albastru,"); break;
					case GALBEN: fprintf(f, "galben,"); break;
					case MOV: fprintf(f, "mov,"); break;
					}
					fprintf(f, "%5.2lf, %i\n", vector[k].timpAfisareCuloare[vector[k].nrCulori - 1], vector[k].nivelIntensitateCuloare[vector[k].nrCulori - 1]);
				}
				fprintf(f, "%5.2f, %5.2f, %5.2f", vector[k].putere, vector[k].rezistenta, vector[k].voltaj);
				if (k < dim - 1) fprintf(f, "\n");
			}
			fclose(f);
			return 1;
		}
		else return 0;
	}
	else return 0;
}

void dezalocare_matrice(struct Girofar*** matrice, int nr_linii, int** nr_coloane) {
	if (*matrice != NULL) {
		for (int i = 0; i < nr_linii; i++)
			for (int j = 0; j < (*nr_coloane)[i]; j++) {
				(*matrice)[i][j].nrCulori = 0;
				if ((*matrice)[i][j].cod != NULL) {
					free((*matrice)[i][j].cod);
					(*matrice)[i][j].cod = NULL;
				}
				if ((*matrice)[i][j].culori != NULL) {
					free((*matrice)[i][j].culori);
					(*matrice)[i][j].culori = NULL;
				}
				if ((*matrice)[i][j].timpAfisareCuloare != NULL) {
					free((*matrice)[i][j].timpAfisareCuloare);
					(*matrice)[i][j].timpAfisareCuloare = NULL;
				}
				if ((*matrice)[i][j].nivelIntensitateCuloare != NULL) {
					free((*matrice)[i][j].nivelIntensitateCuloare);
					(*matrice)[i][j].nivelIntensitateCuloare = NULL;
				}
			}
		free(*matrice);
		*matrice = NULL;
	}
	nr_linii = 0;
	if (*nr_coloane != NULL) {
		free(*nr_coloane);
		*nr_coloane = NULL;
	}
}

void reshapeDupaNrCulori(const struct Girofar* vector, int dim_vector, struct Girofar*** matrice, int* nr_linii, int** nr_coloane) {
	//obiectele cu acelasi numar de culori vor fi plasate pe aceeasi linie a matricei rezultat
	if (vector != NULL && dim_vector > 0) {
		//1. dezalocare matrice si resetare dimensiuni
		if (*matrice != NULL) {
			for (int i = 0; i < *nr_linii; i++)
				for (int j = 0; j < (*nr_coloane)[i]; j++) {
					(*matrice)[i][j].nrCulori = 0;
					if ((*matrice)[i][j].cod != NULL) {
						free((*matrice)[i][j].cod);
						(*matrice)[i][j].cod = NULL;
					}
					if ((*matrice)[i][j].culori != NULL) {
						free((*matrice)[i][j].culori);
						(*matrice)[i][j].culori = NULL;
					}
					if ((*matrice)[i][j].timpAfisareCuloare != NULL) {
						free((*matrice)[i][j].timpAfisareCuloare);
						(*matrice)[i][j].timpAfisareCuloare = NULL;
					}
					if ((*matrice)[i][j].nivelIntensitateCuloare != NULL) {
						free((*matrice)[i][j].nivelIntensitateCuloare);
						(*matrice)[i][j].nivelIntensitateCuloare = NULL;
					}
				}
			free(*matrice);
			*matrice = NULL;
		}
		*nr_linii = 0;
		if (*nr_coloane != NULL) {
			free(*nr_coloane);
			*nr_coloane = NULL;
		}
		//2. calculam numarul valorilor unice pentru campul nrCulori al fiecarui obiect din vector
		int vector_frecventa[1000]; //nu ar trebui sa avem mai mult de 999 de culori per obiect
		for (int i = 0; i < 1000; i++)
			vector_frecventa[i] = 0;
		for (int i = 0; i < dim_vector; i++) {
			if (vector_frecventa[vector[i].nrCulori] == 0) (*nr_linii)++;
			vector_frecventa[vector[i].nrCulori]++;
		}
		//3. nr_linii = numarul valorilor unice calculat anterior; nr_coloane = numarul obiectelor cu aceeasi valoare nrCulori
		//nr_coloane va fi diferit de la linie la linie!
		*nr_coloane = (int*)malloc(sizeof(int) * (*nr_linii));
		if (*nr_coloane != NULL) {
			int k = 0;
			for (int i = 0; i < 1000; i++) {
				if (vector_frecventa[i] > 0)
					(*nr_coloane)[k++] = vector_frecventa[i];
			}
		}
		//4. alocare matrice
		*matrice = (struct Girofar**)malloc(sizeof(struct Girofar*) * (*nr_linii));
		if (*matrice != NULL && *nr_coloane != NULL)
			for (int i = 0; i < *nr_linii; i++)
				(*matrice)[i] = (struct Girofar*)malloc(sizeof(struct Girofar) * ((*nr_coloane)[i]));
		//5. calculare vector_ordine bazat pe vector_frecventa
		int* vector_ordine = (int*)malloc(sizeof(int) * (*nr_linii));
		if (vector_ordine != NULL) {
			int k = 0;
			for (int i = 0; i < 1000; i++)
				if (vector_frecventa[i] > 0)
					vector_ordine[k++] = i;
		}
		//6. adaugare elemente in matrice pe linia corespunzatoare lor (deep copy)
		if (vector_ordine != NULL && *matrice != NULL) {
			int* coloana_curenta = (int*)malloc(sizeof(int) * (*nr_linii));
			if (coloana_curenta != NULL && *nr_coloane != NULL) {
				for (int i = 0; i < *nr_linii; i++)
					coloana_curenta[i] = 0;
				for (int i = 0; i < dim_vector; i++) {
					int linie_curenta = -1;
					for (int j = 0; j < *nr_linii; j++) {
						if (vector[i].nrCulori == vector_ordine[j]) {
							linie_curenta = j;
							break;
						}
					}
					if (linie_curenta >= 0 && (*matrice)[linie_curenta] != NULL) {
						initializeaza(&((*matrice)[linie_curenta][coloana_curenta[linie_curenta]]));
						setValori(&((*matrice)[linie_curenta][coloana_curenta[linie_curenta]++]), vector[i].cod, vector[i].nrCulori, vector[i].culori, vector[i].timpAfisareCuloare, vector[i].nivelIntensitateCuloare, vector[i].putere, vector[i].rezistenta, vector[i].voltaj);
					}
				}
				free(coloana_curenta);
				coloana_curenta = NULL;
			}
		}
		//7. dezalocare vector_ordine
		free(vector_ordine);
		vector_ordine = NULL;
	}
}

void swapVectori(struct Girofar** v1, int* dim1, struct Girofar** v2, int* dim2) {
	if (*v1 != NULL && *dim1 > 0 && *v2 != NULL && *dim2 > 0) {
		int dim_new = *dim1;
		struct Girofar* v_new = (struct Girofar*)malloc(sizeof(struct Girofar) * dim_new);
		if (v_new != NULL) {
			for (int i = 0; i < dim_new; i++) {
				initializeaza(&v_new[i]);
				setValori(&v_new[i], (*v1)[i].cod, (*v1)[i].nrCulori, (*v1)[i].culori, (*v1)[i].timpAfisareCuloare, (*v1)[i].nivelIntensitateCuloare, (*v1)[i].putere, (*v1)[i].rezistenta, (*v1)[i].voltaj);
			}
			dezalocare_vector(v1, *dim1);
			int aux = *dim1;
			*dim1 = *dim2;
			*dim2 = aux;
			*v1 = (struct Girofar*)malloc(sizeof(struct Girofar) * (*dim1));
			if (*v1 != NULL) {
				for (int i = 0; i < *dim1; i++) {
					initializeaza(&((*v1)[i]));
					setValori(&((*v1)[i]), (*v2)[i].cod, (*v2)[i].nrCulori, (*v2)[i].culori, (*v2)[i].timpAfisareCuloare, (*v2)[i].nivelIntensitateCuloare, (*v2)[i].putere, (*v2)[i].rezistenta, (*v2)[i].voltaj);
				}
				dezalocare_vector(v2, *dim1);
				*v2 = (struct Girofar*)malloc(sizeof(struct Girofar) * (*dim2));
				if (*v2 != NULL) {
					for (int i = 0; i < *dim2; i++) {
						initializeaza(&((*v2)[i]));
						setValori(&((*v2)[i]), v_new[i].cod, v_new[i].nrCulori, v_new[i].culori, v_new[i].timpAfisareCuloare, v_new[i].nivelIntensitateCuloare, v_new[i].putere, v_new[i].rezistenta, v_new[i].voltaj);
					}
				}
			}
			dezalocare_vector(&v_new, dim_new);
		}
	}
}

void toMatriceSemipiramidala(struct Girofar*** matrice, int* nr_linii, int** nr_coloane) {
	//liniile matricei finale vor fi repozitionate, astfel incat acestea sa fie sortate dupa nr de elemente de pe linie
	if (*matrice != NULL && *nr_linii > 0 && *nr_coloane != NULL) {
		char inv;
		do {
			inv = 0;
			for (int i = 0; i < (*nr_linii) - 1; i++) {
				for (int j = i + 1; j < (*nr_linii); j++) {
					if ((*nr_coloane)[i] > (*nr_coloane)[j]) {
						swapVectori(&((*matrice)[i]), &(*nr_coloane)[i], &((*matrice)[j]), &(*nr_coloane)[j]);
						inv = 1;
					}
				}
			}
		} while (inv == 1);
	}
}

void afisareMatrice(const struct Girofar** matrice, int nr_linii, int* nr_coloane) {
	printf("\n\n=====================================================================================\n");
	if (matrice != NULL && nr_linii > 0 && nr_coloane != NULL) {
		printf("\n------------------------------------MATRICE------------------------------------\n\n");
		for (int i = 0; i < nr_linii; i++) {
			printf("nrCulori = %d | ", matrice[i][0].nrCulori);
			for (int j = 0; j < nr_coloane[i] - 1; j++) {
				if (matrice[i][j].cod != NULL && strlen(matrice[i][j].cod) > 0)
					printf("%s , ", matrice[i][j].cod);
				else
					printf("%s , ", "N/A");
			}
			if (matrice[i][nr_coloane[i] - 1].cod != NULL && strlen(matrice[i][nr_coloane[i] - 1].cod) > 0)
				printf("%s", matrice[i][nr_coloane[i] - 1].cod);
			else
				printf("%s", "N/A");
			printf("\n");
		}
		printf("\n-------------------------------------------------------------------------------\n");
		printf(", unde:\n");
		for (int i = 0; i < nr_linii; i++)
			for (int j = 0; j < nr_coloane[i]; j++) {
				if (matrice[i][j].cod != NULL && strlen(matrice[i][j].cod) > 0)
					printf("\n\n\"%s\" este obiectul:", matrice[i][j].cod);
				else
					printf("\n\n\"%s\" este obiectul:", "N/A");
				afiseaza(&(matrice[i][j]));
			}
	}
	else printf("\n\nMATRICE NULA!\n");
	printf("\n\n=====================================================================================\n\n");
}

void main() {
	enum Culoare culori[3] = { ALB, ROSU, ALB };
	double timp[3] = { 3.47, 8.84, 1.12 };
	int intensitate[3] = { 30, 60, 90 };
	struct Girofar girofar;
	initializeaza(&girofar);

	afiseaza(&girofar); //girofar initializat

	setValori(&girofar, "XA-20 .24", 3, culori, timp, intensitate, 16, 36, 12);

	afiseaza(&girofar); //girofar cu valori date ca parametri

	double timpTotal = calculeazaTimpTotalCuloare(&girofar, ALB);
	printf("\n\nTimpul total de afisare al culorii \"ALB\" in g1 este: %5.2lf secunde.\n", timpTotal);

	enum Culoare new_culori[6] = { ALB, ROSU, ALBASTRU, MOV, ALB, ROSU };
	double new_timp[6] = { 5.67, 3.23, 1.29, 8.88, 3.41, 9.21 };
	int new_intensitate[6] = { 100, 90, 60, 80, 70, 100 };

	setCuloriGirofar(&girofar, 6, new_culori, new_timp, new_intensitate);

	afiseaza(&girofar); //girofar cu valori modificate prin parametri

	/*struct Girofar new_girofar = citeste();
	afiseaza(&new_girofar); //girofar cu valori citite de la tastatura
	dezalocare(&new_girofar);*/

	enum Culoare culori1[4] = { ALB, MOV, ALB, MOV };
	enum Culoare culori2[6] = { ROSU, ALBASTRU, GALBEN, ROSU, ALBASTRU, GALBEN };
	enum Culoare culori3[3] = { GALBEN, ROSU, MOV };
	enum Culoare culori4[2] = { ROSU, ALB };
	enum Culoare culori5[7] = { MOV, ALBASTRU, ALB, ROSU, GALBEN, ALBASTRU, MOV };
	double timpi1[4] = { 13.4, 3.98, 6.74, 9.99 };
	double timpi2[6] = { 32.12, 12.78, 9.98, 10.01, 41.2, 35.33 };
	double timpi3[3] = { 3.33, 6.66, 9.99 };
	double timpi4[2] = { 81.34, 19.02 };
	double timpi5[7] = { 2, 2.2, 3.4, 4.8, 6.6, 8.2, 9.4 };
	int intensitati1[4] = { 50, 70, 30, 44 };
	int intensitati2[6] = { 98, 4, 16, 100, 34, 78 };
	int intensitati3[3] = { 53, 65, 92 };
	int intensitati4[2] = { 98, 46 };
	int intensitati5[7] = { 89, 82, 62, 30, 43, 12, 2 };

	struct Girofar* vector = (struct Girofar*)malloc(sizeof(struct Girofar) * 5);
	if (vector != NULL) {
		for (int i = 0; i < 5; i++)
			initializeaza(&vector[i]);
		setValori(&vector[0], "G1", 4, culori1, timpi1, intensitati1, 10, 12, 14);
		setValori(&vector[1], "G2", 6, culori2, timpi2, intensitati2, 9, 8, 10);
		setValori(&vector[2], "G3", 3, culori3, timpi3, intensitati3, 11, 13, 12);
		setValori(&vector[3], "G4", 2, culori4, timpi4, intensitati4, 7, 12, 11);
		setValori(&vector[4], "G5", 7, culori5, timpi5, intensitati5, 20, 18, 20);
	}

	struct Girofar* vector_rez = NULL;
	int dim_rez;

	printf("\n\n\nREZULTAT DUPA CONDITIONAREA PE TIMP A VECTORULUI 1:");

	restrictTimp(vector, 5, &vector_rez, &dim_rez, 2, 10);
	afiseaza_vector(vector_rez, dim_rez);

	printf("\n\n\nREZULTAT DUPA CONDITIONAREA PE INTENSITATE A VECTORULUI 1:");

	restrictIntensitate(vector, 5, &vector_rez, &dim_rez, 0, 90);
	afiseaza_vector(vector_rez, dim_rez);

	struct Girofar* vector_rez2 = NULL;
	int dim_rez2;

	printf("\n\n\nREZULTAT DUPA CONDITIONAREA PE INTENSITATE A VECTORULUI 2:");

	restrictIntensitate(vector, 5, &vector_rez2, &dim_rez2, 10, 90);
	afiseaza_vector(vector_rez2, dim_rez2);

	struct Girofar* vector_rez3 = NULL;
	int dim_rez3;

	printf("\n\n\nVECTORUL CONCATENAT DIN VECTORUL 1 SI 2 (DIN RESTRICTIILE DE INTENSITATE):");

	concat_vectori(vector_rez, dim_rez, vector_rez2, dim_rez2, &vector_rez3, &dim_rez3);
	afiseaza_vector(vector_rez3, dim_rez3);

	//task3

	struct Girofar* vector_fisier = NULL;
	int dim_fisier;

	printf("\n\n\nVECTORUL CITIT DIN FISIERUL DE INPUT ESTE:");

	readVectorFromFile("input.txt", &vector_fisier, &dim_fisier);
	afiseaza_vector(vector_fisier, dim_fisier);

	struct Girofar;

	if (writeGirofarToFile("output.txt", &girofar))
		printf("\n\nGIROFARUL A FOST SCRIS IN FISIER!\n\n");
	else printf("\n\nEROARE LA SCRIEREA IN FISIER A GIROFARULUI!\n\n");

	if (writeVectorToFile("vector.txt", vector_rez, dim_rez))
		printf("\n\nVECTORUL A FOST SCRIS IN FISIER!\n\n");
	else printf("\n\nEROARE LA SCRIEREA IN FISIER A VECTORULUI!\n\n");

	struct Girofar* vector_fisier_new = NULL;
	int dim_fisier_new;

	printf("\n\n\nVECTORUL CITIT DIN FISIERUL DE INPUT ESTE:");

	readVectorFromFile("vector.txt", &vector_fisier_new, &dim_fisier_new);
	afiseaza_vector(vector_fisier_new, dim_fisier_new);

	//task 4

	struct Girofar** matrice = NULL;
	int nr_linii = 0;
	int* nr_coloane = NULL;
	reshapeDupaNrCulori(vector_fisier, dim_fisier, &matrice, &nr_linii, &nr_coloane);
	afisareMatrice(matrice, nr_linii, nr_coloane);

	toMatriceSemipiramidala(&matrice, &nr_linii, &nr_coloane);
	printf("\n\n\nDUPA PIRAMIDALIZARE:\n\n\n");
	afisareMatrice(matrice, nr_linii, nr_coloane);

	dezalocare(&girofar);
	dezalocare_vector(&vector, 5);
	dezalocare_vector(&vector_rez, dim_rez);
	dezalocare_vector(&vector_rez2, dim_rez2);
	dezalocare_vector(&vector_rez3, dim_rez3);
	dezalocare_vector(&vector_fisier, dim_fisier);
	dezalocare_vector(&vector_fisier_new, dim_fisier_new);
	dezalocare_matrice(&matrice, nr_linii, &nr_coloane);
}