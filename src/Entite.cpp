#include "Entite.h"
#include <algorithm>
using namespace std;

Entite::Entite(const string& nom, int hpMax)
    : nom(nom), hp(hpMax), hpMax(hpMax) {}

string Entite::getNom() const { return nom; }
int Entite::getHp() const { return hp; }
int Entite::getHpMax() const { return hpMax; }

void Entite::setHp(int h) { hp = max(0, min(h, hpMax)); }

bool Entite::estVivant() const { return hp > 0; }

void Entite::subirDegats(int degats) {
    hp = max(0, hp - degats);
}

void Entite::soigner(int soin) {
    hp = min(hpMax, hp + soin);
}
