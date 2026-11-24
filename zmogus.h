#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>
#include <iostream>

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    Zmogus() : vardas_(""), pavarde_("") {}
    
    Zmogus(const std::string& v, const std::string& p) : vardas_(v), pavarde_(p) {}
    
    virtual ~Zmogus() {}

    virtual void spausdintiInfo() const = 0; 

    std::string vardas() const { return vardas_; }
    std::string pavarde() const { return pavarde_; }
};

#endif
