#include "Garderoba.hpp"
#include "Eveniment.hpp"
#include "Exceptii.hpp"
#include "Haina.hpp"
#include "Incaltaminte.hpp"
#include "Accesoriu.hpp"
#include "Bijuterie.hpp"
#include <iostream>
#include <limits>

static void clearInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void adaugaHaina(Garderoba& g) {
    std::string den, brd, mat;
    double pret; int stil; bool imp;
    std::cout << "Denumire: ";  std::getline(std::cin, den);
    std::cout << "Brand: ";     std::getline(std::cin, brd);
    std::cout << "Pret (RON): "; std::cin >> pret; clearInput();
    std::cout << "Stil (0-100): "; std::cin >> stil; clearInput();
    std::cout << "Material (Bumbac/Matase/Piele/Casmir): "; std::getline(std::cin, mat);
    std::cout << "Impermeabila? (1=Da, 0=Nu): "; std::cin >> imp; clearInput();
    g.adaugaPiesa(new Haina(den, brd, pret, stil, mat, imp));
    std::cout << "Haina adaugata!\n";
}

static void adaugaIncaltaminte(Garderoba& g) {
    std::string den, brd;
    double pret; int stil, marime, confort;
    std::cout << "Denumire: ";  std::getline(std::cin, den);
    std::cout << "Brand: ";     std::getline(std::cin, brd);
    std::cout << "Pret (RON): "; std::cin >> pret; clearInput();
    std::cout << "Stil (0-100): "; std::cin >> stil; clearInput();
    std::cout << "Marime: ";    std::cin >> marime; clearInput();
    std::cout << "Confort (1-10): "; std::cin >> confort; clearInput();
    g.adaugaPiesa(new Incaltaminte(den, brd, pret, stil, marime, confort));
    std::cout << "Incaltaminte adaugata!\n";
}

static void adaugaAccesoriu(Garderoba& g) {
    std::string den, brd, tip;
    double pret; int stil; bool lux;
    std::cout << "Denumire: ";  std::getline(std::cin, den);
    std::cout << "Brand: ";     std::getline(std::cin, brd);
    std::cout << "Pret (RON): "; std::cin >> pret; clearInput();
    std::cout << "Stil (0-100): "; std::cin >> stil; clearInput();
    std::cout << "Tip (Geanta/Esarfa/Ochelari): "; std::getline(std::cin, tip);
    std::cout << "De lux? (1=Da, 0=Nu): "; std::cin >> lux; clearInput();
    g.adaugaPiesa(new Accesoriu(den, brd, pret, stil, tip, lux));
    std::cout << "Accesoriu adaugat!\n";
}

static void adaugaBijuterie(Garderoba& g) {
    std::string den, brd, metal;
    double pret, cantitate; int stil;
    std::cout << "Denumire: ";  std::getline(std::cin, den);
    std::cout << "Brand: ";     std::getline(std::cin, brd);
    std::cout << "Pret (RON): "; std::cin >> pret; clearInput();
    std::cout << "Stil (0-100): "; std::cin >> stil; clearInput();
    std::cout << "Metal (Aur/Argint/Platina): "; std::getline(std::cin, metal);
    std::cout << "Cantitate (grame): "; std::cin >> cantitate; clearInput();
    g.adaugaPiesa(new Bijuterie(den, brd, pret, stil, metal, cantitate));
    std::cout << "Bijuterie adaugata!\n";
}

static void meniuEveniment(const Garderoba& g) {
    std::cout << "Tip eveniment (Gala / Street-Style / Business): ";
    std::string tipStr; std::getline(std::cin, tipStr);
    Eveniment ev(tipStr, parseTipEveniment(tipStr));
    g.afiseazaScorEveniment(ev);
}

int main() {
    std::cout << " TRENDSETTER: SIMULATOR DE INFLUENTA SI STIL \n\n";

    std::string numeIn;
    double bugetIn;
    std::cout << "Nume influencer: "; std::getline(std::cin, numeIn);
    std::cout << "Buget initial (RON): "; std::cin >> bugetIn; clearInput();

    Garderoba garderoba(numeIn, bugetIn);

    try {
        garderoba.incarcaDinFisier("garderoba.csv");
        std::cout << "[INFO] Garderoba incarcata din fisier.\n";
    } catch (const FisierException&) {
        std::cout << "[INFO] Fisier nou - garderoba goala.\n";
    }

    int opt = -1;
    while (opt != 0) {
        std::cout << "\n MENIU \n"
                  << "1. Adauga Haina\n"
                  << "2. Adauga Incaltaminte\n"
                  << "3. Adauga Accesoriu\n"
                  << "4. Adauga Bijuterie\n"
                  << "5. Afiseaza garderoba\n"
                  << "6. Scor eveniment\n"
                  << "7. Top piese\n"
                  << "8. Elimina piese slabe\n"
                  << "9. Haine impermeabile\n"
                  << "10. Salveaza\n"
                  << "0. Iesire\n"
                  << "Alegere: ";
        std::cin >> opt; clearInput();

        try {
            switch (opt) {
                case 1: adaugaHaina(garderoba);        break;
                case 2: adaugaIncaltaminte(garderoba); break;
                case 3: adaugaAccesoriu(garderoba);    break;
                case 4: adaugaBijuterie(garderoba);    break;
                case 5: std::cout << garderoba;        break;
                case 6: meniuEveniment(garderoba);     break;
                case 7: {
                    int n; std::cout << "Cate: "; std::cin >> n; clearInput();
                    garderoba.afiseazaTopPiese(n); break;
                }
                case 8: {
                    double prag; std::cout << "Prag: "; std::cin >> prag; clearInput();
                    garderoba.eliminaPieseSub(prag); break;
                }
                case 9: garderoba.afiseazaHaineImpermeabile(); break;
                case 10:
                    garderoba.salveazaInFisier("garderoba.csv");
                    std::cout << "Salvat!\n"; break;
                case 0: std::cout << "La revedere!\n"; break;
                default: std::cout << "Optiune invalida.\n";
            }
        } catch (const BugetInsuficientException& e) {
            std::cerr << "[EROARE] " << e.what() << "\n";
        } catch (const PiesaInvalidaException& e) {
            std::cerr << "[EROARE] " << e.what() << "\n";
        } catch (const EvenimentInexistentException& e) {
            std::cerr << "[EROARE] " << e.what() << "\n";
        } catch (const FisierException& e) {
            std::cerr << "[EROARE] " << e.what() << "\n";
        }
    }

    return 0;
}
