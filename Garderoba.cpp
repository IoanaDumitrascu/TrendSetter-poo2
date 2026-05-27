#include "Garderoba.hpp"
#include "Exceptii.hpp"
#include "Haina.hpp"
#include "Incaltaminte.hpp"
#include "Accesoriu.hpp"
#include "Bijuterie.hpp"
#include <algorithm>
#include <fstream>

Garderoba::Garderoba(const std::string& nume, double b) : numeInfluencer(nume), buget(b) {}


Garderoba::~Garderoba() {
    for (size_t i = 0; i < piese.size(); ++i) {
        delete piese[i];
    }
    piese.clear();
}

Garderoba::Garderoba(const Garderoba& sursa) : numeInfluencer(sursa.numeInfluencer), buget(sursa.buget) {
    for (size_t i = 0; i < sursa.piese.size(); ++i) {
        piese.push_back(sursa.piese[i]->clone());
    }
}

Garderoba& Garderoba::operator=(const Garderoba& sursa) {
    if (this != &sursa) {
        for (size_t i = 0; i < piese.size(); ++i) delete piese[i];
        piese.clear();
        numeInfluencer = sursa.numeInfluencer;
        buget = sursa.buget;
        for (size_t i = 0; i < sursa.piese.size(); ++i) {
            piese.push_back(sursa.piese[i]->clone());
        }
    }
    return *this;
}

void Garderoba::adaugaPiesa(PiesaVestimentara* p) {
    if (p == NULL) return;
    if (buget < p->getPret()) {
        delete p;
        throw BugetInsuficientException(p->getDenumire(), p->getPret(), buget);
    }
    buget -= p->getPret();
    piese.push_back(p);
}

void Garderoba::eliminaPieseSub(double prag) {
    for (std::vector<PiesaVestimentara*>::iterator it = piese.begin(); it != piese.end(); ) {
        if ((*it)->calculeazaImpact() < prag) {
            delete *it;
            it = piese.erase(it);
        } else {
            ++it;
        }
    }
}

void Garderoba::salveazaInFisier(const std::string& numeFisier) const {
    std::ofstream fout(numeFisier.c_str());
    if (!fout.is_open()) throw FisierException(numeFisier);

    for (size_t i = 0; i < piese.size(); ++i) {
        fout << piese[i]->getTip() << "|" << piese[i]->getDenumire() << "|" << piese[i]->getBrand() << "|" << piese[i]->getPret() << "\n";
    }
    fout.close();
}
void Garderoba::afiseazaScorEveniment(const Eveniment& ev) const {
    double scorTotal = 0;
    for (auto p : piese) {
        scorTotal += p->calculeazaImpact() * ev.calculeazaMultiplicator(p->getTip());
    }
    std::cout << "\n>>> Impact total pentru evenimentul " << ev.getNume() << ": " << scorTotal << " <<<\n";
}

void Garderoba::afiseazaTopPiese(int n) const {
    if (piese.empty()) {
        std::cout << "Garderoba este goala.\n";
        return;
    }
    
    std::vector<PiesaVestimentara*> copie = piese;
    std::sort(copie.begin(), copie.end(), [](PiesaVestimentara* a, PiesaVestimentara* b) {
        return a->calculeazaImpact() > b->calculeazaImpact();
    });

    std::cout << "\n TOP " << n << " PIESE DUPA IMPACT \n";
    for (int i = 0; i < n && i < (int)copie.size(); ++i) {
        std::cout << i + 1 << ". " << *copie[i] << " (Impact: " << copie[i]->calculeazaImpact() << ")\n";
    }
}

void Garderoba::afiseazaHaineImpermeabile() const {
    std::cout << "\n LISTA HAINE IMPERMEABILE \n";
    bool gasit = false;
    for (auto p : piese) {
        Haina* h = dynamic_cast<Haina*>(p);
        if (h) {
            std::cout << *h << "\n";
            gasit = true;
        }
    }
    if (!gasit) std::cout << "Nu exista haine in garderoba.\n";
}

void Garderoba::incarcaDinFisier(const std::string& numeFisier) {
    std::ifstream f(numeFisier);
    if (!f) throw FisierException(numeFisier);

    std::string tip;
    while (f >> tip) {
        try {
            if (tip == "Haina") {
                std::string d, b, m; double p; int s; bool i;
                f >> d >> b >> p >> s >> m >> i;
                adaugaPiesa(new Haina(d, b, p, s, m, i));
            } else if (tip == "Incaltaminte") {
                std::string d, b; double p; int s, m, c;
                f >> d >> b >> p >> s >> m >> c;
                adaugaPiesa(new Incaltaminte(d, b, p, s, m, c));
            } else if (tip == "Bijuterie") {
                std::string d, b; double p; int s; double carate;
                f >> d >> b >> p >> s >> carate;
                adaugaPiesa(new Bijuterie(d, b, p, s, "Aur", carate));
            } else if (tip == "Accesoriu") {
                std::string d, b, t; double p; int s; bool l;
                f >> d >> b >> p >> s >> t >> l;
                adaugaPiesa(new Accesoriu(d, b, p, s, t, l));
            }
        } catch (const TrendsetterException& e) {
            std::cerr << "Eroare la incarcarea unei piese: " << e.what() << "\n";
        }
    }
    std::cout << "Import finalizat din " << numeFisier << "\n";
}

double Garderoba::calculeazaScorPentruEveniment(const Eveniment& ev) const {
    double total = 0;
    for (auto p : piese)
        total += p->calculeazaImpact() * ev.calculeazaMultiplicator(p->getTip());
    return total;
}

std::ostream& operator<<(std::ostream& os, const Garderoba& g) {
    os << "\n=== GARDEROBA: " << g.numeInfluencer << " | Buget ramas: " << g.buget << " RON ===\n";
    for (size_t i = 0; i < g.piese.size(); ++i)
        os << "  " << i+1 << ". " << *g.piese[i] << "\n";
    os << "Total piese create (static): " << PiesaVestimentara::getNrPiese() << "\n";
    return os;
}
