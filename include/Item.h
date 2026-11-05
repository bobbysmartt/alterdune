#pragma once
#include <string>
using namespace std;

// Un item de l'inventaire, pour l'instant seul le type "HEAL" est géré
class Item {
private:
    string nom;
    string type;
    int valeur; // quantité de HP restaurés si HEAL
    int quantite;  // stock disponible

public:
    Item(const string& nom, const string& type, int valeur, int quantite);

    string getNom() const;
    string getType() const;
    int getValeur() const;
    int getQuantite() const;

    void setQuantite(int q);
    bool utiliser(); // décrémente la quantité, retourne false si stock vide

    void afficher() const;
};
