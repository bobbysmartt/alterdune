#pragma once
#include "Item.h"
#include "Monstre.h"
#include "Catalogue.h"
#include <vector>
#include <string>
using namespace std;

class Chargeur {
public:
    static vector<Item> chargerItems(const string& chemin);
    static vector<Monstre> chargerMonstres(const string& chemin, const Catalogue& catalogue);

private:
    static vector<string> split(const string& ligne, char sep);
    static string trim(const string& s);
};
