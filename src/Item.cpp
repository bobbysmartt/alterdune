#include "Item.h"
#include <iostream>
using namespace std;

Item::Item(const string& nom, const string& type, int valeur, int quantite)
    : nom(nom), type(type), valeur(valeur), quantite(quantite) {}

string Item::getNom() const { return nom; }
string Item::getType() const { return type; }
int Item::getValeur() const { return valeur; }
int Item::getQuantite() const { return quantite; }

void Item::setQuantite(int q) { quantite = q; }

bool Item::utiliser() {
    if (quantite <= 0) return false;
    quantite--;
    return true;
}

void Item::afficher() const {
    cout << "  - " << nom << " (x" << quantite << ") : soigne " << valeur << " HP\n";
}
