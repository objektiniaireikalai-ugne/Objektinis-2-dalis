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
    if (nd_.empty()) {
        galutinis_vidurkis_ = 0.6 * egzaminas_;
        galutinis_mediana_ = 0.6 * egzaminas_;
    } else {
        double s = 0;
        for (size_t i = 0; i < nd_.size(); i++) s += nd_[i];
        galutinis_vidurkis_ = 0.4 * (s / nd_.size()) + 0.6 * egzaminas_;

        std::vector<int> kopija = nd_;
        std::sort(kopija.begin(), kopija.end());
        int n = kopija.size();
        double med = (n % 2 == 0) ? (kopija[n/2 - 1] + kopija[n/2]) / 2.0 : kopija[n/2];
        galutinis_mediana_ = 0.4 * med + 0.6 * egzaminas_;
    }
}

std::istream& Studentas::readStudent(std::istream& is) {
    is >> vardas_ >> pavarde_;

    std::vector<int> tempPaz;
    int x;
    while (is >> x) tempPaz.push_back(x);

    if (!tempPaz.empty()) {
        egzaminas_ = tempPaz.back();
        tempPaz.pop_back();
        nd_ = tempPaz;
        skaiciuoti();
    }
    return is;
}

bool RusiuotiPagalVarda(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool RusiuotiPagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool RusiuotiPagalBala(const Studentas& a, const Studentas& b) {
    return a.galVid() < b.galVid();
}


static mt19937 gen(random_device{}());
static uniform_int_distribution<> dist(1, 10);

int GeneruotiPazymi() {
    return dist(gen);
}

Studentas GeneruotiStudenta(int numeris) {
    std::string v = "Vardas" + std::to_string(numeris);
    std::string p = "Pavarde" + std::to_string(numeris);

    std::vector<int> tempPaz;
    int kiek = dist(gen) % 8 + 3;
    for (int i = 0; i < kiek; i++) {
        tempPaz.push_back(GeneruotiPazymi());
    }
    int egzaminas = GeneruotiPazymi();

    return Studentas(v, p, tempPaz, egzaminas);
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
        out << left << setw(16) << A.vardas() << setw(20) << A.pavarde(); 
        for (int j = 0; j < 15; j++) {
            out << right << setw(6) << GeneruotiPazymi();
        }
        out << right << setw(6) << GeneruotiPazymi() << "\n";
    }
}

bool nuskaitymas(std::vector<Studentas>& grupe, const std::string& failas) {
    std::ifstream in(failas.c_str());
    if (!in) return false;

    grupe.clear();
    std::string eilute;
    std::getline(in, eilute);

    while (std::getline(in, eilute)) {
        if (eilute.empty()) continue;
        std::istringstream ss(eilute);
        
        Studentas A(ss); 
        if (!A.vardas().empty()) {
            grupe.push_back(A);
        }
    }
    return true;
}

bool nuskaitymas(std::list<Studentas>& grupe, const std::string& failas) {
    std::ifstream in(failas.c_str());
    if (!in) return false;

    grupe.clear();
    std::string eilute;
    std::getline(in, eilute);

    while (std::getline(in, eilute)) {
        if (eilute.empty()) continue;
        std::istringstream ss(eilute);
        
        Studentas A(ss);
        if (!A.vardas().empty()) {
            grupe.push_back(A);
        }
    }
    return true;
}

void kategorijos(vector<Studentas>& grupe, vector<Studentas>& nabageliai, vector<Studentas>& kietiakai) {
    nabageliai.clear();
    kietiakai.clear();

    nabageliai.reserve(grupe.size());
    kietiakai.reserve(grupe.size());

    for (const auto &a : grupe) {
        if (a.galVid() < 5.0) { 
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

void kategorijos(const std::list<Studentas>& grupe,
                 std::list<Studentas>& nabageliai,
                 std::list<Studentas>& kietiakai) {
    nabageliai.clear();
    kietiakai.clear();

    for (auto it = grupe.begin(); it != grupe.end(); ++it) {
        if (it->galVid() < 5.0) { 
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
        out << left << setw(16) << grupe[i].vardas() << setw(20) << grupe[i].pavarde() << right << setw(20); 
        if (rodytiVid) {
            out << grupe[i].galVid();
        } else {
            out << grupe[i].galMed();
        }
        out << "\n";
    }
}

void IsvestiIFaila(const std::string& failas, const std::list<Studentas>& grupe, bool rodytiVid) {
    ofstream out(failas.c_str());
    out << left << setw(16) << "Vardas" << setw(20) << "Pavarde" << right << setw(20) << "Galutinis" << "\n";
    out << fixed << setprecision(2);

    for (auto it = grupe.begin(); it != grupe.end(); ++it) {
        out << left << setw(16) << it->vardas() << setw(20) << it->pavarde() << right << setw(20); 
        if (rodytiVid) {
            out << it->galVid();
        } else {
            out << it->galMed();
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
        cout << left << setw(16) << grupe[i].vardas() << setw(20) << grupe[i].pavarde();       
        if (rodytiVid) cout << right << setw(20) << grupe[i].galVid();
        if (rodytiMed) cout << right << setw(20) << grupe[i].galMed();
        cout << "\n";
    }
}

void split_1_vector(vector<Studentas>& grupe, vector<Studentas>& v, vector<Studentas>& k) {
    v.clear();
    k.clear();
    v.reserve(grupe.size());
    k.reserve(grupe.size());

    for (const auto& a : grupe) {
        if (a.galVid() < 5.0) { 
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
        if (a.galVid() < 5.0) { 
            v.push_back(a);
        } else {
            k.push_back(a);
        }
    }
}

void split_2_vector(vector<Studentas>& grupe, vector<Studentas>& v) {
    v.clear();

    sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
        return a.galVid() > b.galVid(); 
    });

    while (!grupe.empty() && grupe.back().galVid() < 5.0) { 
        v.push_back(grupe.back());
        grupe.pop_back();
    }
}

void split_2_list(list<Studentas>& grupe, list<Studentas>& v) {
    v.clear();

    grupe.sort([](const Studentas& a, const Studentas& b) {
        return a.galVid() > b.galVid(); 
    });

    while (!grupe.empty() && grupe.back().galVid() < 5.0) { 
        v.push_back(grupe.back());
        grupe.pop_back();
    }
}

void split_3_vector(vector<Studentas>& grupe, vector<Studentas>& v) {
    v.clear();
    auto it = std::partition(grupe.begin(), grupe.end(), [](const Studentas& a) {
        return a.galVid() < 5.0; 
    });

    v.assign(grupe.begin(), it);
    grupe.erase(grupe.begin(), it);
}

void split_3_list(list<Studentas>& grupe, list<Studentas>& v) {
    v.clear();

    auto it = std::partition(grupe.begin(), grupe.end(), [](const Studentas& a) {
        return a.galVid() < 5.0; 
    });

    v.assign(grupe.begin(), it);

    grupe.erase(grupe.begin(), it);
}

std::istream& operator>>(std::istream& is, Studentas& s) {
    is >> s.vardas_ >> s.pavarde_;

    std::vector<int> tempPaz;
    int x;
    while (is >> x) tempPaz.push_back(x);

    if (!tempPaz.empty()) {
        s.egzaminas_ = tempPaz.back();
        tempPaz.pop_back();
        s.nd_ = tempPaz;
        s.skaiciuoti();
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << std::left << std::setw(16) << s.vardas() 
       << std::setw(20) << s.pavarde() 
       << std::right << std::setw(20) << std::fixed << std::setprecision(2) << s.galVid();
    return os;
}
