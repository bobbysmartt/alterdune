#pragma once
#include <string>
using namespace std;

class Entite {
protected:
    string nom;
    int hp;
    int hpMax;

public:
    Entite(const string& nom, int hpMax);
    virtual ~Entite() = default; // virtuel pour que le bon destructeur soit appelé via un pointeur

 
    string getNom() const;
    int getHp() const;
    int getHpMax() const;

    void setHp(int h);
    bool estVivant() const;
    void subirDegats(int degats);
    void soigner(int soin);

    virtual void afficherStats() const = 0; // chaque entité affiche ses stats à sa façon
};
