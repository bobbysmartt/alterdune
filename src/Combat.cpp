#include "Combat.h"
#include <iostream>
#include <random>
#include <limits>
using namespace std;

static mt19937 rng(random_device{}());

Combat::Combat(Joueur& j, Monstre& m, const Catalogue& cat)
    : joueur(j), monstre(m), catalogue(cat) {}

int Combat::tirerDegats(int hpMax) {
    uniform_int_distribution<int> dist(0, hpMax);
    return dist(rng);
}

void Combat::tourMonstre() {
    int degats = tirerDegats(joueur.getHpMax());
    if (degats == 0) {
        cout << "  " << monstre.getNom() << " attaque mais rate completement !\n";
    } else {
        joueur.subirDegats(degats);
        cout << "  " << monstre.getNom() << " vous inflige " << degats
                  << " degats ! (HP: " << joueur.getHp() << "/" << joueur.getHpMax() << ")\n";
    }
}

ResultatCombat Combat::actionFight() {
    int degats = tirerDegats(monstre.getHpMax());
    if (degats == 0) {
        cout << "  Vous attaquez mais ratez completement !\n";
    } else {
        monstre.subirDegats(degats);
        cout << "  Vous infligez " << degats << " degats a " << monstre.getNom()
                  << " ! (HP: " << monstre.getHp() << "/" << monstre.getHpMax() << ")\n";
    }

    if (!monstre.estVivant()) {
        cout << "  " << monstre.getNom() << " est vaincu !\n";
        return ResultatCombat::VICTOIRE_TUE;
    }
    return ResultatCombat::DEFAITE;
}

ResultatCombat Combat::actionAct() {
    const auto& ids = monstre.getActIds();
    int nbDispo = monstre.nbActionsDisponibles();

    cout << "\n  Actions disponibles :\n";
    for (int i = 0; i < nbDispo && i < (int)ids.size(); i++) {
        cout << "    [" << i + 1 << "] " << ids[i] << "\n";
    }
    cout << "    [0] Retour\n";
    cout << "  Choix : ";

    int choix;
    cin >> choix;
    if (cin.fail() || choix == 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return ResultatCombat::DEFAITE;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choix < 1 || choix > nbDispo || choix > (int)ids.size()) {
        cout << "  Choix invalide.\n";
        return ResultatCombat::DEFAITE;
    }

    const ActAction& act = catalogue.get(ids[choix - 1]);
    cout << "\n  >> " << act.texte << "\n";
    monstre.modifierMercy(act.impactMercy);

    if (act.impactMercy > 0)
        cout << "  Mercy augmente ! (" << monstre.getMercy() << "/" << monstre.getMercyGoal() << ")\n";
    else if (act.impactMercy < 0)
        cout << "  Mercy diminue... (" << monstre.getMercy() << "/" << monstre.getMercyGoal() << ")\n";
    else
        cout << "  Mercy inchange. (" << monstre.getMercy() << "/" << monstre.getMercyGoal() << ")\n";

    return ResultatCombat::DEFAITE;
}

ResultatCombat Combat::actionItem() {
    joueur.afficherInventaire();

    bool aDesItems = false;
    for (const auto& it : joueur.getInventaire()) {
        if (it.getQuantite() > 0) { aDesItems = true; break; }
    }
    if (!aDesItems) {
        cout << "  Votre inventaire est vide.\n";
        return ResultatCombat::DEFAITE;
    }

    cout << "  Quel item utiliser ? (0 pour annuler) : ";
    int choix;
    cin >> choix;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choix == 0) return ResultatCombat::DEFAITE;

    joueur.utiliserItem(choix - 1);
    return ResultatCombat::DEFAITE;
}

ResultatCombat Combat::actionMercy() {
    if (!monstre.mercyAtteint()) {
        cout << "  " << monstre.getNom() << " n'est pas encore pret a etre epargne.\n";
        cout << "  Mercy : " << monstre.getMercy() << "/" << monstre.getMercyGoal() << "\n";
        return ResultatCombat::DEFAITE;
    }
    cout << "  Vous epargnez " << monstre.getNom() << ". Il s'en va doucement.\n";
    return ResultatCombat::VICTOIRE_EPARGNE;
}

ResultatCombat Combat::lancer() {
    cout << "\n========================================\n";
    cout << "  COMBAT : " << joueur.getNom() << " vs " << monstre.getNom()
              << " [" << monstre.categorieToString() << "]\n";
    cout << "========================================\n";

    while (joueur.estVivant() && monstre.estVivant()) {
        cout << "\n--- Tour ---\n";
        cout << "  " << joueur.getNom() << " : " << joueur.getHp()
                  << "/" << joueur.getHpMax() << " HP\n";
        cout << "  " << monstre.getNom() << " : " << monstre.getHp()
                  << "/" << monstre.getHpMax() << " HP";
        if (monstre.mercyAtteint())
            cout << "  [MERCY DISPONIBLE]";
        cout << "\n";

        cout << "\n  FIGHT    ACT    ITEM    MERCY\n";
        cout << "  Choix : ";

        string input;
        getline(cin, input);

        ResultatCombat res = ResultatCombat::DEFAITE;
        bool actionValide  = true;

        if      (input == "FIGHT" || input == "1") res = actionFight();
        else if (input == "ACT"   || input == "2") res = actionAct();
        else if (input == "ITEM"  || input == "3") res = actionItem();
        else if (input == "MERCY" || input == "4") res = actionMercy();
        else {
            cout << "  Commande inconnue. (FIGHT / ACT / ITEM / MERCY)\n";
            actionValide = false;
        }

        if (!actionValide) continue;

        if (res == ResultatCombat::VICTOIRE_TUE || res == ResultatCombat::VICTOIRE_EPARGNE)
            return res;

        if (!joueur.estVivant()) break;

        tourMonstre();

        if (!joueur.estVivant()) {
            cout << "\n  Vous etes tombe au combat...\n";
            return ResultatCombat::DEFAITE;
        }
    }

    return ResultatCombat::DEFAITE;
}
