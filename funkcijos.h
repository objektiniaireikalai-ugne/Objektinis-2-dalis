#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "studentas.h"
#include <vector>
#include <list>
#include <string>

double vidurkis(std::vector<int> paz);
double mediana(std::vector<int> paz);

bool RusiuotiPagalVarda(const Studentas& a, const Studentas& b);
bool RusiuotiPagalPavarde(const Studentas& a, const Studentas& b);
bool RusiuotiPagalBala(const Studentas& a, const Studentas& b);

int GeneruotiPazymi();
Studentas GeneruotiStudenta(int numeris);
void GeneruotiStudentus(std::vector<Studentas>& grupe, int kiek);
void GeneruotiFaila(const std::string& failas, int kiek);

bool nuskaitymas(std::vector<Studentas>& grupe, const std::string& failas);
bool nuskaitymas(std::list<Studentas>& grupe, const std::string& failas);

void kategorijos(std::vector<Studentas>& grupe, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietiakiai);
void kategorijos(const std::list<Studentas>& grupe, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietiakiai);

void IsvestiIFaila(const std::string& failas, const std::vector<Studentas>& grupe, bool rodytiVid);
void IsvestiIFaila(const std::string& failas, const std::list<Studentas>& grupe, bool rodytiVid);

void output(const std::vector<Studentas>& grupe, int limit, bool rodytiVid, bool rodytiMed);

void split_1_vector(std::vector<Studentas>& grupe, std::vector<Studentas>& v, std::vector<Studentas>& k);
void split_1_list(std::list<Studentas>& grupe, std::list<Studentas>& v, std::list<Studentas>& k);

void split_2_vector(std::vector<Studentas>& grupe, std::vector<Studentas>& v);
void split_2_list(std::list<Studentas>& grupe, std::list<Studentas>& v);

void split_3_vector(std::vector<Studentas>& grupe, std::vector<Studentas>& v);
void split_3_list(std::list<Studentas>& grupe, std::list<Studentas>& v);

#endif
