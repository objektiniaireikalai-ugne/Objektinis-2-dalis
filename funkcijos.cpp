#include "funkcijos.h"
#include <algorithm>
#include <random>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <list>

using namespace std;

double vidurkis(vector<int> paz) {
    if (paz.size() == 0) return 0;
    double s = 0;
    for (size_t i = 0; i < paz.size(); i++){
        s = s + paz[i];
    }
    return s / paz.size();
}

double mediana(vector<int> paz) {
    if (paz.size() == 0) return 0;
    std::sort(paz.begin(), paz.end());
    int n = paz.size();
    if (n % 2 == 0) return (paz[n/2 - 1] + paz[n/2]) / 2.0;
    return paz[n/2];
}

void Studentas::skaiciuoti() {
    if (paz.empty()) {
        galutinis_vidurkis = 0.6 * egz;
        galutinis_mediana = 0.6 * egz;
    } else {
        double s = 0;
        for (int i = 0; i < paz.size(); i++) s += paz[i];
        galutinis_vidurkis = 0.4 * (s / paz.size()) + 0.6 * egz;

        std::vector<int> kopija = paz;
        std::sort(kopija.begin(), kopija.end());
        int n = kopija.size();
        double med = (n % 2 == 0) ? (kopija[n/2 - 1] + kopija[n/2]) / 2.0 : kopija[n/2];
        galutinis_mediana = 0.4 * med + 0.6 * egz;
    }
}

bool RusiuotiPagalVarda(const Studentas& a, const Studentas& b) {
    return a.getVar() < b.getVar();
}

bool RusiuotiPagalPavarde(const Studentas& a, const Studentas& b) {
    return a.getPav() < b.getPav();
}

bool RusiuotiPagalBala(const Studentas& a, const Studentas& b) {
    return a.getGalVid() < b.getGalVid();
}


static mt19937 gen(random_device{}());
static uniform_int_distribution<> dist(1, 10);

int GeneruotiPazymi() {
    return dist(gen);
}

Studentas GeneruotiStudenta(int numeris) {
    Studentas A;
    A.setVar("Vardas" + to_string(numeris));
    A.setPav("Pavarde" + to_string(numeris));
    
    vector<int> tempPaz;
    int kiek = dist(gen) % 8 + 3;
    for (int i = 0; i < kiek; i++) {
        tempPaz.push_back(GeneruotiPazymi());
    }
    A.setPaz(tempPaz);
    A.setEgz(GeneruotiPazymi());
    
    A.skaiciuoti();
    return A;
}

void GeneruotiStudentus(vector<Studentas>& grupe, int kiek) {
    grupe.clear();
    grupe.reserve(kiek);
    for (int i = 0; i < kiek; i++) {
        grupe.push_back(GeneruotiStudenta(i + 1));
    }
}

void GeneruotiFaila(const string& failas, int kiek) {
    ofstream out(failas.c_str());
    out << left << setw(16) << "Vardas" << setw(20) << "Pavarde";
    for (int i = 1; i <= 15; i++) {
        out << right << setw(6) << ("ND" + to_string(i));
    }
    out << right << setw(6) << "Egz." << "\n";

    for (int i = 0; i < kiek; i++) {
        Studentas A = GeneruotiStudenta(i + 1);
        out << left << setw(16) << A.getVar() << setw(20) << A.getPav();
        for (int j = 0; j < 15; j++) {
            out << right << setw(6) << GeneruotiPazymi();
        }
        out << right << setw(6) << GeneruotiPazymi() << "\n";
    }
}

bool nuskaitymas(vector<Studentas>& grupe, const string& failas) {
    ifstream in(failas.c_str());
    if (!in) return false;

    grupe.clear();
    string eilute;
    getline(in, eilute);

    while (getline(in, eilute)) {
        if (eilute.empty()) continue;

        istringstream ss(eilute);
        Studentas A;
        
        string tempVar, tempPav;
        if (!(ss >> tempVar >> tempPav)) continue;
        A.setVar(tempVar);
        A.setPav(tempPav);

        vector<int> tempPaz;
        int x;
        while (ss >> x) tempPaz.push_back(x);
        if (tempPaz.size() == 0) continue;

        A.setEgz(tempPaz[tempPaz.size() - 1]);
        tempPaz.pop_back();
        A.setPaz(tempPaz);

        A.skaiciuoti();
        grupe.push_back(A);
    }
    return true;
}

bool nuskaitymas(std::list<Studentas>& grupe, const std::string& failas) {
    ifstream in(failas.c_str());
    if (!in) return false;

    grupe.clear();
    string eilute;
    getline(in, eilute);

    while (getline(in, eilute)) {
        if (eilute.empty()) continue;

        istringstream ss(eilute);
        Studentas A;
        
        string tempVar, tempPav;
        if (!(ss >> tempVar >> tempPav)) continue;
        A.setVar(tempVar);
        A.setPav(tempPav);

        vector<int> tempPaz;
        int x;
        while (ss >> x) tempPaz.push_back(x);
        if (tempPaz.size() == 0) continue;

        A.setEgz(tempPaz[tempPaz.size() - 1]);
        tempPaz.pop_back();
        A.setPaz(tempPaz);

        A.skaiciuoti();
        grupe.push_back(A);
    }
    return true;
}

