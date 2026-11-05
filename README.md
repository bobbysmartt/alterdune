# ALTERDUNE

A turn-based console RPG written in C++17, inspired by *Undertale*. Every fight can be won two ways: defeat the monster, or calm it down until it accepts mercy. The choices you make across ten victories decide which ending you get.

## Gameplay

- Create a character, then pick fights from the main menu: **Bestiary**, **Start a fight**, **Stats**, **Items**, **Quit**.
- In combat, each turn offers four commands:
  - **FIGHT**: attack the monster for a random amount of damage (a roll of 0 is a miss). The monster then strikes back the same way.
  - **ACT**: interact with it (compliment, joke, dance...). Each monster has its own set of available actions, and each action raises or lowers its *mercy* gauge.
  - **ITEM**: heal with an item from your inventory.
  - **MERCY**: spare the monster once its mercy gauge is full.
- Monsters come in three tiers (normal, mini-boss, boss). Every monster you beat or spare is recorded in the bestiary.
- After ten victories, the game ends with one of three endings:
  - **Pacifist**: you spared everyone.
  - **Genocide**: you spared no one.
  - **Neutral**: anything in between.

The in-game text is in French.

## Design

The project was built to apply core object-oriented principles:

- **Inheritance and polymorphism**: `Joueur` (player) and `Monstre` derive from an abstract `Entite` base class, which declares a pure virtual `afficherStats()` and a virtual destructor.
- **Encapsulation**: game state lives behind each class's interface (HP, mercy gauge, inventory, victory counters).
- **Composition**: `Jeu` owns the player, the item catalogue and the bestiary. `Combat` works on references to the player, one monster and the catalogue.
- **Data-driven content**: monsters and items are loaded at startup from `data/monsters.csv` and `data/items.csv` by the `Chargeur` class. Malformed lines (missing fields, invalid numbers, unknown monster category) are reported and skipped instead of crashing the game.

The class diagram is in [`docs/UML_ALTERDUNE.pdf`](docs/UML_ALTERDUNE.pdf) (PlantUML source: [`docs/UML_ALTERDUNE.puml`](docs/UML_ALTERDUNE.puml)).

```
include/   headers (Entite, Joueur, Monstre, Combat, Jeu, Item, Catalogue, Bestiaire, Chargeur, ActAction)
src/       implementations and main.cpp
data/      monsters.csv, items.csv
docs/      UML class diagram
```

## Build and run

Requires a C++17 compiler (g++ or clang++) and `make`.

```bash
make
./alterdune
```

Run it from the repository root so the game can find `data/`. `make clean` removes the build files.

## Context

Solo project for the C++ object-oriented programming course at ESILV (2026).
