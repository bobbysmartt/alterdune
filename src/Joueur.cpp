#include "Joueur.h"
#include <iostream>
using namespace std;

Joueur::Joueur(const string& nom, int hpMax)
    : Entite(nom, hpMax), nbTues(0), nbEpargnes(0), nbVictoires(0) {}

int Joueur::getNbTues() const { return nbTues; }
int Joueur::getNbEpargnes() const { return nbEpargnes; }
int Joueur::getNbVictoires() const { return nbVictoires; }

void Joueur::ajouterVictoire(bool tue) {
    nbVictoires++;
    if (tue) nbTues++;
    else     nbEpargnes++;
}

void Joueur::ajouterItem(const Item& item) {
    inventaire.push_back(item);
}

vector<Item>& Joueur::getInventaire() { return inventaire; }
const vector<Item>& Joueur::getInventaire() const { return inventaire; }

void Joueur::afficherStats() const {
    cout << "\n=== Statistiques ===\n";
    cout << "  Nom       : " << nom << "\n";
    cout << "  HP        : " << hp << "/" << hpMax << "\n";
    cout << "  Victoires : " << nbVictoires << "/10\n";
    cout << "  Tues      : " << nbTues << "\n";
    cout << "  Epargnes  : " << nbEpargnes << "\n";
}

void Joueur::afficherInventaire() const {
    cout << "\n=== Inventaire ===\n";
    if (inventaire.empty()) {
        cout << "  (vide)\n";
        return;
    }
    for (size_t i = 0; i < inventaire.size(); i++) {
        cout << "  [" << i + 1 << "] ";
        inventaire[i].afficher();
    }
}

bool Joueur::utiliserItem(int index) {
    if (index < 0 || index >= (int)inventaire.size()) return false;
    Item& it = inventaire[index];
    if (it.getQuantite() <= 0) {
        cout << "  Plus de " << it.getNom() << " disponible.\n";
        return false;
    }
    if (it.getType() == "HEAL") {
        int avant = hp;
        soigner(it.getValeur());
        it.utiliser();
        cout << "  Vous utilisez " << it.getNom() << " et recuperez "
                  << (hp - avant) << " HP. (HP: " << hp << "/" << hpMax << ")\n";
        return true;
    }
    return false;
}