void kategorijos(vector<Studentas>& grupe, vector<Studentas>& nabageliai, vector<Studentas>& kietiakai) {
    nabageliai.clear();
    kietiakai.clear();

    nabageliai.reserve(grupe.size());
    kietiakai.reserve(grupe.size());

    for (const auto &a : grupe) {
        if (a.getGalVid() < 5.0) {
            nabageliai.push_back(a);
        } else {
            kietiakai.push_back(a);
        }
    }
    nabageliai.shrink_to_fit();
    kietiakai.shrink_to_fit();

    grupe.clear();
    grupe.shrink_to_fit();
}

void kategorijos(const std::list<Studentas>& grupe, std::list<Studentas>& nabageliai, std::list<Studentas>& kietiakai) {
    nabageliai.clear();
    kietiakai.clear();

    for (auto it = grupe.begin(); it != grupe.end(); ++it) {
        if (it->getGalVid() < 5.0) { 
            nabageliai.push_back(*it);
        } else {
            kietiakai.push_back(*it);
        }
    }
}


void IsvestiIFaila(const string& failas, const vector<Studentas>& grupe, bool rodytiVid) {
    ofstream out(failas.c_str());

    out << left << setw(16) << "Vardas" << setw(20) << "Pavarde" << right << setw(20) << "Galutinis" << "\n";

    out << fixed << setprecision(2);
    for (int i = 0; i < (int)grupe.size(); i++) {
        out << left << setw(16) << grupe[i].getVar() << setw(20) << grupe[i].getPav() << right << setw(20);
        if (rodytiVid) {
            out << grupe[i].getGalVid();
        } else {
            out << grupe[i].getGalMed(); 
        }
        out << "\n";
    }
}

void IsvestiIFaila(const std::string& failas, const std::list<Studentas>& grupe, bool rodytiVid) {
    ofstream out(failas.c_str());
    out << left << setw(16) << "Vardas" << setw(20) << "Pavarde" << right << setw(20) << "Galutinis" << "\n";
    out << fixed << setprecision(2);

    for (auto it = grupe.begin(); it != grupe.end(); ++it) {
        out << left << setw(16) << it->getVar() << setw(20) << it->getPav() << right << setw(20);
        if (rodytiVid) {
            out << it->getGalVid(); 
        } else {
            out << it->getGalMed(); 
        }
        out << "\n";
    }
}

void output(const vector<Studentas>& grupe, int limit, bool rodytiVid, bool rodytiMed) {
    cout << left << setw(16) << "Vardas" << setw(20) << "Pavarde";
    if (rodytiVid) cout << right << setw(20) << "Galutinis (Vid.)";
    if (rodytiMed) cout << right << setw(20) << "Galutinis (Med.)";
    cout << "\n";

    int br = 36;
    if (rodytiVid) br += 20;
    if (rodytiMed) br += 20;
    for (int i = 0; i < br; i++) cout << "-";
    cout << "\n";

    int n = (int)grupe.size();
    if (limit > 0 && limit < n) n = limit;

    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++) {
        cout << left << setw(16) << grupe[i].getVar()
             << setw(20) << grupe[i].getPav();
        if (rodytiVid) cout << right << setw(20) << grupe[i].getGalVid();
        if (rodytiMed) cout << right << setw(20) << grupe[i].getGalMed(); 
        cout << "\n";
    }
}

void split_1_vector(vector<Studentas>& grupe, vector<Studentas>& v, vector<Studentas>& k) {
    v.clear();
    k.clear();
    v.reserve(grupe.size());
    k.reserve(grupe.size());

    for (const auto& a : grupe) {
        if (a.getGalVid() < 5.0) {
            v.push_back(a);
        } else {
            k.push_back(a);
        }
    }
}

void split_1_list(list<Studentas>& grupe, list<Studentas>& v, list<Studentas>& k) {
    v.clear();
    k.clear();

    for (const auto& a : grupe) {
        if (a.getGalVid() < 5.0) {
            v.push_back(a);
        } else {
            k.push_back(a);
        }
    }
}

void split_2_vector(vector<Studentas>& grupe, vector<Studentas>& v) {
    v.clear();

    sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
        return a.getGalVid() > b.getGalVid();
    });

    while (!grupe.empty() && grupe.back().getGalVid() < 5.0) {
        v.push_back(grupe.back());
        grupe.pop_back();
    }
}

void split_2_list(list<Studentas>& grupe, list<Studentas>& v) {
    v.clear();

    grupe.sort([](const Studentas& a, const Studentas& b) {
        return a.getGalVid() > b.getGalVid();
    });

    while (!grupe.empty() && grupe.back().getGalVid() < 5.0) {
        v.push_back(grupe.back());
        grupe.pop_back();
    }
}

void split_3_vector(vector<Studentas>& grupe, vector<Studentas>& v) {
    v.clear();
    auto it = std::partition(grupe.begin(), grupe.end(), [](const Studentas& a) {
        return a.getGalVid() < 5.0;
    });

    v.assign(grupe.begin(), it);
    grupe.erase(grupe.begin(), it);
}

void split_3_list(list<Studentas>& grupe, list<Studentas>& v) {
    v.clear();

    auto it = std::partition(grupe.begin(), grupe.end(), [](const Studentas& a) {
        return a.getGalVid() < 5.0;
    });

    v.assign(grupe.begin(), it);

    grupe.erase(grupe.begin(), it);
}
