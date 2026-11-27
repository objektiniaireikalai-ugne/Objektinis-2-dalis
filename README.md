# Studentų pažymių skaičiavimo programa

Objektinio programavimo kurso darbas. Programa leidžia surinkti studentų namų darbų ir egzamino pažymius ir apskaičiuoja studento galutinį balą. Galimi pasirinkimai - įvesti pažymius ranka, sugeneruoti atsitiktinai arba nuskaityti iš failo. Galutinio balo skaičiavimas atliekamas dviem būdais - pagal namų darbų vidurkį ir pagal jų medianą.

## Galutinio balo formulės

- **galutinis (vid.)** = 0.4 × namų darbų vidurkis + 0.6 × egzaminas
- **galutinis (med.)** = 0.4 × namų darbų mediana + 0.6 × egzaminas

## Turinys

- [Reikalavimai ir paleidimas](#reikalavimai-ir-paleidimas)
- [Naudojimas](#naudojimas)
- [Duomenų failo formatas](#duomenų-failo-formatas)
- [Klaidų tikrinimas](#klaidų-tikrinimas)
- [Versijos (releases)](#versijos-releases)
- [Efektyvumo tyrimai](#efektyvumo-tyrimai)

## Diegimas ir paleidimas

Projektas naudoja **CMake (3.16 ar naujesnę versiją)** ir reikalauja **C++17** standarto kompiliatoriaus (GCC, Clang arba MSVC).

Sukompiliuoti programą galima šiomis komandomis:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Paleidimas:
- Windows: `.\build\programa.exe`
- Linux / macOS: `./build/programa`

**Windows aplinkos ypatumai:**

- Jei terminalas neranda kompiliatoriaus (`g++`), galite nurodyti kelią iki Code::Blocks MinGW kompiliatoriaus tiesiogiai:

```bash
cmake -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER="C:/Program Files/CodeBlocks/MinGW/bin/g++.exe" -DCMAKE_BUILD_TYPE=Release
```
- Jei paleidus programą pranešama apie trūkstamus `.dll` failus, nukopijuokite `libstdc++-6.dll`, `libgcc_s_seh-1.dll` ir `libwinpthread-1.dll` iš `C:\Program Files\CodeBlocks\MinGW\bin` katalogo į `build` aplanką.
   
## Naudojimas

Paleidus programą rodomas meniu:

```text
===== MENIU =====
1 - Ivesti studentus
2 - Generuoti faila
3 - Generuoti visus 5 failus
4 - Nuskaityti studentus is failo
5 - Padalinti i grupes
6 - Isvesti grupes i failus
7 - Spausdinti studentus i ekrana
8 - Automatinis testavimas (5 failai)
0 - Baigti
```

**1 – Įvesti studentus** – prašoma ranka įvesti vardą ir pavardę, po to vedami namų darbų pažymiai (įvedimas baigiamas įvedus `-1`), tada įvedamas egzamino pažymys. Programa tikrina, kad pažymys būtų intervale [1; 10].

**2 – Generuoti failą** – sugeneruoja vieną failą su nurodytu studentų skaičiumi.

**3 – Generuoti visus 5 failus** – automatiškai sugeneruoja 5 testavimo failus (nuo 1 000 iki 10 000 000 įrašų).

**4 – Nuskaityti studentus iš failo** – nuskaito studentus iš nurodyto failo.

**5 – Padalinti į grupes** – surūšiuoja studentus ir padalina juos į „vargšiukus“ (< 5.0) ir „kietiakus“ (>= 5.0)

**6 – Išvesti į failus** – išsaugo abi grupes į atskirus failus.

**7 – Spausdinti į ekraną** – išveda studentus lentele.

**8 – Automatinis testavimas** – atlieka spartos matavimus su `std::vector` ir `std::list` konteineriais naudojant 5 failus.

## Duomenų failo formatas

Pirma failo eilutė – antraštė (ji praleidžiama). Toliau kiekviena eilutė aprašo vieną studentą:

```text
Vardas          Pavarde                 ND1   ND2   ND3   ND4   ND5   Egz.
Jonas           Jonaitis                  8     9     7    10     6     9
Petras          Petraitis                 5     6     4     7     8     6
Ona             Onaityte                 10    10     9     9    10    10
```
Namų darbų pažymių skaičius iš anksto nėra žinomas – skaitomi visi eilutėje esantys skaičiai, o paskutinis iš jų priskiriamas egzaminui. Stulpelių skaičius skirtingose eilutėse gali skirtis, skiriamieji simboliai – bet koks tarpų kiekis.

## Klaidų tikrinimas

Programa apsaugota nuo neteisingo vartotojo įvedimo ir neegzistuojančių failų:

- **Raidė vietoj skaičiaus** – srautas išvalomas (`cin.clear()`, `cin.ignore()`), rodomas klaidos pranešimas ir prašoma įvesti iš naujo. Programa nenulūžta.

- **Pažymys ne intervale [1; 10]** – rodomas pranešimas ir prašoma įvesti iš naujo.

- **Neįvesta nė vieno namų darbų** – `vidurkis()` ir `mediana()` funkcijos grąžina 0, jei pažymių sąrašas tuščias. Dalyba iš nulio neįvyksta, galutinis balas apskaičiuojamas tik iš egzamino (0.6 × egzaminas).

- **Failas neegzistuoja** – rodomas pranešimas „Nepavyko atidaryti" ir grįžtama į meniu.

## Versijos (releases)

Kiekviena versija turi atskirą žymą (tag) ir atskirą release'ą GitHub'e.

| Versija | Šaka | Trumpai |
|---------|------|---------|
| v.pradinė | v.pradinė | Duomenų įvedimas ranka, vidurkis ir mediana, rezultatų lentelė |
| v0.1 | v0.1 | Skaitymas iš failo, rikiavimas, testavimo failų generavimas |
| v0.2 | v0.2 | Kodo refactoring'as į failus, skirstymas į grupes, rūšiavimas pagal pasirinkimą, efektyvumo tyrimai|
| v0.3 | v0.3 | `std::list` konteinerio palyginimas su `std::vector`, adreso išvedimas|


### v.pradinė

Pirmoji veikianti programos versija. Duomenų įvedimas ranka, rezultatų skaičiavimas ir išvedimas į ekraną.

**Funkcionalumas:**

- Struktūra `studentas` (vardas, pavardė, `vector<int> paz`, egzaminas) ir `vector<studentas> grupe`.
- Namų darbų pažymių skaičius nėra žinomas iš anksto – įvedimas baigiamas įvedus `-1`.
- Galimybė atsitiktinai sugeneruoti tiek namų darbų, tiek egzamino pažymius (`rand()`).
- Galutinio balo skaičiavimas pagal vidurkį (`vidurkis()`) ir pagal medianą (`mediana()`), rezultatas pateikiamas dviejų skaitmenų po kablelio tikslumu.
- Rezultatų išvedimas sulygiuota lentele naudojant `<iomanip>` (`setw`, `left`, `right`, `fixed`, `setprecision`).
- Įvesties klaidų tikrinimas (pvz.: pažymys ne intervale [1; 10]).
- Funkcijos suskirstytos pagal atsakomybes: `IvestiStudenta()`, `GeneruotiStudenta()`, `output()`, `vidurkis()`, `mediana()`.

**Apribojimai:**

- Duomenis galima įvesti tik ranka arba sugeneruoti – failų skaitymo nėra.
- Visas sąrašas visada išvedamas iš karto, todėl su dideliu kiekiu studentų išvestis tampa neperskaitoma.

### v0.1

**Kas nauja, palyginti su v.pradinė:**

- **Duomenų skaitymas iš failo (`nuskaitymas()`):** vartotojas pats nurodo failo pavadinimą, tad programa nėra pririšta prie vieno konkretaus failo. Eilutė skaidoma per `istringstream`, paskutinis skaičius traktuojamas kaip egzaminas.
- **Rikiavimas pagal pavardę** prieš išvedimą (`std::sort` su `rusiuoti()` funkcija).
- **Testavimo failų generavimas (`GeneruotiFaila()`):** vartotojas nurodo failo pavadinimą ir studentų skaičių, programa sukuria failą su atsitiktiniais duomenimis pagal pateiktą formatą.
- **Įvesties klaidų tikrinimas:** pridėti `cin.clear()` ir `cin.ignore()` apsaugai nuo neteisingo įvedimo (raidė vietoj skaičiaus). Programa rodo klaidų pranešimus ir prašo įvesti iš naujo – nenulūžta.
- **Apsauga nuo dalybos iš nulio:** jei studentas neturi nė vieno namų darbų pažymio, `vidurkis()` ir `mediana()` grąžina 0, o galutinis balas skaičiuojamas tik iš egzamino.

### v0.2

**Kas nauja, palyginti su v0.1:**

- **Kodo refactoring'as** – kodas išskaidytas į kelis failus pagal atsakomybes:
  - `studentas.h` – struktūra `studentas`
  - `funkcijos.h` – visų funkcijų deklaracijos
  - `funkcijos.cpp` – visų funkcijų realizacijos
  - `main.cpp` – pagrindinė programa su meniu
- **Atsitiktinių skaičių generavimas perkeltas į `<random>` biblioteką** – naudojamas `std::mt19937` generatorius ir `std::uniform_int_distribution<>`. Tai modernesnis ir kokybiškesnis sprendimas už seną `rand()`.
- **Skirstymas į dvi grupes** pagal galutinį balą:
  - **vargšiukai** – galutinis balas < 5.0
  - **kietiakai** – galutinis balas >= 5.0
- **Rūšiavimas pagal naudotojo pasirinkimą** – trys variantai:
  - pagal vardą (`RusiuotiPagalVarda`)
  - pagal pavardę (`RusiuotiPagalPavarde`)
  - pagal galutinį balą (`RusiuotiPagalBala`)
- **Išvedimas į du atskirus failus** – `vargsiukai.txt` ir `kietiakiai.txt` (arba su testavimo priesaga).
- **Automatinis testavimas** – programa sugeneruoja 5 skirtingo dydžio failus ir kiekvieną testuoja 3 kartus, pateikdama laikų vidurkį.
- **Laiko matavimas** atliekamas kiekvienam etapui atskirai:
  - failų generavimas
  - nuskaitymas iš failo
  - rūšiavimas
  - dalijimas į dvi grupes
  - vargšiukų išvedimas į failą
  - kietiakų išvedimas į failą
- **Efektyvumo tyrimai** atlikti su 5 failais (1 000 – 10 000 000 įrašų) ir aprašyti šio README skyriuje „Efektyvumo tyrimai".

### v0.3

- Pridėtas `std::list` konteinerio palyginimas su `std::vector`.
- Realizuotas funkcijų perkrovimas (overloading) abiems konteineriams.
- Rankinio įvedimo metu išvedamas objekto adresas atmintyje (`&A`).

## Efektyvumo tyrimai

Testavimas atliktas su 5 skirtingo dydžio failais – 1 000, 10 000, 100 000, 1 000 000 ir 10 000 000 įrašų. Kiekvienas testas kartotas **3 kartus**, pateikiamas **laikų vidurkis**.

### Testavimo sistemos parametrai:
- **CPU**: Intel Core i5-1035G1 @ 1.00GHz
- **RAM**: 8.0 GB DDR4
- **Diskas**: SSD NVMe 256 GB

### Failų generavimo laikai

| Failas | Įrašų skaičius | Generavimo laikas |
|--------|---------------:|------------------:|
| studentai1000.txt | 1 000 | 0.016 s |
| studentai10000.txt | 10 000 | 0.044 s |
| studentai100000.txt | 100 000 | 0.461 s |
| studentai1000000.txt | 1 000 000 | 4.574 s |
| studentai10000000.txt | 10 000 000 | 48.486 s |

### Tyrimas v0.2: `std::vector` konteineris

| Įrašai | Nuskaitymas | Rūšiavimas | Dalijimas | Vargšiukų išv. | Kietiakų išv. | Viso |
|-------:|------------:|-----------:|----------:|---------------:|--------------:|-----:|
| 1 000 | 0.008 s | 0.001 s | 0.0005 s | 0.002 s | 0.002 s | 0.014 s |
| 10 000 | 0.059 s | 0.008 s | 0.004 s | 0.009 s | 0.010 s | 0.090 s |
| 100 000 | 0.529 s | 0.097 s | 0.034 s | 0.051 s | 0.086 s | 0.798 s |
| 1 000 000 | 5.321 s | 1.435 s | 0.403 s | 0.557 s | 0.812 s | 8.529 s |
| 10 000 000 | 60.937 s | 19.427 s | 8.860 s | 7.328 s | 9.535 s | 106.087 s |

### v0.2 Išvados

- **Nuskaitymas iš failo** yra lėčiausias etapas – užima apie 60–70 % viso testo laiko. Tai susiję su eilutės skaidymu per `istringstream` ir skaičių konvertavimu.
- **Rūšiavimas** užima apie 15–20 % viso laiko. Naudojamas `std::sort` su vidutiniu O(n log n) sudėtingumu.
- **Dalijimas į dvi grupes** – greičiausias etapas (apie 5–8 %), nes tai tiesiog vienas perėjimas per vektorių.
- **Išvedimas į failus** užima apie 10–15 % laiko.
- **Laikas auga tiesiškai** – 10 kartų daugiau įrašų → maždaug 10–12 kartų ilgesnis laikas. Tai rodo, kad algoritmai efektyvūs.
- **Didžiausias failas (10M įrašų)** buvo apdorotas per ~106 s. Programos resursų naudojimas išlieka priimtinas net ir su labai dideliais duomenų kiekiais.

## Tyrimas v0.3 (Konteinerių palyginimas): `std::vector` vs `std::list`

Tyrimo tikslas – išmatuoti, kaip programos sparta priklauso nuo naudojamo konteinerio.

### Rezultatai su `std::vector`

| Įrašai | Nuskaitymas | Rūšiavimas | Dalijimas | Vargšiukų išv. | Kietiakų išv. | Viso |
|-------:|------------:|-----------:|----------:|---------------:|--------------:|-----:|
| 1 000 | 0.0065 s | 0.0008 s | 0.0003 s | 0.0015 s | 0.0013 s | 0.0107 s |
| 10 000 | 0.0528 s | 0.0082 s | 0.0030 s | 0.0062 s | 0.0074 s | 0.0779 s |
| 100 000 | 0.4986 s | 0.0876 s | 0.0346 s | 0.0531 s | 0.0784 s | 0.7525 s |
| 1 000 000 | 5.6337 s | 1.4595 s | 0.4262 s | 0.6961 s | 1.0415 s | 9.2573 s |
| 10 000 000 | 55.493 s | 18.600 s | 9.0731 s | 7.3728 s | 10.351 s | 100.891 s |

### Rezultatai su `std::list`

| Įrašai | Nuskaitymas | Rūšiavimas | Dalijimas | Vargšiukų išv. | Kietiakų išv. | Viso |
|-------:|------------:|-----------:|----------:|---------------:|--------------:|-----:|
| 1 000 | 0.0062 s | 0.0002 s | 0.0003 s | 0.0018 s | 0.0019 s | 0.0105 s |
| 10 000 | 0.0604 s | 0.0040 s | 0.0036 s | 0.0069 s | 0.0124 s | 0.0875 s |
| 100 000 | 0.6077 s | 0.0683 s | 0.0471 s | 0.0650 s | 0.1065 s | 0.8949 s |
| 1 000 000 | 7.6566 s | 1.0397 s | 0.6317 s | 0.7147 s | 0.9549 s | 10.998 s |
| 10 000 000 | 55.090 s | 12.360 s | 7.7955 s | 6.9762 s | 11.069 s | 93.291 s |

<img width="391" height="594" alt="vector1" src="https://github.com/user-attachments/assets/0a09e056-b76c-4b84-8a4c-d473ab7af64b" />
<img width="376" height="382" alt="vector2" src="https://github.com/user-attachments/assets/1f19fb97-f26e-4517-9f8f-5d37867a60f5" />
<img width="417" height="610" alt="list1" src="https://github.com/user-attachments/assets/99ed24ce-732c-4d9d-b575-b1d297377b98" />
<img width="450" height="375" alt="list2" src="https://github.com/user-attachments/assets/43a730d5-a7d7-4bcb-8734-41b99d72c377" />

### Išvados

- **Nuskaitymas iš failo** – abu konteineriai veikia beveik identiškai, nes duomenų skaitymas labiausiai priklauso nuo disko (SSD) greičio, o ne nuo konteinerio tipo.
- **Rūšiavimas** – tai pati įdomiausia vieta. Su mažesniais duomenų kiekiais `std::vector` rūšiuoja greičiau. Tačiau su 10 000 000 įrašų `std::list` rūšiavimas (12.36 s) buvo **ženkliai greitesnis** nei `std::vector` (18.60 s). Tai nutinka todėl, kad mūsų `studentas` struktūra yra „sunki“ (turi du `string` ir vieną `vector`). `std::sort` (vector atveju) turi fiziškai perkelti visus šiuos didelius objektus atmintyje, o `std::list::sort` tiesiog sukeičia rodykles (pointerius) į atminties vietas. Esant dideliam duomenų kiekiui, rodyklių perstūmimas pasirodė efektyvesnis už objektų kopijavimą.
- **Dalijimas į grupes** – `std::list` taip pat buvo šiek tiek greitesnis (7.79 s prieš 9.07 s), nes dalijimo metu vėlgi perkėlinėjami rodyklės, o ne fiziškai kopijuojami dideli struktūros objektai.
- **Išvedimas į failus** – `std::vector` veikė šiek tiek greičiau (mažiau laiko sąnaudų ieškant elemento, nes jie atmintyje guli ištisai), bet skirtumas nedidelis.
- **Bendras laikas** – nors `vector` yra greitesnis su mažais duomenimis, su 10M įrašų `std::list` bendrai apdorojo duomenis greičiau (93.29 s prieš 100.89 s) dėl sparčiau atlikto rūšiavimo.

## v1.0 – Dalijimo strategijų optimizavimas

### Strategijų aprašymas

Tyrimo metu buvo realizuotos ir palygintos trys skirtingos studentų dalijimo į dvi kategorijas strategijos:

**1 strategija (Du nauji konteineriai):**
Studentai yra tiesiog nukopijuojami iš pradinio konteinerio į du naujus: `vargsiukai` ir `kietiakiai`. Pradinis konteineris lieka nepakitęs. 
*Šios strategijos trūkumas:* Ji yra neefektyvi atminties atžvilgiu, nes kiekvienas studentas atmintyje egzistuoja du kartus.

**2 strategija (Rūšiavimas ir ištrynimas nuo galo):**
Pirminis studentų sąrašas yra surūšiuojamas mažėjančia tvarka pagal galutinį balą (`std::sort` arba `list::sort`). Tada iš konteinerio galo (`pop_back`) yra išimami studentai, kurių balas mažesnis nei 5.0, ir perkeliami į `vargsiukai` konteinerį.
*Šios strategijos trūkumas:* Nors trynimas nuo galo yra greitas, pats rūšiavimas užima daug laiko (O(N log N)).

**3 strategija (Optimizuota su STL algoritmais):**
Ši strategija – tai patobulinimas, panaudojant efektyvius C++ standartinės bibliotekos (STL) algoritmus.
*   **`std::vector` atveju:** Panaudotas `std::partition` algoritmas, kuris per vieną ėjimą (O(N)) suskirsto vektorių į dvi dalis. Tada vargšiukai nukopijuojami į naują konteinerį ir ištrinami iš pradinio vienu `erase` metodu.
*   **`std::list` atveju:** Panaudotas tas pats `std::partition` algoritmas, pritaikytas dvikrypčiam sąrašui.

### Testavimo rezultatai 

**Rezultatai su `std::vector`**

| Įrašai | 1 strategija | 2 strategija | 3 strategija |
|-------:|-------------:|-------------:|-------------:|
| 1 000 | 0.00018 s | 0.00024 s | 0.00007 s |
| 10 000 | 0.00097 s | 0.00221 s | 0.00103 s |
| 100 000 | 0.01142 s | 0.02629 s | 0.01196 s |
| 1 000 000 | 0.11146 s | 0.32653 s | 0.10562 s |
| 10 000 000 | 6.78882 s | 43.2635 s | 37.2504 s |

**Rezultatai su `std::list`**

| Įrašai | 1 strategija | 2 strategija | 3 strategija |
|-------:|-------------:|-------------:|-------------:|
| 1 000 | 0.00018 s | 0.00055 s | 0.00015 s |
| 10 000 | 0.00223 s | 0.00411 s | 0.00233 s |
| 100 000 | 0.02069 s | 0.05169 s | 0.02262 s |
| 1 000 000 | 0.19894 s | 0.79552 s | 0.18301 s |
| 10 000 000 | 18.1231 s | 62.1184 s | 67.3102 s |

<img width="426" height="913" alt="dal" src="https://github.com/user-attachments/assets/9b7a2b99-cac7-4f43-bca1-7dc9568c2dad" />

### Išvados

1. **2 strategijos spartos problema:** Rūšiavimas yra pati brangiausia operacija. Net ir su optimizuotu Release režimu, 2 strategija su 10 milijonų įrašų vektoriuje užtruko net 43,2 s, o liste – 62,1 s. Tai patvirtina, kad ieškoti vargšiukų rūšiuojant visą masyvą nėra efektyvu.
2. **Optimizavimo ribos ir Cache atmintis:** 
   * Su mažesniais duomenimis (iki 1M įrašų) 3 strategija (`std::partition`) dažniausiai yra greičiausia arba labai arti 1-osios, nes jai nereikia papildomai kopijuoti visų elementų į atmintį.
   * Tačiau su 10M įrašų matome netikėtą rezultatą: **1 strategija** vektoriuje (6.78 s) yra kur kas greitesnė už 3 strategiją (37.25 s). Tai lemia procesoriaus *Cache* atmintis – nuoseklus elementų kopijavimas (1 strategija) yra draugiškesnis procesoriui, o `std::partition` atlieka daug vietos keitimų, sukeliančių *cache misses*.
   * Sąraše (`list`) su 10M įrašų 1 strategija (18.12 s) taip pat nugalėjo 3 strategiją (67.31 s) dėl tos pačios priežasties – rodyklių „vaikymasis“ dideliame duomenų kiekyje yra lėtas.
3. **Bendra išvada:** Jei duomenų nedaug, geriausia naudoti `std::partition` (3 strategija). Tačiau esant milžiniškiems duomenų kiekiams, paprastas kopijavimas į du naujus konteinerius (1 strategija) gali pasirodyti netikėtai greitesnis.

## v1.1 – Perėjimas nuo struktūros prie pilnavertės klasės

Šiame atnaujinime programa buvo patobulinta laikantis objektinio programavimo „gerųjų praktikų“. Pagrindiniai pakeitimai:

### Kodo pertvarkymas:
* **Struktūra paversta į klasę:** Sukurta pilnavertė `Studentas` klasė su privačiais duomenimis (naudojamas `_` pabraukimas).
* **Duomenų apsauga:** Panaikinti visi setteriai (`setVar`, `setPav` ir kt.), užtikrinant, kad nuskaityti duomenys negalėtų būti keičiami.
* **Saugus nuskaitymas:** Pridėtas konstruktorius, priimantis `std::istream&` ir `readStudent()` metodas, leidžiantis klasei savarankiškai ir saugiai nuskaityti duomenis iš failo.
* **Rule of 5:** Klasė realizuota su visais reikiamais konstruktoriais (numatytuoju, parametrizuotu, kopijavimo, perkėlimo), priskyrimo operatoriais ir destruktoriumi.
* **Getteriai:** Visi duomenų gavimo metodai (getteriai) realizuoti kaip `inline` funkcijos.

### Struct (v1.0) vs Class (v1.1) spartos palyginimas

Palyginimas atliktas naudojant fiksuotą `std::vector` konteinerį, greičiausią (1-ąją) dalijimo strategiją bei 100 000 ir 1 000 000 įrašų failus. Abu testai atlikti **Release** režime.

| Failas (įrašų sk.) | Struct (v1.0) laikas | Class (v1.1) laikas |
|--------------------|----------------------|---------------------|
| 100 000 | 0.01142 s | 0.01317 s |
| 1 000 000 | 0.11146 s | 0.13989 s |

**Išvada:** Rezultatai parodė, kad perėjus nuo `struct` prie `class`, dalijimo algoritmo sparta išliko praktiškai identiška – skirtumai matuojami milisekundėmis (0.011 s prieš 0.013 s su 100k įrašų). Class versija yra vos šiek tiek lėtesnė dėl papildomo objektų saugumo (konstruktoriai, geteriai) sukeliamo minimalaus atminties perstūmimo krūvio, tačiau tai neturi jokios realios įtakos bendram programos našumui. Objektinio programavimo teikiami privalumai (duomenų apsauga ir vientisumas) šiuo atveju yra kur kas svarbesni už mikroskopinį greičio skirtumą.

## v1.1 – Kompiliatoriaus optimizavimo flag'ų įtaka spartai

Atlikta eksperimentinė analizė, kaip programos sparta ir sugeneruoto vykdomojo failo (`.exe`) dydis priklauso nuo kompiliatoriaus optimizavimo lygio (`-O0`, `-O1`, `-O2`, `-O3`). Testavimas atliktas su fiksuotu `std::vector` konteineriu, naudojant 1-ąją (greičiausią) dalijimo strategiją ir 100 000 bei 1 000 000 įrašų failus.

### Rezultatai su Struct (v1.0)

| Optimizavimo flag'as | 100 000 įrašų laikas | 1 000 000 įrašų laikas | `.exe` dydis |
|----------------------|----------------------|------------------------|--------------|
| Be flag'o (`-O0`)    | 0.4923 s             | 5.6835 s               | 108 KB       |
| `-O1`                | 1.0636 s             | 4.1564 s               | 108 KB       |
| `-O2`                | 1.1331 s             | 4.4827 s               | 108 KB       |
| `-O3`                | 1.0872 s             | 4.0397 s               | 108 KB       |

### Rezultatai su Class (v1.1)

| Optimizavimo flag'as | 100 000 įrašų laikas | 1 000 000 įrašų laikas | `.exe` dydis |
|----------------------|----------------------|------------------------|--------------|
| Be flag'o (`-O0`)    | 0.5280 s             | 7.2698 s               | 107 KB       |
| `-O1`                | 1.0793 s             | 4.6908 s               | 107 KB       |
| `-O2`                | 1.4643 s             | 4.7516 s               | 107 KB       |
| `-O3`                | 1.4144 s             | 4.6276 s               | 107 KB       |

### Išvados

1. **Optimizavimo įtaka klasei:** Be optimizavimo (`-O0`) klasės versija yra pastebimai lėtesnė už struktūros (7.27 s prieš 5.68 s su 1M įrašų), nes kompiliatorius kiekvieną kartą fiziškai kviečia geterius ir konstruktorius. Tačiau įjungus bet kokį optimizavimą (`-O1`, `-O2` ar `-O3`), šis skirtumas išnyksta – kompiliatorius automatiškai įterpia (inline) šiuos paprastus metodus. Su 1M įrašų abiejų versijų laikai susilygina ties ~4.0–4.7 s riba.
2. **Nestabilūs 100k laikai:** Mažesnio failo (100 000 įrašų) matavimai yra labiau veikiami foninių operacinės sistemos procesų ir disko podėlio (I/O). Todėl su `-O1`, `-O2` ir `-O3` laikai gali atrodyti šiek tiek prasčiau nei su `-O0`, nors tai nėra susiję su pačiu algoritmu.
3. **`.exe` failo dydis:** Optimizavimo flag'ai beveik nepakeitė `.exe` failo dydžio (jis išliko 107–108 KB). Taip yra todėl, kad didžioji dalis kodo yra C++ standartinės bibliotekos (STL) komponentai, kurie yra įkeliami dinamiškai, o pats optimizavimas labiau keičia instrukcijų vykdymo efektyvumą, o ne failo apimtį. Klasės versijos `.exe` failas yra net 1 KB mažesnis (107 KB prieš 108 KB), o tai rodo, kad objektyvus kodas yra šiek tiek kompaktiškesnis.

## v1.2 – Rule of Three ir Įvesties/Išvesties operatoriai

Šioje versijoje buvo pilnai įgyvendinta **„Rule of Three“** ir perdengti įvesties bei išvesties operatoriai, leidžiantys lengviau naudoti `Studentas` klasę ateities programuotojams.

### 1. Rule of Three realizacija

Klasė `Studentas` tvarko resursus (dinaminius `std::string` ir `std::vector`), todėl pagal C++ standartus jai būtinai reikia šių trijų specialiųjų metodų:
1. **Destruktorius (`~Studentas()`):** Atlaisvina resursus, kai objektas sunaikinamas. Nors STL konteineriai tai daro automatiškai, mes aiškiai išvalome duomenis, kad parodytume supratimą apie resursų valdymą.
2. **Kopijavimo konstruktorius (`Studentas(const Studentas&)`):** Užtikrina, kad kopijuojant objektą (pvz., dedant į `std::vector`), visi duomenys būtų nukopijuoti saugiai (atliekamas giluminis kopijavimas).
3. **Kopijavimo priskyrimo operatorius (`operator=`):** Leidžia saugiai priskirti vieną jau egzistuojantį studentą kitam, išvengiant atminties nutekėjimo ar savęs priskyrimo problemų.

*(Papildoma pastaba: Kadangi mokomės modernaus C++11 standarto, mes taip pat realizavome ir perkėlimo (move) konstruktorių bei perkėlimo priskyrimo operatorių. Tai reiškia, kad mūsų klasė atitinka ir platesnę „Rule of Five“ taisyklę, tačiau pagrindiniai „Rule of Three“ reikalavimai yra pilnai įvykdyti.)*

### 2. Perdengti įvesties ir išvesties operatoriai

**Įvesties operatorius (`operator>>`)**
Leidžia nuskaityti studento duomenis tiesiai iš bet kokio srauto (`cin`, `ifstream`, `istringstream`). Šis operatorius automatiškai nuskaito vardą, pavardę, pažymius ir paskutinį skaičių priskiria egzaminui.
*Panaudojimas:* `std::cin >> studentas;` arba `ss >> studentas;` (failo skaitymo metu).

**Išvesties operatorius (`operator<<`)**
Leidžia išvesti studento duomenis į bet kokį srautą. Jis išveda bazinę informaciją: vardą, pavardę ir galutinį balą (vidurkį), gražiai sulygiuotą.
*Panaudojimas:* `std::cout << studentas;` arba `out << studentas;`.

### 3. Duomenų įvesties ir išvesties metodų apžvalga

Mūsų programa palaiko kelis skirtingus būdus, kaip dirbti su duomenimis, kas užtikrina lankstumą naudojant klasę:

**Duomenų įvestis:**
*   **Rankiniu būdu:** Vartotojas įveda duomenis per terminalą (naudojant `cin`). Šis būdas naudojamas meniu 1 punkte.
*   **Automatiniu būdu:** Programa pati sugeneruoja studentus su atsitiktiniais pažymiais (`GeneruotiStudenta` funkcija).
*   **Iš failo:** Duomenys nuskaitomi iš `.txt` failo. Failo eilutė paverčiama į `istringstream` ir studentas sukuriamas naudojant `operator>>`.

**Duomenų išvestis:**
*   **Į ekraną:** Naudojama specializuota `output()` funkcija, kuri leidžia pasirinkti, ar rodyti vidurkį, ar medianą, ir gražiai suformatuoja lentelę.
*   **Į failą:** Naudojama `IsvestiIFaila()` funkcija. Ji išsaugo studentų sąrašą į tekstinį failą, taip pat leisdama pasirinkti vidurkio ar medianos stulpelį.

### Programos veikimo demonstracija (v1.2)

**1. Rankinis įvedimas ir operator<< veikimas:**
<img width="435" height="15" alt="image" src="https://github.com/user-attachments/assets/aa805a92-8268-4a27-84ed-31e431f2ef93" />

**2. Duomenų skaitymas iš failo (operator>>):**
<img width="152" height="27" alt="image" src="https://github.com/user-attachments/assets/4854f11b-26ab-4967-8f54-e96312dc0fdf" />

**3. Išvedimas į ekraną:**
<img width="424" height="84" alt="image" src="https://github.com/user-attachments/assets/f84ff191-5ce9-4785-bf36-32b45325cc7e" />

**4. Išvedimas į failą:**
<img width="206" height="158" alt="image" src="https://github.com/user-attachments/assets/526849e2-9a16-4e33-b447-cde6ead8ec68" />

## v1.5 – Paveldėjimas ir Abstrakčios klasės

Šioje versijoje programa buvo papildyta paveldėjimu (Inheritance) ir abstrakčiomis klasėmis.

### Kodo pakeitimai:
* **Bazinė (abstrakti) klasė `zmogus`:** Joje saugomi bendri žmogaus duomenys (`vardas_`, `pavarde_`) ir apibrėžta grynoji virtuali funkcija `virtual void spausdintiInfo() const = 0;`. Dėl šios funkcijos neįmanoma sukurti `zmogus` tipo objekto.
* **Išvestinė (derived) klasė `Studentas`:** Ji paveldi `zmogus` klasę (`class Studentas : public zmogus`), todėl gauna vardą ir pavardę. Studento klasėje liko tik studentui būdingi duomenys (pažymiai, egzaminas).
* **Išsaugota Rule of Three (ir Five):** Kadangi `Studentas` dabar turi bazinę klasę, visi jo konstruktoriai, priskyrimo operatoriai ir destruktorius iškviečia atitinkamus `zmogus` klasės metodus.
* **Polimorfizmas:** Realizuotas `spausdintiInfo()` metodas, kuris leidžia per bazinės klasės rodyklę pasiekti išvestinės klasės informaciją.

### Abstrakčios klasės ir polimorfizmo demonstracija:
<img width="362" height="85" alt="image" src="https://github.com/user-attachments/assets/499a58d6-09b5-47de-af53-491e39b83fbb" />

**Paaiškinimas:** Nuotraukoje matosi, kad programa atpažįsta, jog `zmogus` yra abstrakti klasė, todėl objekto sukurti negalima. Tačiau naudojant bazinės klasės rodyklę (`zmogus* zmogus1 = new Studentas(...)`), programa sėkmingai sukuria išvestinės klasės objektą ir iškviečia būtent `Studentas` klasės realizuotą `spausdintiInfo()` metodą. Tai įrodo, kad paveldėjimas ir polimorfizmas veikia tinkamai.






