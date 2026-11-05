#include "Jeu.h"
#include "Chargeur.h"
#include "Combat.h"
#include <iostream>
#include <random>
#include <limits>
#include <algorithm>
using namespace std;

static mt19937 rngJeu(random_device{}());

Jeu::Jeu() : joueur(nullptr) {}

Jeu::~Jeu() {
    delete joueur;
}

Monstre& Jeu::choisirMonstre() {
    uniform_int_distribution<int> dist(0, (int)monstresDisponibles.size() - 1);
    return monstresDisponibles[dist(rngJeu)];
}

void Jeu::afficherBestiaire() {
    bestiaire.afficher();
}

void Jeu::afficherStats() {
    joueur->afficherStats();
}

void Jeu::menuItems() {
    joueur->afficherInventaire();
    cout << "\n  Utiliser un item ? (numero ou 0 pour annuler) : ";
    int choix;
    cin >> choix;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (choix != 0) {
        joueur->utiliserItem(choix - 1);
    }
}

void Jeu::lancerCombat() {
    Monstre copie = choisirMonstre();

    Combat combat(*joueur, copie, catalogue);
    ResultatCombat res = combat.lancer();

    if (res == ResultatCombat::VICTOIRE_TUE) {
        cout << "\n  Victoire ! " << copie.getNom() << " a ete elimine.\n";
        joueur->ajouterVictoire(true);
        bestiaire.ajouter(copie, true);
    } else if (res == ResultatCombat::VICTOIRE_EPARGNE) {
        cout << "\n  Victoire ! " << copie.getNom() << " a ete epargne.\n";
        joueur->ajouterVictoire(false);
        bestiaire.ajouter(copie, false);
    } else {
        cout << "\n  Defaite... Votre aventure se termine ici.\n";
        cout << "  GAME OVER\n";
        exit(0);
    }

    cout << "  Victoires : " << joueur->getNbVictoires() << "/10\n";
}

void Jeu::afficherFin() {
    cout << "\n\n========================================\n";
    cout << "         FIN DE L'AVENTURE\n";
    cout << "========================================\n";

    int tues     = joueur->getNbTues();
    int epargnes = joueur->getNbEpargnes();

    if (tues == 0) {
        cout << "\n  *** FIN PACIFISTE ***\n";
        cout << "  Vous avez epargne tous vos adversaires.\n";
        cout << "  La paix regne dans ALTERDUNE. Pour l'instant.\n";
    } else if (epargnes == 0) {
        cout << "\n  *** FIN GENOCIDAIRE ***\n";
        cout << "  Aucun survivant. Aucune pitie.\n";
        cout << "  ALTERDUNE tremble encore a votre souvenir.\n";
    } else {
        cout << "\n  *** FIN NEUTRE ***\n";
        cout << "  " << tues << " elimines, " << epargnes << " epargnes.\n";
        cout << "  Vous n'etes ni monstre ni saint. Juste... humain.\n";
    }

    cout << "\n  Merci d'avoir joue a ALTERDUNE.\n";
    cout << "========================================\n\n";
}

void Jeu::menuPrincipal() {
    while (true) {
        if (joueur->getNbVictoires() >= 10) {
            afficherFin();
            return;
        }

        cout << "\n========================================\n";
        cout << "              ALTERDUNE\n";
        cout << "========================================\n";
        cout << "  Joueur : " << joueur->getNom()
                  << "  |  HP : " << joueur->getHp() << "/" << joueur->getHpMax()
                  << "  |  Victoires : " << joueur->getNbVictoires() << "/10\n";
        cout << "----------------------------------------\n";
        cout << "  [1] Bestiaire\n";
        cout << "  [2] Demarrer un combat\n";
        cout << "  [3] Statistiques\n";
        cout << "  [4] Items\n";
        cout << "  [5] Quitter\n";
        cout << "----------------------------------------\n";
        cout << "  Choix : ";

        string input;
        getline(cin, input);

        if      (input == "1") afficherBestiaire();
        else if (input == "2") lancerCombat();
        else if (input == "3") afficherStats();
        else if (input == "4") menuItems();
        else if (input == "5") {
            cout << "  A bientot dans ALTERDUNE.\n";
            return;
        } else {
            cout << "  Option invalide.\n";
        }
    }
}

void Jeu::demarrer() {
    cout << "========================================\n";
    cout << "         Bienvenue dans ALTERDUNE\n";
    cout << "========================================\n";
    cout << "  Entrez le nom de votre personnage : ";

    string nom;
    getline(cin, nom);
    if (nom.empty()) nom = "Voyageur";

    joueur = new Joueur(nom, 100);

    cout << "\n  Chargement des donnees...\n";

    auto items    = Chargeur::chargerItems("data/items.csv");
    monstresDisponibles = Chargeur::chargerMonstres("data/monsters.csv", catalogue);

    for (auto& item : items)
        joueur->ajouterItem(item);

    cout << "\n  === Debut de partie ===\n";
    cout << "  Nom    : " << joueur->getNom() << "\n";
    cout << "  HP     : " << joueur->getHp() << "/" << joueur->getHpMax() << "\n";
    cout << "  Items  :\n";
    joueur->afficherInventaire();
    cout << "\n  " << monstresDisponibles.size() << " monstres charges.\n";

    cout << "\n  Appuyez sur Entree pour commencer...\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    menuPrincipal();
}
