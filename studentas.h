#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <algorithm>

class Studentas {
private:
    std::string var;
    std::string pav;
    std::vector<int> paz;
    int egz;
    double galutinis_vidurkis;
    double galutinis_mediana;

public:
    Studentas() : var(""), pav(""), egz(0), galutinis_vidurkis(0.0), galutinis_mediana(0.0) {}

    Studentas(std::string v, std::string p, std::vector<int> pz, int e) 
        : var(v), pav(p), paz(pz), egz(e), galutinis_vidurkis(0.0), galutinis_mediana(0.0) {}

    Studentas(const Studentas& kitas)
        : var(kitas.var), pav(kitas.pav), paz(kitas.paz), egz(kitas.egz),
          galutinis_vidurkis(kitas.galutinis_vidurkis), galutinis_mediana(kitas.galutinis_mediana) {}

    ~Studentas() {}

    std::string getVar() const { return var; }
    std::string getPav() const { return pav; }
    std::vector<int> getPaz() const { return paz; }
    int getEgz() const { return egz; }
    double getGalVid() const { return galutinis_vidurkis; }
    double getGalMed() const { return galutinis_mediana; }

    void setVar(std::string v) { var = v; }
    void setPav(std::string p) { pav = p; }
    void setPaz(const std::vector<int>& p) { paz = p; }
    void setEgz(int e) { egz = e; }

    void skaiciuoti();
};

#endif
