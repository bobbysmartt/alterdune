#pragma once
#include "Entite.h"
#include "ActAction.h"
#include <vector>
#include <string>
using namespace std;

// Les trois types de monstres — détermine le nombre d'actions ACT et la difficulté
enum class Categorie { NORMAL, MINIBOSS, BOSS };

// Hérite de Entite, ajoute le système de combat et la jauge Mercy
class Monstre : public Entite {
protected:
    Categorie categorie;
    int atk;
    int def;
    int mercy; // jauge actuelle
    int mercyGoal;  // seuil à atteindre pour pouvoir épargner le monstre
    vector<string> actIds; // identifiants des actions ACT disponibles pour ce monstre

public:
    Monstre(const string& nom, Categorie cat, int hp, int atk, int def,
            int mercyGoal, const vector<string>& acts);

    Categorie getCategorie() const;
    int getAtk() const;
    int getDef() const;
    int getMercy() const;
    int getMercyGoal() const;
    const vector<string>& getActIds() const;

    void modifierMercy(int delta); // delta peut être négatif (certaines actions baissent la jauge)
    bool mercyAtteint() const; // true si mercy >= mercyGoal

    string categorieToString() const; // convertit l'enum en string lisible pour l'affichage
    void afficherStats() const override; // redéfinit la version abstraite de Entite


    int nbActionsDisponibles() const; // NORMAL=2, MINIBOSS=3, BOSS=4
};