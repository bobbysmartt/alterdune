#pragma once
#include "Monstre.h"
#include <vector>
#include <string>
using namespace std;


// Représente une entrée dans le bestiaire : le monstre rencontré et ce qu'on en a fait
struct EntreeBestiaire {
    Monstre monstre;
    bool tue; 
};

// Historique de tous les monstres rencontrés pendant la partie
class Bestiaire {
private:
    vector<EntreeBestiaire> entrees;

public:
    void ajouter(const Monstre& m, bool tue);
    void afficher() const;
    bool estVide() const;
};
