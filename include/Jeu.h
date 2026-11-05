#pragma once
#include "Joueur.h"
#include "Monstre.h"
#include "Catalogue.h"
#include "Bestiaire.h"
#include <vector>
using namespace std;

// Chef d'orchestre du jeu, gère le menu, les combats et la progression
class Jeu {
private:
    Joueur* joueur; // pointeur car créé avec new après saisie du nom
    vector<Monstre> monstresDisponibles; // tous les monstres chargés depuis le CSV
    Catalogue catalogue;
    Bestiaire bestiaire;

    // Méthodes internes — appelées uniquement depuis menuPrincipal()
    void menuPrincipal();
    void lancerCombat();
    void afficherBestiaire();
    void afficherStats();
    void menuItems();
    void afficherFin();

    Monstre& choisirMonstre(); // choisit un monstre aléatoire dans monstresDisponibles


public:
    Jeu();
    ~Jeu(); // libère le joueur alloué avec new
    void demarrer(); // point d'entrée — initialise et lance la partie
};
