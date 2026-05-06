#ifndef GARDEROBA_HPP
#define GARDEROBA_HPP

#include "PiesaVestimentara.hpp"
#include "Eveniment.hpp"
#include <vector>

class Garderoba {
private:
    std::string numeInfluencer;
    double buget;
    std::vector<PiesaVestimentara*> piese;

public:
    Garderoba(const std::string& nume, double buget);
    Garderoba(const Garderoba& sursa);
    Garderoba& operator=(const Garderoba& sursa);
    ~Garderoba();

    void adaugaPiesa(PiesaVestimentara* p);
    void eliminaPieseSub(double prag);
    void salveazaInFisier(const std::string& numeFisier) const;
    void incarcaDinFisier(const std::string& numeFisier);
    void afiseazaScorEveniment(const Eveniment& ev) const;
    void afiseazaTopPiese(int n) const;
    void afiseazaHaineImpermeabile() const;

    friend std::ostream& operator<<(std::ostream& os, const Garderoba& g);
};

#endif
