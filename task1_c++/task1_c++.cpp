//C++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

//Gurău Adrian-Florin -> G, A si F

enum Culoare {
	ALB, ROSU, ALBASTRU, GALBEN, MOV
};

struct Girofar {
	char* cod = nullptr; //cod unic de identificare
	int nrCulori = 0; //numarul culorilor din lista ordonata
	Culoare* culori = nullptr; //culorile efective ce se vor afisa in ordinea mentionata
	double* timpAfisareCuloare = nullptr; //timpul de afisare (in secunde) al fiecarei culori
	int* nivelIntensitateCuloare = nullptr; //intensitatea (in procent) fiecarei culori
	float putere = 0; //masurati in watti
	float rezistenta = 0; //masurati in ohmi
	float voltaj = 0; //masurat in volti
};

Girofar citeste() {
	Girofar obiect;

	string buffer;
	do {
		cout << "\nIntroduceti codul de identificare al girofarului (>2caractere): ";
		cin >> ws;
		getline(cin, buffer);
	} while (buffer.length() <= 2);
	obiect.cod = new char[buffer.length() + 1];
	strcpy(obiect.cod, buffer.data());

	do {
		cout << "\nIntroduceti nr de culori (>0): ";
		cin >> obiect.nrCulori;
	} while (obiect.nrCulori <= 0);

	obiect.culori = new Culoare[obiect.nrCulori];
	obiect.timpAfisareCuloare = new double[obiect.nrCulori];
	obiect.nivelIntensitateCuloare = new int[obiect.nrCulori];

	int alegere;
	for (int i = 0; i < obiect.nrCulori; i++) {
		do {
			cout << "\nCuloarea " << i + 1 << " (ALB = 0, ROSU = 1, ALBASTRU = 2, GALBEN = 3, MOV = 4): ";
			cin >> alegere;
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
			cout << "\nTimp " << i + 1 << " (>0): ";
			cin >> obiect.timpAfisareCuloare[i];
		} while (obiect.timpAfisareCuloare[i] <= 0);
		do {
			cout << "\nIntensitate " << i + 1 << " (0-100): ";
			cin >> obiect.nivelIntensitateCuloare[i];
		} while (obiect.nivelIntensitateCuloare[i] < 0 || obiect.nivelIntensitateCuloare[i] > 100);
	}
	do {
		cout << "Putere: ";
		cin >> obiect.putere;
	} while (obiect.putere <= 0);
	do {
		cout << "Rezistenta: ";
		cin >> obiect.rezistenta;
	} while (obiect.rezistenta <= 0);
	do {
		cout << "Voltaj: ";
		cin >> obiect.voltaj;
	} while (obiect.voltaj <= 0);

	return obiect;
}

void setValori(Girofar& obiect, const char* cod, int nrCulori, Culoare* culori,
	double* timpAfisareCuloare, int* nivelIntensitateCuloare,
	float putere, float rezistenta, float voltaj)
{
	if (cod != nullptr && strlen(cod) > 0) {
		if (obiect.cod != nullptr) {
			delete[] obiect.cod;
			obiect.cod = nullptr;
		}
		obiect.cod = new char[strlen(cod) + 1];
		strcpy(obiect.cod, cod);
	}
	else throw exception("Codul girofarului nu poate fi nul!");

	if (nrCulori > 0 && culori != nullptr && timpAfisareCuloare != nullptr
		&& nivelIntensitateCuloare != nullptr) {
		obiect.nrCulori = nrCulori;
		if (obiect.culori != nullptr) {
			delete[] obiect.culori;
			obiect.culori = nullptr;
		}
		if (obiect.timpAfisareCuloare != nullptr) {
			delete[] obiect.timpAfisareCuloare;
			obiect.timpAfisareCuloare = nullptr;
		}
		if (obiect.nivelIntensitateCuloare != nullptr) {
			delete[] obiect.nivelIntensitateCuloare;
			obiect.nivelIntensitateCuloare = nullptr;
		}
		obiect.culori = new Culoare[obiect.nrCulori];
		obiect.timpAfisareCuloare = new double[obiect.nrCulori];
		obiect.nivelIntensitateCuloare = new int[obiect.nrCulori];
		for (int i = 0; i < obiect.nrCulori; i++) {
			obiect.culori[i] = culori[i];
			obiect.timpAfisareCuloare[i] = timpAfisareCuloare[i];
			obiect.nivelIntensitateCuloare[i] = nivelIntensitateCuloare[i];
		}
	}
	else throw exception("Numarul de culori nu este pozitiv si/sau listele aferente culorilor sunt neconforme!");

	if (putere > 0) obiect.putere = putere;
	else throw exception("Pentru putere nu se accepta o valoare nepozitiva!");

	if (rezistenta > 0) obiect.rezistenta = rezistenta;
	else throw exception("Pentru rezistenta nu se accepta o valoare nepozitiva!");

	if (voltaj > 0) obiect.voltaj = voltaj;
	else throw exception("Pentru voltaj nu se accepta o valoare nepozitiva!");
}

double calculeazaTimpTotalCuloare(const Girofar& girofar, Culoare culoare) {
	if (girofar.nrCulori > 0 && girofar.culori != nullptr && girofar.timpAfisareCuloare != nullptr) {
		double timpTotal = 0;
		for (int i = 0; i < girofar.nrCulori; i++)
			if (girofar.culori[i] == culoare)
				timpTotal += girofar.timpAfisareCuloare[i];
		return timpTotal;
	}
	else return 0;
}

