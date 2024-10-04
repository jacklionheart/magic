#pragma once 

#include <vector>
#include <map>
#include <memory>
#include "rules/zones/zone.h"
#include "rules/zones/battlefield/permanent.h"

// Forward declarations
class Player;
class Mana;
class ManaCost;
class Game;

class Battlefield : public Zone {
public:
    std::map<int, std::vector<std::unique_ptr<Permanent>>> permanents;
    
    Battlefield(Game& game);

    virtual void add(Card& card) override;
    virtual void remove(Card& card) override;

    void enter(Card& card);

    Mana producableMana(Player& player) const;
    void produceMana(const ManaCost& mana_cost, Player& player);
};