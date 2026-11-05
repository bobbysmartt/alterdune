#pragma once
#include "ActAction.h"
#include <map>
#include <string>
using namespace std;

// Dictionnaire de toutes les actions ACT du jeu — clé = identifiant (ex: "JOKE")
class Catalogue {
private:
    map<string, ActAction> actions; // ex: "JOKE" → {id, texte, impactMercy}

public:
    Catalogue();
    bool exists(const string& id) const; // vérifie qu'une action existe avant de la récupérer
    const ActAction& get(const string& id) const;
};
