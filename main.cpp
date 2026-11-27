#include "funkcijos.h"
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;
using namespace std::chrono;

double sek(steady_clock::time_point p1, steady_clock::time_point p2) {
    return duration<double>(p2 - p1).count();
}

void RusiavimoPasirinkimas(vector<Studentas>& grupe, int pasirinkimas) {
    if (pasirinkimas == 1)      sort(grupe.begin(), grupe.end(), RusiuotiPagalVarda);
    else if (pasirinkimas == 2) sort(grupe.begin(), grupe.end(), RusiuotiPagalPavarde);
    else                        sort(grupe.begin(), grupe.end(), RusiuotiPagalBala);
}

void TestuotiFaila(const string& failas, int rusRusis, int kartai) {
    double sumN = 0, sumR = 0, sumD = 0, sumV = 0, sumK = 0, sumViso = 0;
    int n = 0;

    for (int k = 0; k < kartai; k++) {
        vector<Studentas> grupe, vargsiukai, kietiakai;

        auto visoP = steady_clock::now();

        auto t1 = steady_clock::now();
        if (!nuskaitymas(grupe, failas)) {
            cout << failas << " - nerastas\n";
            return;
        }
        auto t2 = steady_clock::now();
        sumN += sek(t1, t2);
        n = grupe.size();

        auto t3 = steady_clock::now();
        RusiavimoPasirinkimas(grupe, rusRusis);
        auto t4 = steady_clock::now();
        sumR += sek(t3, t4);

        auto t5 = steady_clock::now();
        kategorijos(grupe, vargsiukai, kietiakai);
        auto t6 = steady_clock::now();
        sumD += sek(t5, t6);

        auto t7 = steady_clock::now();
        IsvestiIFaila("vargsiukai_test.txt", vargsiukai, true);
        auto t8 = steady_clock::now();
        sumV += sek(t7, t8);

        auto t9 = steady_clock::now();
        IsvestiIFaila("kietiakai_test.txt", kietiakai, true);
        auto t10 = steady_clock::now();
        sumK += sek(t9, t10);

        auto visoPab = steady_clock::now();
        sumViso += sek(visoP, visoPab);
    }

    cout << failas << " (" << n << "):\n";
    cout << "  Nuskaitymas: " << (sumN / kartai) << " s\n";
    cout << "  Rusiavimas:  " << (sumR / kartai) << " s\n";
    cout << "  Dalijimas:   " << (sumD / kartai) << " s\n";
    cout << "  Vargsiuku isvedimas: " << (sumV / kartai) << " s\n";
    cout << "  Kietiaku isvedimas:  " << (sumK / kartai) << " s\n";
    cout << "  Viso testo:  " << (sumViso / kartai) << " s\n\n";
}

void TestuotiVisus(int rusRusis) {
    string failai[] = {
        "studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt",
        "studentai10000000.txt"
    };
    for (int i = 0; i < 5; i++) {
        TestuotiFaila(failai[i], rusRusis, 3);
    }
}

void TestuotiFailaList(const string& failas, int rusRusis, int kartai) {
    double sumN = 0, sumR = 0, sumD = 0, sumV = 0, sumK = 0, sumViso = 0;
    int n = 0;

    for (int k = 0; k < kartai; k++) {
        list<Studentas> grupe, vargsiukai, kietiakai;

        auto visoP = steady_clock::now();

        auto t1 = steady_clock::now();
        if (!nuskaitymas(grupe, failas)) {
            cout << failas << " - nerastas\n";
            return;
        }
        auto t2 = steady_clock::now();
        sumN += sek(t1, t2);
        n = grupe.size();

        auto t3 = steady_clock::now();
        if (rusRusis == 1) grupe.sort(RusiuotiPagalVarda);
        else if (rusRusis == 2) grupe.sort(RusiuotiPagalPavarde);
        else grupe.sort(RusiuotiPagalBala);
        auto t4 = steady_clock::now();
        sumR += sek(t3, t4);

        auto t5 = steady_clock::now();
        kategorijos(grupe, vargsiukai, kietiakai);
        auto t6 = steady_clock::now();
        sumD += sek(t5, t6);

        auto t7 = steady_clock::now();
        IsvestiIFaila("vargsiukai_test_list.txt", vargsiukai, true);
        auto t8 = steady_clock::now();
        sumV += sek(t7, t8);

        auto t9 = steady_clock::now();
        IsvestiIFaila("kietiakai_test_list.txt", kietiakai, true);
        auto t10 = steady_clock::now();
        sumK += sek(t9, t10);

        auto visoPab = steady_clock::now();
        sumViso += sek(visoP, visoPab);
    }

    cout << "  [LIST] " << failas << " (" << n << "):\n";
    cout << "    Nuskaitymas: " << (sumN / kartai) << " s\n";
    cout << "    Rusiavimas:  " << (sumR / kartai) << " s\n";
    cout << "    Dalijimas:   " << (sumD / kartai) << " s\n";
    cout << "    Vargsiuku isvedimas: " << (sumV / kartai) << " s\n";
    cout << "    Kietiaku isvedimas:  " << (sumK / kartai) << " s\n";
    cout << "    Viso testo:  " << (sumViso / kartai) << " s\n\n";
}

