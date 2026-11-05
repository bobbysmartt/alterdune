#pragma once
#include <string>
using namespace std;

// Représente une action ACT : son identifiant, le texte affiché, et son effet sur la jauge Mercy
struct ActAction {
    string id;
    string texte;
    int impactMercy; // positif = augmente Mercy, négatif = la baisse
};
