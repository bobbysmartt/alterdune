#include "Catalogue.h"
using namespace std;

Catalogue::Catalogue() {
    actions["COMPLIMENT"] = {"COMPLIMENT", "Vous le complimentez sur sa coiffure. Il rougit visiblement.", 20};
    actions["DISCUSS"]    = {"DISCUSS",    "Vous entamez une conversation sur la météo. Passionnant.", 15};
    actions["JOKE"]       = {"JOKE",       "Vous racontez une blague nulle. Il rit quand meme, un peu.", 25};
    actions["INSULT"]     = {"INSULT",     "Vous l'insultez copieusement. Ce n'etait peut-etre pas une bonne idee.", -30};
    actions["DANCE"]      = {"DANCE",      "Vous dansez le moonwalk. L'ennemi est perplexe, mais touche.", 20};
    actions["MIMIC"]      = {"MIMIC",      "Vous le singez. Il ne sait pas si c'est flatteur ou non.", 10};
    actions["COMFORT"]    = {"COMFORT",    "Vous lui offrez un mouchoir imaginaire. Il renifle doucement.", 30};
    actions["OBSERVE"]    = {"OBSERVE",    "Vous l'observez en silence. Ca le met mal a l'aise.", 5};
    actions["PET"]        = {"PET",        "Vous tentez de le caresser. Contre toute attente, il accepte.", 35};
    actions["OFFER_SNACK"]= {"OFFER_SNACK","Vous lui tendez un snack. Il hesite, puis croque dedans.", 40};
    actions["REASON"]     = {"REASON",     "Vous tentez de raisonner avec lui. Il ecoute, l'air suspicieux.", 20};
    actions["SING"]       = {"SING",       "Vous chantez faux mais avec conviction. Il est desarme.", 25};
    actions["TAUNT"]      = {"TAUNT",      "Vous le narguez. Mauvaise idee. Tres mauvaise idee.", -20};
}
                                     
bool Catalogue::exists(const string& id) const {
    return actions.count(id) > 0;
}

const ActAction& Catalogue::get(const string& id) const {
    return actions.at(id);
}
