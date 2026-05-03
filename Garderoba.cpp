#include "Garderoba.hpp"
#include "Exceptii.hpp"
#include "Haina.hpp"
#include "Incaltaminte.hpp"
#include "Accesoriu.hpp"
#include "Bijuterie.hpp"
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
