#include "include/Garderoba.h"
#include "include/Eveniment.h"
#include "include/Exceptii.h"
#include "include/Haina.h"
#include "include/Incaltaminte.h"
#include "include/Accesoriu.h"
#include "include/Bijuterie.h"
#include <iostream>
#include <limits>

static void clearInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void meniuAdaugaHaina(Garderoba& g) {
    std::string den, brd, mat;
    double pret; int stil; bool imp;
    std::cout << "Denumire: "; std::getline(std::cin, den);
    std::cout << "Brand: ";    std::getline(std::cin, brd);
    std::cout << "Pret (RON): "; std::cin >> pret; clearInput();
    std::cout << "Stil (0-100): "; std::cin >> stil; clearInput();
    std::cout << "Material (ex: Bumbac, Matase, Piele, Casmir): "; std::getline(std::cin, mat);
    std::cout << "Impermeabila? (1=Da, 0=Nu): "; std::cin >> imp; clearInput();
    g.adaugaPiesa(new Haina(den, brd, pret, stil, mat, imp));
    std::cout << "Haina adaugata cu succes!\n";
}

static void meniuAdaugaIncaltaminte(Garderoba& g) {
    std::string den, brd;
    double pret; int stil, marime, confort;
    std::cout << "Denumire: "; std::getline(std::cin, den);
    std::cout << "Brand: ";    std::getline(std::cin, brd);
    std::cout << "Pret (RON): "; std::cin >> pret; clearInput();
    std::cout << "Stil (0-100): "; std::cin >> stil; clearInput();
    std::cout << "Marime: ";   std::cin >> marime; clearInput();
    std::cout << "Confort (1-10): "; std::cin >> confort; clearInput();
    g.adaugaPiesa(new Incaltaminte(den, brd, pret, stil, marime, confort));
    std::cout << "Incaltaminte adaugata cu succes!\n";
}

static void meniuAdaugaAccesoriu(Garderoba& g) {
    std::string den, brd, tip;
    double pret; int stil; bool lux;
    std::cout << "Denumire: "; std::getline(std::cin, den);
    std::cout << "Brand: ";    std::getline(std::cin, brd);
    std::cout << "Pret (RON): "; std::cin >> pret; clearInput();
    std::cout << "Stil (0-100): "; std::cin >> stil; clearInput();
    std::cout << "Tip accesoriu (ex: Geanta, Esarfa, Ochelari): "; std::getline(std::cin, tip);
    std::cout << "De lux? (1=Da, 0=Nu): "; std::cin >> lux; clearInput();
    g.adaugaPiesa(new Accesoriu(den, brd, pret, stil, tip, lux));
    std::cout << "Accesoriu adaugat cu succes!\n";
}

static void meniuAdaugaBijuterie(Garderoba& g) {
    std::string den, brd, metal;
    double pret, cantitate; int stil;
    std::cout << "Denumire: "; std::getline(std::cin, den);
    std::cout << "Brand: ";    std::getline(std::cin, brd);
    std::cout << "Pret (RON): "; std::cin >> pret; clearInput();
    std::cout << "Stil (0-100): "; std::cin >> stil; clearInput();
    std::cout << "Metal (Aur, Argint, Platina, etc.): "; std::getline(std::cin, metal);
    std::cout << "Cantitate (grame/carate): "; std::cin >> cantitate; clearInput();
    g.adaugaPiesa(new Bijuterie(den, brd, pret, stil, metal, cantitate));
    std::cout << "Bijuterie adaugata cu succes!\n";
}

static void meniuEveniment(const Garderoba& g) {
    std::cout << "Tip eveniment (Gala / Street-Style / Business): ";
    std::string tipStr; std::getline(std::cin, tipStr);
    Eveniment ev(tipStr, parseTipEveniment(tipStr));
    g.afiseazaScorEveniment(ev);
}

int main() {
    std::cout << "=== TRENDSETTER: SIMULATOR DE INFLUENTA SI STIL ===\n\n";

    std::string numeIn;
    double bugetIn;
    std::cout << "Nume influencer: "; std::getline(std::cin, numeIn);
    std::cout << "Buget initial (RON): "; std::cin >> bugetIn; clearInput();

    Garderoba garderoba(numeIn, bugetIn);

    // Incarcare automata din fisier daca exista
    try {
        garderoba.incarcaDinFisier("garderoba.csv");
        std::cout << "[INFO] Garderoba incarcata din 'garderoba.csv'.\n";
    } catch (const FisierException&) {
        std::cout << "[INFO] Nu exista fisier salvat. Garderoba este goala.\n";
    }

    int opt = -1;
    while (opt != 0) {
        std::cout << "\n--- MENIU ---\n"
                  << "1. Adauga Haina\n"
                  << "2. Adauga Incaltaminte\n"
                  << "3. Adauga Accesoriu\n"
                  << "4. Adauga Bijuterie\n"
                  << "5. Afiseaza garderoba\n"
                  << "6. Scor eveniment\n"
                  << "7. Top piese dupa impact\n"
                  << "8. Elimina piese sub prag\n"
                  << "9. Afiseaza haine impermeabile\n"
                  << "10. Salveaza garderoba\n"
                  << "0. Iesire\n"
                  << "Alegere: ";
        std::cin >> opt; clearInput();

        try {
            switch (opt) {
                case 1: meniuAdaugaHaina(garderoba);        break;
                case 2: meniuAdaugaIncaltaminte(garderoba); break;
                case 3: meniuAdaugaAccesoriu(garderoba);    break;
                case 4: meniuAdaugaBijuterie(garderoba);    break;
                case 5: std::cout << garderoba;             break;
                case 6: meniuEveniment(garderoba);          break;
                case 7: {
                    int n;
                    std::cout << "Cate piese sa afisez? "; std::cin >> n; clearInput();
                    garderoba.afiseazaTopPiese(n);
                    break;
                }
                case 8: {
                    double prag;
                    std::cout << "Prag impact minim: "; std::cin >> prag; clearInput();
                    garderoba.eliminaPieseSub(prag);
                    break;
                }
                case 9: garderoba.afiseazaHaineImpermeabile(); break;
                case 10:
                    garderoba.salveazaInFisier("garderoba.csv");
                    std::cout << "Garderoba salvata in 'garderoba.csv'.\n";
                    break;
                case 0: std::cout << "La revedere!\n"; break;
                default: std::cout << "Optiune invalida.\n";
            }
        } catch (const BugetInsuficientException& e) {
            std::cerr << "[EROARE BUGET] " << e.what() << "\n";
        } catch (const PiesaInvalidaException& e) {
            std::cerr << "[EROARE PIESA] " << e.what() << "\n";
        } catch (const EvenimentInexistentException& e) {
            std::cerr << "[EROARE EVENIMENT] " << e.what() << "\n";
        } catch (const FisierException& e) {
            std::cerr << "[EROARE FISIER] " << e.what() << "\n";
        } catch (const TrendsetterException& e) {
            std::cerr << "[EROARE] " << e.what() << "\n";
        }
    }

    return 0;
}
