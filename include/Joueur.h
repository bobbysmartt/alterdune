#pragma once
#include "Entite.h"
#include "Item.h"
#include <vector>
using namespace std;

// Hérite de Entite, ajoute l'inventaire et le suivi des victoires
class Joueur : public Entite {
private:
    int nbTues;
    int nbEpargnes;
    int nbVictoires;
    vector<Item> inventaire;

public:
    Joueur(const string& nom, int hpMax);

    int getNbTues() const;
    int getNbEpargnes() const;
    int getNbVictoires() const;

    void ajouterVictoire(bool tue); // true = tué, false = épargné
    void ajouterItem(const Item& item);

    vector<Item>& getInventaire(); // version modifiable
    const vector<Item>& getInventaire() const; // version lecture seule

    void afficherStats() const override;
    void afficherInventaire() const;
    bool utiliserItem(int index);
};
