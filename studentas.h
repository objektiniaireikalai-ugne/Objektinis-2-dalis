#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "zmogus.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Studentas : public Zmogus {
private:
    std::vector<int> nd_;
    int egzaminas_;
    double galutinis_vidurkis_;
    double galutinis_mediana_;

    void skaiciuoti();

public:
    Studentas() : Zmogus(), egzaminas_(0), galutinis_vidurkis_(0.0), galutinis_mediana_(0.0) {}
    Studentas(std::istream& is) : Zmogus(), egzaminas_(0), galutinis_vidurkis_(0.0), galutinis_mediana_(0.0) {
        readStudent(is);
    }

    Studentas(const std::string& v, const std::string& p, const std::vector<int>& pz, int e)
        : Zmogus(v, p), nd_(pz), egzaminas_(e), galutinis_vidurkis_(0.0), galutinis_mediana_(0.0) {
        skaiciuoti();
    }

    Studentas(const Studentas& kitas)
        : Zmogus(kitas), nd_(kitas.nd_), egzaminas_(kitas.egzaminas_),
          galutinis_vidurkis_(kitas.galutinis_vidurkis_), galutinis_mediana_(kitas.galutinis_mediana_) {}

    Studentas(Studentas&& kitas) noexcept
        : Zmogus(std::move(kitas)), nd_(std::move(kitas.nd_)),
          egzaminas_(kitas.egzaminas_), galutinis_vidurkis_(kitas.galutinis_vidurkis_), galutinis_mediana_(kitas.galutinis_mediana_) {
        kitas.egzaminas_ = 0;
        kitas.galutinis_vidurkis_ = 0.0;
        kitas.galutinis_mediana_ = 0.0;
    }

    Studentas& operator=(const Studentas& kitas) {
        if (this != &kitas) {
            Zmogus::operator=(kitas);
            nd_ = kitas.nd_;
            egzaminas_ = kitas.egzaminas_;
            galutinis_vidurkis_ = kitas.galutinis_vidurkis_;
            galutinis_mediana_ = kitas.galutinis_mediana_;
        }
        return *this;
    }

    Studentas& operator=(Studentas&& kitas) noexcept {
        if (this != &kitas) {
            Zmogus::operator=(std::move(kitas));
            nd_ = std::move(kitas.nd_);
            egzaminas_ = kitas.egzaminas_;
            galutinis_vidurkis_ = kitas.galutinis_vidurkis_;
            galutinis_mediana_ = kitas.galutinis_mediana_;
            kitas.egzaminas_ = 0;
            kitas.galutinis_vidurkis_ = 0.0;
            kitas.galutinis_mediana_ = 0.0;
        }
        return *this;
    }

     ~Studentas() override {
         nd_.clear();
         egzaminas_ = 0;
         galutinis_vidurkis_ = 0.0;
         galutinis_mediana_ = 0.0;
     }

    void spausdintiInfo() const override {
        std::cout << "Studentas: " << vardas() << " " << pavarde() << ", Vidurkis: " << galVid() << "\n";
    }

    inline std::vector<int> pazymiai() const { return nd_; }
    inline int egzaminas() const { return egzaminas_; }
    inline double galVid() const { return galutinis_vidurkis_; }
    inline double galMed() const { return galutinis_mediana_; }
    
    std::istream& readStudent(std::istream& is);

    friend std::istream& operator>>(std::istream& is, Studentas& s);
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
};

bool compare(const Studentas& a, const Studentas& b);
bool comparePagalPavarde(const Studentas& a, const Studentas& b);
bool comparePagalEgza(const Studentas& a, const Studentas& b);

#endif
