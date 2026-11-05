#pragma once
#include "Joueur.h"
#include "Monstre.h"
#include "Catalogue.h"
using namespace std;

// Les trois issues possibles d'un combat
enum class ResultatCombat { VICTOIRE_TUE, VICTOIRE_EPARGNE, DEFAITE };

class Combat {
private:
    Joueur& joueur;  // références, on travaille sur les vrais objets, pas des copies
    Monstre& monstre;
    const Catalogue& catalogue;

    // Méthodes internes, une par action possible du joueur
    int tirerDegats(int hpMax);
    void tourMonstre();
    ResultatCombat actionFight();
    ResultatCombat actionAct();
    ResultatCombat actionItem();
    ResultatCombat actionMercy();

public:
    Combat(Joueur& j, Monstre& m, const Catalogue& cat);
    ResultatCombat lancer(); // point d'entrée du combat, lance la boucle principale
};
