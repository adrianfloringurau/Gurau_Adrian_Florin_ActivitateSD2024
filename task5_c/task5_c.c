#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Gurău Adrian-Florin --> G, A, F

struct Fugar {
	int id;
	char* nume;
	char sex;
};

struct Nod {
	struct Fugar* info;
	struct Nod* next;
};

void initializareFugar(struct Fugar* f) {
	if (f != NULL) {
		f->id = -1;
		f->nume = NULL;
		f->sex = 'U';
	}
}

void dezalocareFugar(struct Fugar* f) {
	if (f != NULL) {
		if (f->nume != NULL) {
			free(f->nume);
			f->nume = NULL;
		}
	}
}

void seteazaValoriFugar(struct Fugar* f, int id, const char* nume, char sex) {
	if (f != NULL) {
		f->id = id;
		if (f->nume != NULL) {
			free(f->nume);
			f->nume = NULL;
		}
		if (nume != NULL && strlen(nume) > 0) {
			f->nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
			if (f->nume != NULL) {
				strcpy(f->nume, nume);
			}
		}
		f->sex = sex;
	}
}

void dezalocareLista(struct Nod** prim) {
	if (*prim != NULL) {
		struct Nod* curent = *prim;
		do {
			dezalocareFugar(curent->info);
			curent->info = NULL;
			curent = curent->next;
		} while (curent != NULL);
		*prim = NULL;
	}
}

void copiereInfo(const struct Nod* nod, const struct Fugar* element) {
	if (nod != NULL) {
		initializareFugar(nod->info);
		dezalocareFugar(nod->info);
		nod->info->id = element->id;
		nod->info->nume = (char*)malloc(sizeof(char) * (strlen(element->nume) + 1));
		if (nod->info->nume != NULL) {
			strcpy(nod->info->nume, element->nume);
		}
		nod->info->sex = element->sex;
	}
}

void alocareLista(struct Nod** prim, const struct Fugar* element) {
	if (*prim != NULL) {
		initializareFugar((*prim)->info);
		dezalocareLista(prim);
	}
	*prim = (struct Nod*)malloc(sizeof(struct Nod));
	if (*prim != NULL) {
		(*prim)->info = (struct Fugar*)malloc(sizeof(struct Fugar));
		if ((*prim)->info != NULL) {
			copiereInfo(*prim, element);
		}
		(*prim)->next = NULL;
	}
}

void adaugareLaFinal(struct Nod** prim, const struct Fugar* element) {
	if (*prim == NULL) {
		alocareLista(prim, element);
	}
	else {
		struct Nod* curent = *prim;
		while (curent->next != NULL) {
			curent = curent->next;
		}
		curent->next = (struct Nod*)malloc(sizeof(struct Nod));
		if (curent->next != NULL) {
			curent = curent->next;
			curent->info = (struct Fugar*)malloc(sizeof(struct Fugar));
			copiereInfo(curent, element);
			curent->next = NULL;
		}
	}
}

void citireDinFisier(const char* numeFisier, struct Nod** prim) {
	if (numeFisier != NULL && strlen(numeFisier) > 0) {
		FILE* f = fopen(numeFisier, "r");
		if (f != NULL) {
			struct Fugar fugar;
			initializareFugar(&fugar);
			char buffer[100];
			char* token = NULL;
			while (fgets(buffer, sizeof(buffer), f)) {
				dezalocareFugar(&fugar);
				token = strtok(buffer, ",\n");
				fugar.id = atoi(token);
				token = strtok(NULL, ",\n");
				fugar.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
				if (fugar.nume != NULL) {
					strcpy(fugar.nume, token);
				}
				token = strtok(NULL, "\n");
				fugar.sex = token[0];
				adaugareLaFinal(prim, &fugar);
			}
			//free(token); ??? - de ce crapa la fclose daca exista linia asta de cod
			fclose(f);
		}
	}
}

void stergeNod(struct Nod** prim, int index) {
	if (*prim != NULL) {
		if (index == 0) {
			dezalocareFugar((*prim)->info);
			*prim = (*prim)->next;
		}
		else if (index > 0) {
			struct Nod* curent = (*prim);
			int index_curent = 1;
			char gasit = 0;

			while (curent->next != NULL && !gasit) {
				if (index_curent == index) {
					dezalocareFugar(curent->next->info);
					curent->next = curent->next->next;
					gasit = 1;
				}
				else {
					curent = curent->next;
					index_curent++;
				}
			}
		}
	}
}

void inserareElemente(struct Nod** prim, const struct Fugar* elemente, int dim) {
	if (elemente != NULL && dim > 0) {
		int index = 0;
		if (*prim == NULL) {
			alocareLista(&prim, &(elemente[0]));
			index = 1;
		}
		else {
			for (int i = index; i < dim; i++) {
				struct Nod* curent = *prim;
				if (curent->next == NULL) {
					if (elemente[i].id < curent->info->id) {
						adaugareLaFinal(prim, &(elemente[i]));
						if (curent->next != NULL) {
							curent->next->next = curent;
							curent->next = NULL;
							(*prim) = curent->next;
						}
					}
					else {
						adaugareLaFinal(prim, &(elemente[i]));
					}
				}
				else {
					struct Nod* anterior = *prim;
					char inserat = 0;
					while (anterior->next != NULL && !inserat) {
						if (anterior->next->info != NULL && elemente[i].id < anterior->next->info->id) {
							struct Nod* aux = anterior->next;
							anterior->next = (struct Nod*)malloc(sizeof(struct Nod));
							if (anterior->next != NULL) {
								anterior->next->info = (struct Fugar*)malloc(sizeof(struct Fugar));
								if (anterior->next->info != NULL) {
									copiereInfo(anterior->next, &(elemente[i]));
								}
								anterior->next->next = aux;
								anterior = *prim;
							}
							inserat = 1;
						}
						if (inserat == 0) {
							anterior = anterior->next;
						}
					}
					if (anterior->next == NULL && !inserat) {
						adaugareLaFinal(prim, &(elemente[i]));
					}
				}
			}
		}
	}
}

