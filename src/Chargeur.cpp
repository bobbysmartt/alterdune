#include "Chargeur.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

string Chargeur::trim(const string& s) {
    size_t debut = s.find_first_not_of(" \t\r\n");
    if (debut == string::npos) return "";
    size_t fin = s.find_last_not_of(" \t\r\n");
    return s.substr(debut, fin - debut + 1);
}

vector<string> Chargeur::split(const string& ligne, char sep) {
    vector<string> tokens;
    stringstream ss(ligne);
    string token;
    while (getline(ss, token, sep)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

vector<Item> Chargeur::chargerItems(const string& chemin) {
    ifstream fichier(chemin);
    if (!fichier.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier '" << chemin << "'.\n";
        exit(1);
    }

    vector<Item> items;
    string ligne;
    int numLigne = 0;

    getline(fichier, ligne);

    while (getline(fichier, ligne)) {
        numLigne++;
        ligne = trim(ligne);
        if (ligne.empty() || ligne[0] == '#') continue;

        auto tokens = split(ligne, ';');
        if (tokens.size() < 4) {
            cerr << "Attention : ligne " << numLigne
                      << " mal formee dans items.csv, ignoree.\n";
            continue;
        }

        try {
            string nom = tokens[0];
            string type = tokens[1];
            int valeur    = stoi(tokens[2]);
            int quantite  = stoi(tokens[3]);
            items.emplace_back(nom, type, valeur, quantite);
        } catch (...) {
            cerr << "Attention : ligne " << numLigne
                      << " contient des valeurs invalides, ignoree.\n";
        }
    }

    return items;
}

vector<Monstre> Chargeur::chargerMonstres(const string& chemin, const Catalogue& catalogue) {
    ifstream fichier(chemin);
    if (!fichier.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier '" << chemin << "'.\n";
        exit(1);
    }

    vector<Monstre> monstres;
    string ligne;
    int numLigne = 0;

    getline(fichier, ligne);

    while (getline(fichier, ligne)) {
        numLigne++;
        ligne = trim(ligne);
        if (ligne.empty() || ligne[0] == '#') continue;

        auto tokens = split(ligne, ';');
        if (tokens.size() < 10) {
            cerr << "Attention : ligne " << numLigne
                      << " mal formee dans monsters.csv, ignoree.\n";
            continue;
        }

        try {
            string catStr = tokens[0];
            string nom    = tokens[1];
            int hp         = stoi(tokens[2]);
            int atk        = stoi(tokens[3]);
            int def        = stoi(tokens[4]);
            int mercyGoal  = stoi(tokens[5]);

            Categorie cat;
            if      (catStr == "NORMAL")  cat = Categorie::NORMAL;
            else if (catStr == "MINIBOSS") cat = Categorie::MINIBOSS;
            else if (catStr == "BOSS")    cat = Categorie::BOSS;
            else {
                cerr << "Attention : categorie inconnue ligne " << numLigne << ", ignoree.\n";
                continue;
            }

            vector<string> acts;
            for (int i = 6; i <= 9; i++) {
                if (tokens[i] != "-" && catalogue.exists(tokens[i])) {
                    acts.push_back(tokens[i]);
                }
            }

            if (acts.empty()) {
                cerr << "Attention : monstre ligne " << numLigne
                          << " n'a aucune action valide, ignore.\n";
                continue;
            }

            monstres.emplace_back(nom, cat, hp, atk, def, mercyGoal, acts);
        } catch (...) {
            cerr << "Attention : ligne " << numLigne
                      << " contient des valeurs invalides, ignoree.\n";
        }
    }

    return monstres;
}