void TestuotiVisusList(int rusRusis) {
    string failai[] = {
        "studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt",
        "studentai10000000.txt"
    };
    for (int i = 0; i < 5; i++) {
        TestuotiFailaList(failai[i], rusRusis, 3);
    }
}

void GeneruotiVisus() {
    string failai[] = {
        "studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt",
        "studentai10000000.txt"
    };
    int kiekiai[] = { 1000, 10000, 100000, 1000000, 10000000 };

    for (int i = 0; i < 5; i++) {
        auto t1 = steady_clock::now();
        GeneruotiFaila(failai[i], kiekiai[i]);
        auto t2 = steady_clock::now();
        cout << failai[i] << ": " << sek(t1, t2) << " s\n";
    }
}

void TestuotiStrategijas() {
    cout << "\n===== DALIJIMO STRATEGIJU TESTAVIMAS =====\n";
    string failai[] = {
        "studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt",
        "studentai10000000.txt"
    };

    for (int f = 0; f < 5; f++) {
        cout << "\n--- Failas: " << failai[f] << " ---\n";

        {
            vector<Studentas> grupe, v, k;
            if(nuskaitymas(grupe, failai[f])) {
                auto t1 = steady_clock::now();
                split_1_vector(grupe, v, k);
                auto t2 = steady_clock::now();
                cout << "[Vector] 1 Strategija: " << sek(t1, t2) << " s\n";

                vector<Studentas> grupe2 = grupe;
                t1 = steady_clock::now();
                split_2_vector(grupe2, v);
                t2 = steady_clock::now();
                cout << "[Vector] 2 Strategija: " << sek(t1, t2) << " s\n";

                vector<Studentas> grupe3 = grupe;
                t1 = steady_clock::now();
                split_3_vector(grupe3, v);
                t2 = steady_clock::now();
                cout << "[Vector] 3 Strategija: " << sek(t1, t2) << " s\n";
            }
        }

        {
            list<Studentas> grupe, v, k;
            if(nuskaitymas(grupe, failai[f])) {
                auto t1 = steady_clock::now();
                split_1_list(grupe, v, k);
                auto t2 = steady_clock::now();
                cout << "[List] 1 Strategija: " << sek(t1, t2) << " s\n";

                list<Studentas> grupe2 = grupe;
                t1 = steady_clock::now();
                split_2_list(grupe2, v);
                t2 = steady_clock::now();
                cout << "[List] 2 Strategija: " << sek(t1, t2) << " s\n";

                list<Studentas> grupe3 = grupe;
                t1 = steady_clock::now();
                split_3_list(grupe3, v);
                t2 = steady_clock::now();
                cout << "[List] 3 Strategija: " << sek(t1, t2) << " s\n";
            }
        }
    }
}

void DemonstruotiRuleOfThree() {
    std::cout << "\n===== RULE OF THREE (IR FIVE) DEMONSTRACIJA =====\n";

    std::cout << "\n1. Kuriame studenta A (parametrizuotas konstruktorius):\n";
    Studentas A("Jonas", "Jonaitis", {8, 9, 10}, 9);

    std::cout << "\n2. Kuriame studenta B kaip A kopija (kopijavimo konstruktorius):\n";
    Studentas B = A;

    std::cout << "\n3. Kuriame tuscia studenta C ir priskiriame jam A (kopijavimo priskyrimas):\n";
    Studentas C;
    C = A;

    std::cout << "\n4. Perkeliame B į D (perkelimo konstruktorius):\n";
    Studentas D = std::move(B);

    std::cout << "\n5. Perkeliame D į E (perkelimo priskyrimas):\n";
    Studentas E;
    E = std::move(D);

    std::cout << "\n6. Visi studentai bus sunaikinti (destruktoriai)...\n";
}

void DemonstruotiAbstrakciaKlase() {
    std::cout << "\n===== v1.5 ABSTRAKCIOS KLASES DEMONSTRACIJA =====\n";

    std::cout << "1. Bandymas sukurti 'zmogus' objekta:\n";
    //zmogus z;
    std::cout << "   Klaida! 'zmogus' yra abstrakti klase, objekto sukurti negalima.\n";

    std::cout << "\n2. Polimorfizmas per bazines klases rodykle:\n";
    zmogus* zmogus1 = new Studentas("Antanas", "Antanaitis", {9, 10, 8}, 10);
    zmogus1->spausdintiInfo();
    delete zmogus1;
}