void salveazaInVectorDupaSex(const struct Nod* prim, char sex, struct Fugar** vector, int* dim) {
	if (*vector != NULL) {
		for (int i = 0; i < *dim; i++)
			dezalocareFugar(&((*vector)[i]));
		free(*vector);
		*vector = NULL;
	}
	*dim = 0;
	if (prim != NULL) {
		struct Nod* curent = prim;
		do {
			if (curent->info->sex == sex) {
				(*dim)++;
			}
			curent = curent->next;
		} while (curent != NULL);
		if (*dim > 0) {
			*vector = (struct Fugar*)malloc(sizeof(struct Fugar) * (*dim));
			if (*vector != NULL) {
				int k = 0;
				curent = prim;
				do {
					if (curent->info->sex == sex) {
						(*vector)[k].id = curent->info->id;
						if (curent->info->nume != NULL && strlen(curent->info->nume) > 0) {
							(*vector)[k].nume = (char*)malloc(sizeof(char) * (strlen(curent->info->nume) + 1));
							if ((*vector)[k].nume != NULL) {
								strcpy((*vector)[k].nume, curent->info->nume);
							}
						}
						(*vector)[k].sex = curent->info->sex;
						k++;
					}
					curent = curent->next;
				} while (curent != NULL);
			}
		}
	}
}

void interschimbareNoduri(struct Nod** prim, int index1, int index2) {
	if (*prim != NULL && index1 != index2 && index1 >= 0 && index2 >= 0) {
		struct Nod* nodAnterior1 = NULL;
		struct Nod* nod1 = NULL;
		struct Nod* nodAnterior2 = NULL;
		struct Nod* nod2 = NULL;

		if (index1 == 0) {
			nod1 = *prim;
		}
		else if (index2 == 0) {
			nod2 = *prim;
		}
		
		struct Nod* curent = (*prim);
		int index_curent = 1;

		while (curent->next != NULL && (nod1 == NULL || nod2 == NULL)) {
			if (index_curent == index1) {
				nodAnterior1 = curent;
				nod1 = curent->next;
			}
			else if (index_curent == index2) {
				nodAnterior2 = curent;
				nod2 = curent->next;
			}
			curent = curent->next;
			index_curent++;
		}
		
		if (nod1 != NULL && nod2 != NULL) {
			if (index1 == 0) {
				nodAnterior2->next = nod1;
				struct Nod* aux = nod1->next;
				nod1->next = nod2->next;
				nod2->next = aux;
				*prim = nod2;
			}
			else if (index2 == 0) {
				nodAnterior1->next = nod2;
				struct Nod* aux = nod2->next;
				nod2->next = nod1->next;
				nod1->next = aux;
				*prim = nod1;
			}
			else {
				nodAnterior1->next = nod2;
				nodAnterior2->next = nod1;
				struct Nod* aux = nod1->next;
				nod1->next = nod2->next;
				nod2->next = aux;
			}
		}
	}
}

void sortareBuleListaDupaID(struct Nod** prim) {
	if (*prim != NULL) {
		char inv;
		do {
			inv = 0;
			int index_curent = 0;
			struct Nod* curent = *prim;
			while (curent->next != NULL && !inv) {
				if (curent->info->id > curent->next->info->id) {
					interschimbareNoduri(prim, index_curent, index_curent + 1);
					inv = 1;
				}
				if (inv == 0) {
					curent = curent->next;
					index_curent++;
				}
			}
		} while (inv == 1);
	}
}

void main() {
	struct Nod* prim = NULL;

	citireDinFisier("fugari.txt", &prim);

	stergeNod(&prim, 3);

	struct Fugar f1, f2, f3;
	initializareFugar(&f1);
	initializareFugar(&f2);
	initializareFugar(&f3);
	seteazaValoriFugar(&f1, 3, "FUGAR 1", 'M');
	seteazaValoriFugar(&f2, 3, "FUGAR 2", 'F');
	seteazaValoriFugar(&f3, 5, "FUGAR 3", 'F');

	struct Fugar elemente[3] = { f1, f2, f3 };
	inserareElemente(&prim, elemente, 3);

	struct Fugar* vector = NULL;
	int dim = 0;
	salveazaInVectorDupaSex(prim, 'M', &vector, &dim);

	for (int i = 0; i < dim; i++) {
		printf("%d - ", vector[i].id);
		if (vector[i].nume != NULL && strlen(vector[i].nume) > 0)
			printf("%s - ", vector[i].nume);
		else
			printf("N/A - ");
		printf("%c\n", vector[i].sex);
	}

	interschimbareNoduri(&prim, 1, 2);

	sortareBuleListaDupaID(&prim);

	dezalocareLista(&prim);
	if (vector != NULL) {
		for (int i = 0; i < dim; i++)
			dezalocareFugar(&(vector[i]));
		free(vector);
		vector = NULL;
	}
	dim = 0;
	prim = NULL;
}