void setCuloriGirofar(Girofar& girofar, int nrCulori,
	Culoare* culori, double* timpAfisareCuloare,
	int* nivelIntensitateCuloare)
{
	if (nrCulori > 0 && culori != nullptr && timpAfisareCuloare != nullptr
		&& nivelIntensitateCuloare != nullptr) {
		girofar.nrCulori = nrCulori;
		if (girofar.culori != nullptr) {
			delete[] girofar.culori;
			girofar.culori = nullptr;
		}
		if (girofar.timpAfisareCuloare != nullptr) {
			delete[] girofar.timpAfisareCuloare;
			girofar.timpAfisareCuloare = nullptr;
		}
		if (girofar.nivelIntensitateCuloare != nullptr) {
			delete[] girofar.nivelIntensitateCuloare;
			girofar.nivelIntensitateCuloare = nullptr;
		}
		girofar.culori = new Culoare[girofar.nrCulori];
		girofar.timpAfisareCuloare = new double[girofar.nrCulori];
		girofar.nivelIntensitateCuloare = new int[girofar.nrCulori];
		for (int i = 0; i < girofar.nrCulori; i++) {
			girofar.culori[i] = culori[i];
			girofar.timpAfisareCuloare[i] = timpAfisareCuloare[i];
			girofar.nivelIntensitateCuloare[i] = nivelIntensitateCuloare[i];
		}
	}
	else throw exception("Numarul de culori nu este pozitiv si/sau listele aferente culorilor sunt neconforme!");
}

void afiseaza(const Girofar& girofar) {
	cout << "\n--------------------GIROFAR--------------------";
	cout << "\nCod: ";
	if (girofar.cod != nullptr && strlen(girofar.cod) > 0)
		cout << girofar.cod;
	else cout << "-";
	cout << "\nNr culori: " << girofar.nrCulori;
	if (girofar.nrCulori > 0 && girofar.culori != nullptr &&
		girofar.timpAfisareCuloare != nullptr &&
		girofar.nivelIntensitateCuloare != nullptr) {
		cout << "\nCulori: ";
		for (int i = 0; i < girofar.nrCulori; i++) {
			cout << "\n  ";
			switch (girofar.culori[i]) {
			case ALB:
				cout << "Alb"; break;
			case ROSU:
				cout << "Rosu"; break;
			case ALBASTRU:
				cout << "Albastru"; break;
			case GALBEN:
				cout << "Galben"; break;
			case MOV:
				cout << "Mov"; break;
			}
			cout << " - " << girofar.timpAfisareCuloare[i] << " secunde | ";
			cout << "Intensitate: " << girofar.nivelIntensitateCuloare[i] << "%";
		}
	}
	cout << "\nPutere: " << girofar.putere << "W";
	cout << "\nRezistenta: " << girofar.rezistenta << "ohm";
	cout << "\nVoltaj: " << girofar.voltaj << "V";
	cout << "\n-----------------------------------------------";
}

void dezalocare(Girofar& girofar) {
	girofar.nrCulori = 0;
	if (girofar.cod != nullptr) {
		delete[] girofar.cod;
		girofar.cod = nullptr;
	}
	if (girofar.culori != nullptr) {
		delete[] girofar.culori;
		girofar.culori = nullptr;
	}
	if (girofar.timpAfisareCuloare != nullptr) {
		delete[] girofar.timpAfisareCuloare;
		girofar.timpAfisareCuloare = nullptr;
	}
	if (girofar.nivelIntensitateCuloare != nullptr) {
		delete[] girofar.nivelIntensitateCuloare;
		girofar.nivelIntensitateCuloare = nullptr;
	}
}

void main() {
	Culoare culori[3] = { ALB, ROSU, ALB };
	double timp[3] = { 3.47, 8.84, 1.12 };
	int intensitate[3] = { 30, 60, 90 };
	Girofar girofar;

	afiseaza(girofar); //girofar cu valori default

	try {
		setValori(girofar, "XA-20 .24", 3, culori, timp, intensitate, 16, 36, 12);
	}
	catch (exception ex) {
		cout << endl << endl << ex.what() << endl << endl;
	}

	afiseaza(girofar); //girofar cu valori date ca parametri

	double timpTotal = calculeazaTimpTotalCuloare(girofar, ALB);
	cout << "\n\nTimpul total de afisare al culorii \"ALB\" in g1 este: " << timpTotal << " secunde.\n";

	Culoare new_culori[6] = { ALB, ROSU, ALBASTRU, MOV, ALB, ROSU };
	double new_timp[6] = { 5.67, 3.23, 1.29, 8.88, 3.41, 9.21 };
	int new_intensitate[6] = { 100, 90, 60, 80, 70, 100 };

	try {
		setCuloriGirofar(girofar, 6, new_culori, new_timp, new_intensitate);
	}
	catch (exception ex) {
		cout << endl << endl << ex.what() << endl << endl;
	}

	afiseaza(girofar); //girofar cu valori modificate prin parametri

	Girofar new_girofar = citeste();

	afiseaza(new_girofar); //girofar cu valori citite de la tastatura

	dezalocare(girofar);
	dezalocare(new_girofar);

	//testam afisarea celor 2 obiecte dupa dezalocare
	afiseaza(girofar);
	afiseaza(new_girofar);
}