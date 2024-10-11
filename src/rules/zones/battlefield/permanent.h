// permanent.h
#pragma once

#include <memory>
#include <vector>
#include "rules/engine/mana.h"
#include "rules/cards/card.h"


// Forward Declarations
class Mana;
class Player;
class Game;
class ManaAbility;
class ActivatedAbility;

class Permanent {
public:
    int id;
    static int next_id;

    // TODO: make an ID
    Card& card;
    bool tapped = false;
    bool summoning_sick = false;
    int damage = 0;
    int controller_id;
    
    Permanent(Card& card);

    bool canTap() const;
    void untap();
    void tap();
    void receiveDamage(int damage);
    bool hasLethalDamage() const;
    void clearDamage();
    Mana producableMana(Game& game) const;
    void activateAllManaAbilities(Game& game);
    void activateAbility(ActivatedAbility* ability, Game& game);

    bool operator==(const Permanent& other) const;
};
