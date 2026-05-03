#ifndef EXCEPTII_HPP
#define EXCEPTII_HPP

#include <exception>
#include <string>

class TrendsetterException : public std::exception {
protected:
    std::string mesaj;
public:
    TrendsetterException(const std::string& msg) : mesaj(msg) {}
    virtual ~TrendsetterException() throw() {}
    virtual const char* what() const throw() { return mesaj.c_str(); }
};

class BugetInsuficientException : public TrendsetterException {
public:
    BugetInsuficientException(const std::string& nume, double pret, double buget)
        : TrendsetterException("Fonduri insuficiente!") {}
};

class PiesaInvalidaException : public TrendsetterException {
public:
    PiesaInvalidaException(const std::string& detaliu) : TrendsetterException(detaliu) {}
};

#endif
