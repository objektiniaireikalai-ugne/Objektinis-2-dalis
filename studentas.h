#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> nd_;
    int egzaminas_;
    double galutinis_vidurkis_;
    double galutinis_mediana_;

    void skaiciuoti();

public:
    Studentas() : egzaminas_(0), galutinis_vidurkis_(0.0), galutinis_mediana_(0.0) {}
    Studentas(std::istream& is) : egzaminas_(0), galutinis_vidurkis_(0.0), galutinis_mediana_(0.0) {
        readStudent(is);
    }

    Studentas(const std::string& v, const std::string& p, const std::vector<int>& pz, int e)
        : vardas_(v), pavarde_(p), nd_(pz), egzaminas_(e), galutinis_vidurkis_(0.0), galutinis_mediana_(0.0) {
        skaiciuoti();
    }

    Studentas(const Studentas& kitas)
        : vardas_(kitas.vardas_), pavarde_(kitas.pavarde_), nd_(kitas.nd_), egzaminas_(kitas.egzaminas_),
          galutinis_vidurkis_(kitas.galutinis_vidurkis_), galutinis_mediana_(kitas.galutinis_mediana_) {}

    Studentas(Studentas&& kitas) noexcept
        : vardas_(std::move(kitas.vardas_)), pavarde_(std::move(kitas.pavarde_)), nd_(std::move(kitas.nd_)),
          egzaminas_(kitas.egzaminas_), galutinis_vidurkis_(kitas.galutinis_vidurkis_), galutinis_mediana_(kitas.galutinis_mediana_) {
        kitas.egzaminas_ = 0;
        kitas.galutinis_vidurkis_ = 0.0;
        kitas.galutinis_mediana_ = 0.0;
    }

    Studentas& operator=(const Studentas& kitas) {
        if (this != &kitas) {
            vardas_ = kitas.vardas_;
            pavarde_ = kitas.pavarde_;
            nd_ = kitas.nd_;
            egzaminas_ = kitas.egzaminas_;
            galutinis_vidurkis_ = kitas.galutinis_vidurkis_;
            galutinis_mediana_ = kitas.galutinis_mediana_;
        }
        return *this;
    }

    Studentas& operator=(Studentas&& kitas) noexcept {
        if (this != &kitas) {
            vardas_ = std::move(kitas.vardas_);
            pavarde_ = std::move(kitas.pavarde_);
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

 ~Studentas() {
        vardas_.clear();
        pavarde_.clear();
        nd_.clear();
        egzaminas_ = 0;
        galutinis_vidurkis_ = 0.0;
        galutinis_mediana_ = 0.0;
    }

    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }
    inline std::vector<int> pazymiai() const { return nd_; }
    inline int egzaminas() const { return egzaminas_; }
    inline double galVid() const { return galutinis_vidurkis_; }
    inline double galMed() const { return galutinis_mediana_; }
    
    std::istream& readStudent(std::istream& is);
};

bool compare(const Studentas& a, const Studentas& b);
bool comparePagalPavarde(const Studentas& a, const Studentas& b);
bool comparePagalEgza(const Studentas& a, const Studentas& b);

#endif
