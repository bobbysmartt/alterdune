#include "Bestiaire.h"
#include <iostream>
using namespace std;

void Bestiaire::ajouter(const Monstre& m, bool tue) {
    entrees.push_back({m, tue});
}

void Bestiaire::afficher() const {
    cout << "\n=== Bestiaire ===\n";
    if (entrees.empty()) {
        cout << "  Aucun monstre vaincu pour l'instant.\n";
        return;
    }
    for (size_t i = 0; i < entrees.size(); i++) {
        const auto& e = entrees[i];
        cout << "\n  [" << i + 1 << "] " << e.monstre.getNom()
                  << " (" << e.monstre.categorieToString() << ")\n";
        cout << "      HP max : " << e.monstre.getHpMax()
                  << "  ATK : " << e.monstre.getAtk()
                  << "  DEF : " << e.monstre.getDef() << "\n";
        cout << "      Resultat : " << (e.tue ? "Tue" : "Epargne") << "\n";
    }
}

bool Bestiaire::estVide() const { return entrees.empty(); }
