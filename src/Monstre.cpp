#include "Monstre.h"
#include <iostream>
#include <algorithm>
using namespace std;

Monstre::Monstre(const string& nom, Categorie cat, int hp, int atk, int def,
                 int mercyGoal, const vector<string>& acts)
    : Entite(nom, hp), categorie(cat), atk(atk), def(def),
      mercy(0), mercyGoal(mercyGoal), actIds(acts) {}

Categorie Monstre::getCategorie() const { return categorie; }
int Monstre::getAtk() const { return atk; }
int Monstre::getDef() const { return def; }
int Monstre::getMercy() const { return mercy; }
int Monstre::getMercyGoal() const { return mercyGoal; }
const vector<string>& Monstre::getActIds() const { return actIds; }

void Monstre::modifierMercy(int delta) {
    mercy = max(0, min(mercyGoal, mercy + delta));
}

bool Monstre::mercyAtteint() const { return mercy >= mercyGoal; }

string Monstre::categorieToString() const {
    switch (categorie) {
        case Categorie::NORMAL:  return "NORMAL";
        case Categorie::MINIBOSS: return "MINIBOSS";
        case Categorie::BOSS:    return "BOSS";
    }
    return "?";
}

int Monstre::nbActionsDisponibles() const {
    switch (categorie) {
        case Categorie::NORMAL:  return 2;
        case Categorie::MINIBOSS: return 3;
        case Categorie::BOSS:    return 4;
    }
    return 2;
}

void Monstre::afficherStats() const {
    cout << "  Nom      : " << nom << "\n";
    cout << "  Categorie: " << categorieToString() << "\n";
    cout << "  HP       : " << hp << "/" << hpMax << "\n";
    cout << "  ATK      : " << atk << "\n";
    cout << "  DEF      : " << def << "\n";
    cout << "  Mercy    : " << mercy << "/" << mercyGoal << "\n";
}