int main() {
    vector<Studentas> grupe, vargsiukai, kietiakai;

    cout << "Isvesties failus rusiuoti pagal: 1 - varda, 2 - pavarde, 3 - bala: ";
    int rusRusis;
    cin >> rusRusis;

    int p;
    while (true) {
        cout << "\n===== MENIU =====\n";
        cout << "1 - Ivesti studentus ranka\n";
        cout << "2 - Generuoti faila\n";
        cout << "3 - Generuoti visus 5 failus\n";
        cout << "4 - Nuskaityti is failo\n";
        cout << "5 - Padalinti i grupes\n";
        cout << "6 - Isvesti grupes i failus\n";
        cout << "7 - Spausdinti studentus i ekrana\n";
        cout << "8 - Automatinis testavimas (5 failai)\n";
        cout << "9 - Testuoti dalijimo strategijas\n";
        cout << "10 - Demonstruoti Rule of Three\n";
        cout << "11 - Demonstruoti Abstrakcia klase\n";
        cout << "0 - Baigti\n";
        cout << "Pasirinkimas: ";
        if (!(cin >> p)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (p == 0) break;

        else if (p == 1) {
            cout << "I kuri konteineri vesti? 1 - Vector, 2 - List: ";
            int konteineris;
            cin >> konteineris;

            int n;
            cout << "Kiek studentu? ";
            cin >> n;

            list<Studentas> listGrupe;

            for (int i = 0; i < n; i++) {
                std::string tempVar, tempPav;
                std::vector<int> tempPaz;
                int tempEgz;

                cout << "\nVardas: ";
                cin >> tempVar;
                cout << "Pavarde: ";
                cin >> tempPav;

                cout << "ND pazymiai (baigti - -1):\n";
                while (true) {
                    int x;
                    cin >> x;
                    if (x == -1) break;
                    if (x < 1 || x > 10) { cout << "1-10!\n"; continue; }
                    tempPaz.push_back(x);
                }

                cout << "Egzaminas: ";
                cin >> tempEgz;

                Studentas A(tempVar, tempPav, tempPaz, tempEgz);

                cout << "Sukurtas studentas: " << A << "\n";

                if (konteineris == 1) {
                    grupe.push_back(A);
                    cout << "Studento (Vector) saugojimo atmintyje adresas: " << &grupe.back() << "\n";
                } else {
                    listGrupe.push_back(A);
                    cout << "Studento (List) saugojimo atmintyje adresas: " << &listGrupe.back() << "\n";
                }
            }
        }

        else if (p == 2) {
            string f;
            int n;
            cout << "Failas: ";
            cin >> f;
            cout << "Kiek: ";
            cin >> n;
            auto t1 = steady_clock::now();
            GeneruotiFaila(f, n);
            auto t2 = steady_clock::now();
            cout << sek(t1, t2) << " s\n";
        }

        else if (p == 3) {
            GeneruotiVisus();
        }

        else if (p == 4) {
            string f;
            cout << "Failas: ";
            cin >> f;
            auto t1 = steady_clock::now();
            bool ok = nuskaitymas(grupe, f);
            auto t2 = steady_clock::now();
            if (!ok) {
                cout << "Nerastas failas.\n";
            } else {
                cout << grupe.size() << " studentai, "
                     << sek(t1, t2) << " s\n";
            }
        }

        else if (p == 5) {
            if (grupe.empty()) {
                cout << "Tuscia.\n";
                continue;
            }
            auto t1 = steady_clock::now();
            RusiavimoPasirinkimas(grupe, rusRusis);
            kategorijos(grupe, vargsiukai, kietiakai);
            auto t2 = steady_clock::now();
            cout << "Vargsiukai: " << vargsiukai.size()
                 << ", kietiakai: " << kietiakai.size()
                 << ", laikas: " << sek(t1, t2) << " s\n";
        }

        else if (p == 6) {
            if (vargsiukai.empty() && kietiakai.empty()) {
                cout << "Tuscia.\n";
                continue;
            }
            auto t1 = steady_clock::now();
            IsvestiIFaila("vargsiukai.txt", vargsiukai, true);
            IsvestiIFaila("kietiakai.txt", kietiakai, true);
            auto t2 = steady_clock::now();
            cout << sek(t1, t2) << " s\n";
        }

        else if (p == 7) {
            if (grupe.empty()) {
                cout << "Tuscia.\n";
                continue;
            }
            if (grupe.size() > 100) {
                cout << "Demesio: " << grupe.size() << " studentu!\n";
                cout << "Rekomenduojama naudoti 6 punkta (isvesti i faila).\n";
                cout << "Tikrai spausdinti? (t/n): ";
                char k;
                cin >> k;
                if (k != 't' && k != 'T') continue;
            }

            int v;
            cout << "Rodyti: 1 - Vid., 2 - Med., 3 - abu: ";
            cin >> v;
            bool rodytiVid = (v == 1 || v == 3);
            bool rodytiMed = (v == 2 || v == 3);

            int lim;
            cout << "Kiek rodyti (0 = visus)? ";
            cin >> lim;

            output(grupe, lim, rodytiVid, rodytiMed);
        }

        else if (p == 8) {
            cout << "\n===== TESTAVIMAS SU VECTOR =====\n";
            TestuotiVisus(rusRusis);

            cout << "\n===== TESTAVIMAS SU LIST =====\n";
            TestuotiVisusList(rusRusis);
        }
        else if (p == 9) {
            TestuotiStrategijas();
        }
        else if (p == 10) {
            DemonstruotiRuleOfThree();
        }
        else if (p == 11) {
            DemonstruotiAbstrakciaKlase();
        }
    }
    return 0;
}
